#include <stdio.h>
#include <stdlib.h>

// 노드 정의
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// 스택 정의
typedef struct {
    Node *top;
} Stack;

// 스택 초기화
void init(Stack *s) {
    s->top = NULL;
}

// push (연결 리스트 방식)
void push(Stack *s, int value) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if(newNode == NULL) {
        printf("메모리 할당 실패!\n");
        return;
    }
    newNode->data = value;
    newNode->next = s->top;  // 현재 top과 연결
    s->top = newNode;        // 새 노드가 top이 됨
    printf("Pushed %d\n", value);
}

// 테스트
int main() {
    Stack s;
    init(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    return 0;
}
