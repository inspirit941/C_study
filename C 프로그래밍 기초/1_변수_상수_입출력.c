#include <stdio.h>

int main(void)
{
    printf("hello 안녕 world\n");
    int age2 = 12; //자료형을 앞에 먼저 선언해줘야 함.
    //처음에 한 번만 선언해 주면 그 다음부터는 자료형 선언 안 해도 된다.
    printf("%d\n",age2);
    
    float f = 45.01;
    printf("%.2f\n",f);
    double d = 4.333;
    printf("%f\n",d);
    //아니 float와 double의 차이가 뭔데
    // float는 32bit, double은 64bit

    const int year = 1994;
    printf("%d\n",year);
    
    // 상수 설정하려면 변수 앞에 const로 선언해 주면 된다.

    int add = 3+7;
    printf("3+7 = %d\n",add);
    //작은따옴표 썼을때 오류난 거 보니, 큰따옴표 작은따옴표 구별도 하는 모양임.
    printf("%d + %d = %d\n",3,7,3+7);
    //변수 사용하지 않고도 값을 출력하는 것도 가능하다.

    //scanf : 키보드 입력값을 받아서 저장
    // int input;
    // scanf_s("%d",&input); //숫자값을 받을 거고, 결과는 input에 저장한다.
    // printf("입력값: %d\n",input);
    // 현재 VScode에서는 input값을 받을 수가 없다. 왜인지 모르겠는데 external console이 실행이 안됨.

//문자: 한 글자, 문자열: 한 글자 이상
    char c = 'a'; //작은따옴표
    printf("%c",c); //문자 하나일 때는 %c로 받는다.

    char str[256]; //문자열을 만들겠다는 선언
    // scanf_s("%s",str,sizeof(str));
    // printf("%s",str); //문자열일 때는 %s로 받는다.

    // 프로젝트. 경찰관이 범죄자의 조서를 작성하는 프로그램
    // 받을 내용 - 이름, 나이, 몸무게, 키, 범죄명
    char name[256];
    printf("이름은?\n");
    //scanf_s("%s",name,sizeof(name));
    int age;
    printf("나이는?\n");
    //scanf_s("%d",age);
    float weight;
    printf("몸무게는?\n");
    //scanf_s("%f",weight);
    double height;
    printf("키는 얼마?\n");
    //scanf_s("%f",height);
    char what[256];
    printf("범죄사실은?\n");
    //scanf_s("%s",what,sizeof(what));


    return 0;
}
