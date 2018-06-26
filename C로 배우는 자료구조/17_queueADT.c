#include <stdio.h>
#include <stdlib.h>
#include "17_queueADT.h"

struct node {
    Item data;
    struct node *next;
};

struct queue_type{
    struct node *front;
    struct node *rear;
    int size;
};

void terminate(const char *message){
    printf("%s\n",message);
    exit(EXIT_FAILURE);
}
int get_size(Queue q){
    return q->size;
}

Queue create(){
    Queue q = (Queue)malloc(sizeof(struct queue_type));
    // 여기는 왜 Queue *포인터 형태로 받지 않는가?
    if (q == NULL){
        terminate("Error in create: queue could not be created.");
    }
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}
void destroy(Queue q){
    make_empty(q);
    free(q);
}
void make_empty(Queue q){
    while (!is_empty(q)){
        dequeue(q);
    }
    q->size=0;
}

bool is_empty(Queue q){
    return q->front == NULL;
    // 또는 q->size ==0; 을 해도 된다
}
void enqueue(Queue q, Item i){
    struct node *new_node = malloc(sizeof(struct node));
    if (new_node ==NULL){
        terminate("Error in push :queue is full.");
    }
    new_node -> data = i;
    new_node -> next = NULL;
    if(q->front==NULL){ // queue에 아무 것도 없었을 경우
        q->front = new_node;
        q->rear = new_node;
    }
    else{
        q->rear->next=new_node;
        // q->rear는 가장 마지막에 들어온 데이터를 의미한다.
        // 따라서 원래 있던 near는 next가 null이었을 텐데, 뒤에 새 노드가 붙었으므로
        // q->rear->next 영역에 new_node 주소를 넣어준다
        q->rear = new_node;
        // 그리고 q->rear = 맨 마지막 부분을 new_node로 업데이트해준다.
    }
    q->size++;
}
Item dequeue(Queue q){
    struct node *old_front;
    Item i;
    if(is_empty(q)){
        terminate("Error in dequeue: queue is empty.");
    }
    old_front = q->front; //q의 front주소값을 old_front로 옮긴다.
    i = old_front->data; // 데이터를 i 변수에 저장
    q->front = old_front -> next; 
    // old_front 다음에 연결되어 있던 노드 주소를
    // q->front로 옮긴다. 즉 old_front는 더 이상 queue에 연결되어 있지 않다
    if (q->front == NULL){
        q->rear ==NULL;
    }// 만약 front에 아무것도 업다면, 방금 빼낸 old_front가 마지막이었단 소리
    // 따라서 rear도 null로 바꿔준다
    free(old_front); //노드 주소를 지운다
    q->size--; 
    return i; //지운 노드에 들어가 있던 데이터를 반환한다.
}
Item peek(Queue q){
    if (is_empty(q)){
        terminate("Error in peek: queue is empty.");
    }
    return q->front->data;
    // q의 맨 앞 데이터를 반환한다.
}