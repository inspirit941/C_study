// 구조체 사용하기
// 이름, 전화번호, 이메일 주소, 그룹 지정이 가능하도록.
// 단 이름을 제외한 나머지 항목은 비워둘 수 있다.

/*
파일 형식
"#" 문자를 필드 간 구분자로 사용한다.
존재하지 않느 항목의 경우 하나의 공백문자로 사용한다.
모든 라인은 반드시 구분자로 끝나야 한다. 이렇게 하는 이유는???


** 구조체
항상 같이 붙어다녀야 하는 데이터를 별개의 변수에 분산해 저장하는 건 바람직하지 않다.
ex) 우리의 경우 이름, 전화번호, 이메일 주소 등등.
C의 경우 이런 형태를 '구조체'를 사용한다.
(같이 붙어다녀야 하는 데이터를 하나의 그룹으로 묶는 것)
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define CAPACITY 100
#define BUFFER_LENGTH 100

typedef struct person{
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
void print_person(Person p);
void delete(char *name);


// 구조체 struct person을 정의하면서 Person으로 rename 진행함.
// 이렇게 쓸 경우 struct tag인 person을 지워도 상관없다.

Person directory[CAPACITY];
// Person type의 배열 directory를 선언한다.
int n=0;


int main(){
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


// 파일로부터 라인 단위로 읽기
// 키보드뿐만 아니라 파일로부터도 읽을 수 있도록 하였다.
// 키보드로 읽게 하려면 stdin을 FILE *fp에 넣는 거 같음.
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

    FILE *fp = fopen(filename,"r");
    if (fp ==NULL){
        printf("Open failed.\n");
        return;
    }
    while (1){
        if (read_line(fp, buffer, BUFFER_LENGTH)<=0){
            break;
        }
        name = strtok(buffer,"#");
        number = strtok(NULL,"#");
        email = strtok(NULL,"#");
        group = strtok(NULL,"#");
        // 존재하지 않는 항목은 한 칸 공백으로 설정하기 때문에 비어 있음.
        add(name, number, email, group);
    }
    fclose(fp);
}

void add(char *name, char *number, char *email, char *group){
    int i=n-1;
    
    //새로운 사람이 들어갈 위치 설정. (오름차순)
    while (i>0 && strcmp(directory[i].name, name)>0){
        directory[i+1] = directory[i];
        i--;
    }
    directory[i+1].name =  strdup(name);
    directory[i+1].number = strdup(number);
    directory[i+1].email = strdup(email);
    directory[i+1].group = strdup(group);
    // 모든 항목은 strdup으로 복제하여 저장해야 한다.
    n++;
    printf("%s was added successfully.\n",name);
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

    add(name, (char *)(strlen(number)>0 ? number : empty),
            (char *)(strlen(number)>0 ? email : empty),
            (char *)(strlen(number)>0 ? group : empty));
    // 이름은 있으니까 name그대로.
    // 나머지는 아무것도 안 넣고 enter 칠 수 있음.
    // 입력한 겨우 strlen 값이 0보다 큼.
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
        fprintf(fp, "%s#",directory[i].name);
        fprintf(fp, "%s#",directory[i].number);
        fprintf(fp, "%s#",directory[i].email);
        fprintf(fp, "%s#\n",directory[i].group);
        // 이름쓰기 + 구분자 # 추가. 마지막에는 \n로 줄바꿈.
    }
    fclose(fp);
}
int search(char * name){
    int i;
    for (i=0;i<n;i++){
        if (strcmp(name, directory[i].name)==0){
            return i;
        }
    }
    return -1;
}
void print_person(Person p){
    printf("%s:\n",p.name);
    printf("    Phone: %s\n",p.number);
    printf("    Email: %s\n",p.email);
    printf("    Group: %s\n",p.group);
}
void delete(char *name){
    int i = search(name);
    if (i == -1){
        printf("No person named '%s' exists.\n",name);
        return;
    }
    int j = i;
    for (;i<n-1;j++){
        directory[j] = directory[j+1];
        // j+1에 있던 항목을 j로 옮겨라. 즉 한칸씩 앞으로 땡겨라
        n--;
        printf("'%s' was deleted successfully.\n",name);
    }
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

