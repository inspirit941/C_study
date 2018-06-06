#include <stdio.h>

struct Gameinfo {
    char * name;
    int year;
    int price;
    char *company;

    struct Gameinfo * friendGame; //연관업체 게임
};

int main(void){
struct Gameinfo gameinfo1;
gameinfo1.name = "나도게임";
gameinfo1.year=2017;
gameinfo1.price=50;
gameinfo1.company = "나도회사";

printf("게임 출시정보\n");
printf("%s\n",gameinfo1.name);
printf("%d\n",gameinfo1.year);
printf("%d\n",gameinfo1.price);
printf("%s\n",gameinfo1.company);

struct Gameinfo gameinfo2 = {"너도게임",2017, 100,"너도희사"};
printf("다른게임 출시정보\n");
printf("%s\n",gameinfo2.name);
printf("%d\n",gameinfo2.year);
printf("%d\n",gameinfo2.price);
printf("%s\n",gameinfo2.company);

//구조체 배열
struct Gameinfo gamearray[2]= {
    {"너도게임",2017, 100,"너도희사"},
    {"너도게임2",2017, 100,"너도희사2"}
};
// 구조체 포인터
struct Gameinfo * gamePtr;
gamePtr = &gameinfo1;
printf("게임 출시정보\n");
printf("%s\n",(*gamePtr).name);
printf("%d\n",(*gamePtr).year);
printf("%d\n",(*gamePtr).price);
printf("%s\n",(*gamePtr).company);
// 불-편. 그래서 다른 방식을 쓴다.
// 주소값으로 구조체 데이터를 불러오는 방법.
printf("%s\n",gamePtr->name);
printf("%d\n",gamePtr->year);
printf("%d\n",gamePtr->price);
printf("%s\n",gamePtr->company);

//연관업체 게임
gameinfo1.friendGame = &gameinfo2;
printf("%s\n",gameinfo1.friendGame->name);
printf("%d\n",gameinfo1.friendGame->year);
printf("%d\n",gameinfo1.friendGame->price);
printf("%s\n",gameinfo1.friendGame->company);


// typedef
// 자료형의 이름(별명)을 지정한다.
int i=1;
typedef int a;
a j=3;
// 강의에서는 한글변수 선언도 가능했는데, 내 컴퓨터에서는 한글변수 선언이 안 되던 상태.
printf("%d",j);

typedef struct Gameinfo game;
game game1;
// game1.name = "GG"; // 이런 식으로도 만들 수 있고


// typedef struct Gameinfo {
//     char * name;
//     int year;
//     int price;
//     char *company;

//     struct Gameinfo * friendGame; //연관업체 게임
// } GAME_INFO; //이런 식으로도 처음에 만들 때부터 선언할 수 있다.
    return 0;
}