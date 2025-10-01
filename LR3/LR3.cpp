#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include "omp.h"


int randomIntDiap(int lBound, int uBound)
{
	return (rand() % (uBound - lBound + 1)) + lBound;
}

int iGetDateTime(const char* pc, int32_t* pi6)
{
	int errorID = 0;

	char c = pc[0];
	if (('0' > c) || (c > '9'))
	{
		errorID = 10;
	}
	pi6[0] = c - '0';

	c = pc[1];
	if (('0' > c) || (c > '9'))
	{
		errorID = 20;
	}
	pi6[1] = pi6[0] * 10 + (c - '0');

	c = pc[2];
	if (('0' > c) || (c > '9'))
	{
		errorID = 30;
	}
	pi6[2] = pi6[1] * 10 + (c - '0');

	c = pc[3];
	if (('0' > c) || (c > '9'))
	{
		errorID = 40;
	}
	pi6[3] = pi6[2] * 10 + (c - '0');

	c = pc[4];
	if (c != '-')
	{
		errorID = 50;
	}
	pi6[4] = pi6[3] * 10 + (c - '0');

	c = pc[5];
	if ((c != '0') && (c != '1'))
	{
		errorID = 60;
	}
	pi6[5] = pi6[4] * 10 + (c - '0');

	return errorID;
}


int main()
{
	//int ai6[6];
	//const char* pc = "2025-09-30T23:22:21";
	//int i = sscanf_s(pc, "%04d-%02d-%02dT%02d:%02d:%02d", &ai6[0], ai6 + 1, ai6 + 2, ai6 + 3, ai6 + 4, ai6 + 5);
	
	int iCount = 100000;
	char *pcAll = new char[iCount * 20];
	memset(pcAll, 0, iCount * 20 * sizeof(char));

	srand(1);
	char* pc = pcAll;

	for (int i = 0; i < iCount; i++)
	{
		sprintf(pc, "%04d-", randomIntDiap(0,9999));
		pc += 5;

		sprintf(pc, "%02d-", randomIntDiap(1, 12));
		pc += 3;

		sprintf(pc, "%02dT ", randomIntDiap(1, 28));
		pc += 3;

		sprintf(pc, "%02d:", randomIntDiap(0, 23));
		pc += 3;

		sprintf(pc, "%02d:", randomIntDiap(0, 59));
		pc += 3;

		sprintf(pc, "%02d, ", randomIntDiap(0, 59));
		pc += 3;
	}
	pcAll[iCount * 20 - 1] = '\0';


	int32_t *piAll = new int[iCount * 6];
	double dStart = omp_get_wtime();
	for (int i = 0; i < iCount; i++)
	{
		int32_t *pi = piAll + i * 6;
		int iRet = sscanf_s(pcAll + i * 20, "%04d-%02d-%02dT%02d:%02d:%02d", pi, pi + 1, pi + 2, pi + 3, pi + 4, pi + 5);
	}
	double dEnd = omp_get_wtime();
	printf("Time = %lg\n", dEnd - dStart);

	
	int32_t* piAll2 = new int[iCount * 6];
	dStart = omp_get_wtime();	
	for (int i = 0; i < iCount; i++)
	{
		int32_t* pi = piAll2 + i * 6;
		iGetDateTime(pcAll + i * 20, pi);
		//int iRet = sscanf_s(pcAll + i * 20, "%04d-%02d-%02dT%02d:%02d:%02d", pi, pi + 1, pi + 2, pi + 3, pi + 4, pi + 5);
	}
	dEnd = omp_get_wtime();
	printf("Time = %lg\n", dEnd - dStart);

	int i = memcmp(piAll, piAll2, iCount * 6 * sizeof(int32_t));
	i++;
	return i;
}
