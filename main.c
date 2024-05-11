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
    compCheck();

    return 0;
}

void sia_compCheck() {
    char type1[5], type2[5];
    int i = 0, j = 0;

    printf("ù ��° MBTI ������ �Է��ϼ���: ");
    scanf("%s", type1);
    printf("�� ��° MBTI ������ �Է��ϼ���: ");
    scanf("%s", type2);

    // MBTI ������ ���� �ε����� ��ȯ
    if (type1[0] == 'E') i += 8;
    if (type2[0] == 'E') j += 8;

    if (type1[1] == 'S') i += 4;
    if (type2[1] == 'S') j += 4;

    if (type1[2] == 'F') i += 2;
    if (type2[2] == 'F') j += 2;

    if (type1[3] == 'J') i += 1;
    if (type2[3] == 'J') j += 1;

    // ���� ���� ���
    int compatibility_score = sia_compatibility_table[i][j];

    printf("%s�� %s�� ���� ������ %d%%�Դϴ�.\n", type1, type2, compatibility_score);
}