// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//

#include <stdio.h>
#include "stdafx.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>



// qqView.h : interface of the CQqView class
//
/////////////////////////////////////////////////////////////////////////////
//#if _MSC_VER > 1000
//#pragma once
//#endif // _MSC_VER > 1000
#define name2str(name) (#name)
#define TTT		2//1 position:2
#define RRR		1//2 position:1
#define PPP		-2//4 position:4
#define SSS		0//3 position:2

#define COOPERATE	1.0
#define DEFECT		0.0

#define ROUNDS	50

/* Strategies in IPD tournament */
#define ALLD	0 
#define TFT		1 
#define ALLC	2
#define GRIM	3
#define TFTT	4
#define STFT	5
#define PAVLOV	6
#define RAND	7
#define NEG		8
#define TTFT	9
#define FBF		10
#define GRADUAL		11
#define ADAPTIVE	12
#define C_TFT		13
#define G_TFT		14
#define PROBER		15
#define GROUP		16
#define GROUP1		17



double SStrategy1(int StrategyIndex, double MyLastMove, double OppLastMove, int NumberOfRound, int row, int column);
double SStrategy2(int StrategyIndex, double MyLastMove, double OppLastMove, int NumberOfRound, int row, int column);
double ipd(int strategy1, int strategy2, int rounds, int row, int column, int row1, int column1);
int	competition(int NumOfLine, int NumOfArray, int* Lattice, double* AverageValue);
int	evolution(double* AverageValue, int* Lattice);
int resetpara(void);
int resetpara2(void);

int Lattice[40000];
double AverageValue[40000];
int strID[200][200] = { 0 };

int ParaOfTFTT;
int ParaOfSTFT;
double Rand_Max, Rand_Min;
int ParaOfTTFT;
int Para1OfGRADUAL;
int Para2OfGRADUAL;
int Para3OfGRADUAL;
double ParaOfADAPTIVE;
int ParaOfPROBER;
int ParaOfC_TFT;
int ParaOfGROUP1;
int ParaOfGROUP2;
static int ParaOfGROUP3;
int ParaOfDS001;
int ParaOfDS001_TFT;
int ParaOfDS002;
int ParaOfDS002_TFT;
int ParaMaster1;


int P2OfTFTT;
int P2OfSTFT;
int P2OfTTFT;
int P21OfGRADUAL;
int P22OfGRADUAL;
int P23OfGRADUAL;
double P2OfADAPTIVE;
int P2OfPROBER;
int P2OfC_TFT;
int P2OfGROUP1;
int P2OfGROUP2;
static int P2OfGROUP3;
int P2OfDS001;
int P2OfDS001_TFT;
int P2OfDS002;
int P2OfDS002_TFT;


static COLORREF rgblist[20]{ RGB(255,255,0),RGB(187,255,255),RGB(255,218,185),RGB(84,255,158),RGB(25,25,112),RGB(0,255,0),RGB(106,90,205),RGB(0,255,255),RGB(255,246,112),RGB(0,100,0),RGB(255,255,0),RGB(255,193,37),RGB(205,92,92),RGB(255,215,0),RGB(255,0,0),RGB(155,48,255),RGB(0,191,255),RGB(0,0,255),RGB(255,114,86),RGB(255,215,0) };
// !defined(AFX_QQVIEW_H__A63D46DC_745B_4AB2_BC4F_EEE2662BCB25__INCLUDED_)


int main() {
	//circle(200, 200, 100); // 画圆，圆心(200, 200)，半径 100
	FILE* fp1;
	errno_t err = fopen_s(&fp1, "SIHDG.txt", "a");
	if (err == 0)
		printf("Test.txt opened\n");
	else
		printf("Test.txt not opened\n");

	srand(time(0));

	int turn = 78;
while(turn<1000){
	fprintf(fp1, "turn=%d", turn);
	printf("turn=%d", turn);
	fprintf(fp1, "generation=30, rounds=50");

	float counter[20] = { 0 };
	float ratio[20] = { 0.0 };
	int i, j, n;

	fflush(stdin);
	printf("Strategies index:\n"); printf("[0] ALLD||[1] TFT ||[2] ALLC || [3] GRIM || [4] TFTT || [5] STFT \n"); printf("[6] PAVLOV || [7] RAND || [8] NEG || [9] TTFT || [10] FBF\n");
	printf("Strategies index:\n"); printf("[11] GRADUAL ||[12] ADAPTIVE || [13] C_TFT || [14] G_TFT || [15] PROBE [16] GROUP\n");
	printf("Enter strategy1 and ratio:");
	//	scanf_s("%d %d", &a, &b);
	//	printf("Enter strategy2 and ratio:");1
	//	scanf_s("%d %d", &c, &d);


	srand((unsigned int)time(NULL));
	int value;

	//input
	//ratio[a] = b;
	//ratio[c] = d;
	for (i = 0; i < 20; i++) { printf("%d", counter[i]); }


	for (i = 0; i < 200; i++) {
		for (j = 0; j < 200; j++) {
			/*value = rand() % 100 + 1;
			int rat = 0;
			for (n = 0; n < 20; n++) {
				if (ratio[n] != 0) {
					rat = rat + ratio[n];
					if (value <= rat) {
						Lattice[200 * i + j] = n;
						counter[n]++;
						break;
					}
				}
			}*/
			int randomStr = rand() % 18;
			Lattice[200 * i + j] = randomStr;
			AverageValue[200 * i + j] = 0.0;
		}
	}
	fprintf(fp1, "\ngeneration=0\t");
	for (i = 0; i < 18; i++) {
		counter[i] = 0;
		for (j = 0; j < 40000; j++) {
			if (Lattice[j] == i) {
				counter[i]++;
			}
		}

		ratio[i] = counter[i] / 40000;

		printf("strategy%d=%.4f\n", i, ratio[i]);
		fprintf(fp1, "strategy%d=%.4f\t", i, ratio[i]);
	}
	/*
			int count = 0;
			for (i = 0; i < 200; i++) {
				for (j = 0; j < 200; j++) {
					if (count < b * 400)
					{
						Lattice[200 * i + j] = a;
						count++;
					}
					else
						Lattice[200 * i + j] = c;
				}
			}
	*/
	/*
			FILE* imital;
			if ((imital=fopen("test.txt","w"))==NULL){
			printf("error\n");
			exit(3);
			}
			char as[]=name2str(ALLC);
			for(i=0;i<200;i++){
			for(j=0;j<200;j++){
			if (Lattice[200*i+j]<10){
			fprintf(imital,"0%d",Lattice[200*i+j]);
			}else{
			fprintf(imital,"%d",Lattice[200*i+j]);
			}
			if (j!=199){
			fprintf(imital,",");
			}
			}
			fprintf(imital,"\n");
			}
			for (i=0;i<200;i++){
			for(j=0;j<200;j++){
			if (Lattice[200*i+j]<10){
			printf("0%d",Lattice[200*i+j]);
			}else{
			printf("%d",Lattice[200*i+j]);
			}
			if (j!=199){
			printf(",");
			}
			}
			printf("\n");
			}
			*/
	initgraph(800, 1000, SHOWCONSOLE);
	int numsts = 0;
	for (i = 0; i < 20; i++) {
		if (ratio[i] != 0) {
			setfillcolor(rgblist[i]);
			solidrectangle(60 * numsts + 50, 850, 60 * numsts + 100, 900);
			switch (i) {
			case ALLD:  outtextxy(60 * numsts + 50, 910, _T("ALLD")); break;
			case TFT: outtextxy(60 * numsts + 50, 910, _T("TFT")); break;
			case ALLC: outtextxy(60 * numsts + 50, 910, _T("ALLC")); break;
			case GRIM: outtextxy(60 * numsts + 50, 910, _T("GRIM")); break;
			case TFTT: outtextxy(60 * numsts + 50, 910, _T("TFTT")); break;
			case STFT: outtextxy(60 * numsts + 50, 910, _T("STFT")); break;
			case PAVLOV: outtextxy(60 * numsts + 50, 910, _T("PAVLOV")); break;
			case RAND: outtextxy(60 * numsts + 50, 910, _T("RAND")); break;
			case NEG: outtextxy(60 * numsts + 50, 910, _T("NEG")); break;
			case TTFT: outtextxy(60 * numsts + 50, 910, _T("TTFT")); break;
			case FBF: outtextxy(60 * numsts + 50, 910, _T("FBF")); break;
			case GRADUAL: outtextxy(60 * numsts + 50, 910, _T("GRADUAL")); break;
			case ADAPTIVE: outtextxy(60 * numsts + 50, 910, _T("ADAPTIVE")); break;
			case C_TFT: outtextxy(60 * numsts + 50, 910, _T("C_TFT")); break;
			case G_TFT: outtextxy(60 * numsts + 50, 910, _T("G_TFT")); break;
			case PROBER: outtextxy(60 * numsts + 50, 910, _T("PROBER")); break;
			case GROUP: outtextxy(60 * numsts + 50, 910, _T("GROUP")); break;
			case GROUP1: outtextxy(60 * numsts + 50, 910, _T("GROUP1")); break;
			}
			numsts++;
		}
	}
	int generation = 1;
	do {
		fflush(stdin);
		/*for (i = 0; i < 200; i++) {
			for (j = 0; j < 200; j++) {
				setfillcolor(rgblist[Lattice[200 * i + j]]);
				solidrectangle(4 * j, 4 * i, 4 * j + 2, 4 * i + 2);
			}
		}*/

		//printf("%d------%.4f()------%.4f()\n", generation, counter[a] / 40000.0, counter[c] / 40000.0);
		//fprintf(fp1, "%d\t%.2f\t%.2f\n", generation, counter[a] / 40000.0, counter[c] / 40000.0);

		for (i = 0; i < 200; i++)
		{
			for (j = 0; j < 200; j++)
			{
				if ((rand() % 100) > 50)
					strID[i][j] = 5;
				else
					strID[i][j] = 0;
			}
		}
		competition(200, 200, Lattice, AverageValue);
		evolution(AverageValue, Lattice);
		fprintf(fp1, "\ngeneration=%d\t",generation);
		for (i = 0; i < 18; i++) {
			counter[i] = 0;
			for (j = 0; j < 40000; j++) {
				if (Lattice[j] == i) {
					counter[i]++;
				}
			}

			ratio[i] = counter[i] / 40000;
			printf("strategy%d=%.4f\n", i, ratio[i]);
			fprintf(fp1, "strategy%d=%.4f\t", i, ratio[i]);
		}
		generation++;

	} while (generation < 30);
	fprintf(fp1, "\n\n");
	turn++;
}
		//	while (_getch() != 27);
		fflush(stdin);
		closegraph();
		//readin strategies with name+ratio.
		//rand 40000array with strategies.
		//array->200*200matrix
		//gengration loop start:
		//compition
		//evolution
		//generation loop end
		/*控制台输出验证：
		printf("after one generation:\n");
		for (i=0;i<200;i++){
		for(j=0;j<200;j++){
		if (Lattice[200*i+j]<10){
		printf("0%d",Lattice[200*i+j]);
		}else{
		printf("%d",Lattice[200*i+j]);
		}
		if (j!=199){
		printf(",");
		}
		}
		printf("\n");
		}
		*/
		//控制台输出验证end
		printf("press 'y' to restart\n");
		//} while (_getch() == 'y');

		system("pause");
		fclose(fp1);
		return 0;
	
}
//main up




double SStrategy1(int StrategyIndex, double MyLastMove, double OppLastMove, int NumberOfRound, int row, int column)
{
	double result;
	int asd = strID[row][column];

	switch (StrategyIndex)
	{


	case ALLD:
		return 0.0;

	case TFT:
		return OppLastMove;

	case ALLC:
		return 1.0;

	case GRIM:
		if (OppLastMove <= 0.5 || MyLastMove <= 0.5)
			return 0.0;
		else
			return 1.0;

	case TFTT:
		if (OppLastMove <= 0.5)
			ParaOfTFTT += 1;
		else
			ParaOfTFTT = 0;

		if (ParaOfTFTT >= 2)
		{
			ParaOfTFTT = 2;
			return 0.0;
		}
		else return 1.0;


	case STFT:
		if (NumberOfRound == 0)
			return 0.0;
		else
			return OppLastMove;


	case PAVLOV:
		if (OppLastMove > 0.5 && MyLastMove > 0.5)
			return MyLastMove;
		else if (OppLastMove > 0.5 && MyLastMove <= 0.5)
			return MyLastMove;
		else
		{
			if (MyLastMove > 0.5)
				return 0.0;
			else
				return 1.0;
		}

	case RAND:
		result = (((double)rand() / (double)RAND_MAX) * Rand_Max + Rand_Min);
		if (result > 1.0)
			result = 1.0;
		else if (result < 0.0)
			result = 0.0;
		return result;


	case NEG:
		if (NumberOfRound == 0)
			return DEFECT;
		else if (OppLastMove > 0.5)
			return DEFECT;
		else
			return COOPERATE;


	case TTFT:
		if (OppLastMove <= 0.5)
			ParaOfTTFT = 2;
		if (ParaOfTTFT > 0)
		{
			ParaOfTTFT -= 1;
			return 0.0;
		}
		else
			return 1.0;


	case FBF:
		if (OppLastMove <= 0.5 && MyLastMove <= 0.5)
		{
			result = (((double)rand() / (double)RAND_MAX) * Rand_Max + Rand_Min);
			if (result < 0.333333)
				return 1.0;
			else
				return 0.0;
		}
		else
			return OppLastMove;


	case GRADUAL:
		/* It uses cooperation on the first move and then continues to do so as long as the other player cooperates. Then after the first defection of the other player,
		it defects one time and cooperates two times; after the second defection of the opponent, it defects two times and cooperates two times, ... after
		the nth defection it reacts with n consecutive defections and then calms down its opponent with two cooperations. */
		// Para1OfGRADUAL: The number of opponent's defection
		// Para2OfGRADUAL: The number of retaliations in current moves
		// Para3OfGRADUAL: The number of retaliations and cooperations to be executed
		if (OppLastMove <= 0.5)
			Para1OfGRADUAL++;

		if (Para1OfGRADUAL != Para2OfGRADUAL)
		{
			if (Para3OfGRADUAL == 0)
			{
				Para2OfGRADUAL = Para1OfGRADUAL;
				Para3OfGRADUAL = Para2OfGRADUAL + 1;
				return 0.0;
			}
			else
			{
				if (Para3OfGRADUAL > 2)
				{
					Para3OfGRADUAL--;
					return 0.0;
				}
				else
				{
					Para3OfGRADUAL -= 1;
					return 1.0;
				}
			}
		}

		else
		{
			if (Para3OfGRADUAL == 0)
				return 1.0;
			else
			{
				if (Para3OfGRADUAL > 2)
				{
					Para3OfGRADUAL--;
					return 0.0;
				}
				else
				{
					Para3OfGRADUAL--;
					return 1.0;
				}
			}

		}


	case ADAPTIVE:
		/* the parameter of Adaptive 'world' is set to be 0.6 */
		if (OppLastMove > 0.5)
			ParaOfADAPTIVE += 0.6 * (1.0 - ParaOfADAPTIVE);
		else
			ParaOfADAPTIVE += 0.6 * (0.0 - ParaOfADAPTIVE);

		if (ParaOfADAPTIVE > 0.5)
			return COOPERATE;
		else
			return DEFECT;


	case C_TFT:
		if (MyLastMove <= 0.5 && OppLastMove > 0.5)
			ParaOfC_TFT = 1;

		if ((ParaOfC_TFT == 1) && (OppLastMove <= 0.5))
		{
			ParaOfC_TFT = 0;
			return 1.0;
		}
		else
			return OppLastMove;


	case G_TFT:
		if (OppLastMove <= 0.5)
		{
			result = (((double)rand() / (double)RAND_MAX) * Rand_Max + Rand_Min);
			if (result < 0.333333)
				return 1.0;
			else
				return 0.0;
		}
		else
			return 1.0;


	case PROBER:
		/* begins by playing [cooperate, defect, defect], then if the opponent cooperates on the second and the third move continues to defect, else plays tit-for-tat */
		if (NumberOfRound == 0)
			return 1.0;
		else if (NumberOfRound == 1)
			return 0.0;
		else if (NumberOfRound == 2)
		{
			if (OppLastMove > 0.5)
				ParaOfPROBER++;
			return 0.0;
		}
		else if (NumberOfRound == 3)
		{
			if (OppLastMove > 0.5)
				ParaOfPROBER++;
			if (ParaOfPROBER > 1)
				return 0.0;
			else
				return 1.0;
		}
		else
		{
			if (ParaOfPROBER > 1)
				return 0.0;
			else
				return OppLastMove;
		}



	case GROUP:

		if (NumberOfRound == 0)
		{
			ParaOfGROUP2 = 0;
			return 1.0;
		}
		else if (NumberOfRound == 1)
		{
			if (OppLastMove > 0.5)
				ParaOfGROUP2++;
			else
				ParaOfGROUP2 = -5;
			return 0.0;
		}
		else if (NumberOfRound == 2)
		{
			if (OppLastMove <= 0.5)
				ParaOfGROUP2++;
			else
				ParaOfGROUP2 = -5;
			if (ParaOfGROUP2 > 1)
				return 1.0;
			else
				return 0.0;
		}
		else if (NumberOfRound == 3)
		{
			if (OppLastMove > 0.5)
				ParaOfGROUP2++;
			else
				ParaOfGROUP2 = -5;
			if (ParaOfGROUP2 > 2)
				return 1.0;
			else
				return 0.0;
		}
		else if (NumberOfRound == 4)
		{
			if (OppLastMove > 0.5)
				ParaOfGROUP2++;
			else
				ParaOfGROUP2 = -5;
			return 0.0;
		}
		else if (NumberOfRound == 5)
		{
			if (OppLastMove < 0.5)
				ParaOfGROUP2++;
			else
				ParaOfGROUP2 = -5;
			if (ParaOfGROUP2 > 3)
			{
				if (asd > 0)
					return 0.0;
				else
					return 1.0;
			}
			else
				return 0.0;
		}

		else if (NumberOfRound == 6)
		{
			if (ParaOfGROUP2 > 3)
			{
				if (asd > 0 && OppLastMove < 0.5)
					return 1.0;
				else if (asd > 0 && OppLastMove > 0.5)
				{
					ParaOfGROUP2 = -5;
					return 0.0;
				}

				else
					return 1.0;
			}
			else
				return 0.0;
		}
		else
		{
			if (ParaOfGROUP2 > 3)
			{
				if (asd > 0)
					return 1.0;
				else
					return 1 - OppLastMove;
			}
			else
				return 0.0;
		}
	case GROUP1:

		if (NumberOfRound == 0)
		{
			ParaMaster1 = 0;
			return 1.0;
		}
		else if (NumberOfRound == 1)
		{
			if (OppLastMove > 0.5)
				ParaMaster1++;
			else
				ParaMaster1 = -5;
			return 0.0;
		}
		else if (NumberOfRound == 2)
		{
			if (OppLastMove <= 0.5)
				ParaMaster1++;
			else
				ParaMaster1 = -5;
			if (ParaMaster1 > 1)
				return 1.0;
			else
				return 0.0;
		}
		else if (NumberOfRound == 3)
		{
			if (OppLastMove > 0.5)
				ParaMaster1++;
			else
				ParaMaster1 = -5;

			if (ParaMaster1 > 2)
				return 1.0;
			else
				return 0.0;
		}
		else if (NumberOfRound == 4)
		{
			if (OppLastMove > 0.5)
				ParaMaster1++;
			else
				ParaMaster1 = -5;

			if (ParaMaster1 > 3)
				return 0.0;
			else
				return 0.0;
		}
		else if (NumberOfRound == 5)
		{
			if (OppLastMove < 0.5)
				ParaMaster1++;
			else
				ParaMaster1 = -5;

			if (ParaMaster1 > 3)
				return 1.0;
			else
				return 0.0;
		}
		else
		{
			if (ParaMaster1 > 3 && OppLastMove > 0.5)
				return 1.0;
			else
			{
				ParaMaster1 = -5;
				return 0.0;
			}
		}


	default:
		return 1.1;
	}

	return 1.1;

}

double SStrategy2(int StrategyIndex, double MyLastMove, double OppLastMove, int NumberOfRound, int row, int column)
{
	double result;
	int asd = strID[row][column];

	switch (StrategyIndex)
	{


	case ALLD:
		return 0.0;

	case TFT:
		return OppLastMove;

	case ALLC:
		return 1.0;

	case GRIM:
		if (OppLastMove <= 0.5 || MyLastMove <= 0.5)
			return 0.0;
		else
			return 1.0;

	case TFTT:
		if (OppLastMove <= 0.5)
			P2OfTFTT += 1;
		else
			P2OfTFTT = 0;

		if (P2OfTFTT >= 2)
		{
			P2OfTFTT = 2;
			return 0.0;
		}
		else return 1.0;


	case STFT:
		if (NumberOfRound == 0)
			return 0.0;
		else
			return OppLastMove;


	case PAVLOV:
		if (OppLastMove > 0.5 && MyLastMove > 0.5)
			return MyLastMove;
		else if (OppLastMove > 0.5 && MyLastMove <= 0.5)
			return MyLastMove;
		else
		{
			if (MyLastMove > 0.5)
				return 0.0;
			else
				return 1.0;
		}

	case RAND:
		result = (((double)rand() / (double)RAND_MAX) * Rand_Max + Rand_Min);
		if (result > 1.0)
			result = 1.0;
		else if (result < 0.0)
			result = 0.0;
		return result;


	case NEG:
		if (NumberOfRound == 0)
			return DEFECT;
		else if (OppLastMove > 0.5)
			return DEFECT;
		else
			return COOPERATE;


	case TTFT:
		if (OppLastMove <= 0.5)
			P2OfTTFT = 2;
		if (P2OfTTFT > 0)
		{
			P2OfTTFT -= 1;
			return 0.0;
		}
		else
			return 1.0;


	case FBF:
		if (OppLastMove <= 0.5 && MyLastMove <= 0.5)
		{
			result = (((double)rand() / (double)RAND_MAX) * Rand_Max + Rand_Min);
			if (result < 0.333333)
				return 1.0;
			else
				return 0.0;
		}
		else
			return OppLastMove;


	case GRADUAL:
		/* It uses cooperation on the first move and then continues to do so as long as the other player cooperates. Then after the first defection of the other player,
		it defects one time and cooperates two times; after the second defection of the opponent, it defects two times and cooperates two times, ... after
		the nth defection it reacts with n consecutive defections and then calms down its opponent with two cooperations. */
		// Para1OfGRADUAL: The number of opponent's defection
		// Para2OfGRADUAL: The number of retaliations in current moves
		// Para3OfGRADUAL: The number of retaliations and cooperations to be executed
		if (OppLastMove <= 0.5)
			P21OfGRADUAL++;

		if (P21OfGRADUAL != P22OfGRADUAL)
		{
			if (P23OfGRADUAL == 0)
			{
				P22OfGRADUAL = P21OfGRADUAL;
				P23OfGRADUAL = P22OfGRADUAL + 1;
				return 0.0;
			}
			else
			{
				if (P23OfGRADUAL > 2)
				{
					P23OfGRADUAL--;
					return 0.0;
				}
				else
				{
					P23OfGRADUAL -= 1;
					return 1.0;
				}
			}
		}

		else
		{
			if (P23OfGRADUAL == 0)
				return 1.0;
			else
			{
				if (P23OfGRADUAL > 2)
				{
					P23OfGRADUAL--;
					return 0.0;
				}
				else
				{
					P23OfGRADUAL--;
					return 1.0;
				}
			}

		}


	case ADAPTIVE:
		/* the parameter of Adaptive 'world' is set to be 0.6 */
		if (OppLastMove > 0.5)
			P2OfADAPTIVE += 0.6 * (1.0 - P2OfADAPTIVE);
		else
			P2OfADAPTIVE += 0.6 * (0.0 - P2OfADAPTIVE);

		if (P2OfADAPTIVE > 0.5)
			return COOPERATE;
		else
			return DEFECT;


	case C_TFT:
		if (MyLastMove <= 0.5 && OppLastMove > 0.5)
			P2OfC_TFT = 1;

		if ((P2OfC_TFT == 1) && (OppLastMove <= 0.5))
		{
			P2OfC_TFT = 0;
			return 1.0;
		}
		else
			return OppLastMove;


	case G_TFT:
		if (OppLastMove <= 0.5)
		{
			result = (((double)rand() / (double)RAND_MAX) * Rand_Max + Rand_Min);
			if (result < 0.333333)
				return 1.0;
			else
				return 0.0;
		}
		else
			return 1.0;


	case PROBER:
		/* begins by playing [cooperate, defect, defect], then if the opponent cooperates on the second and the third move continues to defect, else plays tit-for-tat */
		if (NumberOfRound == 0)
			return 1.0;
		else if (NumberOfRound == 1)
			return 0.0;
		else if (NumberOfRound == 2)
		{
			if (OppLastMove > 0.5)
				P2OfPROBER++;
			return 0.0;
		}
		else if (NumberOfRound == 3)
		{
			if (OppLastMove > 0.5)
				P2OfPROBER++;
			if (P2OfPROBER > 1)
				return 0.0;
			else
				return 1.0;
		}
		else
		{
			if (P2OfPROBER > 1)
				return 0.0;
			else
				return OppLastMove;
		}



	case GROUP:

		if (NumberOfRound == 0)
		{
			P2OfGROUP2 = 0;
			return 1.0;
		}
		else if (NumberOfRound == 1)
		{
			if (OppLastMove > 0.5)
				P2OfGROUP2++;
			else
				P2OfGROUP2 = -5;
			return 0.0;
		}
		else if (NumberOfRound == 2)
		{
			if (OppLastMove <= 0.5)
				P2OfGROUP2++;
			else
				P2OfGROUP2 = -5;
			if (P2OfGROUP2 > 1)
				return 1.0;
			else
				return 0.0;
		}
		else if (NumberOfRound == 3)
		{
			if (OppLastMove > 0.5)
				P2OfGROUP2++;
			else
				P2OfGROUP2 = -5;
			if (P2OfGROUP2 > 2)
				return 1.0;
			else
				return 0.0;
		}
		else if (NumberOfRound == 4)
		{
			if (OppLastMove > 0.5)
				P2OfGROUP2++;
			else
				P2OfGROUP2 = -5;
			return 0.0;
		}
		else if (NumberOfRound == 5)
		{
			if (OppLastMove < 0.5)
				P2OfGROUP2++;
			else
				P2OfGROUP2 = -5;
			if (P2OfGROUP2 > 3)
			{
				if (asd > 0)
					return 0.0;
				else
					return 1.0;
			}
			else
				return 0.0;
		}

		else if (NumberOfRound == 6)
		{
			if (P2OfGROUP2 > 3)
			{
				if (asd > 0 && OppLastMove < 0.5)
					return 1.0;
				else if (asd > 0 && OppLastMove > 0.5)
				{
					P2OfGROUP2 = -5;
					return 0.0;
				}

				else
					return 1.0;
			}
			else
				return 0.0;
		}
		else
		{
			if (P2OfGROUP2 > 3)
			{
				if (asd > 0)
					return 1.0;
				else
					return 1 - OppLastMove;
			}
			else
				return 0.0;
		}
	case GROUP1:

		if (NumberOfRound == 0)
		{
			ParaMaster1 = 0;
			return 1.0;
		}
		else if (NumberOfRound == 1)
		{
			if (OppLastMove > 0.5)
				ParaMaster1++;
			else
				ParaMaster1 = -5;
			return 0.0;
		}
		else if (NumberOfRound == 2)
		{
			if (OppLastMove <= 0.5)
				ParaMaster1++;
			else
				ParaMaster1 = -5;
			if (ParaMaster1 > 1)
				return 1.0;
			else
				return 0.0;
		}
		else if (NumberOfRound == 3)
		{
			if (OppLastMove > 0.5)
				ParaMaster1++;
			else
				ParaMaster1 = -5;

			if (ParaMaster1 > 2)
				return 1.0;
			else
				return 0.0;
		}
		else if (NumberOfRound == 4)
		{
			if (OppLastMove > 0.5)
				ParaMaster1++;
			else
				ParaMaster1 = -5;

			if (ParaMaster1 > 3)
				return 0.0;
			else
				return 0.0;
		}
		else if (NumberOfRound == 5)
		{
			if (OppLastMove < 0.5)
				ParaMaster1++;
			else
				ParaMaster1 = -5;

			if (ParaMaster1 > 3)
				return 1.0;
			else
				return 0.0;
		}
		else
		{
			if (ParaMaster1 > 3 && OppLastMove > 0.5)
				return 1.0;
			else
			{
				ParaMaster1 = -5;
				return 0.0;
			}
		}


	default:
		return 1.1;
	}

	return 1.1;

}

int resetpara(void)
{
	ParaOfTFTT = 0;
	ParaOfSTFT = 0;
	Rand_Max = 1.0;
	Rand_Min = 0.0;
	ParaOfTTFT = 0;
	ParaOfPROBER = 0;
	Para1OfGRADUAL = 0;
	Para2OfGRADUAL = 0;
	Para3OfGRADUAL = 0;
	ParaOfADAPTIVE = 1.0;
	ParaOfC_TFT = 0;
	ParaOfGROUP1 = 0;
	ParaOfGROUP2 = 0;
	ParaOfGROUP3 = 0;
	ParaOfDS001 = 0;
	ParaOfDS001_TFT = 0;
	ParaOfDS002 = 0;
	ParaOfDS002_TFT = 0;
	ParaMaster1 = 0;

	return 1;
}

int resetpara2(void)
{
	P2OfTFTT = 0;
	P2OfSTFT = 0;
	Rand_Max = 1.0;
	Rand_Min = 0.0;
	P2OfTTFT = 0;
	P2OfPROBER = 0;
	P21OfGRADUAL = 0;
	P22OfGRADUAL = 0;
	P23OfGRADUAL = 0;
	P2OfADAPTIVE = 1.0;
	P2OfC_TFT = 0;
	P2OfGROUP1 = 0;
	P2OfGROUP2 = 0;
	P2OfGROUP3 = 0;
	P2OfDS001 = 0;
	P2OfDS001_TFT = 0;
	P2OfDS002 = 0;
	P2OfDS002_TFT = 0;

	return 1;
}


double ipd(int strategy1, int strategy2, int rounds, int row, int column, int row1, int column1)
{
	double MyLastMove = 1.0;
	double OppLastMove = 1.0;
	double Move1, Move2, scores;
	int i;

	resetpara();
	resetpara2();
	scores = 0.0;

	//value1 = (double)rand() / (double)RAND_MAX;
	//value2 = (double)rand() / (double)RAND_MAX;
	if (strategy1 == 16 && strategy2 == 16)
		strategy1 = 16;

	int asd = strID[row][column];
	int sdf = strID[row1][column1];


	for (i = 0; i < rounds; i++)
	{
		Move1 = SStrategy1(strategy1, MyLastMove, OppLastMove, i, row, column);
		Move2 = SStrategy2(strategy2, OppLastMove, MyLastMove, i, row1, column1);

		MyLastMove = Move1;
		OppLastMove = Move2;

		if (Move1 > 0.5 && Move2 > 0.5)
		{
			scores += RRR;
			//			scores[strategy2] += RRR;
		}
		else if (Move1 <= 0.5 && Move2 <= 0.5)
		{
			scores += PPP;
			//			scores[strategy2] += PPP;
		}
		else if (Move1 > 0.5 && Move2 <= 0.5)
		{
			scores += SSS;
			//			scores[strategy2] += TTT;
		}
		else
		{
			scores += TTT;
			//			scores[strategy2] += SSS;
		}
	}

	return scores;
}


int	competition(int NumOfLine, int NumOfArray, int* Lattice, double* AverageValue)
{
	int Index[200][200];
	double Value[200][200];
	int i, j;

	for (i = 0; i < NumOfLine; i++)
		for (j = 0; j < NumOfArray; j++)
		{
			Index[i][j] = Lattice[i * 200 + j];
			Value[i][j] = 0.0;
		}

	for (i = 0; i < NumOfLine; i++)
		for (j = 0; j < NumOfArray; j++)
		{
			if (i == 0 && j == 0)
			{
				Value[i][j] += ipd(Index[i][j], Index[0][0], ROUNDS, i, j, 0, 0) / 4.0;
				Value[i][j] += ipd(Index[i][j], Index[0][1], ROUNDS, i, j, 0, 1) / 4.0;
				Value[i][j] += ipd(Index[i][j], Index[1][0], ROUNDS, i, j, 1, 0) / 4.0;
				Value[i][j] += ipd(Index[i][j], Index[1][1], ROUNDS, i, j, 1, 1) / 4.0;
			}
			else if (i == 0 && j == (NumOfArray - 1))
			{
				Value[i][j] += ipd(Index[i][j], Index[i][j], ROUNDS, i, j, i, j) / 4.0;
				Value[i][j] += ipd(Index[i][j], Index[i][j - 1], ROUNDS, i, j, i, j - 1) / 4.0;
				Value[i][j] += ipd(Index[i][j], Index[i + 1][j], ROUNDS, i, j, i + 1, j) / 4.0;
				Value[i][j] += ipd(Index[i][j], Index[i + 1][j - 1], ROUNDS, i, j, i + 1, j - 1) / 4.0;
			}
			else if (i == 0 && j < (NumOfArray - 1))
			{
				Value[i][j] += ipd(Index[i][j], Index[i][j], ROUNDS, i, j, i, j) / 6.0;
				Value[i][j] += ipd(Index[i][j], Index[i][j - 1], ROUNDS, i, j, i, j - 1) / 6.0;
				Value[i][j] += ipd(Index[i][j], Index[i][j + 1], ROUNDS, i, j, i, j + 1) / 6.0;
				Value[i][j] += ipd(Index[i][j], Index[i + 1][j], ROUNDS, i, j, i + 1, j) / 6.0;
				Value[i][j] += ipd(Index[i][j], Index[i + 1][j - 1], ROUNDS, i, j, i + 1, j - 1) / 6.0;
				Value[i][j] += ipd(Index[i][j], Index[i + 1][j + 1], ROUNDS, i, j, i + 1, j + 1) / 6.0;
			}
			else if (i < (NumOfLine - 1) && j == 0)
			{
				Value[i][j] += ipd(Index[i][j], Index[i][j], ROUNDS, i, j, i, j) / 6.0;
				Value[i][j] += ipd(Index[i][j], Index[i - 1][j], ROUNDS, i, j, i - 1, j) / 6.0;
				Value[i][j] += ipd(Index[i][j], Index[i + 1][j], ROUNDS, i, j, i + 1, j) / 6.0;
				Value[i][j] += ipd(Index[i][j], Index[i][j + 1], ROUNDS, i, j, i, j + 1) / 6.0;
				Value[i][j] += ipd(Index[i][j], Index[i - 1][j + 1], ROUNDS, i, j, i - 1, j + 1) / 6.0;
				Value[i][j] += ipd(Index[i][j], Index[i + 1][j + 1], ROUNDS, i, j, i + 1, j + 1) / 6.0;
			}
			else if (i < (NumOfLine - 1) && j == (NumOfArray - 1))
			{
				Value[i][j] += ipd(Index[i][j], Index[i][j], ROUNDS, i, j, i, j) / 6.0;
				Value[i][j] += ipd(Index[i][j], Index[i - 1][j], ROUNDS, i, j, i - 1, j) / 6.0;
				Value[i][j] += ipd(Index[i][j], Index[i + 1][j], ROUNDS, i, j, i + 1, j) / 6.0;
				Value[i][j] += ipd(Index[i][j], Index[i][j - 1], ROUNDS, i, j, i, j - 1) / 6.0;
				Value[i][j] += ipd(Index[i][j], Index[i - 1][j - 1], ROUNDS, i, j, i - 1, j - 1) / 6.0;
				Value[i][j] += ipd(Index[i][j], Index[i + 1][j - 1], ROUNDS, i, j, i + 1, j - 1) / 6.0;
			}
			else if (i < (NumOfLine - 1))
			{
				Value[i][j] += ipd(Index[i][j], Index[i][j], ROUNDS, i, j, i, j) / 9.0;
				Value[i][j] += ipd(Index[i][j], Index[i - 1][j], ROUNDS, i, j, i - 1, j) / 9.0;
				Value[i][j] += ipd(Index[i][j], Index[i + 1][j], ROUNDS, i, j, i + 1, j) / 9.0;
				Value[i][j] += ipd(Index[i][j], Index[i][j - 1], ROUNDS, i, j, i, j - 1) / 9.0;
				Value[i][j] += ipd(Index[i][j], Index[i - 1][j - 1], ROUNDS, i, j, i - 1, j - 1) / 9.0;
				Value[i][j] += ipd(Index[i][j], Index[i + 1][j - 1], ROUNDS, i, j, i + 1, j - 1) / 9.0;
				Value[i][j] += ipd(Index[i][j], Index[i][j + 1], ROUNDS, i, j, i, j + 1) / 9.0;
				Value[i][j] += ipd(Index[i][j], Index[i - 1][j + 1], ROUNDS, i, j, i - 1, j + 1) / 9.0;
				Value[i][j] += ipd(Index[i][j], Index[i + 1][j + 1], ROUNDS, i, j, i + 1, j + 1) / 9.0;
			}
			else if (i == (NumOfLine - 1) && j == 0)
			{
				Value[i][j] += ipd(Index[i][j], Index[i][j], ROUNDS, i, j, i, j) / 4.0;
				Value[i][j] += ipd(Index[i][j], Index[i - 1][j], ROUNDS, i, j, i - 1, j) / 4.0;
				Value[i][j] += ipd(Index[i][j], Index[i][j + 1], ROUNDS, i, j, i, j + 1) / 4.0;
				Value[i][j] += ipd(Index[i][j], Index[i - 1][j + 1], ROUNDS, i, j, i - 1, j + 1) / 4.0;
			}
			else if (i == (NumOfLine - 1) && j == (NumOfArray - 1))
			{
				Value[i][j] += ipd(Index[i][j], Index[i][j], ROUNDS, i, j, i, j) / 4.0;
				Value[i][j] += ipd(Index[i][j], Index[i - 1][j], ROUNDS, i, j, i - 1, j) / 4.0;
				Value[i][j] += ipd(Index[i][j], Index[i][j - 1], ROUNDS, i, j, i, j - 1) / 4.0;
				Value[i][j] += ipd(Index[i][j], Index[i - 1][j - 1], ROUNDS, i, j, i - 1, j - 1) / 4.0;
			}
			else
			{
				Value[i][j] += ipd(Index[i][j], Index[i][j], ROUNDS, i, j, i, j) / 6.0;
				Value[i][j] += ipd(Index[i][j], Index[i][j - 1], ROUNDS, i, j, i, j - 1) / 6.0;
				Value[i][j] += ipd(Index[i][j], Index[i][j + 1], ROUNDS, i, j, i, j + 1) / 6.0;
				Value[i][j] += ipd(Index[i][j], Index[i - 1][j], ROUNDS, i, j, i - 1, j) / 6.0;
				Value[i][j] += ipd(Index[i][j], Index[i - 1][j - 1], ROUNDS, i, j, i - 1, j - 1) / 6.0;
				Value[i][j] += ipd(Index[i][j], Index[i - 1][j + 1], ROUNDS, i, j, i - 1, j + 1) / 6.0;
			}

		}

	for (i = 0; i < NumOfLine; i++)
		for (j = 0; j < NumOfArray; j++)
		{
			AverageValue[200 * i + j] = Value[i][j];
		}

	return 1;
}

int	evolution(double* AverageValue, int* Lattice)
{
	int Index[200][200], trans[200][200];
	double Value[200][200], value1;
	int i, j;

	for (i = 0; i < 200; i++)
		for (j = 0; j < 200; j++)
		{
			Index[i][j] = Lattice[i * 200 + j];
			trans[i][j] = Index[i][j];
			Value[i][j] = AverageValue[i * 200 + j];
		}


	for (i = 0; i < 200; i++)
		for (j = 0; j < 200; j++)
		{
			value1 = Value[i][j];

			if (j - 1 > 0) {
				if (value1 < Value[i][j - 1])
				{
					//printf("value1=%lf. ", value1);
					value1 = Value[i][j - 1];
					trans[i][j] = Index[i][j - 1];
					if (trans[i][j] < 0) {
						printf("Value[%d][%d]=%lf. ", i, j - 1, Value[i][j - 1]);
						printf("1:trans[%d, %d]=%d", i, j, trans[i][j]);
					}

				}
				// else if (value1 == Value[i][j - 1])
				// {
				// 	if ((rand() % 100) > 98)
				// 		trans[i][j] = Index[i][j - 1];
				// 	if (trans[i][j] < 0) {
				// 		//printf("value1=%lf. ", value1);
				// 		printf("Value[%d][%d]=%lf. ", i, j - 1, Value[i][j - 1]);
				// 		printf("2:trans[%d, %d]=%d", i, j, trans[i][j]);
				// 	}
				// }
			}

			if (j + 1 < 200) {
				if (value1 < Value[i][j + 1])
				{
					//printf("value1=%lf. ", value1);
					value1 = Value[i][j + 1];
					trans[i][j] = Index[i][j + 1];
					if (trans[i][j] < 0) {
						printf("Value[%d][%d]=%lf. ", i, j + 1, Value[i][j + 1]);
						printf("3:trans[%d, %d]=%d", i, j, trans[i][j]);
					}
				}
				// else if (value1 == Value[i][j + 1])
				// {
				// 	if ((rand() % 100) > 98)
				// 		trans[i][j] = Index[i][j + 1];
				// 	if (trans[i][j] < 0) {
				// 		//printf("value1=%lf. ", value1);
				// 		printf("Value[%d][%d]=%lf. ", i, j + 1, Value[i][j + 1]);
				// 		printf("4:trans[%d, %d]=%d", i, j, trans[i][j]);
				// 	}
				// }
			}



			if ((i - 1 > 0) && (j - 1 > 0)) {
				if (value1 < Value[i - 1][j - 1])
				{
					//printf("value1=%lf. ", value1);
					value1 = Value[i - 1][j - 1];
					trans[i][j] = Index[i - 1][j - 1];
					if (trans[i][j] < 0) {
						printf("Value[%d][%d]=%lf. ", i - 1, j - 1, Value[i - 1][j - 1]);
						printf("5:trans[%d, %d]=%d", i, j, trans[i][j]);
					}
				}
				// else if (value1 == Value[i - 1][j - 1])
				// {
				// 	if ((rand() % 100) > 98)
				// 		trans[i][j] = Index[i - 1][j - 1];

				// 	if (trans[i][j] < 0) {
				// 		//printf("value1=%lf. ", value1);
				// 		printf("Value[%d][%d]=%lf. ", i - 1, j - 1, Value[i - 1][j - 1]);
				// 		printf("6:trans[%d, %d]=%d", i, j, trans[i][j]);
				// 	}
				// }
			}

			if ((i - 1 > 0) && (j + 1 < 200)) {
				if (value1 < Value[i - 1][j + 1])
				{
					//printf("value1=%lf. ", value1);
					value1 = Value[i - 1][j + 1];
					trans[i][j] = Index[i - 1][j + 1];
					if (trans[i][j] < 0) {
						printf("Value[%d][%d]=%lf. ", i - 1, j + 1, Value[i - 1][j + 1]);
						printf("7:trans[%d, %d]=%d", i, j, trans[i][j]);
					}
				}
				// else if (value1 == Value[i - 1][j + 1])
				// {
				// 	if ((rand() % 100) > 98)
				// 		trans[i][j] = Index[i - 1][j + 1];
				// 	if (trans[i][j] < 0) {
				// 		//printf("value1=%lf. ", value1);
				// 		printf("Value[%d][%d]=%lf. ", i - 1, j + 1, Value[i - 1][j + 1]);
				// 		printf("8:trans[%d, %d]=%d", i, j, trans[i][j]);
				// 	}
				// }
			}

			if ((i + 1 < 200) && (j - 1 > 0)) {
				if (value1 < Value[i + 1][j - 1])
				{
					//	printf("value1=%lf. ", value1);
					value1 = Value[i + 1][j - 1];
					trans[i][j] = Index[i + 1][j - 1];
					if (trans[i][j] < 0) {
						printf("Value[%d][%d]=%lf. ", i + 1, j - 1, Value[i + 1][j - 1]);
						printf("9:trans[%d, %d]=%d", i, j, trans[i][j]);
					}
				}
				// else if (value1 == Value[i + 1][j - 1])
				// {
				// 	if ((rand() % 100) > 98)
				// 		trans[i][j] = Index[i + 1][j - 1];
				// 	if (trans[i][j] < 0) {
				// 		//printf("value1=%lf. ", value1);
				// 		printf("Value[%d][%d]=%lf. ", i + 1, j - 1, Value[i + 1][j - 1]);
				// 		printf("10:trans[%d, %d]=%d", i, j, trans[i][j]);
				// 	}
				// }
			}

			if ((i + 1 < 200) && (j + 1 < 200)) {
				if (value1 < Value[i + 1][j + 1])
				{
					//printf("value1=%lf. ", value1);
					value1 = Value[i + 1][j + 1];
					trans[i][j] = Index[i + 1][j + 1];
					if (trans[i][j] < 0) {
						printf("Value[%d][%d]=%lf. ", i + 1, j + 1, Value[i + 1][j + 1]);
						printf("11:trans[%d, %d]=%d", i, j, trans[i][j]);
					}
				}
				// else if (value1 == Value[i + 1][j + 1])
				// {
				// 	if ((rand() % 100) > 98)
				// 		trans[i][j] = Index[i + 1][j + 1];
				// 	if (trans[i][j] < 0) {
				// 		//printf("value1=%lf. ", value1);
				// 		printf("Value[%d][%d]=%lf. ", i + 1, j + 1, Value[i + 1][j + 1]);
				// 		printf("12:trans[%d, %d]=%d", i, j, trans[i][j]);
				// 	}
				// }
			}

			if (i - 1 > 0) {
				if (value1 < Value[i - 1][j])
				{
					//printf("value1=%lf. ", value1);
					value1 = Value[i - 1][j];
					trans[i][j] = Index[i - 1][j];
					if (trans[i][j] < 0) {
						printf("Value[%d][%d]=%lf. ", i - 1, j, Value[i - 1][j]);
						printf("13:trans[%d, %d]=%d", i, j, trans[i][j]);
					}
				}
				// else if (value1 == Value[i - 1][j])
				// {
				// 	if ((rand() % 100) > 98)
				// 		trans[i][j] = Index[i - 1][j];
				// 	if (trans[i][j] < 0) {
				// 		//printf("value1=%lf. ", value1);
				// 		printf("Value[%d][%d]=%lf. ", i - 1, j, Value[i - 1][j]);
				// 		printf("14:trans[%d, %d]=%d", i, j, trans[i][j]);
				// 	}
				// }
			}


			if (i + 1 < 200) {
				if (value1 < Value[i + 1][j])
				{

					//printf("value1=%lf. ", value1);
					value1 = Value[i + 1][j];
					trans[i][j] = Index[i + 1][j];
					if (trans[i][j] < 0) {
						printf("Value[%d][%d]=%lf. ", i + 1, j, Value[i + 1][j]);
						printf("15:trans[%d, %d]=%d", i, j, trans[i][j]);
					}
				}
				// else if (value1 == Value[i + 1][j])
				// {
				// 	if ((rand() % 100) > 98)
				// 		trans[i][j] = Index[i + 1][j];
				// 	if (trans[i][j] < 0) {
				// 		//printf("value1=%lf. ", value1);
				// 		printf("Value[%d][%d]=%lf. ", i + 1, j, Value[i + 1][j]);
				// 		printf("16:trans[%d, %d]=%d", i, j, trans[i][j]);
				// 	}
				// }
			}


		}

	for (i = 0; i < 200; i++)
		for (j = 0; j < 200; j++)
		{
			Lattice[(i) * 200 + j] = trans[i][j];
		}

	return 0;
}












