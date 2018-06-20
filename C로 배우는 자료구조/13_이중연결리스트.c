// 단방향 연결리스트 : 한 방향으로만 노드가 연결되어 있는 것.
// 문제점: 어떤 노드의 앞에 새로운 노드 삽입 / 삭제가 어려움
// 단방향 순회만 가능하다

// 이중연결리스트
// 각각의 노드가 'next'노드와 'previous'노드의 주소를 가지는 연결 리스트
// 양방향 순회(traverse) 가능

//각 노드는 2개의 link field (next, prev)를 가지고 있다.
// 마지막 노드는 next가 null이고, 첫 번째 노드는 prev가 null이다.
// head는 첫 번째 노드의 주소를, tail은 마지막 노드의 주소를 가지고 있다.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct node{
    char *data;
    Node *next;
    Node *prev;
} Node;
Node *head;
Node *tail;
int size =0; // 노드개수


// 특정 노드 앞에 삽입하기
/*
add_node(Node *p){
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = "Sharon";
    new_node->next = p; //새 노드의 next는 p가 된다 (특정 노드 앞에 삽입하는 거니까)
    new_node->prev = p->prev; //새 노드의 prev는 원래 p가 가지고 있던 prev
    p->prev->next = new_node; //원래 p 이전노드의 next는 new_node로 변경
    p->prev = new_node; //p 바로 앞 노드도 new_node로 변경함.
    // 순서가 중요하다!

    // 맨 앞에 삽입, 맨 뒤에 삽입, 특정 노드 사이에 삽입 등등 몇 가지 예외사항은 있음
}
*/

// 노드 삭제하기
// p->prev->next = p->next;
// p->next->prev = p->prev;
// ** 여기서 p는 삭제할 노드를 지칭.
// 그리고 p는 free선언 해줘야 하겠지?
// struct p뿐만 아니라 p 안에 있는 data, prev, next까지 전부

void add_after(Node *pre, char *item){// 예외상황 전부 반영
// 이전 노드값 pre를 받는 것.
    // 노드 생성
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = item;
    new_node->prev = NULL;
    new_node->next = NULL;

// pre 바로 다음에 새 노드 추가하기.
// 1. 노드가 하나도 없는 상황에서 새 노드 만들기
    if (pre==NULL && head ==NULL){// head가 null이라는 건 노드가 하나도 없다는 걸 말함
        head = new_node;
        tail = new_node;
        // 첫번째 노드라면 head나 tail 전부 하나의 노드를 지칭해야 하니까
    }
// 2. 연결리스트 맨 앞에 삽입하는 경우
    else if (pre==NULL){ //pre가 null이라면, 맨 앞에 넣는단 소리다
        new_node->next = head; //new node의 next를 head 노드로.
        head->prev = new_node; //현재 head노드의 prev를 새 노드 주소로
        head = new_node;
    }
// 3. 맨 뒤에 삽입
    else if(pre == tail){
        new_node->prev = tail;
        tail ->next = new_node;
        tail = new_node;
    }
// 4. 특정 노드 사이에 들어가는 경우
    else {
        new_node -> prev = pre;
        new_node -> next = pre->next;
        pre->next->prev = new_node;
        pre->next = new_node;
    }
    size++;//노드 개수의 증가
}

void delete(Node *p){
    //4가지 경우로 나눠 처리한다
    // p가 유일한 노드 -> head tail 둘 다 null
    // p가 head인 경우 -> head는 변화, tail은 그대로
    // p가 tail인 경우 -> head는 그대로, tail은 변화
    // 일반적인 경우 -> 앞뒤 노드만 알아서 처리
    // -> 각각의 경우마다 다름.
    // 실습
}

void add_ordered_list(char *item){
    // 알파벳순으로 정렬되어 있을 때.. 새 아이템 추가? -> 순서에 맞게 삽입
    Node *p = tail;
    while(p!=NULL && strcmp(item, p->data)<0){
        p = p->prev;
    } // 맨 뒤에서부터 앞으로 순회.
    add_after(p,item);
    // 1. 연결리스트가 empty인 경우???? while문 바로 빠져나올 것.
    // head도 tail도 null. -> 첫 번째 노드 생성
    // 2. 맨 뒤에 삽입할 경우

}

// 원형 연결리스트
// 마지막 노드의 다음 노드가 첫번째 노드가 되는 단순 연결리스트
// 원형 이중연결 리스트
// 마지막 노드의 다음 노드가 첫번째 노드가 되고
// 첫 노드의 이전 노드가 마지막 노드가 된다.