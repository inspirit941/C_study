//미로찾기 로직은 보통
// recursion, stack, queue로 해결한다.
// recursion과 stack은 DFS방식이다.
// 깊이 우선 탐색

// 반면 queue는 Breadth First search -> 넓이우선탐색 방식이다

// DFS - 깊이 우선: 한 방향으로 끝까지 들어갔다가
// 더 이상 갈 곳이 없으면 되돌아나오는 방식

// BFS - 출발점에서 한 칸 떨어진 지점씩 전부 탐색
// 그렇게 출구 나올 때까지 간다.

// 출발지점 L0
/*
L1 = L0에서 한번에 갈 수 있는 모든 셀
L2 = L1에서 한번에 갈 수 있는 모든 셀 중 L0에 속하지 않는 셀
...

이 경우, 입구에서 출구까지 가는 가장 짧은 경로를 찾을 수 있다.
DFS의 경우, 최단경로를 보장하는 결과가 아님.
*/
/*
너비 우선 탐색으로 미로찾기
1. 하나의 큐를 만든다
2. 위치 (0,0)은 이미 방문한 위치임을 표시하고, 큐에 위치 (0,0)을 넣는다
3. 큐가 빌 때까지 다음을 반복한다
    큐에서 하나의 위치 p를 꺼낸다
    p에서 한 칸 떨어진 위치들 중 이동가능하면서 아직 방문하지 않은 모든 위치를
    방문된 위치임을 표시하고 큐에 넣는다.
    만약 그 위치가 출구라면 종료한다.
즉 queue는 두 개임. 방문할 queue를 담는 거 하나,
방문한 값을 넣는 queue 하나.
방문할 queue를 꺼내고, 거기서 갈 수 있는 모든 좌표를 방문할 queue에 넣고
꺼낸 값은 방문한 queue에 넣는다.
*/
// 너비우선 탐색 핵심 알고리즘
#include <stdio.h>
#include <stdlib.h>
#include "17_queueADT.h"

Queue queue = create_queue();
Position cur; // 현재 내가 서 있는 위치
cur.x = 0; 
cur.y = 0; //출발점 (0,0)

enqueue(queue, cur); //출발점을 queue에 넣고 시작한다.
maze[0][0] = -1 // 추가배열을 쓰지 않기 위해 방문표시를 음수로 저장한다.
bool found = false;

while(!is_empty(queue)){
    Position cur = dequeue(queue);
    for (int dir=0; dir<4;dir++){ //동서남북 네 개라서 <4인듯
        if (movable(cur,dir)){ // 이동할 수 있는 함수인지 (벽 제외, 이미 간 지점 제외)
            Position p = move_to(cur, dir);
            maze[p.x][p.y] = maze[cur.x][cur.y] -1; //방문 표시를 음수로 저장한다.
            if (p.x==n-1 && p.y ==n-1){
                printf("Found the path.\n");
                found = true;
                break;
            }
            enqueue(queue, p);
        }

    }
}
// 방문했다는 표시는 전부 음수로, 못 가는 벽은 1로, 아직 안 간 지점은 0으로 설정함



// 큐의 변형?
/*
Deque : 양쪽 끝에서 삽입과 삭제가 가능한 큐. 덱 or 디큐로 읽는다
priority queue : 큐에 들어온 순서와 무관하게 큐에 저장된 값 중 가장 큰/작은 값이 가장 먼저 꺼내지는 큐
대표적인 구현 방법으로는 이진 힙(binary heap)이 있음.
*/