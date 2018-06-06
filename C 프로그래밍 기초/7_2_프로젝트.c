#include <stdio.h>
#include <time.h>
// 무한루프가 뜨는데, 왜인지 모르겠다.
// arrayAnimal 자체가 [4][5]로 한정이 안 되는 거 같은데, 이유를 모르겠음.

int arrayAnimal[4][5]; //카드 지도. 총 20장
int checkAnimal[4][5]; //뒤집혔는지 여부 확인하기.

char * strAnimal[10]; //10개의 공간배열. 글자가 특정 메모리 주소를 갖는단 의미.
void initAnimalArray();
void initAnimalName();
void shuffleAnimal();
int convert_position_x();
int convert_position_y();
void printAnimals();
void printQuestion();
int foundAllAnimals();

int main(void){
// 10마리의 서로 다른 동물
// 사용자로부터 2개의 입력값을 받아서, 같은 동물이면 카드 뒤집기
// 총 실패횟수 알려주기

    srand(time(NULL));
    initAnimalArray();
    initAnimalName();
    shuffleAnimal();

    int failCount = 0;//
    
    while (1){
        int select1 = 0; //사용자가 선택한 첫번째 수
        int select2 = 0; //사용자가 선택한 두번째 수
        
        
        printf("뒤집을 카드를 고르세요.\n");
        printAnimals();
        printQuestion();
        
        scanf_s("%d, %d", &select1, &select2); //받아서 메모리주소에 저장
        if (select1 == select2){ //같은 카드 선택 시 무효
            printf("같은 카드를 선택하였습니다.\n");
            continue;
        }
        int firstSelect_x = convert_position_x(select1);
        int firstSelect_y = convert_position_y(select1);

        int secondSelect_x = convert_position_x(select2);
        int secondSelect_y = convert_position_y(select2);
        // 카드가 뒤집히지 않았고, 두 동물이 같을 경우
        if ((checkAnimal[firstSelect_x][firstSelect_y]==0 &&checkAnimal[secondSelect_x][secondSelect_y]==0) 
             && (arrayAnimal[firstSelect_x][firstSelect_y]
             == arrayAnimal[secondSelect_x][secondSelect_y])) {
                 printf("정답입니다");
                 checkAnimal[firstSelect_x][firstSelect_y]=1;
                 checkAnimal[secondSelect_x][secondSelect_y]=1;
                 //'선택된 카드' 상태로 조건 변경
             }
             else{
                 printf("틀렸거나, 이미 뒤집힌 카드입니다.\n");
                 printf("%d, %s\n",select1, strAnimal[firstSelect_x][firstSelect_y]);
                 printf("%d, %s\n",select2, strAnimal[secondSelect_x][secondSelect_y]);
                 printf("\n\n");
                 failCount++;
             }
             if (foundAllAnimals()==1){
                printf("모든 동물을 전부 찾으셨습니다.\n");
                printf("지금까지 총 %d번 실수했습니다.\n",failCount);
                break;
             }
             
    }
    return 0;
}

void initAnimalArray(){
    for (int i=0;i<4;i++){
        for (int j=0; j<5;j++){
            arrayAnimal[i][j] = -1;
        }
    }
}

void initAnimalName(){
    strAnimal[0]="원숭이";
    strAnimal[1]="토끼";
    strAnimal[2]="쥐";
    strAnimal[3]="소";
    strAnimal[4]="호랑이";

    strAnimal[5]="용";
    strAnimal[6]="뱀";
    strAnimal[7]="말";
    strAnimal[8]="양";
    strAnimal[9]="개";
}
// 10마리 동물이 한 쌍으로 자리잡아야 함.
// 비어있는 위치를 랜덤으로 뽑아서 같은 동물을 지정하는 것.
void shuffleAnimal(){
    for(int i=0; i<10;i++){
        for (int j=0; j<2; j++){
            int pos =  getEmptyPosition();
            int x = convert_position_x(pos);
            int y = convert_position_y(pos);
            arrayAnimal[x][y]=i;
        }
    }
}
// 좌표에서 빈 공간 찾기
int getEmptyPosition(){
    while(1){
        int randPos = rand() % 20; //0~19 사이의 숫자 반환
        // 19면 [3,4]로 접근할 수 있어야 함. = 바꾸는 작업 필요
        int x = convert_position_x(randPos);
        int y = convert_position_y(randPos);
        if (arrayAnimal[x][y]==-1){
            return randPos; //비어있으면 randPos 반환.
        }

    }
    return 0;
}

int convert_position_x(x){
    // array[4][5]는 가로는 5로 나눈 나머지, 세로는 5로 나눈 몫으로 분류할 수 있다.
    return x/5; // 세로값이기 때문
}

int convert_position_y(y){
    return y %5; //가로값이기 때문. 나머지 계산이 가로
    // 일반적으로 생각하는 x축과 y축이 반대로 돼 있다. array[x][y]이기 때문.
}

void printAnimals(){
    //정답 확인을 위해 보여주는 것.
    for (int i=0; i<4; i++){
        for (int j=0; i<5;j++){
            printf("%8s",strAnimal[arrayAnimal[i][j]]);
        }
        printf("0\n");
    }
    printf("\n==========================");
}
void printQuestion(){
    printf("\n문제:\n");
    int seq = 0;
// 시퀀스: 몇 번 카드를 집을 건지 (0~19번) 보여주는 것.

// ㅁ ㅁ ㅁ ㅁ ㅁ 0  1  2  3  4  5
// ㅁ ㅁ ㅁ ㅁ ㅁ 6 ...
// ㅁ ㅁ ㅁ ㅁ ㅁ 
// ㅁ ㅁ ㅁ ㅁ ㅁ 
// checkanimal은 0 또는 1. 찾은 값은 1, 아닌 값은 0을 의미한다.
    for (int i=0; i<4; i++){
        for (int j=0; i<5;j++){
            //카드를 뒤집어 정답을 맞췄으면 동물 이름 반환
            
            if (checkAnimal[i][j]!=0){
                printf("%8s",strAnimal[arrayAnimal[i][j]]);
            }
            // 뒤집지 못했으면 (정답을 맞추지 못했으면) -> 위치를 나타내는 숫자 반환
            else {
                printf("%8d",seq);
            }
            seq++;
        }
        printf("\n");
    }
}

int foundAllAnimals(){
     for (int i=0; i<4; i++){
        for (int j=0; i<5;j++){
                if (checkAnimal[i][j]==0){
                return 0;
            }
            
            
        }
     }
     return 1;
}