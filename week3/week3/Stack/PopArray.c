#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} Stack;

void init(Stack *s) {
    s->top = -1;   // 스택 초기화
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

int pop(Stack *s) {
    if(isEmpty(s)) {
        printf("Stack Underflow!\n");
        return -1;  // 에러 코드
    }
    return s->data[(s->top)--];
}

int main() {
    Stack s;
    init(&s);

    // 테스트용
    s.data[++s.top] = 10;
    s.data[++s.top] = 20;
    s.data[++s.top] = 30;

    printf("Popped %d\n", pop(&s)); // 30
    printf("Popped %d\n", pop(&s)); // 20
    printf("Popped %d\n", pop(&s)); // 10
    printf("Popped %d\n", pop(&s)); // Underflow (-1)
    
    return 0;
}
