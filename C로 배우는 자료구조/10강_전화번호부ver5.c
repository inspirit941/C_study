//구조체에 대한 포인터, 동적 메모리할당.
// C에서는 일반적으로 구조체를 만들어 쓰지 않음.
// C에서는 매개변수 호출방식이 call-by-value (pass by assignment) = 값에 의한 전달방식
// 실 매개변수와 호출변수가 사실 별개이다.
// 무언가를 호출할 때, 값을 복사해와서 만든다는 소리.

/*
    이를테면 전화번호부 ver4에서 Person이라는 struct에 데이터가 저장되어 있다.
    이걸 status함수로 호출하면, 이 함수는 print_person이라는 함수로 값을 불러온다.
    이 때 print_person이 받는 변수인 Person p는
    실제 directory를 불러오는 게 아니라
    directory에 있는 모든 struct 값을 메모리 어딘가에 "복사"한 다음
    그 값을 불러오는 구조로 이루어진다.
    
    여기서의 특이점은, 구조체 변수를 복사한다. 
    구조체 안의 name, number... 등 모든 변수가 복사된다.
    각각의 값을 따로 복사해야 한다 = 복사해야 하는 데이터의 양이 많다.
    전화번호부의 예시 정도는 상관없지만, 프로그램이 복잡해질 경우 비효율적임.
    
    return문의 경우도 마찬가지.
    어떤 함수에서 Person thePerson = get_person("John"); 라고 정의하면
    Person get_person(char *name){
        return directory[i];
    }
    이런 식이 될 거다.

    return directory[i]의 의미는, 
    전체 directory 중에서 [i]에 해당하는 값을 임시 객체에 복사한 다음
    임시 객체에 있는 값을 thePerson이란 이름의 구조체로 복사하는 식이다.
    = 구조체 안의 모든 값이 따로따로 복사된다는 소리.

    특히 return의 경우
    return된 값이 임시 객체 안 어딘가에 복사된 다음, 이 복사된 개체가 호출함수에 활용되는 식.
    즉 복사가 두 번 일어난다.
    => 구조체 크기가 커지면 성능에 영향을 줄 수 있다.

    add()나 delete()의 경우에도, 알파벳순으로 정렬하는 과정에서
    모든 구조체의 값이 다음 칸으로 복사되어야 한다.
    = 복사되어야 하는 데이터의 양이 많다.

    구조체로 데이터를 만들면 이런 문제를 감수해야만 한다.

    따라서 구조체의 배열을 그대로 쓰지 않고, 구조체의 포인터 배열을 사용한다.

    -> struct 정의한 다음
    Person * directory[CAPACITY]; 로 변경한다는 소리. 포인터 타입.
    배열의 각 칸이 하나의 포인터일 뿐이고, 그 포인터 주소가 구조체의 값을 불러오는 식.

    포인터 변수를 쓰면
    구조체의 주소를 복사하는 식이기 때문에
    복사에 걸리는 시간이나 부하가 훨씬 줄어든다.

    포인터변수를 쓸 때 자주 쓰게 될 연산자 ->

    void print_person(Person *p){
        printf("    Phone: %s\n", p-> number); 이런 식.
        printf("    Email: %s\n", (*p).email);
        // 동일한 표현이지만, -> 연산자를 더 많이 쓴다.
    }
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INIT_CAPACITY 100
#define BUFFER_LENGTH 100

typedef struct {
    char *name;
    char *number;
    char *email;
    char *group;
} Person;

void status();
void find(char *name);
int read_line(FILE *fp, char str[], int n);
void load(char *filename);
void add(char *name, char *number, char *email, char *group);
int compose_name(char str[], int limit);
void handle_add(char *name);
void save(char *filename);
int search(char * name);
void print_person(Person *p);
void delete(char *name);
void release_person(Person *p);
void reallocate();


Person ** directory;
// directory는 배열이다. Person type 포인터들의 배열.
// 한 칸마다 person의 pointer를 말함.
// 그리고 배열의 이름(여기서는 directory)도 하나의 변수다.
// 이 변수도 포인터로 설정할 수 있다.
// 이 배열의 시작 주소를 가리키는 포인터변수로 만들 수 있단 소리

// 배열 크기를 고정하고 싶다면 Person * directory[배열크기];
// 만약 배열 재할당해서 크기를 키우고 싶다면
// Person ** directory 형태로 선언하고
// 나중에 동적메모리 재할당으로 변경해야 함. 


// Person * directory는, directory 배열 안에 어떤 형태의 값을 받을 건지 (=주소값)
// Person ** directroy는 directory 배열 안에 어떤 형태의 값을 받을 건지 +
// 그 값을 저장하는 directory라는 이름도 포인터변수 (= 주소값)라는 소리

int capacity;
int n;

void init(){ // 초기화 작업
    directory = (Person **)malloc(INIT_CAPACITY*sizeof(Person *));
    // 동적메모리 할당.
    capacity =  INIT_CAPACITY;
    n=0;
}

int main(){

    init();
    char command_line[BUFFER_LENGTH];
    char *command, *argument;
    char name_str[BUFFER_LENGTH];

    while(1){
        printf("$ ");
        if (read_line(stdin, command_line, BUFFER_LENGTH)<=0){
            // standard input file = stdin. 키보드 입력을 받는 의미.
            continue;
        }
        command = strtok(command_line, " ");
        if (strcmp(command,"read")==0){
            argument = strtok(NULL," ");
            if (argument == NULL){
                printf("Invaild argument.\n");
                continue;
            }
            load(argument);
// read 뒤에는 파일이름만 올 거기 때문에 strtok 한 번으로 끝.
        } else if (strcmp(command, "add")==0){
            // add 다음에 있는 공백이 아무리 많아도, 군더더기 없이 압축해야함.
            // 단어와 단어 사이에 두 개 이상의 공백이 있을 때 처리할 함수 = compose_name
            // name_str로 이름을 담는다.
            if (compose_name(name_str, BUFFER_LENGTH)<=0){
                printf("Name required.\n");
                continue;
            }
            handle_add(name_str);

        } else if (strcmp(command, "find")==0){
            if (compose_name(name_str,BUFFER_LENGTH)<=0){
                printf("Name required.\n");
                continue;
            }
            find(name_str);
        } else if (strcmp(command,"status")==0){
            status();
        } else if (strcmp(command, "delete")==0){
            if (compose_name(name_str,BUFFER_LENGTH)<=0){
                printf("Invaild argument.\n");
                continue;
            }
            delete(name_str);
        } else if (strcmp(command, "save")==0){
            argument = strtok(NULL," ");
            if (argument == NULL){
                printf("Invaild argument.\n");
                continue;
            }
            save(argument);
        } else if (strcmp(command, "exit")==0){
            break;
        }
    }
    return 0;

}

int read_line(FILE *fp, char str[], int n){
    int ch,i = 0;
    while (( ch =fgetc(fp) )!='\n' && ch !=EOF){
        // 파일로부터 데이터를 읽어야 하므로 getchar()가 아니라 fgetc (파일에서 한 character를 읽음)
        // 파일의 맨 마지막줄은 \n이 없다. 그래서 파일의 마지막을 지정하기 위해 EOF가 필요.
        if (i<n){
            str[i++]=ch;
        } //overflow 생기지 않게 제약
    }
    str[i] = '\0';
    return i;
}

void load(char *filename){
    char buffer[BUFFER_LENGTH];
    char *name, *number, *email, *group;
    char *token;

    FILE *fp = fopen(filename,"r");
    if (fp==NULL){
        printf("Open Failed.\n");
        return;
    }
    while (1){
        if(read_line(fp, buffer, BUFFER_LENGTH)<=0){
            break;
        }
        name = strtok(buffer,"#"); //이름은 반드시 있다고 가정.
        token = strtok(NULL,"#");
        if (strcmp(token," ")==0){
            number = NULL;
        } else {
            number = strdup(token);
        }
        token = strtok(NULL,"#");
        if (strcmp(token," ")==0){
            email = NULL;
        } else {
            email = strdup(token);
        }
        token = strtok(NULL,"#");
        if (strcmp(token," ")==0){
            group = NULL;
        } else {
            group = strdup(token);
        }
        add(strdup(name), number, email, group);
    }
    fclose(fp);
}

void add(char *name, char *number, char *email, char *group){
    if (n>=capacity){
        reallocate();
    }
    int i = n-1;
    while (i>=0 && strcmp(directory[i]->name, name)>0){
        directory[i+1] = directory[i];
        // 여기서는 directory[i]에는 변수가 들어있는 게 아니라 주소가 들어 있다.
        // 4와 복사 매커니즘은 동일하지만 부담이 더 적음.
        i--;
    }
    directory[i+1] = (Person *)malloc(sizeof(Person));
    // directory[i]가 struct 배열을 직접 담는 게 아니라
    // struct을 가리키는 포인터들의 배열을 의미하므로
    // 저장할 구조체 자체가 있진 않다.
    // 그래서 데이터를 담을 구조체(=새로운 구조체 객체)가 하나 필요함. 
    // 동적메모리할당으로 만들어준다.
// 동영상 14:32

    directory[i+1]->name = name;
    directory[i+1]->number = number;
    directory[i+1]->email = email;
    directory[i+1]->group = group;
    // strdup으로 복제하지 않고 저장한다. 
    n++;
    printf("'%s' was added successfully.\n",name);
}
void reallocate(){
    capacity *=2;
    Person **tmp = (Person **)malloc(capacity*sizeof(Person *));
    for (int i=0;i<n;i++){
        tmp[i] = directory[i];
    }
    free(directory);
    directory = tmp;
    // 동영상 17:51
    // 구조체 데이터는 가만히 있고, 구조체를 가리키는 주소값만 계속 바뀌는것.

    // garbage는 heap에 저장된다.
    // 이 garbage들 때문에 heap 용량이 부족하면 프로그램 실행에 지장이 된다.

    // 동적메모리 할당일 경우 꼭, 더이상 필요없으면 free 선언을 해줘야 한다.
    // malloc으로 할당받은 메모리가 아닌 경우는 free 선언이 필요없음.
    // 지역변수는 특정 함수 내에서만 실행되고, 함수가 종료되면 알아서 지워지며
    // 전역변수는 프로그램 끝날 때까지 유지돼야 함.
}

void delete(char *name){
    int i = search(name);
    if (i==-1){
        printf("No person named '%s' exists.\n",name);
        return;
    }
    Person *p = directory[i]; //directory[i] = 포인터(=주소값)
    for(int j=i; j<n-1;j++){
        directory[j]=directory[j+1];
    }
    n--;
    release_person(p);
    printf("'%s' was deleted successfully.\n", name);
}
// 이렇게, struct에 할당된 주소값 변경은 완료함.
// 그런데, 원래 struct도 동적메모리로 할당받은 변수였다.
// 이제 안 쓸 struct라면 free로 반환해야 한다. 그 함수가 아래의 release_person
void release_person(Person *p){
    free(p->name);
    if (p->number!= NULL) free(p->number);
    if (p->email!= NULL) free(p->email);
    if (p->group!= NULL) free(p->group);
    free(p);
    // free(p)로 안 하는 이유?
    // name, number에 들어간 각각의 문자들도 전부 malloc (strdup으로)으로 만든 거다.
    // strdup 함수 안에서 malloc을 만들기 때문에
    // strdup을 썼으면 free가 필요하다!
    // 따라서 이것들도 전부 free시켜줘야 하다보니 free(p)로 한번에 해결이 안됨.

    //cf. 만약 null일 경우 굳이 free시켜주지 않아도 된다.
    // 그래서 if문으로 null일 경우에만 free시켜주도록 만들었음.
}


int compose_name(char str[], int limit){
    char *ptr;
    int length = 0;

    ptr = strtok(NULL, " ");
    // 입력 라인의 두 번째 토큰, 보통 '이름'이 될 것이다.
    if (ptr == NULL){
        return 0;
        // 또는 return -1을 둬도 상관없다
    }
    // 이름 입력값이 null이면 return 0
    // 즉 add나 find, delete를 할 때 if문에서 걸러지게 만든다.

    strcpy(str,ptr);
    // 이름의 첫 단어를 copy한다. (이동건이면 '이', Lee Donggeon이라면 Lee)
    length+=strlen(ptr);
    // 이름의 길이는 첫 번째 토큰의 길이가 될 것.
    while ((ptr = strtok(NULL," "))!= NULL){
        // 두 번째 단어를 읽는다.
        if (length+strlen(ptr)+1 < limit){
            // 현재 str에 들어간 단어 + 아직 str에 안들어가고 ptr에 남은 단어의 합
            // limit을 넘지 않아야 한다 = overflow 방지용.
            // +1을 하는 이유는, 마지막에 \0을 넣어야 해서.
            str[length++] = ' ';
            //단어와 단어 사이에 공백 추가
            str[length] = '\0';
            strcat(str, ptr);
            // strcat은 두 단어가 null 캐릭터로 끝난다는 전제하에만 동작한다.
            // 즉 두 단어가 완전해야 함. (\0이 들어가야.)
            // 그래서 strcat 위에 str[length]=\0이 필요한 것.

            // 즉
            // Lee Dong geon에서 "Dong \0"를 만든 다음 
            // 처음 저장된 "Lee"라는 str과 strcat을 진행하는 것.
            // 최종적으로 저장되는 건 Lee Dong geon \0이 될 거다.
            length+= strlen(ptr);
        }
    }
    return length;
}

// 변경된 자료구조와 add함수에 맞게 프로그램 나머지 부분을 수정해라.
// save, search, print_person, status, find, handle_add.
// v4와 달리 존재하지 않는 항목들은 전부 null로 저장되어 있다.
// ex) handle_add에서 미리 strdup을 해야 한다 (강의에서 말한 힌트)

// handle_add는 변경할 사항이 없다.
// 어차피 지역변수 배열은 함수 끝나면 다 사라지기 때문.
void handle_add(char *name){
    char number[BUFFER_LENGTH], email[BUFFER_LENGTH], group[BUFFER_LENGTH];
    char empty[]=" ";

    printf(" Phone: ");
    read_line(stdin, number, BUFFER_LENGTH);
    // 만약 scanf로 이 값을 받으면, 사용자가 어떤 값을 입력하지 않고 엔터를 치면
    // 값을 입력할 때까지 계속 기다린다. = 우리가 원하는 바가 아님.
    printf(" Email: ");
    read_line(stdin, email, BUFFER_LENGTH);

    printf(" Group: ");
    read_line(stdin, group, BUFFER_LENGTH);

    add(strdup(name), (char *)(strlen(number)>0 ? strdup(number) : empty),
            (char *)(strlen(number)>0 ? strdup(email) : empty),
            (char *)(strlen(number)>0 ? strdup(group) : empty));
    // 이름은 있으니까 name그대로.
    // 나머지는 아무것도 안 넣고 enter 칠 수 있음.
    // 입력한 경우 strlen 값이 0보다 큼.
    // strlen(number) >0 ? number : empty
    /* -> strlen(number >0 조건을 만족하면 number를, 만족하지 않으면 empty를 택해라.)
    add라는 함수를 설정할 때 "아무 값도 입력하지 않으면 공백처리"가 있었기 때문에
    empty[] = " "를 정의하고 strlen()>0 조건을 만족하지 않으면 공백 선택.
    */
}

void save(char *filename){
    int i;
    FILE *fp = fopen(filename,"w");
    if (fp = NULL){
        printf("Open failded.\n");
        return;
    }
    for (i=0;i<n;i++){
        fprintf(fp, "%s#",directory[i]->name);
        fprintf(fp, "%s#",directory[i]->number);
        fprintf(fp, "%s#",directory[i]->email);
        fprintf(fp, "%s#\n",directory[i]->group);
        // 이름쓰기 + 구분자 # 추가. 마지막에는 \n로 줄바꿈.
    }
    fclose(fp);
}

int search(char *name){
    int i;
    for (i=0;i<n;i++){
        if (strcmp(name, (*directory[i]).name)==0){
            return i;
        }
    }
    return -1;
}

void print_person(Person *p){
    printf("%s:\n",(*p).name);
    printf("    Phone: %s\n",p->number);
    printf("    Email: %s\n",p->email);
    printf("    Group: %s\n",p->group);
}

void status(){
    int i;
    for (i=0;i<n;i++){
        print_person(directory[i]);
    }
    printf("Total %d persons.\n",n);
}

void find(char *name){
    int index = search(name);
    if (index==-1){
        printf("No person named '%s' exists.\n",name);
    } else{
        print_person(directory[index]);
    }
}