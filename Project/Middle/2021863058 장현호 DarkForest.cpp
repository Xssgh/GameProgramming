#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>

// --- ANSI 색상 코드 정의 ---
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#define ANSI_RESET  "\x1b[0m"
#define ANSI_YELLOW "\x1b[93m"
#define ANSI_RED    "\x1b[91m"
#define ANSI_GREEN  "\x1b[92m"
#define ANSI_BROWN  "\x1b[38;5;94m"

// --- 블록 게임 상수 ---
#define box_length 10
#define box_height 20
#define GOAL_HEIGHT 10

// --- 전역 변수 선언 ---
int badChoices = 0;
int heardAboutBigBird = 0;
int heardAboutLongBird = 0;
int heardAboutSmallBird = 0;

// --- 함수 원형 선언 ---
void intro(void);
void startGame(void);
void pressAnyKey(void);
void slowPrint(const char* text, int delay);
void enterForest(void);
void fallDownHeadFirst(void);
void grabBranch(void);
void passOut(void);
void wakeUpScene(void);
void choiceMushroom(void);
void choiceSilent(void);
void deerTrust(void);
void askAboutBirds(void);
void explainBigBird(void);
void explainLongBird(void);
void explainSmallBird(void);
void chapterThree(void);
void chapterFour(void);
void chapterFive(void);
void chapterSix(void);
void endGame(void);
void enableANSI(void);
void printForestFrame1(void);
void printForestFrame2(void);
void animateLamp2s(void);
void animateScales(void);
int playBlockGame(void);
void gotoxy(int x, int y);
void playIntroMelody(void);
void playGameOverMelody(void);
void playFallSound(void);
void playApocalypseMelody(void);


void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int getChoice(int min, int max, void (*printOptions)(void))
{
    int choice = -1;
    while (1)
    {
        while (kbhit()) getch(); 
        int key = getch();

        // 엔터키나 특수키 무시
        if (key == 13 || key == 224)
            continue;

        // 숫자가 아닐 경우
        if (key < '0' || key > '9')
        {
            system("cls");
            slowPrint("주어진 번호중 선택하세요 .", 15);
            printf("\n\n");
            if (printOptions != NULL)
                printOptions(); // 선택지 다시 출력
            printf("\n  선택 > ");
            continue;
        }

        choice = key - '0';

        // 유효 범위 체크
        if (choice >= min && choice <= max)
            return choice;

        // 잘못된 숫자 입력 시 선택지 다시 출력
        system("cls");
        slowPrint("올바른 선택지를 입력하세요.", 15);
        printf("\n\n");
        if (printOptions != NULL)
            printOptions();
        printf("\n  선택 > ");
    }
}

// --- 공용 함수 ---
void slowPrint(const char* text, int delay)
{
    for (int i = 0; text[i] != '\0'; i++)
    {
        printf("%c", text[i]);
        fflush(stdout);
        Sleep(delay);
    }
    printf("\n");
}

void pressAnyKey(void)
{
    printf("\n\n(계속하려면 아무 키나 누르세요...)");
    while (kbhit()) getch();
    getch();
}


void intro(void)
{
    enableANSI();

    for (int i = 0; i < 10; ++i) {
        system("cls");
        if (i % 2 == 0) printForestFrame1();
        else            printForestFrame2();
        Sleep(300);
    }
    playIntroMelody();  
	slowPrint(ANSI_YELLOW "\n\n- DARK FOREST -" ANSI_RESET, 50);
    printf("\n");
    printf("\n");
    printf("// ⓒ Project Moon. Original concept inspired by Lobotomi Corporation / Library of Ruina universe.\n");
    printf("\n\n");
    pressAnyKey();
}

void printOptions_startGame(void)
{
    printf("  1. 숲으로 가본다.\n");
    printf("  2. 그냥  가던 길을 계속 간다.\n");
}

void startGame(void)
{
    system("cls");
    slowPrint("여행자이며 개척자이면서, 동시에  아무것도 아닌 존재인  당신은 어느날 따뜻하고 나무가 울창한 숲가를 지나가고 있었습니다.", 15);
    printf("\n");
    slowPrint("얼마 전에 들었던 숲에 대한 소문이 떠올랐습니다.", 15);
    printf("\n");
    slowPrint("\"최근 숲의 분위기가 이상해졌다고 하던데.. 동물들도 외부인을 필요 이상으로 경계하고 있다고 들었어.\"", 15);
    printf("\n");
    slowPrint("...", 100);
    printf("\n");
    slowPrint("무언가 마음에 걸린다. 숲에 직접 가보는게 나을지도 모르겠다.", 70);
    printf("\n");
    printOptions_startGame();
    printf("\n  선택 > ");
    int choice = getChoice(1, 2, printOptions_startGame);
    printf("%d\n", choice);
    Sleep(1000);
    if (choice == 1) enterForest();
    else {
        system("cls");
        slowPrint("결국 당신은 귀찮음을 이기지 못하고 가던 길을 계속 갔습니다.", 15);
        slowPrint("숲에 들어가는건 다음 기회에...", 15);
        slowPrint("\n- THE END -", 50);
        playGameOverMelody();
        Sleep(2000);
        exit(0);
    }
}

void printOptions_enterForest(void)
{
    printf("  1. 머리를 감싸서 보호한다.\n");
    printf("  2. 나뭇가지를 잡는다.\n");
}

void enterForest(void)
{
    system("cls");
    slowPrint("숲으로 발걸음을 옮겼습니다.", 15);
    slowPrint("...", 100);
    pressAnyKey();
    system("cls");
    slowPrint("당신은 숲의 입구에 도착했습니다. 숲은 따뜻한 분위기와 동시에 알 수 없는 서늘함이 느껴집니다.", 15);
    printf("\n");
    slowPrint("입구에서 동물들이 당신을 보고 황급히 도망치는것을 보았습니다.", 15);
    printf("\n");
    slowPrint("당신이 안으로 들어서려는 순간", 15);
    printf("\n");
    slowPrint("\"어어?\"", 15);
    printf("\n");
    slowPrint("당신의 발끝에 돌부리에 걸렸습니다", 15);
    printOptions_enterForest();
    printf("\n  선택 > ");
    int choice = getChoice(1, 2, printOptions_enterForest);
    printf("%d\n", choice);
    Sleep(1000);
    if (choice == 1) fallDownHeadFirst();
    else grabBranch();
}

void fallDownHeadFirst(void)
{
    system("cls");
    slowPrint("당신은 머리를 감싸쥐고 넘어졌습니다.", 15);
    printf("\n");
    slowPrint("다행히 큰 부상은 피한 듯했지만...", 15);
    pressAnyKey();
    passOut();
}

void grabBranch(void)
{
    system("cls");
    slowPrint("당신은 재빨리 근처 나뭇가지를 붙잡았습니다.", 15);
    printf("\n");
    slowPrint("하지만 나뭇가지는 당신의 무게를 버티기엔 너무 얇았고, 당신은 바위에 넘어져 머리를 부딪혔습니다.", 15);
    pressAnyKey();
    passOut();
}

void passOut(void)
{
    system("cls");
    slowPrint("당신의 눈앞이 캄캄해집니다.", 15);
    playFallSound();
    printf("\n");
    slowPrint("...", 200);
    printf("\n");
    slowPrint("당신은 정신을 잃었습니다.", 15);
    Sleep(1500);
    pressAnyKey();
    system("cls");
}

void printOptions_wakeUp(void)
{
    printf("  1. \"숲이 변했다는 소문을 듣고 찾아왔다고 한다.\"\n");
    printf("  2. \"산책하러 왔다고 한다.\"\n");
    printf("  3. \"...\" (말없이 사슴을 바라본다)\n");
}

void wakeUpScene(void)
{
    system("cls");
    slowPrint("얼마나 지났을까...", 50);
    printf("\n");
    slowPrint("정신을 차리자, 당신은 푹신한 나뭇잎 더미 위에 누워있었습니다.", 15);
    pressAnyKey();
    system("cls");
    slowPrint("몸을 일으키자, 당신의 옆에서 부스럭거리는 소리가 들렸습니다.", 15);
    printf("\n");
    slowPrint("그곳에는... 작은 사슴 한 마리가 조용히 당신을 지켜보고 있었습니다.", 15);
    pressAnyKey();
    system("cls");
    slowPrint("사슴 : \"숲에는 왜 들어오셨나요?\"", 15);
    printf("\n");
    printOptions_wakeUp();
    printf("\n  선택 > ");
    int choice = getChoice(1, 3, printOptions_wakeUp);
    printf("%d\n", choice);
    Sleep(1000);
    if (choice == 1) choiceMushroom();
    else if (choice == 2) {
        system("cls");
        slowPrint("사슴 : \"산책이라고요? 여긴 외부인은 절대 들어올 수 없는 곳인데...\"", 15);
        slowPrint("사슴 : \"당신은 수상해요.\"", 15);
        slowPrint("사슴은 경계심 가득한 눈빛으로 당신을 노려보았습니다.", 15);
        slowPrint("사슴 : \"죄송하지만 이만 숲에서 나가주세요.\"", 15);
        slowPrint("- 당신은 숲에서 쫓겨났다 -", 50);
        playGameOverMelody();
        Sleep(2000);
        exit(0);
    }
    else choiceSilent();
}

void choiceMushroom(void)
{
    system("cls");
    slowPrint("사슴 : \"소문이요? 소문에 대해서 얼마나 알고 있나요?\"", 15);
    printf("\n");
    slowPrint("당신 : \"최근 숲의 분위기가 이상해졌다고 들었어요.\"", 15);
    printf("\n");
    slowPrint("사슴 : \"흠.. 소문에 대해서 알고 싶은신가요?\"", 15);
    printf("\n");
    printf("\n");
    slowPrint("당신은 고개를 끄덕였다", 50);
    pressAnyKey();
    deerTrust();
}

void choiceSilent(void)
{
    system("cls");
    slowPrint("당신 : \"...\" (말없이 사슴을 바라본다)", 15);
    printf("\n");
    slowPrint("당신 : \"...\"숲에서 무슨 일이 있었는지 알고 싶어요", 15);
    printf("\n");
    slowPrint("당신 : \"...\"진짜로 무슨 일이 있었는지 알고 싶어요 제발 알려주세요", 15);
    pressAnyKey();
    deerTrust();
}

void deerTrust(void)
{
    system("cls");
    slowPrint("사슴 : \"좋아요. 숲에 무슨 일이 있었는지 말씀드릴게요.\"", 15);
    printf("\n");
    slowPrint("\"고개를 끄덕였다\"", 15);
    pressAnyKey();
    system("cls");
    slowPrint("사슴 : \"햇빛이 가장 반짝반짝하게 빛나던 정오였어요.\"", 15);
    printf("\n");
    slowPrint("사슴 : \"한 낯선 이가 숲에 찾아왔죠.\"", 15);
    printf("\n");
    slowPrint("사슴 : \"그는 숲에 들어오기를 원했지만 동물들은 그를 수상하다고 여겨 들여보내주지 않았어요.\"", 15);
    printf("\n");
    slowPrint("사슴 : \"그러자 화가난 낯선이는 숲을 떠나며 동물들에게 소리쳤어요.\"", 15);
    pressAnyKey();
    system("cls");
    slowPrint("낯선이 : \"머지않아 이 숲에는 비극이 들이닥칠 것이다! 숲은 악행과 죄로 물들 것이고 싸움이 멈추지 않을 것이다!\"", 15);
    printf("\n");
    slowPrint("낯선이 : \"비극이 멈추는 날은, 끔찍한 괴수가 나타나 모든 것을 집어삼키는 그 날이다....\"", 15);
    printf("\n");
    slowPrint("낯선이 : \"숲에서 해와 달이 모습을 드러내는 일은 다시는 없을 것이며, 숲은 결코 예전의 모습으로 되돌아오지 않을 것이다!\"", 15);
    printf("\n");
    pressAnyKey();
    system("cls");
    slowPrint("사슴 : \"그 말을 들은 동물들은 심각한 고민에 빠지게 되었어요.\"", 15);
    printf("\n");
    slowPrint("동물들 : \"저 남자의 말대로 숲에서 싸움이 멈추지 않으면 어떡하지?\"", 15);
    slowPrint("동물들 : \"괴수가 나타나서 숲을 해치게 되면 어떡하지??\"", 15);
    printf("\n");
    slowPrint("사슴 : \"그 예언 이후, 숲의 동물들은 서로를 의심하며 불안에 떨었어요.\"", 15);
    slowPrint("사슴 : \"싸움을 멈추지 않으면 괴수가 나타난다는 말이 모두의 마음을 짓눌렀죠.\"", 15);
    slowPrint("사슴 : \"그때, 세 마리의 새가 모두를 대신해 숲의 파수꾼이 되겠다고 나섰어요.\"", 15);
    slowPrint("사슴 : \"그들은 누구보다도 이 숲을 사랑했기에, 평화를 되찾기 위해 각자 스스로의 역할을 맡았죠.\"", 15);
    printf("\n");
    slowPrint("당신 : \"어떤 새들이 숲을 지키기로 한거야?\"", 15);
    pressAnyKey();
    askAboutBirds();
}


void printOptions_askBirds(void)
{
    printf("  1. 작은 새\n");
    printf("  2. 큰 새\n");
    printf("  3. 긴 새\n");
    if (heardAboutBigBird == 1 && heardAboutLongBird == 1 && heardAboutSmallBird == 1)
        printf("  4. 이제 충분히 들은 것 같다.\n");
}

void askAboutBirds(void)
{
    while (1)
    {
        system("cls");
        slowPrint("사슴 : \"좋아요\"", 15);
        slowPrint("사슴 : \"어떤 새에 대해서 들어보시겠어요?\"", 15);
        printf("\n");
        printOptions_askBirds();
        printf("\n  선택 > ");

        int maxOpt = (heardAboutBigBird && heardAboutLongBird && heardAboutSmallBird) ? 4 : 3;
        int choice = getChoice(1, maxOpt, printOptions_askBirds);
        printf("%d\n", choice);
        Sleep(1000);

        switch (choice)
        {
            case 1:
                explainSmallBird();
                heardAboutSmallBird = 1;
                break;
            case 2:
                explainBigBird();
                heardAboutBigBird = 1;
                break;
            case 3:
                explainLongBird();
                heardAboutLongBird = 1;
                break;
            case 4:
                if (maxOpt == 4)
                {
                    system("cls");
                    slowPrint("당신은 새들에 대한 모든 이야기를 들었습니다.", 15);
                    pressAnyKey();
                    return;
                }
                else
                {
                    system("cls");
                    slowPrint("사슴 : \"아직 듣지 않은 이야기가 있는 것 같네요...\"", 15);
                    pressAnyKey();
                }
                break;
        }
    }
}

void explainBigBird(void)
{
    system("cls");
    slowPrint("사슴 : \"눈이 많았던 큰 새는 숲에 침입자가 없는지 감시하기로 했어요.\"", 15);
    printf("\n");
    slowPrint("사슴 : \"큰 새의 눈은 먼 곳까지, 그리고 다른 이들이 보지 못하는 것까지 볼 수 있었기 때문이죠.\"", 15);
    pressAnyKey();
}

void explainLongBird(void)
{
    system("cls");
    slowPrint("사슴 : \"긴 새는 숲의 평화를 위해서 숲에 들어오는 자들의 죄의 무게를 재었어요.\"", 15);
    printf("\n");
    slowPrint("사슴 : \"긴 새의 천칭은 공명정대해서, 모든 죄의 무게를 잴 수 있고,\"", 15);
    printf("\n");
    slowPrint("사슴 : \"어떤 죄의 무게도 소홀히 여기지 않거든요.\"", 15);
    pressAnyKey();
}

void explainSmallBird(void)
{
    system("cls");
    slowPrint("사슴 : \"작은 새는 자신의 부리로 나쁜 자들에게 벌을 주기로 했어요.\"", 15);
    printf("\n");
    slowPrint("사슴 : \"작은 새의 부리는 뾰족하고 날카로웠기 때문이죠.\"", 15);
    pressAnyKey();
}


void printOptions_ch3(void)
{
    printf("  1. 새들을 찾아간다.\n");
    printf("  2. 숲을 빠져나가 갈 길 간다.\n");
}

void chapterThree(void)
{
    system("cls");
    slowPrint("당신 : \"그럼 새들이 숲을 지키고 있으니, 오히려 안전해진 것 아닌가요?\"", 15);
    pressAnyKey();
    system("cls");
    slowPrint("사슴 : \"분명 숲은 이전보다 안전해진게 맞지만 요즘 새들이 뭔가 고민이 있는 것처럼 보였어요\"", 15);
    slowPrint("사슴 : \"그들을 도와주실 수 있으신가요?\"", 15);
    pressAnyKey();

    system("cls");
    printOptions_ch3();
    printf("\n  선택 > ");
    int choice = getChoice(1, 2, printOptions_ch3);
    printf("%d\n", choice);
    Sleep(1000);

    switch (choice)
    {
        case 1:
            system("cls");
            slowPrint("당신은 사슴의 부탁을 들어주기로 했습니다.", 15);
            printf("\n");
            slowPrint("사슴 : \"좋아요. 당신에 대해서 새들한테 미리 알려둘게요\"", 15);
            slowPrint("사슴 : \"오늘은 여기서 쉬고 내일 새들을 찾아가주세요\"", 15);
            printf("\n");
            pressAnyKey();
            break;
        case 2:
            system("cls");
            slowPrint("당신은 더 이상 숲의 일에 휘말리고 싶지 않았습니다.", 15);
            slowPrint("사슴에게 작별인사를 하고, 조용히 숲을 빠져나왔습니다.", 15);
            slowPrint("\n- THE END -", 50);
            playGameOverMelody();
            Sleep(2000);
            exit(0);
            break;
    }
}


void printOptions_ch4(void)
{
    printf("  1. \"밤에 괴수가 숲에 들어오지 못하도록 허수아비를 세워두자.\"\n");
    printf("  2. \"너의 깃털을 모조리 태워서 영원히 꺼지지 않는 등불을 만들어 밤에도 숲을 지키는 건 어때?\"\n");
    printf("  3. \"밤에는 괴수가 나타나지 않을 테니, 마음 편히 쉬라고 안심시킨다.\"\n");
}

void chapterFour(void)
{
    int choice;
    system("cls");
    slowPrint("다음날. 당신은 큰 새의 집을 찾아갔습니다.", 15);
    slowPrint("커다란 문을 두드리니 안에서 커다랗고 눈이 많이 달린 새가 나왔습니다", 15);
    printf("\n");
    slowPrint("...", 100);
    printf("\n");
    slowPrint("큰 새 : \"아 사슴이 말한 사람이 너구나.\"", 15);
    slowPrint("큰 새 : \"나를 도와주러 온거야?\"", 15);
    printf("\n");
    slowPrint("당신은 고개를 끄덕이며 무엇이 고민인지 물어보았습니다.", 15);
    printf("\n");
    slowPrint("큰 새 : \"최근 숲을 감시하다가 어느 작은 동물을 만났는데 그가 벌벌 떨면서  말했어\"", 15);
    printf("\n");
    slowPrint("작은 동물 : \"모두가 잠드는 캄캄한 밤 중에 괴수가 나타나면 어떡하지?\"", 15);
    printf("\n");
    slowPrint("큰 새 : \"괴수가 밤에 활동할 수도 있는거잖아?\"", 15);
    slowPrint("큰 새 : \"그래서 어떻게 해야 밤에도 숲을 지킬 수 있을지 고민중이야\"", 15);
    printf("\n");
    pressAnyKey();

    system("cls");
    slowPrint("당신은 큰 새의 고민을 듣고 잠시 생각에 잠겼습니다.", 15);
    printf("\n");
    printOptions_ch4();
    printf("\n  선택 > ");
    choice = getChoice(1, 3, printOptions_ch4);
    printf("%d\n", choice);
    Sleep(1000);

    system("cls");
    switch (choice)
    {
        case 1:
            slowPrint("큰 새 : \"허수아비? 그거 좋은 생각이네! 숲의 동물들이 허수아비를 보면 괴수라 생각하고 도망갈 거야!\"", 15);
            slowPrint("당신은 큰 새와 함께 허수아비를 만들었습니다.", 15);
            break;
        case 2:
            slowPrint("큰 새 : \"내 깃털을 태우면 영원히 꺼지지 않는 등불을 만들 수 있다고??\"", 15);
            slowPrint("당신 : \"응 맞아. 대신 깃털을 전부 태워야만해\"", 15);
            slowPrint("당신은 큰 새의 깃털을 모두 태워 영원히 꺼지지 않는 등불을 만들어주었습니다.", 15);
            printf("\n");
            pressAnyKey();
            animateLamp2s();
            badChoices++;
            break;
        case 3:
            slowPrint("큰 새 : \"밤에는 괴수가 나타나지 않는다고? 정말로?\"", 15);
            slowPrint("당신은 큰 새에게 걱정할 필요가 없다고 말했습니다.", 15);
            slowPrint("큰 새는 당신의 말을 믿는 듯했지만, 아직 불안한 기색이 남아있었습니다.", 15);
            break;
    }
    pressAnyKey();
}


void printOptions_ch5(void)
{
    printf("  1. \"부리에 날카로운 철을 덧대자.\"\n");
    printf("  2. \"더 아프게 벌할 수 있도록 연습하자.\"\n");
    printf("  3. \"입을 찢어서 크게 만들어보자.\"\n");
}

void chapterFive(void)
{
    int choice;
    system("cls");
    slowPrint("당신은 작은 새의 둥지로 찾아갔습니다.", 15);
    slowPrint("작은 새가 반갑게 말을 걸었습니다.", 15);
    printf("\n");
    slowPrint("...", 100);
    printf("\n");
    slowPrint("작은 새 : \"사슴이 말한 사람이 너구나?\"", 15);
    slowPrint("작은 새 : \"나를 도와주러 온거야?\"", 15);
    printf("\n");
    slowPrint("당신은 고개를 끄덕이며, 작은 새에게 맞다고 대답합니다.", 15);
    printf("\n");
    slowPrint("작은 새 : \"얼마 전에 하늘을 날다가 다른 동물이 내 이야기를 하는 것을 들었어\"", 15);
    printf("\n");
    slowPrint("동물 : \"작은 새가 나쁜 자들에게 벌을 주겠대~\"", 15);
    slowPrint("동물 : \"하지만 그 새의 부리는 너무나도 조그매서 아무도 아파하지 않을거야 ㅋㅋ\"", 15);
    printf("\n");
    slowPrint("작은 새 : \"내 부리가 작다는것은 알고 있어\"", 15);
    slowPrint("작은 새 : \" 상대가 진심으로 잘못을 깨닫게 하려면, 얼마나 아프게 해야 할까?\"", 15);
    pressAnyKey();

    system("cls");
    slowPrint("당신은 작은 새의 고민을 듣고 잠시 생각에 잠겼습니다.", 15);
    printf("\n");
    printOptions_ch5();
    printf("\n  선택 > ");
    choice = getChoice(1, 3, printOptions_ch5);
    printf("%d\n", choice);
    Sleep(1000);

    system("cls");
    switch (choice)
    {
        case 1:
            slowPrint("작은 새 : \"부리에 날카로운 철을 덧대? 그거 좋은 생각이네! 모두 나를 두려워하겠지?\"", 15);
            slowPrint("당신은 작은 새의 부리에 날카로운 철을 덧대주었습니다.", 15);
            break;
        case 2:
            slowPrint("작은 새 : \"벌주는 연습? 좋아! 어떤 연습을 하면 좋을까?\"", 15);
            slowPrint("당신은 작은 새와 함께 벌을 주는 연습을 했습니다.", 15);
            break;
        case 3:
            slowPrint("작은 새 : \"입을 찢어서 크게 만들어? 그게 정말로 가능한거야?... 엄청 아플거 같아\"", 15);
            printf("\n");
            slowPrint("당신은 작은 새에게 괜찮다고 안심시켰습니다.", 15);
            printf("\n");
            slowPrint("당신은 작은 새를 붙잡아 입을 찢어 어떤 생물도 한 입에 삼킬 수 있도록 크게 만들어주었습니다.", 15);
            printf("\n");
            slowPrint("...", 15);            
            printf("\n");
            
            printf(ANSI_RED);
            printf("       ####    ######  ##   ##   ####     #####   ######    ######  #####    \n");
   	 		printf("     ##   ##   ##      ###  ##  ##  ##   ##   ##  ###  ##   ##      ##  ##   \n");
    		printf("    ##         ##      #### ##  ##       ##   ##  ##   ##   ##      ##   ##  \n");
    		printf("    ##         #####   #######   #####   ##   ##  ##  ##    #####   ##   ##  \n");
    		printf("    ##         ##      ## ####       ##  ##   ##  #####     ##      ##   ##  \n");
    		printf("     ##   ##   ##      ##  ###  ##   ##  ##   ##  ## ###    ##      ##  ##   \n");
    		printf("       ####    ######  ##   ##   #####    #####   ##  ###   ######  #####    \n");
    		printf(ANSI_RESET);
    		printf("\n");
    
            badChoices++;
            break;
    }
    pressAnyKey();
}


void printOptions_ch6(void)
{
    printf("  1. \"억울한 동물이 나오지 않도록 더 공정히 죄를 잴 수 있도록 노력해보자.\"\n");
    printf("  2. \"그럼 언제나 한쪽으로 기울어져 유죄가 나오는 천칭을 만들자.\"\n");
    printf("  3. \"다른 방식으로 죄를 재보자.\"\n");
}

void chapterSix(void)
{
    int choice;
    system("cls");
    slowPrint("당신은 긴 새가 있는 곳으로 찾아갔습니다.", 15);
    slowPrint("그곳에는 눈을 붕대로 감은 채, 길고 구부러진 다리로 서서 커다란 천칭을 들고 있는 새가 있었습니다.", 15);
    printf("\n");
    slowPrint("...", 100);
    printf("\n");
    slowPrint("긴 새 : \"넌 누구지? 난 앞이 보이지 않아서 네가 누군지 모르겠어\"", 15);
    printf("\n");
    slowPrint("당신은 사슴이 보냈다고 말하며, 긴 새를 도와주러 왔다고 말했습니다.", 15);
    printf("\n");
    slowPrint("긴 새 : \"나를? 도와주러?\"", 15);
    printf("\n");
    slowPrint("당신은 그렇다고 대답합니다.", 15);
    pressAnyKey();
    system("cls");
    slowPrint("긴 새 : \"얼마 전에 새로 알게된 고라니가 그러더라\"", 15);
    printf("\n");
    slowPrint("고라니 : \"언젠가 너의 저울이 어느 한 쪽으로도 기울어지지 않게 되면 어떡하지?\"", 15);
    printf("\n");
    slowPrint("긴 새 : \"그 말을 듣고 생각해보니 맞는 말이더라. 내 천칭으로도 죄를 잴 수 없는 생물이 나타나면 나는 어떻게 해야 할까\"", 15);
    slowPrint("긴 새 : \"그래서 어떻게 해야 좋을지 고민중이야\"", 15);
    pressAnyKey();
    system("cls");
    slowPrint("당신은 긴 새의 고민을 듣고 잠시 생각에 잠겼습니다.", 15);
    printf("\n");
    printOptions_ch6();
    printf("\n  선택 > ");
    choice = getChoice(1, 3, printOptions_ch6);
    printf("%d\n", choice);
    Sleep(1000);

    system("cls");
    switch (choice)
    {
        case 1:
            slowPrint("긴 새 : \"더 열심히? 내가 열심히 노력하면 되는 거였구나!\"", 15);
            slowPrint("당신은 긴 새와 함께 죄의 무게를 재는 연습을 했습니다.", 15);
            break;
        case 2:
            slowPrint("긴 새 : \"언제나 유죄가 나오는 저울? 그거라면 더 이상 고민할 필요가 없겠군.\"", 15);
            printf("\n");
            slowPrint("긴 새 : \"앞으로는 심판의 결과가 명확하게 나오겠지?\"", 15);
            printf("\n");
            slowPrint("당신은 긴 새의 천징을 조작해서 무조건 유죄가 나오도록  한쪽으로만 기울어지게 만들어주었습니다.", 15);
            printf("\n");
		    pressAnyKey();
            animateScales();
            badChoices++;
            break;
        case 3:
            slowPrint("긴 새 : \"다른 방식으로? 죄를 재는 것 말고?\"", 15);
            slowPrint("당신은 긴 새에게 죄를 벌하는 것이 아닌, 용서하고 기회를 주는 방법에 대해 설명했습니다.", 15);
            break;
    }
    pressAnyKey();
    system("cls");
}


void printOptions_end1(void)
{
    printf("  1. \"너희들 각자의 방식으로는 이 숲을 지키기에 조금 버겁지 않아?\"\n");
}
void printOptions_end2(void)
{
    printf("  1. \"만약 너희의 힘을 하나로 모은다면, 지금보다 훨씬 강해질 수 있을거야.\"\n");
}

void endGame(void)
{
    system("cls");
    if (badChoices >= 2)
    {
        int choice;
        printf("\n");
        slowPrint("당신이 새들의 고민을 들어준 이후로", 15);
        printf("\n");
        slowPrint("모든 것이 바뀌었습니다.", 15);
        printf("\n");
        slowPrint("숲 속의 동물들은 불평하기 시작했습니다.", 15);
        printf("\n");
        slowPrint("동물들 : \"숲에서 살아가는 생물들은 모두 끔찍한 일을 당해\"", 15);
        printf("\n");
        slowPrint("동물들 : \"큰 새는 숲에 있는 생물들을 언제나 감시해서 한 순간도 자유로울 수 없어\"", 15);
        printf("\n");
        slowPrint("동물들 : \"작은 새의 징벌은 너무 무서워\"", 15);
        printf("\n");
        slowPrint("동물들 : \"긴 새의 저울은 전혀 공정하지 않아\"", 15);
        printf("\n");
        pressAnyKey();
        system("cls");
        slowPrint("새들은 화가 났어요.", 15);
        printf("\n");
        slowPrint("새들 : \"우리는 이 숲을 지키려고 이렇게 열심히 노력하는데 어째서 우리의 수고로움을 아무도 알아주지 않는거지?\"", 15);
        printf("\n");
        slowPrint("점점 숲을 찾아오는 손님의 수는 줄어들었으며", 15);
        printf("\n");
        slowPrint("점차 많은 생물들이 더 많은 불만을 내뱉었고 숲에는 매일 싸움이 일어났습니다 .", 15);
        printf("\n");
        slowPrint("당신 : \"......\"", 15);
        printf("\n");
        slowPrint("지켜보던 당신이 입을 열었습니다.", 15);
        pressAnyKey();

        system("cls");
        printOptions_end1();
        printf("\n\n  선택 > ");
        choice = getChoice(1, 1, printOptions_end1);
        printf("%d\n", choice);
        Sleep(1000);

        pressAnyKey();
        system("cls");
        printOptions_end2();
        printf("\n\n  선택 > ");
        choice = getChoice(1, 1, printOptions_end2);
        printf("%d\n", choice);
        Sleep(1000);

        system("cls");

        slowPrint("당신은 새들에게 마지막 조언을 해주고 숲을 빠져나와 여행을 이어나갔습니다.", 15);
        printf("\n");
        pressAnyKey();
        printf("\n");
        slowPrint("새들은 곧 당신의 조언을 받아들였습니다.", 15);
        pressAnyKey();
        printf("\n");
        playBlockGame();
        slowPrint("백 리 밖도 볼 수 있는 큰 새의 눈과", 15);
        printf("\n");
        slowPrint(" 어떤 자의 죄라도 심판할 수 있는 긴 새의 팔,.", 15);
        printf("\n");
        slowPrint("모든 것을 집어삼킬 수 있는 작은 새의 입이 하나가 된 순간.", 15);
        printf("\n");
        slowPrint("숲에는 어둠이 찾아왔습니다..", 15);
    	pressAnyKey();
    	system("cls");
        slowPrint("새의 모습을 본 생물들은 그 끔찍함과 공포심에 비명을 질렀고, 곧 숲은 아수라장이 되었습니다.", 15);
        printf("\n");
        slowPrint("그때, 아수라장 속에서 누군가 소리쳤습니다.", 15);
        printf("\n");
        slowPrint(ANSI_RED "저기 괴수가 있다! 검고 어두운 숲에는 크고 무서운 괴물이 산다!" ANSI_RESET, 25);
        pressAnyKey();
        system("cls");
        slowPrint("종말새 : \"괴수가 있다고?\"", 15);
        printf("\n");
        slowPrint("하나로 합쳐진 세 마리의 새들은 주위를 둘러보았지만 아무도 보이지 않았어요", 25);
        printf("\n");
        slowPrint("종말새는 숲 속을 배회하며 괴수를 찾기 시작했어요. 괴수가 숲에 오면 큰일이니 말이에요", 25);
        printf("\n");
        slowPrint("하지만 아무도 없었습니다.", 25);
        printf("\n");
        slowPrint("생물들도, 해와 달도, 괴수도. 남은건 그저 한 마리의 새와 검은 숲이었습니다.", 25);
        printf("\n");
        slowPrint("그 후로 숲에는 아주 어두운 밤만 계속 되었습니다.", 25);
        printf("\n");
        slowPrint("...", 100);
        printf("\n");
        slowPrint("...", 100);
        printf("\n");
        slowPrint("...", 100);
        printf("\n");
        slowPrint("아무도 살지 않는 검은 숲에는 무서운 괴수가 살고 있다는 소문이 들리고 있습니다.", 25); 
        printf("\n");
    	playApocalypseMelody();
        Sleep(1000);
        slowPrint("- END : 검은 숲 -", 50);
    }
    else
    {
        slowPrint("모든 새들의 고민을 해결해준 당신에게, 새들은 진심으로 고마워했습니다.", 15);
        slowPrint("큰 새는 숲을 감시하며 낮과 밤의 조화를 되찾았고, 동물들을 작은 새의 부리를 믿었습니다.", 15);
        slowPrint("그리고 긴 새는 더 공정하고 정의로운 판결을 내릴 수 있었습니다.", 15);
        printf("\n");
        slowPrint("당신은 숲의 평화를 되찾아준 구원자가 되었습니다.", 15);
        slowPrint("모든 동물들은 당신의 이름을 부르며 행복한 웃음을 지었고, 당신은 조용히 숲을 떠났습니다.", 15);
        printf("\n");
        slowPrint("- END : 평화 -", 50);
    }
    pressAnyKey();
    exit(0);
}


void enableANSI(void)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode = 0;
    if (GetConsoleMode(hOut, &mode)) {
        mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
        SetConsoleMode(hOut, mode);
    }
}

/* 숲 배경 프레임 */
void printForestFrame1(void)
{
    printf(ANSI_GREEN);
    printf("                       _-_                           \n");
    printf("                     /~~   ~~|                         \n");
    printf("                   /~~       ~~||                    \n");
    printf("                  {              }                    \n");
    printf("                    ~~  _-   -_  /             _-_     \n");
    printf("                        ~  ~~\\ //  ~       /~~   ~~|  \n");
    printf("                          | |            /~~     ~~|| \n");
    printf("           _-_            | |             {         ~  }\n");
    printf("         /~~   ~~|       // \\\\           \\ ~ _- -_ / \n");
    printf("       /~~        ~~|                    ~   \\\\ //  ~  \n");
    printf("      {       ~      }                        | |      \n");
    printf("       \\  _-     -_ /                        | |      \n");
    printf("         ~  ~~\\ | ~                         // \\\\     \n");
    printf("             |  |                                   \n");
    printf("             |  |                                   \n");
    printf("            // \\\\                                  \n");
    printf("=================================================================\n");
    printf(ANSI_RESET);
}

void printForestFrame2(void)
{
    printf(ANSI_GREEN);
    printf("                       _-_                           \n");
    printf("                     /~~   ~~|                         \n");
    printf("                   /~~       ~~||                      \n");
    printf("                   {            }                      \n");
    printf("                    ~~  _-   -_  /             _-_     \n");
    printf("                        ~  ~~\\ //  ~       /~~   ~~|  \n");
    printf("                          | |              /~~     ~~|| \n");
    printf("           _-_            | |             {        ~  } \n");
    printf("         /~~   ~~|       // \\\\           \\  _- -_  /  \n");
    printf("       /~~        ~~|                    ~  \\\\ //  ~   \n");
    printf("       {       ~     }                        | |       \n");
    printf("       \\  _-     -_ /                        | |       \n");
    printf("         ~  ~~\\ | ~                         // \\\\      \n");
    printf("             |  |                                   \n");
    printf("             |  |                                   \n");
    printf("            // \\\\                                  \n");
    printf("=================================================================\n");
    printf(ANSI_RESET);
}

/* 등불 애니메이션 */
static void printLine3(const char* left, const char* mid, const char* right)
{
    printf(ANSI_RED "%s" ANSI_YELLOW "%s" ANSI_RED "%s" ANSI_RESET "\n", left, mid, right);
}
static void printFrame0(void)
{
    printLine3("      . ", "' . '", "              ");
    printLine3("    `   ", ".   .", "`            ");
    printLine3("   '  . ", " . . ", "  '           ");
    printLine3("   :   .", "  .  ", ".   :          ");
    printLine3("  : ' . ", ": - :", " ' . :        ");
    printLine3(" `  .   ", "(   )", "   .  `       ");
    printLine3(" . ' .  ", "|===|", "  . ' .      ");
    printLine3(" `   .  ","| . |", "   .   `     ");
    printLine3(" '  .   ", "|' _'|", "  .  '       ");
    printLine3(" :   .  ", "| /  ||", " .   :       ");
    printLine3("  : . ' ", "| \\|_/|", " ' . :       ");
    printLine3("   ` .  ", "|_____|", "  . `        ");
    printLine3("     '  ","|||||||", "  '          ");
    printLine3("      ` ","|||||||", " `           ");
    printLine3("       ", "`-----`", "              ");
}
static void printFrame1(void)
{
    printLine3("      . ", "^ . ^", "              ");
    printLine3("    `   ", "^   ^", "`            ");
    printLine3("   '  ^ ", " ^ ^ ", "  '           ");
    printLine3("   :   ^", "  ^  ", "^   :          ");
    printLine3("  : ^ . ", ": - :", " ^ . :        ");
    printLine3(" `  ^   ", "(   )", "   ^  `       ");
    printLine3(" . ' .  ", "|===|", "  . ' .      ");
    printLine3(" `   .  ","| . |", "   .   `     ");
    printLine3(" '  .   ", "|' _'|", "  .  '       ");
    printLine3(" :   .  ", "| /  ||", " .   :       ");
    printLine3("  : . ' ", "| \\|_/|", " ' . :       ");
    printLine3("   ` .  ", "|_____|", "  . `        ");
    printLine3("     '  ","|||||||", "  '          ");
    printLine3("      ` ","|||||||", " `           ");
    printLine3("       ", "`-----`", "              ");
}
void animateLamp2s(void)
{
    const int frameDelayMs = 200;
    const int totalTimeMs  = 2000;
    const int totalFrames  = totalTimeMs / frameDelayMs;
    for (int i = 0; i < totalFrames; ++i) {
        system("cls");
        if ((i % 2) == 0) printFrame0();
        else              printFrame1();
        Sleep(frameDelayMs);
    }
}

/* 저울 애니메이션 */
static void printScales1(void)
{
    printf(ANSI_BROWN);
    printf("\n");
    printf("                              _|_              \n");
    printf("             |------------     |               \n");
    printf("             |           `----|----           \n");
    printf("            | |                |   `-----------|\n");
    printf("           |   |               |               |\n");
    printf("         |-----------|         |              | |\n");
    printf("         |___________|         |             |   |\n");
    printf("                               |       |-----------|\n");
    printf("                               |       |___________|\n");
    printf("                      ======================        \n");
    printf(ANSI_RESET);
}
static void printScales2(void)
{
    printf(ANSI_BROWN);
    printf("\n");
    printf("                                _|_            \n");
    printf("               |------------     |             \n");
    printf("               |           `----|----         \n");
    printf("              | |                |   `-----------|\n");
    printf("             |   |               |               |\n");
    printf("           |-----------|         |              | |\n");
    printf("           |___________|         |             |   |\n");
    printf("                                 |       |-----------|\n");
    printf("                                 |       |___________|\n");
    printf("                      ======================          \n");
    printf(ANSI_RESET);
}
void animateScales(void)
{
    const int frameDelayMs = 200;
    const int totalTimeMs  = 2000;
    const int totalFrames  = totalTimeMs / frameDelayMs;
    for (int i = 0; i < totalFrames; ++i) {
        system("cls");
        if ((i % 2) == 0) printScales1();
        else              printScales2();
        Sleep(frameDelayMs);
    }
}
//인트로 음악 
void playIntroMelody(void)

{


    Beep(392, 300);  Sleep(80);   
    Beep(440, 350);  Sleep(80);   
    Beep(494, 350);  Sleep(100);  

    Beep(523, 400);  Sleep(100);  
    Beep(587, 350);  Sleep(80);   
    Beep(523, 350);  Sleep(80);  
    Beep(659, 400);  Sleep(100);  

    Beep(587, 450);  Sleep(100);  
    Beep(523, 500);  Sleep(100);  
    Beep(392, 650);             
}
//플레이어가 바위에서 넘어 짐 
void playFallSound(void)
{
    Beep(330, 120);  Sleep(60);
    Beep(294, 100);  Sleep(50);
    Beep(196, 200);  Sleep(80);
    Beep(130, 300);  Sleep(100);
    Beep(98, 500);
}

//기본 게임오버 음악 
void playGameOverMelody(void)
{
    Beep(392, 400);  Sleep(100);  // G4
    Beep(349, 400);  Sleep(100);  // F4
    Beep(330, 450);  Sleep(100);  // E4
    Beep(294, 500);  Sleep(120);  // D4
    Beep(262, 700);               // C4 (여운)
}

//종말새 엔딩 음 
void playApocalypseMelody(void)
{
    Beep(220, 500);  Sleep(100);
    Beep(196, 600);  Sleep(120);
    Beep(165, 500);  Sleep(150);
    Beep(147, 700);  Sleep(200);
    Beep(175, 400);  Sleep(120);
    Beep(131, 600);  Sleep(150);
    Beep(110, 800);  Sleep(200); 
    Beep(98, 1000);
}


/* ==== 블록 쌓기 미니게임 함수 ==== */
int playBlockGame(void)
{
    int block_order = 0;
    int success_flag = 0;
    int block_stack[box_length * 2 + 1] = {0};
    
    system("cls");
    printf("새들이 하나로 합쳐지려 하고 있습니다... 최대한 높이 쌓아올리세요\n");
    Sleep(1500);
    printf("\n");
    Sleep(2000);

    while (block_order < 3)
    {
        int w, h;
        if (block_order == 0) { w = 4; h = 4; }
        else if (block_order == 1) { w = 1; h = 4; }
        else { w = 2; h = 2; }

        int temp_x = 4, temp_y = 2, temp = 2;

        // 블록 이동
        do {
            for (int i = 0; i < h; i++) {
                gotoxy(temp_x, temp_y + i);
                for (int j = 0; j < w * 2; j++)
                    printf(" ");
            }

            temp_x += temp;
            if (temp_x >= (box_length * 2 - (w * 2))) temp = -2;
            if (temp_x <= 4) { temp_x = 4; temp = 2; }

            for (int i = 0; i < h; i++) {
                gotoxy(temp_x, temp_y + i);
                for (int j = 0; j < w; j++)
                    printf("□");
            }
            Sleep(60);

        } while (!kbhit());
        getch();

        // 바닥 높이 계산
        int max_h = 0;
        for (int i = 0; i < w * 2; i++)
            if (block_stack[temp_x + i] > max_h)
                max_h = block_stack[temp_x + i];

        int target_y = box_height + 2 - max_h - h + 1;

        // 낙하
        for (int y = 2; y < target_y; y++) {
            for (int i = 0; i < h; i++) {
                gotoxy(temp_x, y + i);
                for (int j = 0; j < w; j++)
                    printf("□");
            }
            Sleep(40);
            for (int i = 0; i < h; i++) {
                gotoxy(temp_x, y + i);
                for (int j = 0; j < w * 2; j++)
                    printf(" ");
            }
        }

        // 착지 후 고정
        for (int i = 0; i < h; i++) {
            gotoxy(temp_x, target_y + i);
            for (int j = 0; j < w; j++)
                printf("□");
        }
        for (int i = 0; i < w * 2; i++)
            block_stack[temp_x + i] += h;

        // 누적 높이 체크
        int overall_max = 0;
        for (int i = 0; i < box_length * 2; i++)
            if (block_stack[i] > overall_max)
                overall_max = block_stack[i];

        if (overall_max >= GOAL_HEIGHT) {
            gotoxy(1, box_height + 5);
            printf("세 마리의 새들이 모여 종말새가 되었습니다.\n");
            printf("\n");
            success_flag = 1;
            break;
        }
        block_order++;
    }

    if (!success_flag) {
        gotoxy(1, box_height + 5);
        printf("실패....\n");
        Sleep(2500);
        printf("\n");
    	printf("새들의 조율에 실패했습니다...\n");
    	Sleep(1000);
        printf("\n");
    	printf("그들은 하나가 되지 못했고\n");
    	Sleep(1000);
        printf("\n");
    	printf("숲 속의 동물들에게 내쫓겨, 결국 숲을 떠났습니다.\n");
    	Sleep(1500);
        printf("\n");
        printf("이후 숲에는 평화가 찾아왔습니다.\n");
    	Sleep(1500);
        printf("\n");
        slowPrint("- END : 조율 실패 -", 50);
        playGameOverMelody();
        Sleep(2000);
        exit(0);
    }

    Sleep(2000);
    return 1;
}

int main(void)
{
    intro();
    startGame();
    wakeUpScene();
    chapterThree();
    chapterFour();
    chapterFive();
    chapterSix();
    endGame();
    return 0;
}
