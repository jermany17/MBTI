#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "sia_compTable.h"
#include "jun_celebrity.h"

#define QUESTION_NUM 12 // 질문의 총 개수
#define MBTI_NUM 16 // MBTI 갯수
int sih_used[QUESTION_NUM] = { 0 };
int sih_cnt[QUESTION_NUM / 3] = { 3,3,3,3 };
char MBTI[5]; // MBTI 검사 결과 저장
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

const char sih_recommended_jobs[MBTI_NUM][101] = {
    "회계사, 경찰관, 시스템 분석가, 감사관, 법관", // ISTJ
    "간호사, 교사, 사회복지사, 행정직, 식품 서비스 관리자", // ISFJ
    "상담사, 작가, 예술가, 심리학자, 대학 교수", // INFJ
    "CEO, 컨설턴트, 연구원, 변호사, 건축가", // INTJ
    "엔지니어, 기술자, 경주 드라이버, 파이로테크닉스, 경호원", // ISTP
    "예술가, 디자이너, 음악가, 화가, 사진가", // ISFP
    "저널리스트, 사회사업가, 작가, 심리학자, 예술치료사", // INFP
    "과학자, 프로그래머, 철학자, 소프트웨어 엔지니어, 시스템 분석가", // INTP
    "스포츠 선수, 판매원, 경영자, 소방관, 파티 계획자", // ESTP
    "배우, 음식 서비스 직원, 이벤트 플래너, 판매원, 스타일리스트", // ESFP
    "마케터, 교육자, 커뮤니케이션 전문가, 엔터테이너, 사회사업가", // ENFP
    "변호사, 경영 컨설턴트, 엔지니어, 마케터, 신제품 개발자", // ENTP
    "경영자, 군인, 경찰관, 은행원, 프로젝트 관리자", // ESTJ
    "커뮤니티 서비스 직원, 공동체 조직가, 판매원, 교사, 은행원", // ESFJ
    "교육자, 상담사, 사회사업가, 의료 전문가, 식음료 관리자", // ENFJ
    "CEO, 변호사, 컨설턴트, 공학자, 경영자" // ENTJ
};

const char MBTI_TYPES[MBTI_NUM][5] = { // 16가지 MBTI 배열 생성(상수화 시킴) 
    "ISTJ",
    "ISFJ",
    "INFJ",
    "INTJ",
    "ISTP",
    "ISFP",
    "INFP",
    "INTP",
    "ESTP",
    "ESFP",
    "ENFP",
    "ENTP",
    "ESTJ",
    "ESFJ",
    "ENFJ",
    "ENTJ"
}; 

/*
MBTI 별 항목 대응 시킬 수 있도록 MBTI_TYPE 배열 생성함
다른 MBTI 별 추천 항목 넣을 때, 활용하면 좋을 듯
*/

void sih_recommendJob(char MBTI[5]);
void sia_compCheck();
int sih_shuffleQ();
void sih_printQ();
void sih_printMBTI();
void jun_MBTIratio(); // MBTI 퍼센트 결과
void jun_people(char MBTI[5]); // 같은 MBTI 연예인 출력 

int main() {
    sia_compCheck();
    sih_printQ(); // MBTI 질문
    sih_printMBTI(); // MBTI 결과
    jun_people(MBTI);// 같은 MBTI 연예인 출력
    jun_MBTIratio(); // MBTI 퍼센트 결과
    return 0;
}

void sia_compCheck() {
    char type1[5], type2[5];
    int i = 0, j = 0;

    printf("첫 번째 MBTI 유형을 입력하세요: ");
    scanf("%s", type1);
    printf("두 번째 MBTI 유형을 입력하세요: ");
    scanf("%s", type2);

    for (int x = 0; x < 4; x++) { // standardisation of input
        if (type1[x] >= 'a' && type1[x] <= 'z') type1[x] -= 32;
        if (type2[x] >= 'a' && type2[x] <= 'z') type2[x] -= 32;
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
int idx = -1;
for (int i = 0; i < QUESTION_NUM; i++)
{
    if(idx==-1) // 예외처리(잘못된 입력일 경우 같은 질문 출력)
     idx = sih_shuffleQ(); // 무작위로 질문 출력
    printf("%d. %s\n", i + 1, sih_Q[idx]);
    scanf(" %c", &answer);
    getchar();
    switch (answer)
    {
    case 'N':
        sih_cnt[idx / 3] -= 1;
        idx = -1;
        break;
    case 'n':
        sih_cnt[idx / 3] -= 1;
        idx = -1;
        break;

    case 'Y':
        idx = -1;
        break;
    case 'y':
        idx = -1;
        break;

    default:
        printf("잘못된 입력입니다. 다시 입력해주세요\n");
        i--; // 같은 질문 반복
        continue;
    }
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

    sih_recommendJob(MBTI); // 여기다 추천직업 출력 넣었어요.
}


void jun_MBTIratio() { // MBTI 퍼센트 결과
    double E = 0, I = 0, N = 0, S = 0, T = 0, F = 0, J = 0, P = 0;
    E = sih_cnt[0];     // E 대답 개수
    I = 3 - sih_cnt[0]; // I 대답 개수
    N = sih_cnt[1];     // N 대답 개수
    S = 3 - sih_cnt[1]; // S 대답 개수
    T = sih_cnt[2];     // T 대답 개수
    F = 3 - sih_cnt[2]; // F 대답 개수
    J = sih_cnt[3];     // J 대답 개수
    P = 3 - sih_cnt[3]; // P 대답 개수
    printf("\n<MBTI 비율>\n");
    printf("E 비율: %.1f%% I 비율: %.1f%%\n", E / 3 * 100, I / 3 * 100); // 퍼센트 출력
    printf("N 비율: %.1f%% S 비율: %.1f%%\n", N / 3 * 100, S / 3 * 100); // 퍼센트 출력
    printf("T 비율: %.1f%% F 비율: %.1f%%\n", T / 3 * 100, F / 3 * 100); // 퍼센트 출력
    printf("J 비율: %.1f%% P 비율: %.1f%%\n", J / 3 * 100, P / 3 * 100); // 퍼센트 출력
}

void sih_recommendJob(char MBTI[5])
{
    int recommend_index = 0;
    for (int i = 0; i < MBTI_NUM; i++)
    {
        if (strcmp(MBTI, MBTI_TYPES[i])==0) 
        {
            recommend_index = i; // 추천 직업 인덱스 저장
            break;
        }
    }

    printf("\n");
    printf("\n당신에게 추천할 직업은...!\n");
    printf("%s\n", sih_recommended_jobs[recommend_index]);

}

void jun_people(char MBTI[5])
{
    int celebrity_index = 0;
    for (int i = 0; i < MBTI_NUM; i++)
    {
        if (strcmp(MBTI, MBTI_TYPES[i]) == 0)
        {
            celebrity_index = i; // 같은 MBTI 연예인 인덱스 저장
            break;
        }
    }

    printf("\n");
    printf("\n같은 MBTI 연예인은 ?!\n");
    printf("%s\n", jun_celebrity[celebrity_index]);

}
