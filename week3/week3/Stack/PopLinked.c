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

// pop (연결 리스트 방식)
int pop(Stack *s) {
    if(s->top == NULL) {
        printf("Stack Underflow!\n");
        return -1; // 에러 코드
    }

    Node *temp = s->top;
    int value = temp->data;

    s->top = temp->next;  // top을 다음 노드로 이동
    free(temp);           // 메모리 해제

    return value;
}

// 테스트
int main() {
    Stack s;
    init(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    printf("Popped %d\n", pop(&s)); // 30
    printf("Popped %d\n", pop(&s)); // 20
    printf("Popped %d\n", pop(&s)); // 10
    printf("Popped %d\n", pop(&s)); // Underflow (-1)

    return 0;
}
