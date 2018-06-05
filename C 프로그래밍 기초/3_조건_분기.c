#include <stdio.h>
#include <time.h>

int main(void){
//조건|분기. if else, continue, break, switch를 다룬다
// if (조건) {} else if(조건) {} else {}
int age=12;
if (age>=20){
    printf("성인입니다.");
}
else if( age >=8 && age <=13){
    printf("청소년입니다.");
}
else{
    printf("학생입니다.");
}
//break, continue

for (int i=1; i<=30;i++){
    if (i>=6){
        printf("나머지 학생은 집에 가세요.\n");
        break;
    }
    printf("%d번 학생은 조별발표 준비를 하세요.\n",i);
    
}
for(int i=1; i<=30;i++){
    if (i>=6 && i<=10){
        if (i==7){
            printf("%d번은 결석입니다.\n",i);
            continue;
        }
        printf("%d번은 발표준비하세요.\n",i);
    }
    
}

// and = &&, or = ||

//가위바위보
srand(time(NULL));
//랜덤 수를 뽑는 명령어라고 함.
//정확히는 '난수 초기회 명령어'라고. 
//rand()함수를 실행하기 전 어느 위치에서건 한 번 선언해줘야 함.
int i = rand() %3;
if (i==0){
    printf("가위\n");
}else if (i==1){
    printf("바위\n");
}else if (i==2){
    printf("보\n");
}else{
    printf("알 수 없음\n");
}
//switch (값) { case 가위: case 바위: case 보: default:} 형태로도 만들 수 있다.
//위의 if문과 비슷하지만 완벽히 같지는 않다.

// switch문에는 break를 넣지 않으면, 조건 아래에 있는 모든 값은 전부 다 실행하도록 돼 있음
// 이를테면 case 1이 충족되면, case 1의 반환값인 바위가 출력된 후
// 보, 알 수 없음 두 개도 그냥 다 출력된다는 소리
// 조건이 만족되면, 그 아래 있는 값이 전부 반환된다. 따라서 break를 넣어줘야 함

switch(i){
    case 0:printf("가위\n"); break;
    case 1:printf("바위\n"); break;
    case 2:printf("보\n"); break;
    default: printf("알 수 없음\n"); break;
}


//up and down 프로젝트
// srand(time(NULL));
// int num = rand() % 100 + 1;
// printf("%d\n",num);
// int answer = 0;
// int chance = 0;
// while (1){
//     printf("남은 기회 %d번\n",chance--);
//     printf("숫자를 맞춰보세요(1~100)");
//     // scanf_s("%d",&answer);
//     if (answer >num){
//         printf("down\n");
//     }else if (answer<num){
//         printf("up\n");
//     }else if (answer ==num){
//         printf("정답\n");
//     }else{
//         printf("알 수 없는 오류 발생\n");
//     }
//     if (chance==0){
//         printf("기회 소멸\n");
//         break;
//     }
// } 
    return 0;
}
