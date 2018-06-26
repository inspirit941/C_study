#ifndef QUEUEADT_H
#define QUEUEADT_H

#include <stdbool.h>

typedef int Item; 
//저장되는 타입을 정수로 가정
typedef struct queue_type *Queue;

Queue create();
void destroy(Queue q);
void make_empty(Queue q);
bool is_empty(Queue q);
void enqueue(Queue q, Item i);
Item dequeue(Queue q);
Item peek(Queue q);
int get_size(Queue q);
// 수업에서는 안 쓰지만
// queue를 사용할 경우 현재 queue 안에 데이터가 얼마나 있는지 알아야 한다.
// 스택은 보통 비었나 아닌가만 확인하지만..

#endif