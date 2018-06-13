// 프롬프트 출력, 사용자 입력을 받는다
// 1. add 이름 전화번호
// 엔터 치면 '이름 was added successfully' 출력
// 2. find 이름
// 이름이 있으면 전화번호 출력, 없으면 no person named 이름 exists.
// 3. status
// 현재 전화번호부에 저장된 모든 사람 출력
// 출력 후 'total 몇 명인지'
// 4. delete 이름
// 없으면 없다고 피드백, 있으면 지운다
// 5. 지운 다음에 status 입력하면 지운 사람은 저장되지 않는다.
// 6. exit 입력하면 프로그램 종료
#include <stdio.h>
#include <string.h>

#define CAPACITY 100
#define BUFFER_SIZE 20

// 프로그래밍에서 가장 먼저 생각할 것이 자료구조.
// 프로그램에서 저장되고 사용되는 데이터를 어떻게 저장하고 쓸 것인가
/* 1. 이 프로그램은 어떤 데이터를 보관해야 하는가
-> name과 number가 필요.
  name과 number 각각 배열 사용.
  배열: 동일한 타입 데이터가 여러 개 있을 때 그걸 보관하는 가장 기본 타입.
  name과 number 배열 index가 같으면 동일한 사람이도록.
*/

char * names[CAPACITY]; // 사람이름 = 문자열, 문자를 받는 배열이므로 char
char * numbers[CAPACITY]; // 생긴 건 숫자이지만, 숫자처럼 다루면 프로그램에서 맨 앞 0을 지워버리는 등의 문제 발생
// 문자열의 맨 끝에는 \0 들어가는것 잊지 말기
int n = 0; // number of people in 전화번호부

void add();
void find();
void status();
void delete();

int main(){
    char command[BUFFER_SIZE];
    while(1){
        printf("$ ");
        scanf("%s",command);
        if (strcmp(command,"add")==0){ //strcmp는 두 문자열이 동일하면 0을 반환한다. string compare
            add();
        }else if (strcmp(command,"find")==0){
            find();
        }else if (strcmp(command, "status")==0){
            status();
        }else if (strcmp(command,"delete")==0){
            delete();
        }else if (strcmp(command,"exit")==0){
            break;
        }
    }

    return 0;
}

void add(){
    char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
    scanf("%s", buf1);
    scanf("%s", buf2);
    names[n]=strdup(buf1);
    numbers[n]=strdup(buf2);
    // strdup와 strcpy 차이를 앞에서 설명했었다.
    // strdup는 string.h가 제공하는 라이브러리.
    // 배열을 만들고, 매개변수로 받은 하나의 문자열을 만든 배열에 복사하고 그 배열의 주소값을 반환한다.
    // buf1과 buf2는 지역변수. 따라서 함수 실행이 종료되면 이 배열은 사라진다.
    // 그런데 만약 names나 numbers가 이 지역변수의 주소값을 받으면,
    // 함수가 끝나면 buf1,2의 배열이 사라지기 때문에 names나 numbers에도 아무것도 남지 않는다.
    // 따라서 strdup으로 buf1과 2의 값을 저장하는 배열(예컨대 temp)을 따로 생성하고
    // name과 number는 temp의 주소값을 지정하는 식이다.

    // C언어에서 메모리 형태
    /* 
    
    1. 전역변수 -> 프로그램 종료될 때까지 메모리 유지. Data section이라 부르는 영역에 저장
    2. 지역변수 -> 함수 호출될 때에만 메모리 할당, return될 때 소멸. stack이라 부르는 영역에 위치.
    3. 동적 메모리 할당 -> malloc 호출로 필요한 크기의 메모리만 할당. heap이라 부르는 영역에 저장.
       *** 동적으로 할당된 메모리는 명시적으로 free()를 호출해 반환하지 않는 이상 계속 유지된다.
        즉, 동적메모리로 할당받은 메모리는 함수 안에서 호출되었다 해도 함수가 끝난 뒤에도 살아남아 있다.
        (메모리의 주소를 잊어버리지 않는 한..) 동적메모리 할당이 필요없어지면 free()함수로 반환한다.
    stack의 크기는 일정하지 않고 계속 변한다.
    data section과 code 영역은 크기가 바뀌지 않는다.
    heap도 마찬가지로 크기가 계속 변한다.
    */
    n++;
    printf("%s was added successfully.\n",buf1);
}
void find(){ //이름을 받고 전화번호를 찾는 기능.
    char buf[BUFFER_SIZE];
    scanf("%s",buf);

    int i;
    for (i=0; i<n; i++){
        if (strcmp(buf, names[i])==0){
            printf("%s\n", numbers[i]);
            return;
        }
    }
    printf("No person named '%s exists.\n",buf);
}
void status(){
    int i;
    for (i=0; i<n; i++){
        printf("%s %s\n",names[i],numbers[i]);
    printf("Total %d persons.\n",n);
    }
}
void delete(){
    char buf[BUFFER_SIZE];
    scanf("%s",buf);

    int i;
    for(i=0;i<n;i++){
        if (strcmp(buf, names[i])==0){ // 삭제할 사람을 찾았다면 아래 일을 시행한다.
            names[i] = names[n-1]; //맨 마지막 사람을 삭제된 자리로 옮겨놓는다.
            numbers[i] = numbers[n-1];
            n--;
            printf("'%s' was deleted successfully. \n",buf);
            return;
            // 누군가를 삭제한 자리를 빈칸으로 두면, status 함수값에 오류가 생김.
        }
    }
    printf("No person named '%s' exists.\n",buf);

}