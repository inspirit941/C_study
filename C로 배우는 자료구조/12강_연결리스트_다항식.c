// 1원 다항식을 input으로 받을 수 있다.
// 다항식의 이름은 x를 제외한 영문소문자이다.
// 변수는 항상 x
// 각 항의 계수는 정수이고, 지수는 양의 정수이다.
// =,+,- 등의 연산자 앞뒤로는 공백이 있을 수도, 없을 수도 있다.
// 항들이 반드시 차수에 대해 내림차순인 것이 아니고, 동일차수의 항이 여러개일 수도 있다
// 함수는 차숭 ㅔ대해 내림차순으로 정렬되어 저장되고 출력되어야 한다
// 동일 이름의 함수를 새로 정의할 수 있다. 이 경우 기존 함수는 지워진다.


// 각각의 항을 연결리스트로 설정한다.
// 연결리스트를 활용해 하나의 다항식을 표현하는 구조체 polynomial 정의.
// 항들을 차수에 대한 내림차순으로 정렬하여 정의.
// polynomial 구조체 안의 항목: name, first(term의 주소), size(항의 개수)
// term 구조체: 계수(coef), 차수(expo), 다음 항의 주소


#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_POLYS 100
#define BUFFER_LENGTH 100


typedef struct term{
    int coef;
    int expo;
    struct term *next;
} Term;

typedef struct polynomial {
    char name; //다항식 이름
    Term *first;
    int size;
} Polynomial;

Polynomial *polys[MAX_POLYS];
// 각각의 다항식 struct 주소값을 저장하는 배열.
int n = 0;
// 저장된 다항식 개수
Term *create_term_instance();
Polynomial *create_polynomial_instance(char name);
void add_term(int c, int e, Polynomial *poly);
int evalfunc(Polynomial *poly, int x);
int evalfunc2(Term *term, int x);
void print_poly(Polynomial *p);
void print_term(Term *pterm);
void process_command();
void handle_print(char name);
int read_line(FILE *fp, char str[], int n);
void handle_calc(char name, char *x_str);
void handle_definition(char *expression);
void erase_blanks(char *expression);
Polynomial *create_by_parse_polynomial(char name, char *body);
int parse_and_add_term(char *expr, int begin, int end, Polynomial *p_poly);
void insert_polynomial(Polynomial *ptr_poly);
Polynomial * create_by_add_two_polynomials(char name, char f, char g);
void destroy_polynomial(Polynomial *ptr_poly);

Term *create_term_instance(){
    Term *t = (Term *)malloc(sizeof(Term));
    t->coef = 0;
    t->expo = 0;
    return t;
}
// 다항식 객체를 생성할 때 이름을 지정하도록 만들었다.
// Q. 여기서는 왜 char *name이 아니라 char name일까?
Polynomial *create_polynomial_instance(char name){
    Polynomial *ptr_poly = (Polynomial *)malloc(sizeof(Polynomial));
    ptr_poly->name = name;
    ptr_poly->size = 0;
    ptr_poly->first = NULL;
    return ptr_poly;
}

int main(){


    return 0;
}
// 동적으로 생성된 객체를 적절히 초기화하지 않을 경우 프로그램 오류를 야기한다.
// 이렇게 객체를 생성하고 기본값으로 초기화하는 함수를 따로 만들어 쓰는 것이 좋다.
 

// add_term 함수
// poly가 가리키는 다항식에 새로운 하나의 항(계수, 차수)을 추가하는 함수.
// 1. 추가하려는 항과 동일 차수의 항이 이미 있는 경우? -> 기존 항의 계수만 변경 (더하거나 빼거나)
// 2. 그렇지 않은 경우 -> 새로운 항 삽입. (항의 차수는 내림차순으로 정렬)

// 새로운 항이 삽입될 위치: 차수가 작거나 같은 항이 나올 때까지 첫 번째 항부터 순서대로 검사해야 한다.
// 하지만 연결리스트에서 새로운 항을 넣으려면 '이전 노드'의 주소가 필요하다.
// (작거나 같은 항이 나오기 전까지는 내가 어떤 위치에 들어가야 할지 모르지만)
// 어떤 위치로 들어가는지 알게 되는 순간, 그 노드의 직전노드를 알아야 삽입 가능.

void add_term(int c, int e, Polynomial *poly){
    if (c==0){
        return ;
    }
    Term *p = poly->first, *q = NULL;
    while (p!=NULL && p->expo > e){
        q=p;
        p=p->next;
        // 차수가 작거나 같을 때까지 while을 돌면서
        // 직전 노드의 주소를 q에 저장해둔다.
    }
    if (p!=NULL && p->expo ==e){ // 동일 차수의 항이 존재하는 경우
        p->coef+=c; //계수를 더해준다. 처음에는 0이었으니.
        if (p->coef == 0){ //더했을 때 계수가 0이 되면?
            if (q==NULL){ // q가 null이면 첫 번째 노드를 삭제한다
            // p를 지워야 하는데 q도 null이라는 건, p가 첫번째 노드였다는 소리다.
                poly->first = p->next;
            } else {
                q->next = p->next; // p가 가지고 있던 next 주소를 q로 옮긴다.
                // 다시말해 p를 지워버린다.
            }
            poly->size--;
            free(p); //불필요해진 p를 free선언 해준다.
        }
        return;
    }
    // 여기까지 왔다는 건, 동일한 차수의 항이 없다는 것이므로
    // 새로 노드를 만들어줘야 한다
    Term *term = create_term_instance();
    term->coef = c;
    term->expo = e;
    if (q==NULL){ //q가 null이라는 건, 맨 첫번째 항이라는 거다
    // add_first와 동일한 의미.
        term->next = poly->first;
        poly->first = term; 
    }else{
        term->next = p;
        q->next = term;
    }
    poly->size++;
}

int evalfunc(Polynomial *poly, int x){
    // 다항식의 값을 계산하는 함수
    // 각각의 항의 값을 구해서 전부 더하면 된다.
    int result = 0;
    Term *t = poly->first;
    while(t!= NULL){
        result+=evalfunc2(t,x); //각각의 항의 값을 계산하여 더한다
        t = t->next;
        // 각각의 노드가 방문하는 항의 값을 계산해서
        //result로 계산
    }
    return result;
}
int evalfunc2(Term *term, int x){ //하나의 항의 값을 계산하는 함수
    int result = term->coef;
    // c* x^e일 경우, 먼저 c 값을 result에 정의해준다
    for (int i=0; i<term->expo; i++){
        result *=x;
        // result에 x를 e번 곱해준다
    }
    return result;
}
void print_poly(Polynomial *p){
    printf("%c=",p->name);
    Term *t = p->first;
    while(t!=NULL){
        print_term(t); //각각의 항 출력
        printf("+"); //중간에 +입력..? (계수에 따라 다르다)
        t = t->next;
    }
}
void print_term(Term *pterm){
    printf("%dx^%d",pterm->coef, pterm->expo);
    // 하지만 이대로 내버려둘 경우
    // 1. 계수가 -일 경우
    // 2. 차수가 1인 경우
    // 3. 차수가 0인 경우 -> 다항식이 예쁘게 나오지 않는다.
    // 해결과제로 주어짐.
}
void process_command(){
    char command_line[BUFFER_LENGTH];
    char copied[BUFFER_LENGTH];
    char *command, *arg1, *arg2;

    while (1){
        printf("$ ");
        if (read_line(stdin,command_line, BUFFER_LENGTH)<=0){
            continue;
        }
        strcpy(copied, command_line); //꼭 이래야 하는 건 아니고, 
        //함수 정의하는 명령어를 쉽게 처리하기 위해서 썼다고 함
        command = strtok(command_line, " ");
        if (strcmp(command,"print")==0){
            arg1 = strtok(NULL," ");
            if (arg1 == NULL){
                printf("Invalid arguments.\n");
                continue;
            }
            handle_print(arg1[0]);
        } else if(strcmp(command,"calc")==0){
            // calc f 1처럼 명령어 입력. 함수 이름 / x값이라는 의미
            arg1 = strtok(NULL, " ");
            if (arg1 == NULL){
                printf("Invalid arguments.\n");
                continue;
            }
            arg2 = strtok(NULL, " ");
            if (arg2 == NULL){
                printf("Invalid arguments.\n");
                continue;
            }
            handle_calc(arg1[0], arg2);
            // 첫번째 매개변수는 함수이름. -> 문자 한 개만 받은 것.
            // 두번째 매개변수는 문자열을 받음. 12,100처럼 두세자리 일 수도 있기 때문
            // atoi()등을 통해 정수값으로 변환해도 된다.
        }else if (strcmp(command, "exit")==0){
            break;
        }else{
            handle_definition(copied);
            //사용자가 입력한 다항식을 입력받아 정의한다.
        }
    }
}

void handle_print(char name){
    // left as exercise
    // print할 다항식을 검색해서, 있으면 출력
    int i=0;
    for (i=0;i<n;i++){
        if (polys[i]->name == name){
            print_poly(polys[i]);
        }
    }
}
void handle_calc(char name, char *x_str){
    // 위에 정의한 eval 함수들 가져와서 쓰기.
    // 다항식을 먼저 검색하고, 해당 값이 있으면 가져와서 계산하면 된다.
    // x는 문자열로 넘어왔다는 거 유의
    for (int i=0;i<n;i++){
        if (polys[i]->name==name){
            evalfunc(polys[i],(int)(x_str-'0'));
        }
    }
}
void handle_definition(char *expression){
    // 문자열 전체를 받은 걸 expression으로 정의한다
    erase_blanks(expression); //모든 공백문자 제거하기.
    char *f_name = strtok(expression,"=");
    if (f_name == NULL|| strlen(f_name)!=1){
        printf("Unsupported comand.\n");
        return;
        // f = dfqjer 이런 식이어야 하는데
        // 등호 왼쪽 글자가 1글자가 아니거나, 값이 없는 경우 예외처리
    }
    char *exp_body = strtok(NULL,"=");
    if (exp_body==NULL || strlen(exp_body)<=0){
        printf("Invalid expression format.--\n");
        return;
        // 등호 기준으로 strtok 했는데 null이라는 건
        // f = '아무것도 없음' 이거나
        // strlen이 0 또는 음수인 것도 마찬가지로 아무것도 없다는 것
    }
     
    // 정의방법이 두 가지라고 봤다.
    // 1. g = f+k 처럼 함수를 '다른 함수'를 갖고 정의하는 경우
    // 2. f = 2x^2 이런 식으로 숫자를 통해 정의하는 경우,
    
    //1. 기존 두 다항식의 합 형태로 정의하는 경우. (+ 연산자만 받는다.)
    if(exp_body[0]>='a'&& exp_body[0]<='z'&&exp_body[0] != 'x'){
        char *former = strtok(exp_body,"+");
        if (former==NULL || strlen(former)!=1){
            // 함수는 영문 소문자 한 글자뿐이므로, 한 글자가 아니면 예외처리
            printf("Invalid expression format.\n");
            return;
        }
        char *later = strtok(NULL,"+");// f=g+h면 두 번째는 사실상 h 전체를 선택한다. +가 없으니까
        if(later==NULL||strlen(later)!=1){
            printf("Invalid expression format.\n");
            return;
        }
        Polynomial *pol = create_by_add_two_polynomials(f_name[0], former[0],later[0]);
        if (pol = NULL){
            printf("Invalid expression format.\n");
            return;
        }
        insert_polynomial(pol);
    }//2. 새로 정의하는 함수
    // f = -5x^2+x+12
    else {
        Polynomial *pol = create_by_parse_polynomial(f_name[0],exp_body);
        if (pol ==NULL){
            // null return은, 만약 f=g+h에서 g나 h가 정의되어 있지 않은 경우 예외처리로 null 반환
            printf("Invalid expression format.\n");
            return;
        }
        insert_polynomial(pol); //polys라는 다항식 저장 배열에 추가하기.
        // 만약 f=g+h에서 미리 정의된 f가 있다면
        // 새로 정의한 f로 교체
    }
}

void erase_blanks(char *expression){
    //left as exercise
    // 문자배열 expressiond에서 모든 공백문자를 제거하여 압축한다.
    // (배열된 문자 위치를 밀착시키면 된다.)
    //문자열 끝에 \0 추가해야 한다.
}

Polynomial *create_by_parse_polynomial(char name, char *body){
    // f=수식. 에서 f가 name, 수식이 body
    Polynomial *ptr_poly = create_polynomial_instance(name);
    // name을 갖는 새 다항식 struct 생성 및 초기화
    int i=0, begin_term = 0;
    // i는 첫번째 문자열부터 한 글자씩을 말함.
    while(i<strlen(body)){
        // 각 항별로 잘라낸다.
        // 첫 번째 항을 제외하면, 모든 항은 +나 -로 구분될 수 있다.
        
        if (body[i]=='+'||body[i]=='-'){
            i++; //첫 번째 항은 +나 -가 있을수도 있고 없을수도 있으니
            // 일단 i에 더해주고 넘어간다.
        }
        while (i<strlen(body)&& body[i]!= '+' && body[i]!='-'){
            i++;
            // 하나의 항이 끝날 때까지 전진한다.
        }
        int result = parse_and_add_term(body,begin_term, i, ptr_poly);
        // body[begin_term, i)까지가 하나의 항이다.
        // while문을 통과한다는 건, i가 +나 -에 걸렸을 때다.
        // 따라서 begin_term부터 i-1까지가 문자열.
        // 이 항(계수와 차수)을 인식해서 ptr_poly에 추가한다.
        if (result ==0){
            destroy_polynomial(ptr_poly);
            //다항식 개체를 하나 만들었는데 뭔가 잘못되었으면
            // 할당받은 동적메모리도 없애야 하기 때문.
            return NULL;
        }// 잘못된 항일 경우 0을 반환하고, 
        //그런 경우 만들고 있던 다항식 자체를 destroy
        begin_term = i; //다음 항의 시작 위치는 i가 된다.
    }
    return ptr_poly;
    // 문자열의 끝까지 빠져나왔을 경우 return해준다.
}

// begin_term부터 i까지 잘라낸 배열을 정리하는 함수
//1. 계수 잘라내기.
int parse_and_add_term(char *expr, int begin, int end, Polynomial *p_poly){
//강의안에는 Term *parse_and_add_term(char *expr, int begin, int end, Polynomial *p_poly)    
    int i = begin;
    int sign_coef = 1, coef = 0, expo = 1;
    // +, - 기호로부터 계수의 부호를 결정한다.
    // 하지만 첫 번째 항의 경우 기호가 없을 수도 있다. 그래서 default를 1로 설정
    // 부호 기억하기
    if (expr[i]=='+'){
        i++;
    }else if(expr[i]=='-'){ // +, - 없이 바로 숫자 나올 수도 있으니 else로 쓰면 안 됨
        sign_coef = -1;
        i++;
    } 
    
    //계수의 절대값
    while (i<end && expr[i]>='0' && expr[i]<='9'){ //digit인 경우
        // i<end인 이유
        coef = coef*10 +(int)(expr[i]-'0');
        // 문자를 숫자로 바꾸는 게 (int)(expr[i]-'0')라는 거 같다
        i++;
        // 숫자 인식방법: 첫 번째 숫자는 그대로
        // 두 번째 숫자는 첫 번째 숫자 *10 + 두 번째 숫자
        // 세 번째 숫자는 ....
        // 이런 식이다.
    }
    // 만약 계수가 없으면(문자 앞에 숫자가 없으면)
    // 위의 while문을 그냥 건너뛴다.
    // = coef = 0으로 남아 있다.
    if (coef ==0){
        coef = sign_coef;
        // coef를 1 or -1로 바꿔준다.
    }else {
        coef *= sign_coef;
        // while문 다 돈 다음에
        // 아까 저장한 부호값을 곱해준다.
    }
    if (i >=end){ //계수만 인식했는데 i가 end보다 커진다는 건,
    // x도 없고 차수도 0이라는 소리. 계수만 있는 항.
    // 따라서 coef에 차수 0을 넣고 끝낸다.
        add_term(coef,0,p_poly);
        return 1;
    
    }
    // 상수항은 여기서 끝
    // 상수항이 끝났다면 반드시 x가 나와야 함
    if(expr[i]!='x'){
        return 0;
        // 계수 다음에 x가 아닌 다른 문자가 온다? -> 오류. 0 리턴
    }
    i++;
    // x는 건너뛴다
    if(i>=end){//그랬더니 end에 도착했다 == 일차항이다
        add_term(coef,1,p_poly);
        return 1;
    }
    if (expr[i]!='^'){
        return 0;
        // x 다음 ^가 안오면 오류
    }
    i++;
    expo = 0;
    while (i<end && expr[i]>='0' && expr[i]<='9'){
        expo = expo*10 + (int)(expr[i]-'0');
        i++;
        // 지수 값 인식
    }
    add_term(coef,expo,p_poly);//지수까지 완료하고 poly에 넣는다.
    return 1;
}
void insert_polynomial(Polynomial *ptr_poly){
    for (int i=0; i<n;i++){
        if (polys[i]->name == ptr_poly->name){
            // 이름이 똑같은 경우
            destroy_polynomial(polys[i]);
            polys[i]=ptr_poly;
            return;
        }
    }
    polys[n++]=ptr_poly;
    // for문이 없다는 건, 겹치는 다항식이 없다는 것
    // 배열 맨 마지막에 ptr_poly 넣고 끝
}
void destroy_polynomial(Polynomial *ptr_poly){
    // 구조체만 free시키는 게 아니라,
    // 각 term도 전부 free시켜줘야 한다. 동적메모리 할당받은 것들이라서
    if(ptr_poly == NULL){
        return;
    }// 없는 걸 destroy할 수는 없으니 그냥 return
    Term *t = ptr_poly->first, *tmp;
    while(t!=NULL){
        tmp = t;
        t=t->next;
        free(tmp);
        // 다항식에 속한 모든 항을 free 시킨다
        // * t를 먼저 free시켜 버리면, 다음 항으로 넘어갈 수가 없음.
    }
    free(ptr_poly);
    // 모든 term을 free 시킨 다음 ptr_poly 객체도 free선언.
}

Polynomial * create_by_add_two_polynomials(char name, char f, char g){
    /* left as exercise 
        두 개의 다항식 g와 h가 있다면
        해당 항들이 달려 있을 것
        새로운 다항식을 하나 만들고
        두 다항식의 각각의 항을 순서대로 add_term 해 주면 된다.
        두 다항식의 항을 순서대로 scan하면서 새 다항식에 add term 함수 써주면 된다.
        동일한 차수를 합치거나 하는 걸 add term이 처리하기 때문에 신경쓰지 않아도 된다.
    */
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