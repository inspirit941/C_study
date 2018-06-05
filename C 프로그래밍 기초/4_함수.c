#include <stdio.h>

//함수 선언은 main함수 위에서 한다.
void p(int num); //p는 함수명. 받게될 변수는 int num

// 함수의 종류
// 1.반환값이 없는 함수
void function_without_return();
// 2. 반환값이 있는 함수
int function_with_return();
// 3. 전달값이 없는 함수(parameter가 없는 함수)
void function_without_params();
// 4. 전달값이 있는 함수
void function_with_parmas(int num1, int num2, int num3);
// 5. 전달값도 받고 반환값도 주는 함수
int apple(int total, int eat);

int main(void){
// +=, -=, *=, /= 연산이 가능하다.

int num = 2;
p(num);
function_without_return();

//반환값이 있는 함수를 쓰려면 함수 결과를 반환값 형식에 맞게 설정해줘야 한다.
int ret = function_with_return();
p(ret); //출력
function_without_params();

function_with_params(1,2,3);
int rest = apple(5,2);
printf("%d",rest);




    return 0;
}

//함수 정의는 main함수 아래에.
void p(int num){
    printf("num은 %d입니다.\n",num);
}
void function_without_return(){
    printf("반환값이 없는 함수\n");
}
int function_with_return(){
    printf("반환값이 있는 함수\n");
    return 10;
}
void function_without_params(){
    printf("전달값이 없는 함수입니다\n");
}

void function_with_params(int num1, int num2, int num3){
    printf("params가 있는 함수이며, 값은 %d, %d, %d입니다.\n", num1, num2, num3);
}

//반환형 함수이름 (전달값) 형태로 구성됨.
//반환형: 보내주는 자료형에 맞춰준다.
/* int 함수이름(num){
    return num+4;
    }
만약 아무것도 반환하고 싶지 않을 경우 void를 쓴다.
void는 아무것도 반환하지 않는다는 의미.
전달값에도 어떤 자료형을 받을 것인지 정할 수 있고,
여러 가지 종류의 전달값을 받을 수 있다.
선언은 main 위에, 적용은 main 아래에.    
*/

int apple(int total, int eat){
    printf("전달값과 반환값이 있는 함수\n");
    return total - eat;
}

//마지막 강의에서, 난이도 높아지는 함수 만들기
/* int getRandomNumber(int level){
    return rand() % (level*7)+1;
}
\t는 스페이스바 8번(tab)을 의미함.

*/

