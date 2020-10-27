#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define LEN 30
#include "main.h"
char reverseNo1[LEN], reverseNo2[LEN], resultAnswer[2*LEN], input1[LEN], input2[LEN];
bool isPositive = 1, isMul = 0;
int no1Length = 0, no2Length = 0, borrow = 0;
int carr[2 * LEN] = { 0 };

int main(void) {
	test();
	printf("abc");
	return 0;
}

void Print(char result[], bool isPositive){
	int i;
	if (isPositive)	printf("+");
	else printf("-");
	for (i = LEN - 1; i > 0; i--)
		if (result[i] != 0) break;
	for (; i >= 0; i--)	printf("%d", result[i]);
	printf("\n");
}

void init() {
	for (int i = 0; i < LEN; i++) {
		reverseNo1[i] = 0;
		reverseNo2[i] = 0;
	}
	for (int i = 0; i < 2 * LEN; i++) {
		resultAnswer[i] = 0;
		carr[i] = 0;
	}
	isMul = 0;
	isPositive = 1;
}

void checkWhichBiggerAndWriteReverse(char no1[], char no2[], bool isNo1Negative) {
	//�P�_���t
	if (no1Length > no2Length) {
		isPositive = !isNo1Negative;
		writeInReverseArr(no1, no2, false);
	}else if (no1Length < no2Length){
		isPositive = isNo1Negative;
		writeInReverseArr(no1, no2, true);
	}else {
		for (int i = 0; i < no1Length; i++) {
			if (no1[i] > no2[i]) {
				isPositive = !isNo1Negative;
				writeInReverseArr(no1, no2, false);
				break;
			}else if (no1[i] < no2[i]) {
				isPositive = isNo1Negative;
				writeInReverseArr(no1, no2, true);
				break;
			}
		}
	}
}

void writeInReverseArr(char no1[], char no2[], bool needSwitch) {
	switch (needSwitch) {
		case true://switch //�⵴���Ȥj�����e��   ex: -1+2 = -(2-1)
			for (int i = 0; i < no1Length; i++)	reverseNo2[i] = no1[no1Length - i - 1] - '0';
			for (int i = 0; i < no2Length; i++)	reverseNo1[i] = no2[no2Length - i - 1] - '0';
			break;
		case false:
			for (int i = 0; i < no1Length; i++)	reverseNo1[i] = no1[no1Length - i - 1] - '0';
			for (int i = 0; i < no2Length; i++)	reverseNo2[i] = no2[no2Length - i - 1] - '0';
			break;
	}
}

void startCouning(char no1[], char no2[], int type) {
	no1Length = strlen(no1);
	no2Length = strlen(no2);

	//�u���[ //�u����
	if (type == 1 || type == 4){
		writeInReverseArr(no1, no2, false);
		calculation(true);
	}//�u����
	else if(type == 2){
		checkWhichBiggerAndWriteReverse(no1, no2, true);
		calculation(false);
	}//�u����
	else if(type == 3){
		checkWhichBiggerAndWriteReverse(no1, no2, false);
		calculation(false);
	}
	Print(resultAnswer, isPositive);
}

void calculation(bool isRealAdd) {
	switch (isRealAdd) {
	case true:
		if (isMul) {
			for (int i = 0; i < LEN; ++i){
				for (int j = 0; i + j < LEN; ++j) {
					if (reverseNo1[i] == 0 || reverseNo1[i] == -3 || reverseNo2[j] == -3)	continue;
					//char�d���q -128 �� 127
					while (127 - resultAnswer[i + j] < reverseNo1[i] * reverseNo2[j]){
						carr[i + j + 1] += resultAnswer[i + j] / 10;
						resultAnswer[i + j] %= 10;
					}
					resultAnswer[i + j] += reverseNo1[i] * reverseNo2[j];
				}
			}
		}
		else {
			for (int i = 0; i < LEN; i++) {
				//���פ@�� //ASCII - '0' �ҥH'-' = -3
				if (reverseNo1[i] == -3 && reverseNo2[i] == -3)	resultAnswer[i] = 0;
				else if (reverseNo1[i] == -3)	resultAnswer[i] = reverseNo2[i];
				else if (reverseNo2[i] == -3)	resultAnswer[i] = reverseNo1[i];
				else resultAnswer[i] = reverseNo1[i] + reverseNo2[i];
			}
		}
		addCarry();
		break;
	case false:
		for (int i = 0; i < LEN; i++) {
			if (reverseNo1[i] == -3 && reverseNo2[i] == -3)	resultAnswer[i] = 0;
			else if (reverseNo1[i] == -3)	resultAnswer[i] = 0 - reverseNo2[i];
			else if (reverseNo2[i] == -3)	resultAnswer[i] = reverseNo1[i];
			else resultAnswer[i] = reverseNo1[i] - reverseNo2[i] - borrow;
		}
		minusBorrow();
		break;
	}
}

void addCarry() {
	if (isMul) {
		for (int i = 0; i < LEN; ++i) {
			while (127 - resultAnswer[i] < carr[i]) {
				carr[i + 1] += resultAnswer[i] / 10;
				resultAnswer[i] %= 10;
			}
			resultAnswer[i] += carr[i];
			carr[i + 1] += resultAnswer[i] / 10;
			resultAnswer[i] %= 10;
		}
	}else {
		for (int i = 0; i < LEN - 1; i++) {
			if (resultAnswer[i] >= 10) {
				resultAnswer[i + 1] += resultAnswer[i] / 10;
				resultAnswer[i] = resultAnswer[i] % 10;
			}
		}
	}
}

void minusBorrow() {
	for (int i = 0; i < LEN; i++) {
		if (resultAnswer[i] < 0){
			borrow = 1;
			resultAnswer[i] += 10;
		}else borrow = 0;
	}
}

void Add(char no1[], char no2[]) {
	//�t�t/�t��/���t/���� //'-'��ASCII = 45
	if (no1[0] == 45 && no2[0] == 45) {
		isPositive = 0;
		startCouning(no1, no2, 1);
	}else if (no1[0] == 45)	startCouning(no1, no2, 2);
	else if (no2[0] == 45)	startCouning(no1, no2, 3);
	else startCouning(no1, no2, 4);
}

void Subtract(char no1[], char no2[]) {
	//�t�t/�t��/���t/���� ---- �t���t = �t�[�� = Add ��type 2...�H������
	if (no1[0] == 45 && no2[0] == 45)	startCouning(no1, no2, 2);
	else if (no1[0] == 45) {
		isPositive = 0;
		startCouning(no1, no2, 1);
	}else if (no2[0] == 45)	startCouning(no1, no2, 4);
	else startCouning(no1, no2, 3);
}

void Multiply(char no1[], char no2[]) {
	isMul = 1;
	isPositive = 1;
	if ((no1[0] == 45 && no2[0] != 45) || (no1[0] != 45 && no2[0] == 45))	isPositive = 0;
	startCouning(no1, no2, 4);
}

void excuteOperation(char no1[], char no2[], char operator[]) {
	init();
	if (operator[0] == '+') Add(no1, no2);
	else if (operator[0] == '-') Subtract(no1, no2);
	else if (operator[0] == '*') Multiply(no1, no2);
}

void test() {
	excuteOperation("9999999", "987", "+");	printf("+10000986\n\n");
	excuteOperation("-9999999", "-987", "+");	printf("-10000986\n\n");
	excuteOperation("1111333", "333", "+");	printf("+1111666\n\n");
	excuteOperation("333", "1111333", "+");	printf("+1111666\n\n");
	excuteOperation("333", "-1111333", "+");	printf("-1111000\n\n");
	excuteOperation("-333", "1111333", "+");	printf("+1111000\n\n");
	excuteOperation("-9999999", "987", "-");	printf("-10000986\n\n");
	excuteOperation("9999999", "-987", "-");	printf("+10000986\n\n");
	excuteOperation("9999999", "987", "-");	printf("+9999012\n\n");
	excuteOperation("-9999999", "-987", "-");	printf("-9999012\n\n");
	excuteOperation("333", "1111333", "-");	printf("-1111000\n\n");
	excuteOperation("0", "0", "*");	printf("+0\n\n");
	excuteOperation("123", "123", "*");	printf("+15129\n\n");
	excuteOperation("-123", "123", "*");	printf("-15129\n\n");
	excuteOperation("123", "-123", "*");	printf("-15129\n\n");
	excuteOperation("-123", "-123", "*");	printf("+15129\n\n");
	excuteOperation("1231", "123", "*");	printf("+151413\n\n");
	excuteOperation("-123", "1231", "*");	printf("-151413\n\n");
	excuteOperation("-2", "9999999999999999999999999999", "*");	printf("-19999999999999999999999999998\n\n");
	excuteOperation("9999999999999999999999999999", "-2", "*");	printf("-19999999999999999999999999998\n\n");
}
