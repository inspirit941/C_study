// 배열 재할당 (공간이 모자랄 때 배열크기 올리는 것)
// 라인 단위 입력과 문자열 tokenizing

// 1. read, save 등의 명령어 뒤에 데이터파일 이름을 주지 않으면 오류 반환
//  -> 사용자가 enter를 누르면 라인을 통째로 읽고, 그 라인을 분석해서 올바른 명령어인지 아닌지 판별하도록 수정.
// 배열 용량 초과 시 동적메모리 할당으로 크기 키우기.

// 2. 문자열 tokenize ... delimiter를 설정한다는 소리. (긴 문자열을 잘라내는 기준)
// delimiter를 기준으로 잘려진 문자를 각각 token이라고 부른다.
// C언어에서는 strtok 함수를 쓴다.

// strtok에서는 구분자가 중복나열된 경우 하나로 인식한다.
// ex) delim[] = "#"이고 잘라낼 문자열이 'a # b ### c'라면
//      a / b / c/로 잘라낸다는 소리

/*
delim[] = "#"
char *token;
token = strtok(str, delim)
token은 str 문자열을 토크나이징 했을 때 나오는 첫 번째 문자열의 주소를 반환한다.
더 이상 문자열이 없으면 NULL을 return함.

strtok에서 논란이 되는 부분 중 하나가

while (token!=NULL){
    printf("next token is %s:%d\n",token, strlen(token));
    token = strtok(NULL, delim);
    token의 재정의가 필요함.
    여기서 정의된 token은 delim으로 잘라낸 나머지 문자 맨 앞을 의미한다고.
    "a # b ### c"를 잘라낸 경우
    'a '잘라낸 나머지 문자열 ' b ### c'에서 b 앞의 공백을 지정하는 명령어라고 한다.
    즉 다음 문자열 시작점을 지정하는 token 정의가 필요함.
}

좀 더 정확히 말하면
" time   to  start\0"라는 문자열이 있을 때
strtok를 쓰면 맨 앞 공백은 제외하고 time~~~의 맨 앞 글자 t의 주소값이 token이 됨.
그리고 다음 delimiter가 등장하면, 그 앞에 \0를 붙여서 문자열을 잘라내는 방식임.
예컨대 token = strtok(str,delim);을 했다는 건, time\0을 하나 만든 것.

그 다음 token = strtok(NULL,delim);을 해서
잘라내고 남은 문자열 중 delim이 아닌 문자 첫번째 주소값을 반환하게 함.
(즉 그 다음 주소값을 반환하며 \0를 다시 삽입하는 과정 반복.)

*** strtok은 원본 문자열을 변환시킨다. (\0를 삽입하기 때문)
따라서 원본 문자열이 보존되어야 한다면 복사한 후 strtok을 해야 함

strtok은 새로운 배열을 생성하는 게 아니다.
즉 strdup과는 다르다.

cf. 겹따옴표로 정의된 게 string literal.
문자 배열(str[])의 값은 수정이 가능하지만 string literal(*str)은 수정이 불가능하다.
만약 문자열을 *str로 정의하면, 해당 문자열은 수정이 불가능하기에 strtok이 오류난것.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INIT_CAPACITY 3 //배열 재할당 테스트를 위해 일부러 작은 값으로
#define BUFFER_SIZE 50

char ** names; // char * 타입 배열의 이름이므로 char ** 타입의 변수이다.
char ** numbers; // 동적메모리 할당을 위해서는 배열로 설정하는 게 아니라 포인터로 설정해야 함.
void init_directory();

/*char *str; simply declares a pointer 
with no memory allocated to it, 
whereas char str[10]; 
allocates an array of 10 chars on the local stack. 

The local array will disappear once it goes out of scope though, 
which is why if you want to return a string from a function,
you want to use a pointer with dynamically allocated (malloc'd) memory.

Also, char *str = "Some string constant"; is also a pointer to a string constant. 
String constants are stored in the global data section of your compiled program 
and can't be modified. 
You don't have to allocate memory for them 
because they're compiled/hardcoded into your program, 
so they already take up memory.


char **x is a pointer to a pointer, which is useful 
when you want to modify an existing pointer outside of its scope

이해한 대로 비유하자면
char str[10]은 모래바닥에 글 쓰는 것과 같다. 함수 안에서만 작동하고, 함수 끝나면 지워버림.
char *str = '문자'는 바위에 글 쓴 것과 같다. 한 번 선언하면 수정 불가능.
char **str은 *str에 쓴 내용을 불변하는 게 아니라 가변하게 만들고 싶을 때 선언.
*/

int capacity = INIT_CAPACITY; // array 사이즈
int n=0; // 전화번호부 사람 수

char delim[] =" ";
int main(){
    init_directory(); // 배열 name과 number 선언
    process_command(); // 사용자의 명령을 받아 처리하는 부분을 별개의 함수로 변경

    return 0;
}

void init_directory(){
    names = (char **)malloc(INIT_CAPACITY * sizeof(char *));
    numbers = (char **)malloc(INIT_CAPACITY  * sizeof(char *));
    // 동적메모리 할당으로 받는다. 하나의 char가 몇 바이트인지는 시스템마다 다르므로.
    // 호환성을 맞추기 위해.
    // 우리의 경우 배열 각 칸에 캐릭터 포인터를 저장할 것이므로, 배열 한 칸의 사이즈가 sizeof(char *)가 되는 것임.
}
int read_line(char str[], int limit){ // 배열 str의 크기. limit보다 긴 line의 경우 뒷부분이 짤린다.
    int ch, i = 0;
    //line 단위로 입력받는 건 fgets, getline이 있긴 하지만
    // 보통 c 프로그래머는 자기가 알아서 함수를 만들어 쓴다.
    while (ch = getchar()!= '\n'){ //줄바꿈 문자가 나오기 전까지 읽는다.
    
    // ch는 한 문자를 입력받지만, 희한하게도 선언은 int로 해야 한다. 이유는 설명하지 않았음
        if (i<limit-1){ // 배열의 용량을 초과하지 않을 때만 저장한다.
            str[i++] = ch;
        }
    str[i] = '\0'; //마지막에 null character 추가하기.
    return i; //실제로 읽은 문자 수를 반환한다.
    }
}
void process_command(){
    char command_line[BUFFER_SIZE]; //라인 하나 통째로 읽어오기
    char *command, *argument1, *argument2;

    while (1){
        printf("$ ");
        if (read_line(command_line, BUFFER_SIZE)<=0){
            continue;
        }
        command = strtok(command_line, delim); //command에 strtok를 넣을 수 있는 이유는
        // command에 들어가 있는 건 string literl이 아니라 문자배열이기 때문
        // 즉 *command = "문자"일 경우 수정이 불가능하지만
        // 지금은 *command에 str[] 형태의 문자 배열이 입력된 것.

        // if (command ==NULL) continue; 없어도 됨 이건.
        if (strcmp(command,"read")==0){
            argument1 = strtok(NULL,delim);
            if (argument1 == NULL){
                printf("file name required.\n");
                continue;
            }
            load(argument1);
        }else if(strcmp(command,"add")==0){
            argument1 = strtok(NULL,delim);
            argument2 = strtok(NULL, delim);
            if (argument1 ==NULL || argument2 ==NULL){
                printf("Invalid arguments.\n");
                continue;
            }
            add(argument1,argument2);
            printf("%s was added successfully.\n",argument1);
        } else if(strcmp(command,"find")==0){
            argument1 = strtok(NULL, delim);
            if (argument1 ==NULL){
                printf("Invalid arguments.\n");
                continue;
            }
            find(argument1);
        } else if (strcmp(command, "find")==0){
            argument1 = strtok(NULL, delim);
            if (argument1 ==NULL){
                printf("Invalid arguments.\n");
                continue;
            }
            find(argument1);
        } else if (strcmp(command, "status")==0){
            status();
        } else if (strcmp(command, "delete")==0){
            argument1 = strtok(NULL, delim);
            if (argument1 ==NULL){
                printf("Invalid arguments.\n");
                continue;
            }
            delete(argument1);
        } else if (strcmp(command, "save")==0){
            argument1 = strtok(NULL, delim);
            if (argument1 ==NULL){
                printf("Invalid arguments.\n");
                continue;
            }
            save(argument1);
        }
        
    }
}

void load(char *filename){
    char buf1[BUFFER_SIZE];
    char buf2[BUFFER_SIZE];

    FILE *fp = fopen(filename,'r');
    if (fp=NULL){
        printf("open failed.\n");
        return;
    }
    while(fscanf(fp, "%s",buf1)!=EOF){
        fscanf(fp,"%s",buf2);
        add(buf1, buf2);
    }
    fclose(fp);
}

void add(char *name, char *number){
    if (n>=capacity){
        reallocate();
    }
    int i = n-1;
    while (i>=0 && strcmp(names[i],name)>0){
        names[i+1] = names[i];
        numbers[i+1] = numbers[i];
        i--;
    }
    names[i+1] = strdup(name);
    numbers[i+1] = strdup(number);
    // name과 number는 load 함수 실행시에만 값이 생기는 함수다. 
    // 즉 load함수 호출이 끝나면 name과 number에 할당된 값이 지워진다.
    // 따라서 name과 number값이 저장된 주소가 필요한 게 아니라
    // 이 값을 그대로 복사해와야 하기 때문에 strdup.
    n++;
} 
void status(){
    int i;
    for (i=0;i<n;i++){
        printf("%s %s\n",names[i],numbers[i]);
    }
    printf("Total %d persons.\n", n);
}
void find(char *name){
    int index = search(name);
    if (index ==-1){
        printf("No person named '%s' exists.\n", name);
    }else{
        printf("%s\n",numbers[index]);
    }
}
int search(char *name){
    int i;
    for (i=0;i<n;i++){
        if (strcmp(name, names[i])==0){
            return i;
        }
    }
    return -1;
}
void delete(char *name){
    int i=search(name);
    if (i==-1){
        printf("No person named '%s' exists.\n",name);
        return;
    }
    int j=i;
    for (;j<n-1;j++){
        names[j]=names[j+1];
        numbers[j]=numbers[j+1];
    }
    n--;
    printf("'%s' was deleted successfully.\n",name);
}
void save(char *filename){
    int i;
    FILE *fp = fopen(filename, "w");
    if (fp==NULL){
        printf("Open failed.\n");
        return;
    }
    for (i=0;i<n;i++){
        fprintf(fp,"%s %s\n", names[i],numbers[i]);
    }
    fclose(fp);
}

void reallocate(){
    // 더 큰 배열을 할당받아서 원래 쓰던 배열을 버리고 옮기는 것.
    int i;
    capacity *=2;
    char **tmp1 = (char **)malloc(capacity * sizeof(char *));
    char **tmp2 = (char **)malloc(capacity * sizeof(char *));
    for (i=0;i<n;i++){
        tmp1[i] = names[i];
        tmp2[i] = numbers[i];
    }
    free(names);
    free(numbers);
    /* 다 옮겼으므로 원본 배열 name과 number는 이제 필요없다.
    그런데 두 배열은 동적메모리할당으로 만들어진 것이므로
    그냥 두면 없어지지 않고 계속 존재한다. 이런 메모리를 garbage라 부름.
    garbage는 free 함수를 이용해 반환한다.
    */
    names = tmp1;
    numbers = tmp2;
    // names과 numbers가 새로운 배열을 가리키도록 한다.
    // 배열의 이름은 포인터 변수이다.
    

    /*
        내가 이해한 방식대로 정리하기.
        C에서는 무언가를 선언하면, 특정 메모리에 그 선언된 값을 집어넣는다.
        그리고 이 선언값은 기본적으로는 바꿀 수 없는 모양.
        str[] = 'asb'라고 하면, str[]이 할당된 메모리 주소값도 있을 거다.
        하지만 메모리 주소값으로 뭘 하는 게 아니라, 그냥 저장되는 값 자체를 중시하는 것.

        만약 *str 형태로 저장하면, 저장된 값의 메모리 주소를 불러올 수 있다.
        그리고 이건 단지 주소이기 때문에, 다른 주소로 옮길 수 있는 듯.
        예컨대 *str가 str[] = 'asdf'를 가리킬 수도 있는 거고
        str2[] = 'bad'를 가리킬 수도 있는 거다.

        포인터변수 vs 일반 변수
        비유하자면
        선물꾸러미가 있다고 할 때
        일반 변수는 선물꾸러미 위에 이름을 쓰는 느낌이다.
        포인터변수는 멀찍이 떨어져서 선물꾸러미를 손가락으로 찍는 느낌.
        둘 중 뭐가 선물꾸러미를 변경하기 쉬울까? 의 생각으로 접근하면 되지 않을까
        
        저 위에 free(names)과 free(numbers)한 다음
        names = tmp1 이런 식으로 선언이 가능한 이유다.
        애초에 names와 numbers를 포인터변수로 설정해 뒀기 때문.
        동적 메모리 할당을 위해 char * 형태로 선언을 하지만
        그 할당된 메모리주소를 멀찍이 떨어져서 손가락으로 가리키게 한 게 포인터변수.

        따라서 포인터변수는 언제든 변경이 가능 (가리키는 손가락만 바꾸면 되니까)
        tmp1과 tmp2로 동적메모리함수를 새로 만들고 (얘네도 포인터변수다.)
        names와 numbers를 각각 tmp1, tmp2를 가리키도록 변경하는 시스템임.
    */
}