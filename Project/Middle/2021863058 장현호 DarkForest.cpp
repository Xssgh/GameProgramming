#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>

// --- ANSI ���� �ڵ� ���� ---
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#define ANSI_RESET  "\x1b[0m"
#define ANSI_YELLOW "\x1b[93m"
#define ANSI_RED    "\x1b[91m"
#define ANSI_GREEN  "\x1b[92m"
#define ANSI_BROWN  "\x1b[38;5;94m"

// --- ��� ���� ��� ---
#define box_length 10
#define box_height 20
#define GOAL_HEIGHT 10

// --- ���� ���� ���� ---
int badChoices = 0;
int heardAboutBigBird = 0;
int heardAboutLongBird = 0;
int heardAboutSmallBird = 0;

// --- �Լ� ���� ���� ---
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

        // ����Ű�� Ư��Ű ����
        if (key == 13 || key == 224)
            continue;

        // ���ڰ� �ƴ� ���
        if (key < '0' || key > '9')
        {
            system("cls");
            slowPrint("�־��� ��ȣ�� �����ϼ��� .", 15);
            printf("\n\n");
            if (printOptions != NULL)
                printOptions(); // ������ �ٽ� ���
            printf("\n  ���� > ");
            continue;
        }

        choice = key - '0';

        // ��ȿ ���� üũ
        if (choice >= min && choice <= max)
            return choice;

        // �߸��� ���� �Է� �� ������ �ٽ� ���
        system("cls");
        slowPrint("�ùٸ� �������� �Է��ϼ���.", 15);
        printf("\n\n");
        if (printOptions != NULL)
            printOptions();
        printf("\n  ���� > ");
    }
}

// --- ���� �Լ� ---
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
    printf("\n\n(����Ϸ��� �ƹ� Ű�� ��������...)");
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
    printf("// �� Project Moon. Original concept inspired by Lobotomi Corporation / Library of Ruina universe.\n");
    printf("\n\n");
    pressAnyKey();
}

void printOptions_startGame(void)
{
    printf("  1. ������ ������.\n");
    printf("  2. �׳�  ���� ���� ��� ����.\n");
}

void startGame(void)
{
    system("cls");
    slowPrint("�������̸� ��ô���̸鼭, ���ÿ�  �ƹ��͵� �ƴ� ������  ����� ����� �����ϰ� ������ ��â�� ������ �������� �־����ϴ�.", 15);
    printf("\n");
    slowPrint("�� ���� ����� ���� ���� �ҹ��� ���ö����ϴ�.", 15);
    printf("\n");
    slowPrint("\"�ֱ� ���� �����Ⱑ �̻������ٰ� �ϴ���.. �����鵵 �ܺ����� �ʿ� �̻����� ����ϰ� �ִٰ� �����.\"", 15);
    printf("\n");
    slowPrint("...", 100);
    printf("\n");
    slowPrint("���� ������ �ɸ���. ���� ���� �����°� �������� �𸣰ڴ�.", 70);
    printf("\n");
    printOptions_startGame();
    printf("\n  ���� > ");
    int choice = getChoice(1, 2, printOptions_startGame);
    printf("%d\n", choice);
    Sleep(1000);
    if (choice == 1) enterForest();
    else {
        system("cls");
        slowPrint("�ᱹ ����� �������� �̱��� ���ϰ� ���� ���� ��� �����ϴ�.", 15);
        slowPrint("���� ���°� ���� ��ȸ��...", 15);
        slowPrint("\n- THE END -", 50);
        playGameOverMelody();
        Sleep(2000);
        exit(0);
    }
}

void printOptions_enterForest(void)
{
    printf("  1. �Ӹ��� ���μ� ��ȣ�Ѵ�.\n");
    printf("  2. ���������� ��´�.\n");
}

void enterForest(void)
{
    system("cls");
    slowPrint("������ �߰����� �Ű���ϴ�.", 15);
    slowPrint("...", 100);
    pressAnyKey();
    system("cls");
    slowPrint("����� ���� �Ա��� �����߽��ϴ�. ���� ������ ������� ���ÿ� �� �� ���� �������� �������ϴ�.", 15);
    printf("\n");
    slowPrint("�Ա����� �������� ����� ���� Ȳ���� ����ġ�°��� ���ҽ��ϴ�.", 15);
    printf("\n");
    slowPrint("����� ������ ������ ����", 15);
    printf("\n");
    slowPrint("\"���?\"", 15);
    printf("\n");
    slowPrint("����� �߳��� ���θ��� �ɷȽ��ϴ�", 15);
    printOptions_enterForest();
    printf("\n  ���� > ");
    int choice = getChoice(1, 2, printOptions_enterForest);
    printf("%d\n", choice);
    Sleep(1000);
    if (choice == 1) fallDownHeadFirst();
    else grabBranch();
}

void fallDownHeadFirst(void)
{
    system("cls");
    slowPrint("����� �Ӹ��� ������� �Ѿ������ϴ�.", 15);
    printf("\n");
    slowPrint("������ ū �λ��� ���� ��������...", 15);
    pressAnyKey();
    passOut();
}

void grabBranch(void)
{
    system("cls");
    slowPrint("����� �绡�� ��ó ���������� ����ҽ��ϴ�.", 15);
    printf("\n");
    slowPrint("������ ���������� ����� ���Ը� ��Ƽ�⿣ �ʹ� ��Ұ�, ����� ������ �Ѿ��� �Ӹ��� �ε������ϴ�.", 15);
    pressAnyKey();
    passOut();
}

void passOut(void)
{
    system("cls");
    slowPrint("����� ������ įį�����ϴ�.", 15);
    playFallSound();
    printf("\n");
    slowPrint("...", 200);
    printf("\n");
    slowPrint("����� ������ �Ҿ����ϴ�.", 15);
    Sleep(1500);
    pressAnyKey();
    system("cls");
}

void printOptions_wakeUp(void)
{
    printf("  1. \"���� ���ߴٴ� �ҹ��� ��� ã�ƿԴٰ� �Ѵ�.\"\n");
    printf("  2. \"��å�Ϸ� �Դٰ� �Ѵ�.\"\n");
    printf("  3. \"...\" (������ �罿�� �ٶ󺻴�)\n");
}

void wakeUpScene(void)
{
    system("cls");
    slowPrint("�󸶳� ��������...", 50);
    printf("\n");
    slowPrint("������ ������, ����� ǫ���� ������ ���� ���� �����־����ϴ�.", 15);
    pressAnyKey();
    system("cls");
    slowPrint("���� ����Ű��, ����� ������ �ν����Ÿ��� �Ҹ��� ��Ƚ��ϴ�.", 15);
    printf("\n");
    slowPrint("�װ�����... ���� �罿 �� ������ ������ ����� ���Ѻ��� �־����ϴ�.", 15);
    pressAnyKey();
    system("cls");
    slowPrint("�罿 : \"������ �� �����̳���?\"", 15);
    printf("\n");
    printOptions_wakeUp();
    printf("\n  ���� > ");
    int choice = getChoice(1, 3, printOptions_wakeUp);
    printf("%d\n", choice);
    Sleep(1000);
    if (choice == 1) choiceMushroom();
    else if (choice == 2) {
        system("cls");
        slowPrint("�罿 : \"��å�̶���? ���� �ܺ����� ���� ���� �� ���� ���ε�...\"", 15);
        slowPrint("�罿 : \"����� �����ؿ�.\"", 15);
        slowPrint("�罿�� ���� ������ �������� ����� ������ҽ��ϴ�.", 15);
        slowPrint("�罿 : \"�˼������� �̸� ������ �����ּ���.\"", 15);
        slowPrint("- ����� ������ �Ѱܳ��� -", 50);
        playGameOverMelody();
        Sleep(2000);
        exit(0);
    }
    else choiceSilent();
}

void choiceMushroom(void)
{
    system("cls");
    slowPrint("�罿 : \"�ҹ��̿�? �ҹ��� ���ؼ� �󸶳� �˰� �ֳ���?\"", 15);
    printf("\n");
    slowPrint("��� : \"�ֱ� ���� �����Ⱑ �̻������ٰ� ������.\"", 15);
    printf("\n");
    slowPrint("�罿 : \"��.. �ҹ��� ���ؼ� �˰� �����Ű���?\"", 15);
    printf("\n");
    printf("\n");
    slowPrint("����� ���� ��������", 50);
    pressAnyKey();
    deerTrust();
}

void choiceSilent(void)
{
    system("cls");
    slowPrint("��� : \"...\" (������ �罿�� �ٶ󺻴�)", 15);
    printf("\n");
    slowPrint("��� : \"...\"������ ���� ���� �־����� �˰� �;��", 15);
    printf("\n");
    slowPrint("��� : \"...\"��¥�� ���� ���� �־����� �˰� �;�� ���� �˷��ּ���", 15);
    pressAnyKey();
    deerTrust();
}

void deerTrust(void)
{
    system("cls");
    slowPrint("�罿 : \"���ƿ�. ���� ���� ���� �־����� �����帱�Կ�.\"", 15);
    printf("\n");
    slowPrint("\"���� ��������\"", 15);
    pressAnyKey();
    system("cls");
    slowPrint("�罿 : \"�޺��� ���� ��¦��¦�ϰ� ������ ���������.\"", 15);
    printf("\n");
    slowPrint("�罿 : \"�� ���� �̰� ���� ã�ƿ���.\"", 15);
    printf("\n");
    slowPrint("�罿 : \"�״� ���� �����⸦ �������� �������� �׸� �����ϴٰ� ���� �鿩�������� �ʾҾ��.\"", 15);
    printf("\n");
    slowPrint("�罿 : \"�׷��� ȭ���� �����̴� ���� ������ �����鿡�� �Ҹ��ƾ��.\"", 15);
    pressAnyKey();
    system("cls");
    slowPrint("������ : \"�����ʾ� �� ������ ����� ���̴�ĥ ���̴�! ���� ����� �˷� ���� ���̰� �ο��� ������ ���� ���̴�!\"", 15);
    printf("\n");
    slowPrint("������ : \"����� ���ߴ� ����, ������ ������ ��Ÿ�� ��� ���� �����Ű�� �� ���̴�....\"", 15);
    printf("\n");
    slowPrint("������ : \"������ �ؿ� ���� ����� �巯���� ���� �ٽô� ���� ���̸�, ���� ���� ������ ������� �ǵ��ƿ��� ���� ���̴�!\"", 15);
    printf("\n");
    pressAnyKey();
    system("cls");
    slowPrint("�罿 : \"�� ���� ���� �������� �ɰ��� ��ο� ������ �Ǿ����.\"", 15);
    printf("\n");
    slowPrint("������ : \"�� ������ ����� ������ �ο��� ������ ������ �����?\"", 15);
    slowPrint("������ : \"������ ��Ÿ���� ���� ��ġ�� �Ǹ� �����??\"", 15);
    printf("\n");
    slowPrint("�罿 : \"�� ���� ����, ���� �������� ���θ� �ǽ��ϸ� �Ҿȿ� �������.\"", 15);
    slowPrint("�罿 : \"�ο��� ������ ������ ������ ��Ÿ���ٴ� ���� ����� ������ ��������.\"", 15);
    slowPrint("�罿 : \"�׶�, �� ������ ���� ��θ� ����� ���� �ļ����� �ǰڴٰ� �������.\"", 15);
    slowPrint("�罿 : \"�׵��� �������ٵ� �� ���� ����߱⿡, ��ȭ�� ��ã�� ���� ���� �������� ������ �þ���.\"", 15);
    printf("\n");
    slowPrint("��� : \"� ������ ���� ��Ű��� �Ѱž�?\"", 15);
    pressAnyKey();
    askAboutBirds();
}


void printOptions_askBirds(void)
{
    printf("  1. ���� ��\n");
    printf("  2. ū ��\n");
    printf("  3. �� ��\n");
    if (heardAboutBigBird == 1 && heardAboutLongBird == 1 && heardAboutSmallBird == 1)
        printf("  4. ���� ����� ���� �� ����.\n");
}

void askAboutBirds(void)
{
    while (1)
    {
        system("cls");
        slowPrint("�罿 : \"���ƿ�\"", 15);
        slowPrint("�罿 : \"� ���� ���ؼ� ���ðھ��?\"", 15);
        printf("\n");
        printOptions_askBirds();
        printf("\n  ���� > ");

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
                    slowPrint("����� ���鿡 ���� ��� �̾߱⸦ ������ϴ�.", 15);
                    pressAnyKey();
                    return;
                }
                else
                {
                    system("cls");
                    slowPrint("�罿 : \"���� ���� ���� �̾߱Ⱑ �ִ� �� ���׿�...\"", 15);
                    pressAnyKey();
                }
                break;
        }
    }
}

void explainBigBird(void)
{
    system("cls");
    slowPrint("�罿 : \"���� ���Ҵ� ū ���� ���� ħ���ڰ� ������ �����ϱ�� �߾��.\"", 15);
    printf("\n");
    slowPrint("�罿 : \"ū ���� ���� �� ������, �׸��� �ٸ� �̵��� ���� ���ϴ� �ͱ��� �� �� �־��� ��������.\"", 15);
    pressAnyKey();
}

void explainLongBird(void)
{
    system("cls");
    slowPrint("�罿 : \"�� ���� ���� ��ȭ�� ���ؼ� ���� ������ �ڵ��� ���� ���Ը� ������.\"", 15);
    printf("\n");
    slowPrint("�罿 : \"�� ���� õĪ�� ���������ؼ�, ��� ���� ���Ը� �� �� �ְ�,\"", 15);
    printf("\n");
    slowPrint("�罿 : \"� ���� ���Ե� ��Ȧ�� ������ �ʰŵ��.\"", 15);
    pressAnyKey();
}

void explainSmallBird(void)
{
    system("cls");
    slowPrint("�罿 : \"���� ���� �ڽ��� �θ��� ���� �ڵ鿡�� ���� �ֱ�� �߾��.\"", 15);
    printf("\n");
    slowPrint("�罿 : \"���� ���� �θ��� �����ϰ� ��ī�ο��� ��������.\"", 15);
    pressAnyKey();
}


void printOptions_ch3(void)
{
    printf("  1. ������ ã�ư���.\n");
    printf("  2. ���� �������� �� �� ����.\n");
}

void chapterThree(void)
{
    system("cls");
    slowPrint("��� : \"�׷� ������ ���� ��Ű�� ������, ������ �������� �� �ƴѰ���?\"", 15);
    pressAnyKey();
    system("cls");
    slowPrint("�罿 : \"�и� ���� �������� ���������� ������ ���� ������ ���� ����� �ִ� ��ó�� �������\"", 15);
    slowPrint("�罿 : \"�׵��� �����ֽ� �� �����Ű���?\"", 15);
    pressAnyKey();

    system("cls");
    printOptions_ch3();
    printf("\n  ���� > ");
    int choice = getChoice(1, 2, printOptions_ch3);
    printf("%d\n", choice);
    Sleep(1000);

    switch (choice)
    {
        case 1:
            system("cls");
            slowPrint("����� �罿�� ��Ź�� ����ֱ�� �߽��ϴ�.", 15);
            printf("\n");
            slowPrint("�罿 : \"���ƿ�. ��ſ� ���ؼ� �������� �̸� �˷��ѰԿ�\"", 15);
            slowPrint("�罿 : \"������ ���⼭ ���� ���� ������ ã�ư��ּ���\"", 15);
            printf("\n");
            pressAnyKey();
            break;
        case 2:
            system("cls");
            slowPrint("����� �� �̻� ���� �Ͽ� �ָ����� ���� �ʾҽ��ϴ�.", 15);
            slowPrint("�罿���� �ۺ��λ縦 �ϰ�, ������ ���� �������Խ��ϴ�.", 15);
            slowPrint("\n- THE END -", 50);
            playGameOverMelody();
            Sleep(2000);
            exit(0);
            break;
    }
}


void printOptions_ch4(void)
{
    printf("  1. \"�㿡 ������ ���� ������ ���ϵ��� ����ƺ� ��������.\"\n");
    printf("  2. \"���� ������ ������ �¿��� ������ ������ �ʴ� ����� ����� �㿡�� ���� ��Ű�� �� �?\"\n");
    printf("  3. \"�㿡�� ������ ��Ÿ���� ���� �״�, ���� ���� ����� �Ƚɽ�Ų��.\"\n");
}

void chapterFour(void)
{
    int choice;
    system("cls");
    slowPrint("������. ����� ū ���� ���� ã�ư����ϴ�.", 15);
    slowPrint("Ŀ�ٶ� ���� �ε帮�� �ȿ��� Ŀ�ٶ��� ���� ���� �޸� ���� ���Խ��ϴ�", 15);
    printf("\n");
    slowPrint("...", 100);
    printf("\n");
    slowPrint("ū �� : \"�� �罿�� ���� ����� �ʱ���.\"", 15);
    slowPrint("ū �� : \"���� �����ַ� �°ž�?\"", 15);
    printf("\n");
    slowPrint("����� ���� �����̸� ������ ������� ����ҽ��ϴ�.", 15);
    printf("\n");
    slowPrint("ū �� : \"�ֱ� ���� �����ϴٰ� ��� ���� ������ �����µ� �װ� ���� ���鼭  ���߾�\"", 15);
    printf("\n");
    slowPrint("���� ���� : \"��ΰ� ���� įį�� �� �߿� ������ ��Ÿ���� �����?\"", 15);
    printf("\n");
    slowPrint("ū �� : \"������ �㿡 Ȱ���� ���� �ִ°��ݾ�?\"", 15);
    slowPrint("ū �� : \"�׷��� ��� �ؾ� �㿡�� ���� ��ų �� ������ ������̾�\"", 15);
    printf("\n");
    pressAnyKey();

    system("cls");
    slowPrint("����� ū ���� ����� ��� ��� ������ �����ϴ�.", 15);
    printf("\n");
    printOptions_ch4();
    printf("\n  ���� > ");
    choice = getChoice(1, 3, printOptions_ch4);
    printf("%d\n", choice);
    Sleep(1000);

    system("cls");
    switch (choice)
    {
        case 1:
            slowPrint("ū �� : \"����ƺ�? �װ� ���� �����̳�! ���� �������� ����ƺ� ���� ������ �����ϰ� ������ �ž�!\"", 15);
            slowPrint("����� ū ���� �Բ� ����ƺ� ��������ϴ�.", 15);
            break;
        case 2:
            slowPrint("ū �� : \"�� ������ �¿�� ������ ������ �ʴ� ����� ���� �� �ִٰ�??\"", 15);
            slowPrint("��� : \"�� �¾�. ��� ������ ���� �¿��߸���\"", 15);
            slowPrint("����� ū ���� ������ ��� �¿� ������ ������ �ʴ� ����� ������־����ϴ�.", 15);
            printf("\n");
            pressAnyKey();
            animateLamp2s();
            badChoices++;
            break;
        case 3:
            slowPrint("ū �� : \"�㿡�� ������ ��Ÿ���� �ʴ´ٰ�? ������?\"", 15);
            slowPrint("����� ū ������ ������ �ʿ䰡 ���ٰ� ���߽��ϴ�.", 15);
            slowPrint("ū ���� ����� ���� �ϴ� ��������, ���� �Ҿ��� ����� �����־����ϴ�.", 15);
            break;
    }
    pressAnyKey();
}


void printOptions_ch5(void)
{
    printf("  1. \"�θ��� ��ī�ο� ö�� ������.\"\n");
    printf("  2. \"�� ������ ���� �� �ֵ��� ��������.\"\n");
    printf("  3. \"���� ��� ũ�� ������.\"\n");
}

void chapterFive(void)
{
    int choice;
    system("cls");
    slowPrint("����� ���� ���� ������ ã�ư����ϴ�.", 15);
    slowPrint("���� ���� �ݰ��� ���� �ɾ����ϴ�.", 15);
    printf("\n");
    slowPrint("...", 100);
    printf("\n");
    slowPrint("���� �� : \"�罿�� ���� ����� �ʱ���?\"", 15);
    slowPrint("���� �� : \"���� �����ַ� �°ž�?\"", 15);
    printf("\n");
    slowPrint("����� ���� �����̸�, ���� ������ �´ٰ� ����մϴ�.", 15);
    printf("\n");
    slowPrint("���� �� : \"�� ���� �ϴ��� ���ٰ� �ٸ� ������ �� �̾߱⸦ �ϴ� ���� �����\"", 15);
    printf("\n");
    slowPrint("���� : \"���� ���� ���� �ڵ鿡�� ���� �ְڴ�~\"", 15);
    slowPrint("���� : \"������ �� ���� �θ��� �ʹ����� ���׸ż� �ƹ��� �������� �����ž� ����\"", 15);
    printf("\n");
    slowPrint("���� �� : \"�� �θ��� �۴ٴ°��� �˰� �־�\"", 15);
    slowPrint("���� �� : \" ��밡 �������� �߸��� ���ݰ� �Ϸ���, �󸶳� ������ �ؾ� �ұ�?\"", 15);
    pressAnyKey();

    system("cls");
    slowPrint("����� ���� ���� ����� ��� ��� ������ �����ϴ�.", 15);
    printf("\n");
    printOptions_ch5();
    printf("\n  ���� > ");
    choice = getChoice(1, 3, printOptions_ch5);
    printf("%d\n", choice);
    Sleep(1000);

    system("cls");
    switch (choice)
    {
        case 1:
            slowPrint("���� �� : \"�θ��� ��ī�ο� ö�� ����? �װ� ���� �����̳�! ��� ���� �η����ϰ���?\"", 15);
            slowPrint("����� ���� ���� �θ��� ��ī�ο� ö�� �����־����ϴ�.", 15);
            break;
        case 2:
            slowPrint("���� �� : \"���ִ� ����? ����! � ������ �ϸ� ������?\"", 15);
            slowPrint("����� ���� ���� �Բ� ���� �ִ� ������ �߽��ϴ�.", 15);
            break;
        case 3:
            slowPrint("���� �� : \"���� ��� ũ�� �����? �װ� ������ �����Ѱž�?... ��û ���ð� ����\"", 15);
            printf("\n");
            slowPrint("����� ���� ������ �����ٰ� �Ƚɽ��׽��ϴ�.", 15);
            printf("\n");
            slowPrint("����� ���� ���� ����� ���� ���� � ������ �� �Կ� ��ų �� �ֵ��� ũ�� ������־����ϴ�.", 15);
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
    printf("  1. \"����� ������ ������ �ʵ��� �� ������ �˸� �� �� �ֵ��� ����غ���.\"\n");
    printf("  2. \"�׷� ������ �������� ������ ���˰� ������ õĪ�� ������.\"\n");
    printf("  3. \"�ٸ� ������� �˸� �纸��.\"\n");
}

void chapterSix(void)
{
    int choice;
    system("cls");
    slowPrint("����� �� ���� �ִ� ������ ã�ư����ϴ�.", 15);
    slowPrint("�װ����� ���� �ش�� ���� ä, ��� ���η��� �ٸ��� ���� Ŀ�ٶ� õĪ�� ��� �ִ� ���� �־����ϴ�.", 15);
    printf("\n");
    slowPrint("...", 100);
    printf("\n");
    slowPrint("�� �� : \"�� ������? �� ���� ������ �ʾƼ� �װ� ������ �𸣰ھ�\"", 15);
    printf("\n");
    slowPrint("����� �罿�� ���´ٰ� ���ϸ�, �� ���� �����ַ� �Դٰ� ���߽��ϴ�.", 15);
    printf("\n");
    slowPrint("�� �� : \"����? �����ַ�?\"", 15);
    printf("\n");
    slowPrint("����� �׷��ٰ� ����մϴ�.", 15);
    pressAnyKey();
    system("cls");
    slowPrint("�� �� : \"�� ���� ���� �˰Ե� ���ϰ� �׷�����\"", 15);
    printf("\n");
    slowPrint("���� : \"������ ���� ������ ��� �� �����ε� �������� �ʰ� �Ǹ� �����?\"", 15);
    printf("\n");
    slowPrint("�� �� : \"�� ���� ��� �����غ��� �´� ���̴���. �� õĪ���ε� �˸� �� �� ���� ������ ��Ÿ���� ���� ��� �ؾ� �ұ�\"", 15);
    slowPrint("�� �� : \"�׷��� ��� �ؾ� ������ ������̾�\"", 15);
    pressAnyKey();
    system("cls");
    slowPrint("����� �� ���� ����� ��� ��� ������ �����ϴ�.", 15);
    printf("\n");
    printOptions_ch6();
    printf("\n  ���� > ");
    choice = getChoice(1, 3, printOptions_ch6);
    printf("%d\n", choice);
    Sleep(1000);

    system("cls");
    switch (choice)
    {
        case 1:
            slowPrint("�� �� : \"�� ������? ���� ������ ����ϸ� �Ǵ� �ſ�����!\"", 15);
            slowPrint("����� �� ���� �Բ� ���� ���Ը� ��� ������ �߽��ϴ�.", 15);
            break;
        case 2:
            slowPrint("�� �� : \"������ ���˰� ������ ����? �װŶ�� �� �̻� ����� �ʿ䰡 ���ڱ�.\"", 15);
            printf("\n");
            slowPrint("�� �� : \"�����δ� ������ ����� ��Ȯ�ϰ� ��������?\"", 15);
            printf("\n");
            slowPrint("����� �� ���� õ¡�� �����ؼ� ������ ���˰� ��������  �������θ� �������� ������־����ϴ�.", 15);
            printf("\n");
		    pressAnyKey();
            animateScales();
            badChoices++;
            break;
        case 3:
            slowPrint("�� �� : \"�ٸ� �������? �˸� ��� �� ����?\"", 15);
            slowPrint("����� �� ������ �˸� ���ϴ� ���� �ƴ�, �뼭�ϰ� ��ȸ�� �ִ� ����� ���� �����߽��ϴ�.", 15);
            break;
    }
    pressAnyKey();
    system("cls");
}


void printOptions_end1(void)
{
    printf("  1. \"����� ������ ������δ� �� ���� ��Ű�⿡ ���� ������ �ʾ�?\"\n");
}
void printOptions_end2(void)
{
    printf("  1. \"���� ������ ���� �ϳ��� �����ٸ�, ���ݺ��� �ξ� ������ �� �����ž�.\"\n");
}

void endGame(void)
{
    system("cls");
    if (badChoices >= 2)
    {
        int choice;
        printf("\n");
        slowPrint("����� ������ ����� ����� ���ķ�", 15);
        printf("\n");
        slowPrint("��� ���� �ٲ�����ϴ�.", 15);
        printf("\n");
        slowPrint("�� ���� �������� �����ϱ� �����߽��ϴ�.", 15);
        printf("\n");
        slowPrint("������ : \"������ ��ư��� �������� ��� ������ ���� ����\"", 15);
        printf("\n");
        slowPrint("������ : \"ū ���� ���� �ִ� �������� ������ �����ؼ� �� ������ �����ο� �� ����\"", 15);
        printf("\n");
        slowPrint("������ : \"���� ���� ¡���� �ʹ� ������\"", 15);
        printf("\n");
        slowPrint("������ : \"�� ���� ������ ���� �������� �ʾ�\"", 15);
        printf("\n");
        pressAnyKey();
        system("cls");
        slowPrint("������ ȭ�� �����.", 15);
        printf("\n");
        slowPrint("���� : \"�츮�� �� ���� ��Ű���� �̷��� ������ ����ϴµ� ��°�� �츮�� ����ο��� �ƹ��� �˾����� �ʴ°���?\"", 15);
        printf("\n");
        slowPrint("���� ���� ã�ƿ��� �մ��� ���� �پ�������", 15);
        printf("\n");
        slowPrint("���� ���� �������� �� ���� �Ҹ��� ������� ������ ���� �ο��� �Ͼ���ϴ� .", 15);
        printf("\n");
        slowPrint("��� : \"......\"", 15);
        printf("\n");
        slowPrint("���Ѻ��� ����� ���� �������ϴ�.", 15);
        pressAnyKey();

        system("cls");
        printOptions_end1();
        printf("\n\n  ���� > ");
        choice = getChoice(1, 1, printOptions_end1);
        printf("%d\n", choice);
        Sleep(1000);

        pressAnyKey();
        system("cls");
        printOptions_end2();
        printf("\n\n  ���� > ");
        choice = getChoice(1, 1, printOptions_end2);
        printf("%d\n", choice);
        Sleep(1000);

        system("cls");

        slowPrint("����� ���鿡�� ������ ������ ���ְ� ���� �������� ������ �̾�����ϴ�.", 15);
        printf("\n");
        pressAnyKey();
        printf("\n");
        slowPrint("������ �� ����� ������ �޾Ƶ鿴���ϴ�.", 15);
        pressAnyKey();
        printf("\n");
        playBlockGame();
        slowPrint("�� �� �۵� �� �� �ִ� ū ���� ����", 15);
        printf("\n");
        slowPrint(" � ���� �˶� ������ �� �ִ� �� ���� ��,.", 15);
        printf("\n");
        slowPrint("��� ���� �����ų �� �ִ� ���� ���� ���� �ϳ��� �� ����.", 15);
        printf("\n");
        slowPrint("������ ����� ã�ƿԽ��ϴ�..", 15);
    	pressAnyKey();
    	system("cls");
        slowPrint("���� ����� �� �������� �� �����԰� �����ɿ� ����� ������, �� ���� �Ƽ������� �Ǿ����ϴ�.", 15);
        printf("\n");
        slowPrint("�׶�, �Ƽ����� �ӿ��� ������ �Ҹ��ƽ��ϴ�.", 15);
        printf("\n");
        slowPrint(ANSI_RED "���� ������ �ִ�! �˰� ��ο� ������ ũ�� ������ ������ ���!" ANSI_RESET, 25);
        pressAnyKey();
        system("cls");
        slowPrint("������ : \"������ �ִٰ�?\"", 15);
        printf("\n");
        slowPrint("�ϳ��� ������ �� ������ ������ ������ �ѷ��������� �ƹ��� ������ �ʾҾ��", 25);
        printf("\n");
        slowPrint("�������� �� ���� ��ȸ�ϸ� ������ ã�� �����߾��. ������ ���� ���� ū���̴� ���̿���", 25);
        printf("\n");
        slowPrint("������ �ƹ��� �������ϴ�.", 25);
        printf("\n");
        slowPrint("�����鵵, �ؿ� �޵�, ������. ������ ���� �� ������ ���� ���� ���̾����ϴ�.", 25);
        printf("\n");
        slowPrint("�� �ķ� ������ ���� ��ο� �㸸 ��� �Ǿ����ϴ�.", 25);
        printf("\n");
        slowPrint("...", 100);
        printf("\n");
        slowPrint("...", 100);
        printf("\n");
        slowPrint("...", 100);
        printf("\n");
        slowPrint("�ƹ��� ���� �ʴ� ���� ������ ������ ������ ��� �ִٴ� �ҹ��� �鸮�� �ֽ��ϴ�.", 25); 
        printf("\n");
    	playApocalypseMelody();
        Sleep(1000);
        slowPrint("- END : ���� �� -", 50);
    }
    else
    {
        slowPrint("��� ������ ����� �ذ����� ��ſ���, ������ �������� �����߽��ϴ�.", 15);
        slowPrint("ū ���� ���� �����ϸ� ���� ���� ��ȭ�� ��ã�Ұ�, �������� ���� ���� �θ��� �Ͼ����ϴ�.", 15);
        slowPrint("�׸��� �� ���� �� �����ϰ� ���Ƿο� �ǰ��� ���� �� �־����ϴ�.", 15);
        printf("\n");
        slowPrint("����� ���� ��ȭ�� ��ã���� �����ڰ� �Ǿ����ϴ�.", 15);
        slowPrint("��� �������� ����� �̸��� �θ��� �ູ�� ������ ������, ����� ������ ���� �������ϴ�.", 15);
        printf("\n");
        slowPrint("- END : ��ȭ -", 50);
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

/* �� ��� ������ */
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

/* ��� �ִϸ��̼� */
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

/* ���� �ִϸ��̼� */
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
//��Ʈ�� ���� 
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
//�÷��̾ �������� �Ѿ� �� 
void playFallSound(void)
{
    Beep(330, 120);  Sleep(60);
    Beep(294, 100);  Sleep(50);
    Beep(196, 200);  Sleep(80);
    Beep(130, 300);  Sleep(100);
    Beep(98, 500);
}

//�⺻ ���ӿ��� ���� 
void playGameOverMelody(void)
{
    Beep(392, 400);  Sleep(100);  // G4
    Beep(349, 400);  Sleep(100);  // F4
    Beep(330, 450);  Sleep(100);  // E4
    Beep(294, 500);  Sleep(120);  // D4
    Beep(262, 700);               // C4 (����)
}

//������ ���� �� 
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


/* ==== ��� �ױ� �̴ϰ��� �Լ� ==== */
int playBlockGame(void)
{
    int block_order = 0;
    int success_flag = 0;
    int block_stack[box_length * 2 + 1] = {0};
    
    system("cls");
    printf("������ �ϳ��� �������� �ϰ� �ֽ��ϴ�... �ִ��� ���� �׾ƿø�����\n");
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

        // ��� �̵�
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
                    printf("��");
            }
            Sleep(60);

        } while (!kbhit());
        getch();

        // �ٴ� ���� ���
        int max_h = 0;
        for (int i = 0; i < w * 2; i++)
            if (block_stack[temp_x + i] > max_h)
                max_h = block_stack[temp_x + i];

        int target_y = box_height + 2 - max_h - h + 1;

        // ����
        for (int y = 2; y < target_y; y++) {
            for (int i = 0; i < h; i++) {
                gotoxy(temp_x, y + i);
                for (int j = 0; j < w; j++)
                    printf("��");
            }
            Sleep(40);
            for (int i = 0; i < h; i++) {
                gotoxy(temp_x, y + i);
                for (int j = 0; j < w * 2; j++)
                    printf(" ");
            }
        }

        // ���� �� ����
        for (int i = 0; i < h; i++) {
            gotoxy(temp_x, target_y + i);
            for (int j = 0; j < w; j++)
                printf("��");
        }
        for (int i = 0; i < w * 2; i++)
            block_stack[temp_x + i] += h;

        // ���� ���� üũ
        int overall_max = 0;
        for (int i = 0; i < box_length * 2; i++)
            if (block_stack[i] > overall_max)
                overall_max = block_stack[i];

        if (overall_max >= GOAL_HEIGHT) {
            gotoxy(1, box_height + 5);
            printf("�� ������ ������ �� �������� �Ǿ����ϴ�.\n");
            printf("\n");
            success_flag = 1;
            break;
        }
        block_order++;
    }

    if (!success_flag) {
        gotoxy(1, box_height + 5);
        printf("����....\n");
        Sleep(2500);
        printf("\n");
    	printf("������ ������ �����߽��ϴ�...\n");
    	Sleep(1000);
        printf("\n");
    	printf("�׵��� �ϳ��� ���� ���߰�\n");
    	Sleep(1000);
        printf("\n");
    	printf("�� ���� �����鿡�� ���Ѱ�, �ᱹ ���� �������ϴ�.\n");
    	Sleep(1500);
        printf("\n");
        printf("���� ������ ��ȭ�� ã�ƿԽ��ϴ�.\n");
    	Sleep(1500);
        printf("\n");
        slowPrint("- END : ���� ���� -", 50);
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
