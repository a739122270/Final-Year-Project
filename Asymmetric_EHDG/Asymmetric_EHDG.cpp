#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <graphics.h>
#include <conio.h>
#include <math.h>


#define name2str(name) (#name)
#define HH		-0.5//-0.5/k
#define DD		2.0//2k 
#define HD		2.0//-2
#define DH		0.0//0
#define k		0.8

#define COOPERATE	1.0
#define DEFECT		0.0

#define ROUNDS 1
#define ALLD	0 
#define ALLC	1


double SStrategy1(int StrategyIndex, double MyLastMove, double OppLastMove, int NumberOfRound, int row, int column);
double SStrategy2(int StrategyIndex, double MyLastMove, double OppLastMove, int NumberOfRound, int row, int column);
double ipd(int strategy1, int strategy2, int rounds, int row, int column, int row1, int column1);
int	competition(int NumOfLine, int NumOfArray, int* Lattice, double* AverageValue);
int	evolution(double* AverageValue, int* Lattice);

int Lattice[10000];
double AverageValue[10000];
int strID[200][200] = { 0 };
int strength[10000];



static COLORREF rgblist[20]{ RGB(255,255,0),RGB(187,255,255),RGB(255,218,185),RGB(84,255,158),RGB(25,25,112),RGB(0,255,0),RGB(106,90,205),RGB(0,255,255),RGB(255,246,112),RGB(0,100,0),RGB(255,255,0),RGB(255,193,37),RGB(205,92,92),RGB(255,215,0),RGB(255,0,0),RGB(155,48,255),RGB(0,191,255),RGB(0,0,255),RGB(255,114,86),RGB(255,215,0) };
// !defined(AFX_QQVIEW_H__A63D46DC_745B_4AB2_BC4F_EEE2662BCB25__INCLUDED_)


int main() {
	//circle(200, 200, 100); // 画圆，圆心(200, 200)，半径 100
	FILE* fp1;
	errno_t err = fopen_s(&fp1, "AEHDG_ratio91.txt", "a");
	if (err == 0)
		printf("Test.txt opened\n");
	else
		printf("Test.txt not opened\n");


	//fprintf(fp1, "generation=100, rounds=1");
	int turn = 0;
	while (turn < 50) {
		float counter[2] = { 0 };
		float ratio[2] = { 0.0 };
		int i, j, n;

		fflush(stdin);
		printf("Strategies index:\n"); printf("[0] ALLD||[1] TFT ||[2] ALLC || [3] GRIM || [4] TFTT || [5] STFT \n"); printf("[6] PAVLOV || [7] RAND || [8] NEG || [9] TTFT || [10] FBF\n");
		printf("Strategies index:\n"); printf("[11] GRADUAL ||[12] ADAPTIVE || [13] C_TFT || [14] G_TFT || [15] PROBE [16] GROUP\n");
		printf("Enter strategy1 and ratio:");
		int a = 0, b = 0, c = 0, d = 0;

		a = 0;
		b = 90;
		c = 1;
		d = 10;

		srand((unsigned int)time(NULL));
		int value;
		int bsvalue;
		//input
		ratio[a] = b;
		ratio[c] = d;
		//for (i = 0; i < 20; i++) { printf("%d", counter[i]); }
		float counter0[2] = { 0 };
		float counter1[2] = { 0 };
		int bigcompany=0;
		int smallcompany=0;
		for (i = 0; i < 100; i++) {
			for (j = 0; j < 100; j++) {
				value = rand() % 100 + 1;
				bsvalue = rand() % 100 + 1;
				if (bsvalue <= 30) {
					strength[100 * i + j]=1;//big
					bigcompany++;
				}
				else {
					strength[100 * i + j]=0;//small
					smallcompany++;
				}
				int rat = 0;
				for (n = 0; n < 2; n++) {
					if (ratio[n] != 0) {
						rat = rat + ratio[n];
						if (value <= rat) {
							Lattice[100 * i + j] = n;
							counter[n]++;
							break;
						}

					}
				}
				// int randomStr = rand() % 2;
				// Lattice[200 * i + j] = randomStr;
				AverageValue[100 * i + j] = 0.0;
			}
		}
		
		//fprintf(fp2, "\nturn=%d,generation=0,", turn);
		printf("big=%d, small=%d", bigcompany, smallcompany);
		// for (j = 0; j < 10000; j++) {
		// 	fprintf(fp2, "%d,", Lattice[j]);
		// 	fprintf(fp2, "%d,", strength[j]);
		// }

		for (i = 0; i < 2; i++) {
			counter[i] = 0;
			counter0[i]=0;
			counter1[i]=0;
			for (j = 0; j < 10000; j++) {
				if (Lattice[j] == i) {
					counter[i]++;
					if (strength[j]==0){
						counter0[i]++;
					}
					else if (strength[j]==1){
						counter1[i]++;
					}
				}
			}
			ratio[i] = counter[i] / 10000;			
			printf("strategy%d=%.4f\n", i, ratio[i]);
			printf("smallcompany=%.4f\n", counter0[i] / smallcompany);
			printf("bigcompany=%.4f\n", counter1[i] / bigcompany);
			fprintf(fp1, "turn=%d,generation=0,", turn);
			fprintf(fp1, "smallcompany=%.4f,", counter0[i] / smallcompany);
			fprintf(fp1, "bigcompany=%.4f,", counter1[i] / bigcompany);
			fprintf(fp1, "strategy%d=%.4f\n", i, ratio[i]);
		}

		initgraph(800, 1000, SHOWCONSOLE);
		int numsts = 0;
		for (i = 0; i < 2; i++) {
			if (ratio[i] != 0) {
				//setfillcolor(rgblist[i]);
				//solidrectangle(60 * numsts + 50, 850, 60 * numsts + 100, 900);
				switch (i) {
				case ALLD:  outtextxy(60 * numsts + 50, 910, _T("ALLD")); break;
				case ALLC: outtextxy(60 * numsts + 50, 910, _T("ALLC")); break;
				}
				numsts++;
			}
		}
		int generation = 1;
		do {
			fflush(stdin);
			for (i = 0; i < 100; i++) {
				for (j = 0; j < 100; j++) {
					//setfillcolor(rgblist[Lattice[100 * i + j]]);
					//solidrectangle(4 * j, 4 * i, 4 * j + 2, 4 * i + 2);
				}
			}

			//printf("%d------%.4f()------%.4f()\n", generation, counter[a] / 40000.0, counter[c] / 40000.0);
			//fprintf(fp1, "%d\t%.2f\t%.2f\n", generation, counter[a] / 40000.0, counter[c] / 40000.0);

			for (i = 0; i < 100; i++)
			{
				for (j = 0; j < 100; j++)
				{
					if ((rand() % 100) > 50)
						strID[i][j] = 1;
					else
						strID[i][j] = 0;
				}
			}
			competition(100, 100, Lattice, AverageValue);
			evolution(AverageValue, Lattice);
			printf("turn=%d generation=%d", turn, generation);
			// for (j = 0; j < 10000; j++) {
			// 	fprintf(fp2, "%d,", Lattice[j]);
			// 	fprintf(fp2, "%d,", strength[j]);
			// }
			for (i = 0; i < 2; i++) {
				counter[i] = 0;
				counter0[i]=0;
				counter1[i]=0;
				for (j = 0; j < 10000; j++) {
					if (Lattice[j] == i) {
						counter[i]++;
						if (strength[j]==0){
							counter0[i]++;
						}
						else if (strength[j]==1){
							counter1[i]++;
						}
					}
				}
				ratio[i] = counter[i] / 10000;
				printf("strategy%d=%.4f\n", i, ratio[i]);
				printf("smallcompany=%.4f\n", counter0[i] / smallcompany);
				printf("bigcompany=%.4f\n", counter1[i] / bigcompany);
				fprintf(fp1, "turn=%d,generation=%d,", turn, generation);
			fprintf(fp1, "smallcompany=%.4f,", counter0[i] / smallcompany);
			fprintf(fp1, "bigcompany=%.4f,", counter1[i] / bigcompany);
			fprintf(fp1, "strategy%d=%.4f\n", i, ratio[i]);
			}
			generation++;

		} while (generation < 100);
		fprintf(fp1, "\n\n");
		turn++;
	}
	//	while (_getch() != 27);
	fflush(stdin);
	closegraph();

	printf("press 'y' to restart\n");
	//} while (_getch() == 'y');

	system("pause");
	fclose(fp1);
	return 0;

}
//main up




double SStrategy1(int StrategyIndex, double MyLastMove, double
	OppLastMove, int NumberOfRound, int row, int column)
{
	double result;
	int asd = strID[row][column];

	switch (StrategyIndex)
	{
	case ALLD:
		return 0.0;

	case ALLC:
		return 1.0;

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

	case ALLC:
		return 1.0;
	}

	return 1.1;

}

double ipd(int strategy1, int strategy2, int rounds, int row, int column, int row1, int column1)
{
	double MyLastMove = 1.0;
	double OppLastMove = 1.0;
	double Move1, Move2, scores;
	int i;

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

		if(Move1 > 0.5 && Move2 <= 0.5){
			scores += DH;
		}
		else if (Move1 > 0.5 && Move2 > 0.5){
			if(strength[100 * row + column]==strength[100 * row1 + column1]){
				scores += 1;
			}
			else if(strength[100 * row + column]==1) {//big
				scores += DD*k;
			}else{
				scores += DD*(1-k);
			}

		}
		else if(Move1 <= 0.5 && Move2 > 0.5){
			scores += HD;
		}
		else{
			if(strength[100 * row + column]==strength[100 * row1 + column1]){
				scores += -1;
			}
			else if(strength[100 * row + column]==1) {//big
				scores += HH/k;
			}else{
				scores += HH/(1-k);
			}
		}

		// if (Move1 > 0.5 && Move2 > 0.5)
		// {
		// 	scores += RRR;
		// 	//			scores[strategy2] += RRR;
		// }
		// else if (Move1 <= 0.5 && Move2 <= 0.5)
		// {
		// 	scores += PPP;
		// 	//			scores[strategy2] += PPP;
		// }
		// else if (Move1 > 0.5 && Move2 <= 0.5)
		// {
		// 	scores += SSS;
		// 	//			scores[strategy2] += TTT;
		// }
		// else
		// {
		// 	scores += TTT;
		// 	//			scores[strategy2] += SSS;
		// }
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
	double Value2 = 0;

	int i, j, newstr;

	for (i = 0; i < 200; i++) {
		for (j = 0; j < 200; j++)
		{
			Index[i][j] = Lattice[i * 200 + j];
			trans[i][j] = Index[i][j];
			Value[i][j] = AverageValue[i * 200 + j];
		}
	}

	for (i = 0; i < 200; i++)
		for (j = 0; j < 200; j++)
		{
			Value2 = 0;
			value1 = Value[i][j];
			if (Index[i][j] == 0) {
				newstr = 1;
			}
			else {
				newstr = 0;
			}
			if (i == 0 && j == 0)
			{
				Value2 += ipd(newstr, Index[0][0], ROUNDS, i, j, 0, 0) / 4.0;
				Value2 += ipd(newstr, Index[0][1], ROUNDS, i, j, 0, 1) / 4.0;
				Value2 += ipd(newstr, Index[1][0], ROUNDS, i, j, 1, 0) / 4.0;
				Value2 += ipd(newstr, Index[1][1], ROUNDS, i, j, 1, 1) / 4.0;
			}
			else if (i == 0 && j == 199)
			{
				Value2 += ipd(newstr, Index[i][j], ROUNDS, i, j, i, j) / 4.0;
				Value2 += ipd(newstr, Index[i][j - 1], ROUNDS, i, j, i, j - 1) / 4.0;
				Value2 += ipd(newstr, Index[i + 1][j], ROUNDS, i, j, i + 1, j) / 4.0;
				Value2 += ipd(newstr, Index[i + 1][j - 1], ROUNDS, i, j, i + 1, j - 1) / 4.0;
			}
			else if (i == 0 && j < 199)
			{
				Value2 += ipd(newstr, Index[i][j], ROUNDS, i, j, i, j) / 6.0;
				Value2 += ipd(newstr, Index[i][j - 1], ROUNDS, i, j, i, j - 1) / 6.0;
				Value2 += ipd(newstr, Index[i][j + 1], ROUNDS, i, j, i, j + 1) / 6.0;
				Value2 += ipd(newstr, Index[i + 1][j], ROUNDS, i, j, i + 1, j) / 6.0;
				Value2 += ipd(newstr, Index[i + 1][j - 1], ROUNDS, i, j, i + 1, j - 1) / 6.0;
				Value2 += ipd(newstr, Index[i + 1][j + 1], ROUNDS, i, j, i + 1, j + 1) / 6.0;
			}
			else if (i < 199 && j == 0)
			{
				Value2 += ipd(newstr, Index[i][j], ROUNDS, i, j, i, j) / 6.0;
				Value2 += ipd(newstr, Index[i - 1][j], ROUNDS, i, j, i - 1, j) / 6.0;
				Value2 += ipd(newstr, Index[i + 1][j], ROUNDS, i, j, i + 1, j) / 6.0;
				Value2 += ipd(newstr, Index[i][j + 1], ROUNDS, i, j, i, j + 1) / 6.0;
				Value2 += ipd(newstr, Index[i - 1][j + 1], ROUNDS, i, j, i - 1, j + 1) / 6.0;
				Value2 += ipd(newstr, Index[i + 1][j + 1], ROUNDS, i, j, i + 1, j + 1) / 6.0;
			}
			else if (i < 199 && j == 199)
			{
				Value2 += ipd(newstr, Index[i][j], ROUNDS, i, j, i, j) / 6.0;
				Value2 += ipd(newstr, Index[i - 1][j], ROUNDS, i, j, i - 1, j) / 6.0;
				Value2 += ipd(newstr, Index[i + 1][j], ROUNDS, i, j, i + 1, j) / 6.0;
				Value2 += ipd(newstr, Index[i][j - 1], ROUNDS, i, j, i, j - 1) / 6.0;
				Value2 += ipd(newstr, Index[i - 1][j - 1], ROUNDS, i, j, i - 1, j - 1) / 6.0;
				Value2 += ipd(newstr, Index[i + 1][j - 1], ROUNDS, i, j, i + 1, j - 1) / 6.0;
			}
			else if (i < 199)
			{
				Value2 += ipd(newstr, Index[i][j], ROUNDS, i, j, i, j) / 9.0;
				Value2 += ipd(newstr, Index[i - 1][j], ROUNDS, i, j, i - 1, j) / 9.0;
				Value2 += ipd(newstr, Index[i + 1][j], ROUNDS, i, j, i + 1, j) / 9.0;
				Value2 += ipd(newstr, Index[i][j - 1], ROUNDS, i, j, i, j - 1) / 9.0;
				Value2 += ipd(newstr, Index[i - 1][j - 1], ROUNDS, i, j, i - 1, j - 1) / 9.0;
				Value2 += ipd(newstr, Index[i + 1][j - 1], ROUNDS, i, j, i + 1, j - 1) / 9.0;
				Value2 += ipd(newstr, Index[i][j + 1], ROUNDS, i, j, i, j + 1) / 9.0;
				Value2 += ipd(newstr, Index[i - 1][j + 1], ROUNDS, i, j, i - 1, j + 1) / 9.0;
				Value2 += ipd(newstr, Index[i + 1][j + 1], ROUNDS, i, j, i + 1, j + 1) / 9.0;
			}
			else if (i == 199 && j == 0)
			{
				Value2 += ipd(newstr, Index[i][j], ROUNDS, i, j, i, j) / 4.0;
				Value2 += ipd(newstr, Index[i - 1][j], ROUNDS, i, j, i - 1, j) / 4.0;
				Value2 += ipd(newstr, Index[i][j + 1], ROUNDS, i, j, i, j + 1) / 4.0;
				Value2 += ipd(newstr, Index[i - 1][j + 1], ROUNDS, i, j, i - 1, j + 1) / 4.0;
			}
			else if (i == 199 && j == 199)
			{
				Value2 += ipd(newstr, Index[i][j], ROUNDS, i, j, i, j) / 4.0;
				Value2 += ipd(newstr, Index[i - 1][j], ROUNDS, i, j, i - 1, j) / 4.0;
				Value2 += ipd(newstr, Index[i][j - 1], ROUNDS, i, j, i, j - 1) / 4.0;
				Value2 += ipd(newstr, Index[i - 1][j - 1], ROUNDS, i, j, i - 1, j - 1) / 4.0;
			}
			else
			{
				Value2 += ipd(newstr, Index[i][j], ROUNDS, i, j, i, j) / 6.0;
				Value2 += ipd(newstr, Index[i][j - 1], ROUNDS, i, j, i, j - 1) / 6.0;
				Value2 += ipd(newstr, Index[i][j + 1], ROUNDS, i, j, i, j + 1) / 6.0;
				Value2 += ipd(newstr, Index[i - 1][j], ROUNDS, i, j, i - 1, j) / 6.0;
				Value2 += ipd(newstr, Index[i - 1][j - 1], ROUNDS, i, j, i - 1, j - 1) / 6.0;
				Value2 += ipd(newstr, Index[i - 1][j + 1], ROUNDS, i, j, i - 1, j + 1) / 6.0;
			}
			if (value1 < Value2) {
				Index[i][j] = newstr;
				trans[i][j] = newstr;
			}

		}

	for (i = 0; i < 200; i++)
		for (j = 0; j < 200; j++)
		{
			Lattice[(i) * 200 + j] = trans[i][j];
		}

	return 0;
}












