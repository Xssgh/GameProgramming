#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

#define W 10
#define H 20
#define ORGX 4
#define ORGY 1

typedef struct {
    int type;
    int rot;
    int x, y;
} Piece;

static int board[H][W];
static Piece cur;
static int score = 0, lines_cleared = 0, level = 1;
static int tick_ms = 500;
static int running = 1, paused = 0;

static const char *shapes[7][4] = {
    { "...."
      "####"
      "...."
      "....",

      "..#."
      "..#."
      "..#."
      "..#.",

      "...."
      "...."
      "####"
      "....",

      ".#.."
      ".#.."
      ".#.."
      ".#.." },

    { ".#.."
      ".#.."
      "##.."
      "....",

      "...."
      "#..."
      "###."
      "....",

      "##.."
      "#..."
      "#..."
      "....",

      "...."
      "###."
      "..#."
      "...." },

    { "#..."
      "#..."
      "##.."
      "....",

      "...."
      "..#."
      "###."
      "....",

      "##.."
      ".#.."
      ".#.."
      "....",

      "...."
      "###."
      "#..."
      "...." },

    { ".#.."
      "###."
      "...."
      "....",

      ".#.."
      ".##."
      ".#.."
      "....",

      "...."
      "###."
      ".#.."
      "....",

      ".#.."
      "##.."
      ".#.."
      "...." },

    { "##.."
      "##.."
      "...."
      "....",

      "##.."
      "##.."
      "...."
      "....",

      "##.."
      "##.."
      "...."
      "....",

      "##.."
      "##.."
      "...."
      "...." },

    { ".##."
      "##.."
      "...."
      "....",

      ".#.."
      ".##."
      "..#."
      "....",

      ".##."
      "##.."
      "...."
      "....",

      ".#.."
      ".##."
      "..#."
      "...." },

    { "##.."
      ".##."
      "...."
      "....",

      "..#."
      ".##."
      ".#.."
      "....",

      "##.."
      ".##."
      "...."
      "....",

      "..#."
      ".##."
      ".#.."
      "...." }
};

void hide_cursor(int hide) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ci;
    GetConsoleCursorInfo(h, &ci);
    ci.bVisible = hide ? FALSE : TRUE;
    SetConsoleCursorInfo(h, &ci);
}

void gotoxy(int x, int y) {
    COORD c; c.X = (SHORT)x; c.Y = (SHORT)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void clear_screen() {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count, cellCount;
    COORD home = {0,0};
    GetConsoleScreenBufferInfo(h, &csbi);
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;
    FillConsoleOutputCharacter(h, ' ', cellCount, home, &count);
    FillConsoleOutputAttribute(h, csbi.wAttributes, cellCount, home, &count);
    SetConsoleCursorPosition(h, home);
}

int cell(const Piece *p, int r, int c) {
    const char *s = shapes[p->type][p->rot];
    return s[r*4 + c] == '#';
}

int can_place(const Piece *p, int nx, int ny, int nrot) {
    Piece t = *p; t.x = nx; t.y = ny; t.rot = nrot;
    for (int r=0;r<4;r++) for (int c=0;c<4;c++) {
        if (!cell(&t,r,c)) continue;
        int bx = nx + c, by = ny + r;
        if (bx < 0 || bx >= W || by >= H) return 0;
        if (by >= 0 && board[by][bx]) return 0;
    }
    return 1;
}

void merge_piece(const Piece *p, int val) {
    for (int r=0;r<4;r++) for (int c=0;c<4;c++) {
        if (!cell(p,r,c)) continue;
        int bx = p->x + c, by = p->y + r;
        if (by>=0 && by<H && bx>=0 && bx<W) board[by][bx] = val;
    }
}

void draw_frame() {
    gotoxy(0,0);
    printf("+");
    for (int i=0;i<W*2;i++) printf("-");
    printf("+\n");
    for (int y=0;y<H;y++) {
        printf("|");
        for (int x=0;x<W;x++) {
            if (board[y][x]) printf("[]");
            else printf("  ");
        }
        printf("|\n");
    }
    printf("+");
    for (int i=0;i<W*2;i++) printf("-");
    printf("+\n");

    gotoxy(ORGX + W*2 + 4, ORGY + 0);
    printf("Score : %d", score);
    gotoxy(ORGX + W*2 + 4, ORGY + 1);
    printf("Lines : %d", lines_cleared);
    gotoxy(ORGX + W*2 + 4, ORGY + 2);
    printf("Level : %d", level);
    gotoxy(0, H + 3);
    printf("[←/→ Move] [↓ Soft Drop] [↑ Rotate] [Space Hard Drop] [P Pause] [Q Quit]");
}

void draw_piece(const Piece *p, int on) {
    for (int r=0;r<4;r++) for (int c=0;c<4;c++) {
        if (!cell(p,r,c)) continue;
        int bx = p->x + c, by = p->y + r;
        if (by<0 || by>=H || bx<0 || bx>=W) continue;
        gotoxy(1 + bx*2, 1 + by);
        if (on) printf("[]"); else printf("  ");
    }
}

int clear_lines() {
    int removed = 0;
    for (int y=H-1;y>=0;y--) {
        int full = 1;
        for (int x=0;x<W;x++) if (!board[y][x]) { full = 0; break; }
        if (full) {
            removed++;
            for (int yy=y; yy>0; yy--) {
                for (int x=0;x<W;x++) board[yy][x] = board[yy-1][x];
            }
            for (int x=0;x<W;x++) board[0][x] = 0;
            y++;
        }
    }
    if (removed) {
        lines_cleared += removed;
        int add = 0;
        if (removed==1) add = 100;
        else if (removed==2) add = 300;
        else if (removed==3) add = 500;
        else if (removed==4) add = 800;
        score += add * level;
        if (lines_cleared/10 + 1 > level) {
            level = lines_cleared/10 + 1;
            int nm = 500 - (level-1)*35;
            if (nm < 80) nm = 80;
            tick_ms = nm;
        }
    }
    return removed;
}

void spawn_piece() {
    cur.type = rand()%7;
    cur.rot = 0;
    cur.x = W/2 - 2;
    cur.y = -1;
}

void rotate_piece(int dir) {
    int nrot = (cur.rot + dir + 4) % 4;
    if (can_place(&cur, cur.x, cur.y, nrot)) { cur.rot = nrot; return; }
    if (can_place(&cur, cur.x-1, cur.y, nrot)) { cur.x-=1; cur.rot=nrot; return; }
    if (can_place(&cur, cur.x+1, cur.y, nrot)) { cur.x+=1; cur.rot=nrot; return; }
}

void hard_drop() {
    while (can_place(&cur, cur.x, cur.y+1, cur.rot)) cur.y++;
}

void input_step() {
    if (!_kbhit()) return;
    int ch = _getch();   // never echoes

    // Arrow key prefix (0 or 224)
    if (ch == 0 || ch == 224) {
        int k = _getch();  // second code
        if (k == 75) { // ←
            if (can_place(&cur, cur.x-1, cur.y, cur.rot)) cur.x--;
        } else if (k == 77) { // →
            if (can_place(&cur, cur.x+1, cur.y, cur.rot)) cur.x++;
        } else if (k == 80) { // ↓
            if (can_place(&cur, cur.x, cur.y+1, cur.rot)) cur.y++;
            else {
                merge_piece(&cur, 1);
                clear_lines();
                spawn_piece();
                if (!can_place(&cur, cur.x, cur.y, cur.rot)) running = 0;
            }
        } else if (k == 72) { // ↑
            rotate_piece(+1);
        }
        return; // handled, no echo
    }

    // Normal keys
    if (ch == 'q' || ch == 'Q') { running = 0; return; }
    if (ch == 'p' || ch == 'P') { paused = !paused; return; }
    if (ch == ' ') { hard_drop(); return; }
}

void game_over_screen() {
    gotoxy(0, H + 5);
    printf("Game Over!\n");
    printf("Score: %d   Lines: %d   Level: %d\n", score, lines_cleared, level);
    printf("Press any key to exit...\n");
    _getch();
}

int main() {
    srand((unsigned)time(NULL));
    clear_screen();
    hide_cursor(1);
    for (int y=0;y<H;y++) for (int x=0;x<W;x++) board[y][x]=0;
    spawn_piece();

    draw_frame();
    DWORD last = GetTickCount();
    while (running) {
        if (!paused) {
            draw_piece(&cur, 0);
            input_step();
            DWORD now = GetTickCount();
            if (now - last >= (DWORD)tick_ms) {
                last = now;
                if (can_place(&cur, cur.x, cur.y+1, cur.rot)) {
                    cur.y++;
                } else {
                    merge_piece(&cur, 1);
                    clear_lines();
                    spawn_piece();
                    if (!can_place(&cur, cur.x, cur.y, cur.rot)) break;
                }
            }
            draw_frame();
            draw_piece(&cur, 1);
        } else {
            gotoxy(0, H + 5);
            printf("[PAUSED] Press P to resume, Q to quit");
            Sleep(50);
            if (_kbhit()) input_step();
        }
        Sleep(10);
    }
    hide_cursor(0);
    game_over_screen();

    system("pause");
    return 0;
}
