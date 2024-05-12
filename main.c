#pragma warning(disable:4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>
#include "sia_compTable.h"

void sia_compCheck();

int main() {
    sia_compCheck();

    return 0;
}

void sia_compCheck() {
    char type1[5], type2[5];
    int i = 0, j = 0;

    printf("첫 번째 MBTI 유형을 입력하세요: ");
    scanf("%s", type1);
    printf("두 번째 MBTI 유형을 입력하세요: ");
    scanf("%s", type2);

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