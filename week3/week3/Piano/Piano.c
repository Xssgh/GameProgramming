#include <windows.h>
#include <stdio.h>

// 음계 정의 (4옥타브, 5옥타브 혼합)
#define C4 262
#define D4 294
#define E4 330
#define F4 349
#define G4 392
#define A4 440
#define B4 494
#define C5 523

int main() {
    // "학교 종이 땡땡땡" 멜로디
    int melody[] = {
        C4, C4, G4, G4, A4, A4, G4,   // 학교 종이 땡땡땡
        F4, F4, E4, E4, D4, D4, C4    // 어서 모이자
    };

    // 각 음의 길이 (ms)
    int duration[] = {
        500, 500, 500, 500, 500, 500, 1000,
        500, 500, 500, 500, 500, 500, 1000
    };

    int length = sizeof(melody) / sizeof(melody[0]);

    for(int i=0; i<length; i++) {
        Beep(melody[i], duration[i]); // 음 재생
        Sleep(50); // 음과 음 사이 간격
    }

    return 0;
}
