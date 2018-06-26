#include <stdio.h>
#include <stdlib.h>
#include "17_queueADT.h"

#define INIT_CAPACITY 100

struct queue_type{
    Item *contents; //배열 <- 포인터 선언했다는 건, 이 배열도 동적메모리 할당으로 받는다는 의미
    int front;
    int rear;
    int size;   //저장된 데이터 개수
    int capacity; //배열 content의 크기
};

void terminate(const char *message){
    printf("%s\n",message);
    exit(1);
}
int get_size(Queue q){
    return q->size;
}

Queue create(){
    Queue q = (Queue)malloc(sizeof(struct queue_type));
    // 여기는 왜 Queue *포인터 형태로 받지 않는가?
    if (q==NULL){
        terminate("Error in create: queue could not be created.");
    }
    q->contents = (Item *)malloc(INIT_CAPACITY*sizeof(Item));
    if (q->contents==NULL){
        free(q);
        terminate("Error in create: queue could not be created.");
    }
    q->front=0;
    q->rear = -1; // 초기값이 왜 0과 -1인지는 코드 아래에 나온다.
    q->size = 0;
    q->capacity = INIT_CAPACITY;
    return q;
}
void destroy(Queue q){
    free(q->contents);
    free(q);
}
void make_empty(Queue q){
    q->front = 0;
    q->rear = -1;
    q->size =0;
}
bool is_empty(Queue q){
    return q->size==0;
}
bool is_full(Queue q){
    return q->size ==q->capacity;
}
void enqueue(Queue q, Item i){
    if (is_full(q)){
        reallocate(q);
    }
    q->rear = (q->rear+1) % q->capacity;
    // 만약 rear에서 한 번 더 더했더니 더 이상 배열이 없다면? -> 맨 처음으로 돌아가야 함
    // 그걸 해결하는 코드가 위의 한 줄.
    // = > rear+1을 capacity로 나눈 나머지를 계산한다.

    // circular 로직을 구현할 때는 나머지 연산을 쓴다. 기억해두기.
    q->contents[q->rear]=i;
    q->size++;
}
Item dequeue(Queue q){
    if (is_empty(q)){
        terminate("Error in dequeue: queue is empty.");
    }
    // front도 마찬가지로, front로 쭉 진행하다가 맨 뒤까지 도달하면,
    // 다시 맨 앞으로 돌아가야 한다.
    Item result = q->contents[q->front];
    q->front = (q->front+1) % q->capacity;
    q->size--;
    return result;
}
Item peek(Queue q){
    if (is_empty(q)){
        terminate("Error in peek: queue is empty.");
    }
    return q->contents[q->front];
}
void reallocate(Queue q){
    Item *tmp = (Item *)malloc(2*q->capacity * sizeof(Item));
    if (tmp==NULL){
        terminate("Error in create: queue could not be expanded.");
    }
    int j = q->front;
    // front와 rear가 배열을 순환하다보면 바뀔 수 있다.
    // 따라서 맨 앞 인덱스부터 넣으면 배열 순서가 깨진다
    for (int i=0;i<q->size;i++){
        tmp[i] = q->contents[j];
        j=(j+1)&q->capacity;
    }
    free (q->contents);
    q->front = 0;
    q->rear = q->size -1;
    q->contents = tmp;
    q->capacity *=2;
}
