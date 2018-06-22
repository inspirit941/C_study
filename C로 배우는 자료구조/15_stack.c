#include "15_stack.h"
#include <string.h>
#define MAX_CAPACITY 100
// 문자 저장 스택


char stack[MAX_CAPACITY];
int top=-1;
// 하나의 배열 + 어디까지 차 있는지 확인하는 값 top
// 맨 처음에는 top이 비어 있으므로 -1.
// 리스트로 구현하기
void push(char ch){
    if (is_full()){
        printf("Stack is full.\n");
        return;
    }
    top++;
    stack[top]=ch;
}
char pop(){
    if (is_empty()){
        printf("Stack is empty.\n");
        return;
    }
    char tmp = stack[top];
    top--;
    return tmp;
}
char peek(){
    return stack[top];
}
int is_empty(){

    if(top==-1){
        return 0;
    }
    else{
        return 1;
    }
}
int is_full(){
    return top == MAX_CAPACITY -1;
}

// 연결리스트로 만들 때 
// -> 연결리스트 앞부분에 데이터를 삭제할지, 맨 뒤에 삽입할지에 따라 top이 다르다
// 보통은 연결리스트 첫 노드를 top으로 본다. 맨 뒤로 가면 '이전노드 주소값'을 알아야 해서 골치아픔
// add_first, remove_first가 push, pop역할을 한다

typedef struct node{
    char *data;
    struct node *next;
} Node;

Node *top = NULL; // 연결리스트 첫번째 노드 정의

void push2(char *item){
    Node *p = (Node *)malloc(sizeof(Node));
    p->data = item;
    p->next = top;
    top = p;
}
char *pop2(){
    if (is_empty2()){
        printf("Stack is empty.\n");
        return NULL;
    }
    Node *p = top;
    char *result = p->data; //top 넣으면 오류나는데, 이걸 어떻게 처리하나?
    top = p->next;
    free(p);
    return result;
}
char *peek2(){
    if (is_empty2()){
        return NULL;
    }
    Node *p = top;
    return p->data;
}
int is_empty2(){
    return top==NULL;
}

// 지금까지의 문제점: 만약 스택이 동시에 2개 이상 필요하다면?
// 배열이 두 개라면, 함수도 2개가 필요하다 (stack[top]이런 식으로 설계했기 때문)
// = 비 효 율

// 서로 다른 타입의 데이터를 저장할 스택이 필요하면??
// 함수 설계 시 받을 변수에 stack을 넣어야 할 듯.