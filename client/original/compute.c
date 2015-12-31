#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
	
int main(int argc, char *argv[])
{
	//indices
	int i,j,k;

	char buffer[33];
	char fileNameA[33];
	char fileNameB[33];
	char fileNameC[33];
	FILE *f;
	FILE *f1;
	FILE *f2;
	FILE *f3;
	int temp = 0;
	int nameIndex = 0;
	int tempA = 0;
	int tempB = 0;
	int size = b;
	double variable = matrix_size / b; 
	//fprintf(stdout, "variable = %f", variable);
	
	//matrix element C
	int C=0;

	//read file name
	f = fopen("name", "r");
	fscanf(f, "%d", &temp);
	fclose(f);
	
	//create A's file name
	memset(fileNameA, 0, strlen(fileNameA));
	memset(buffer, 0, strlen(buffer));
	fileNameA[0] = 'A';
	sprintf(buffer, "%d", temp);	
	strcat(fileNameA, buffer);

	//create B's file name
	memset(fileNameB, 0, strlen(fileNameB));
	memset(buffer, 0, strlen(buffer));
	fileNameB[0] = 'B';
	sprintf(buffer, "%d", temp);	
	strcat(fileNameB, buffer);

	//compute C elements for first A row
	f2 = fopen(fileNameB, "r");	
	nameIndex = 0;
	for(i = 0; i < variable; i++){
		//create fileNameC
		memset(fileNameC, 0, strlen(fileNameC));
		fileNameC[0] = 'C';
		
		sprintf(buffer, "%d", nameIndex);
		strcat(fileNameC, buffer);

		f3 = fopen(fileNameC, "a");
		f1 = fopen(fileNameA, "r");
		nameIndex++;
	
		//compute C element
		for(k = 0; k < size; k++){	
			fscanf(f1, "%d", &tempA);		
			fscanf(f2, "%d", &tempB);
			//fprintf(stdout, "A = %d, B = %d\n", tempA, tempB);
		
			//compute C1
			C += tempA * tempB;
			//fprintf(stdout, "C = %d\n", C);
		}		

		//write C to file C
		fprintf(stdout, "%d\n", C);
		fprintf(f3, "%d", C);
		fclose(f3);
		fclose(f1);	
		C=0;
	}
	fclose(f2);


	//compute C elements for second A row
	f2 = fopen(fileNameB, "r");
	for(i = 0; i < variable; i++){
		//create fileNameC
		memset(fileNameC, 0, strlen(fileNameC));
		fileNameC[0] = 'C';
		
		sprintf(buffer, "%d", nameIndex);
		strcat(fileNameC, buffer);

		f3 = fopen(fileNameC, "a");
		f1 = fopen(fileNameA, "r");
		nameIndex++;
	
		//move to 2nd row of A
		for(j = 0; j < size; j++){
			fscanf(f1, "%d", &tempA);
		}

		//compute C element
		for(k = 0; k < size; k++){	
			fscanf(f1, "%d", &tempA);		
			fscanf(f2, "%d", &tempB);
			//fprintf(stdout, "A = %d, B = %d\n", tempA, tempB);
		
			//compute C
			C += tempA * tempB;
			//fprintf(stdout, "C = %d\n", C);
		}		

		//write C to file C
		fprintf(stdout, "%d\n", C);
		fprintf(f3, "%d", C);
		fclose(f3);
		fclose(f1);	
		C=0;
	}
	fclose(f2);

	
	#ifdef debug
	fprintf(stdout, "temp=%d\n", temp);
	fprintf(stdout, "buffer=%s\n", buffer);
	#endif


	return 0;
}
