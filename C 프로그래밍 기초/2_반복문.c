#include <stdio.h>

int main(void)
{
    // 1에서 main이 정의되어 있기에 문제가 생김.
    // 이전에 만든 파일에서 main 이름을 바꿔야 함.
    //반복문의 종류는 for, while, do while문이 있다.
    
    //++ 
    int a=10;
    printf("a는 %d\n",a);
    a++;
    printf("a는 %d\n",a);
    
    int b=20;
    printf("b는 %d\n",++b);
    printf("b는 %d\n",b++);
    printf("b는 %d\n",b);
    //b 앞에 ++이면 문장에서 ++을 먼저 수행하고 문장을 끝내라
    //b 뒤에 ++이면 문장을 수행하고 나서 ++연산을 수행하라

    //반복문
    //for while do while
    // for 선언;조건;증감
    for (int i=1; i<=10; i++)
    {
        printf("hello world %d\n",i);
    }

    //while 조건
    int i=1;
    while (i<=10)
    {
        printf("hello world \n",i++);
    }
    // do {} while 조건
    int j=1;
    do {
        printf("hello world \n",j++);
    } while (j<=10);

    // 이중 반복문
    for (int i=1; i<=10;i++)
    {
        printf("첫 번째 반복문\n",i);
        for (int j=1;j<=5;j++)
        {
            printf("두 번째 반복문\n",j);
        }
    }
// 왼쪽 정렬 트리
    for (int i=0; i<5; i++)
    {
        for (int j=0; j<=i; j++)
        {
            printf("*");
        }
        printf("\n");
    }
// 오른쪽 정렬 트리
    for (int i=0; i<5; i++)
    {
        for(int j=i; j<5-1; j++){
            printf("S");
        }
        for (int k=0; k<=i; k++){
            printf("*");
        }
        printf("\n");
    }

// 피라미드 쌓기프로젝트
int floor = 10;
printf("몇 층으로 쌓을 것인지?");
// scanf_s("%d",&floor);
for(int i=0; i<floor; i++){
    for (int j=i; j<floor-1;j++){
        printf("S");
    }
    for (int k=0; k<i*2-1; k++){
        printf("*");
    }
    printf("\n");
}
    return 0;
}