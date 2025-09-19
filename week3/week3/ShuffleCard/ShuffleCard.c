#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct trump {
    char shape[10];    // 모양 (UTF-8 문자 고려해서 여유 있게)
    char number[3];    // 숫자/문자 ("A", "2", ..., "10", "J", "Q", "K")
};

void make_card(struct trump m_card[]);
void display_card(struct trump m_card[]);
void shuffle_card(struct trump m_card[]);

int main(void)
{
    struct trump card[52];
    make_card(card);
    shuffle_card(card);
    display_card(card);
    return 0;
}

void make_card(struct trump m_card[])
{
    int i, j;
    char shape[4][10] = {"♠", "◆", "♥", "♣"};
    char *numbers[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
    int idx = 0;

    for(i=0; i<4; i++)   // 모양 4개
    {
        for(j=0; j<13; j++)  // 숫자 13개
        {
            strcpy(m_card[idx].shape, shape[i]);
            strcpy(m_card[idx].number, numbers[j]);
            idx++;
        }
    }
}

void shuffle_card(struct trump m_card[])
{
    int i, rnd;
    struct trump temp;
    srand(time(NULL));    // 난수 초기화

    for(i=0; i<52; i++)
    {
        rnd = rand() % 52;
        temp = m_card[rnd];
        m_card[rnd] = m_card[i];
        m_card[i] = temp;
    }
}

void display_card(struct trump m_card[])
{
    int i;
    for(i=0; i<52; i++)
    {
        printf("%s%-2s  ", m_card[i].shape, m_card[i].number);
        if((i+1) % 13 == 0)   // 13장마다 줄바꿈
            printf("\n");
    }
}
