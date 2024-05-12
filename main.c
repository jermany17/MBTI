#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "sia_compTable.h"

#define QUESTION_NUM 12 // 질문의 총 개수
int sih_used[QUESTION_NUM] = { 0 };
int sih_cnt[QUESTION_NUM / 3] = { 3,3,3,3 };
char sih_Q[QUESTION_NUM][100] = {

    "당신은 친구들과 약속잡는 것을 좋아하나요? (Y/N)",
    "혼자있을 때 외로움을 많이 타나요? (Y/N)",
    "사람들이 많은 곳에 자주 가나요? (Y/N)", 
    //0~2번은 E/I인 경우(Y일 때 E임)
    
    "상상에 빠져들기 쉬우신가요? (Y/N)",
    "새로운 경험을 추구하는 편인가요? (Y/N)",
    "4차원 같다는 말을 많이 들으시나요? (Y/N)", 
    // 3~5번은 N/S인 경우(Y일 때 N임)
    
    "타인의 감정에 관심없는 편인가요? (Y/N)", 
    "공감해줘라는 말을 많이 듣는 편인가요 (Y/N)",
    "감정보다 이성을 따르는 편인가요? (Y/N)", 
    // 6~8번은 T/F (Y일 때 T임)
    
    "규칙적인 일상을 선호하시나요? (Y/N)", 
    "마감기한을 잘 지키시나요? (Y/N)", 
    "휴식을 취하기 전에 집안일을 먼저 끝내시나요? (Y/N) "  
    // 9~11번은 J/P (Y일 때 J임)

};
void sia_compCheck();
int sih_shuffleQ();
void sih_printQ();
void sih_printMBTI();

int main() {
    //sia_compCheck();
    sih_printQ();
    sih_printMBTI();
    return 0;
}

void sia_compCheck() {
    char type1[5], type2[5];
    int i = 0, j = 0;

    printf("첫 번째 MBTI 유형을 입력하세요: ");
    scanf("%s", type1);
    printf("두 번째 MBTI 유형을 입력하세요: ");
    scanf("%s", type2);

    for (int i = 0; i < 4; i++) { // standardisation of input
        if (type1[i] >= 'a' || type1[i] <= 'z') type1[i] -= 32;
        if (type2[i] >= 'a' || type2[i] <= 'z') type2[i] -= 32;
    }

    // MBTI 유형을 숫자 인덱스로 변환
    if (type1[0] == 'E') i += 8;
    if (type2[0] == 'E') j += 8;

    if (type1[1] == 'S') i += 4;
    if (type2[1] == 'S') j += 4;

    if (type1[2] == 'F') i += 2;
    if (type2[2] == 'F') j += 2;

    if (type1[3] == 'J') i += 1;
    if (type2[3] == 'J') j += 1;

    // 궁합 점수 계산
    int compatibility_score = sia_compatibility_table[i][j];

    printf("%s와 %s의 궁합 점수는 %d%%입니다.\n", type1, type2, compatibility_score);
}
 
void sih_printQ()
{
    char answer;
    printf("\n질문에 Y(예) 또는 N(아니오)로 답해주세요\n");

    for (int i = 0; i < QUESTION_NUM; i++)
    {
        int idx = sih_shuffleQ();
        printf("%d. %s\n", i + 1, sih_Q[idx]);
        scanf(" %c", &answer);
        getchar();
        if (answer == 'N') { sih_cnt[idx / 3] -= 1; }
    }
}

int sih_shuffleQ()
{
    int idx;
    do {
        idx = rand() % QUESTION_NUM;
    } while (sih_used[idx]);
    sih_used[idx] = 1;
    return idx;
}


void sih_printMBTI()
{
    char MBTI[5];

    if (sih_cnt[0] >= 2) {
        MBTI[0] = 'E';
    }
    else MBTI[0] = 'I';

    if (sih_cnt[1] >= 2) {
        MBTI[1] = 'N';
    }
    else MBTI[1] = 'S';
    
    if (sih_cnt[2] >= 2) {
        MBTI[2] = 'T';
    }
    else MBTI[2] = 'F';
    
    
    if (sih_cnt[3] >= 2) {
        MBTI[3] = 'J';
    }
    else MBTI[3] = 'P';

    MBTI[4] = '\0';
    printf("당신의 MBTI는 %s입니다!",MBTI);
}
