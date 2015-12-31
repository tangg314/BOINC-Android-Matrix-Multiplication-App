#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
	
//Creates matrix A,B,C. Breaks matrix A,B into tiles as files.
//Creates workload folders.
int main(int argc, char *argv[])
{
	//indices
	int i,j,k;

	//create matrix A
  	int** A = (int **)malloc(matrix_size * sizeof(int *));
  	//create matrix B
  	int** B = (int **)malloc(matrix_size * sizeof(int *));
  	//create matrix C
  	int** C = (int **)malloc(matrix_size * sizeof(int *));

	for(i = 0; i < matrix_size; i++){
		A[i] = (int *)malloc(matrix_size * sizeof(int));
	}

	for(i = 0; i < matrix_size; i++){
		B[i] = (int *)malloc(matrix_size * sizeof(int));
	}

	for(i = 0; i < matrix_size; i++){
		C[i] = (int *)malloc(matrix_size * sizeof(int));
	}

	//tile index in x direction
	int tx;
	//tile index in y direction
	int ty;
	//used in computing max tile index
	double variable = matrix_size / b;
	//max tile index
	double tileI;


	//intialize matrix A
	for(i = 0; i < matrix_size; i++){
		for(j = 0; j < matrix_size; j++){
			A[i][j] = i;
		}
  	}

	//intialize matrix B
	for(i = 0; i < matrix_size; i++){
		for(j = 0; j < matrix_size; j++){
			B[i][j] = i+j;
		}
  	}

	//intialize matrix C
	for(i = 0; i < matrix_size; i++){
		for(j = 0; j < matrix_size; j++){
			C[i][j] = 0;
		}
  	}

	#ifdef debug
	//print matrix A
	fprintf(stdout, "matrix A\n");
	for(i = 0; i < matrix_size; i++){
		for(j = 0; j < matrix_size; j++){
			fprintf(stdout, "%d ", A[i][j]);
		}
		fprintf(stdout, "\n");
  	}

	//print matrix B
	fprintf(stdout, "matrix B\n");
	for(i = 0; i < matrix_size; i++){
		for(j = 0; j < matrix_size; j++){
			fprintf(stdout, "%d ", B[i][j]);
		}
		fprintf(stdout, "\n");
  	}

	//print matrix C
	fprintf(stdout, "matrix C\n");
	for(i = 0; i < matrix_size; i++){
		for(j = 0; j < matrix_size; j++){
			fprintf(stdout, "%d ", C[i][j]);
		}
		fprintf(stdout, "\n");
  	}
	#endif


	char buffer[33];
	char fileName[33];
	char fileName2[33];
	FILE *f;

	//distribute matrix by rows and columns
	#ifdef version1
	//write matrixA to file A#
	for(i = 0; i < matrix_size; i++){
		//make file name
		memset(fileName, 0, strlen(fileName));
		memset(buffer, 0, strlen(buffer));
		fileName[0] = 'A';
		sprintf(buffer, "%d", i);
		strcat(fileName, buffer);
		f = fopen(fileName, "a");

		//write to file
		for(j = 0; j < matrix_size; j++){					
			fprintf(f, "%d ", A[i][j]);		
		}	
	}
	fclose(f);	
		
	//write matrixB to file B#
	for(i = 0; i < matrix_size; i++){
		//make file name
		memset(fileName, 0, strlen(fileName));	
		memset(buffer, 0, strlen(buffer));
		fileName[0] = 'B';	
		sprintf(buffer, "%d", i);
		strcat(fileName, buffer);
		f = fopen(fileName, "a");

		//write to file
		for(j = 0; j < matrix_size; j++){			
			fprintf(f, "%d ", B[i][j]);		
		}	
	}	
	fclose(f);
	#endif


	//distribute matrix by tiles
	#ifdef version2
	//max tile index
	tileI = ceil(variable) - 1;
	
	int h = 0;
	char command1[33];
	char command2[33];
	//create tiles of Matrix A
	for(tx = 0; tx <= tileI; tx++){
		for(ty = 0; ty <= tileI; ty++){
			//make file name
			memset(fileName, 0, strlen(fileName));
			memset(buffer, 0, strlen(buffer));
			fileName[0] = 'A';
			sprintf(buffer, "%d", h);
			strcat(fileName, buffer);

			//mkdir #
			//memset(command1, 0, strlen(command1));
			//strcpy(command1, "mkdir ");
			//strcat(command1, buffer);
			//fprintf(stdout, "%s\n", command1);
			//system(command1);

			//cd #
			//chdir(buffer);

			f = fopen(fileName, "a");
			h++;
			
			//write tile
			for(i = (tx * b); i < (b* (tx + 1)) && i < matrix_size; i++){
				for(j = (ty * b); j < (b * (ty + 1)) && j < matrix_size; j++){
					fprintf(f, "%d ", A[i][j]);
				}
			}

			//chdir("..");
		}	
	}
	fclose(f);

	h=0;
	int temp;
	//create tiles of Matrix B
	for(tx = 0; tx <= tileI; tx++){
		for(ty = 0; ty <= tileI; ty++){
			//make file name
			memset(fileName, 0, strlen(fileName));
			memset(buffer, 0, strlen(buffer));
			fileName[0] = 'B';
			sprintf(buffer, "%d", h);
			strcat(fileName, buffer);

			//cd #
			//chdir(buffer);

			f = fopen(fileName, "a");
			temp = h;
			h++;
		
			//write tile
			for(i = (tx * b); i < (b* (tx + 1)) && i < matrix_size; i++){
				for(j = (ty * b); j < (b * (ty + 1)) && j < matrix_size; j++){
					fprintf(f, "%d ", B[i][j]);
				}
			}

			//make name file
			//memset(fileName2, 0, strlen(fileName2));
			//strcpy(fileName2, "name");
			//f = fopen(fileName2, "a");

			//write number into file
			//fprintf(f, "%d", temp);

			//chdir("..");
		}	
	}
	fclose(f);


	int numFolder = variable * variable * variable;
	//make workunit folders
	for(i = 0; i < numFolder; i ++){
		//mkdir #	
		memset(command1, 0, strlen(command1));
		memset(buffer, 0, strlen(buffer));
		strcpy(command1, "mkdir ");	
		sprintf(buffer, "%d", i);
		strcat(command1, buffer);
		//fprintf(stdout, "%s\n", command1);
		system(command1);

		//cd #
		chdir(buffer);

		//make name file, associated with workunit number
		memset(fileName2, 0, strlen(fileName2));
		strcpy(fileName2, "name");
		f = fopen(fileName2, "a");

		//write number into file
		fprintf(f, "%d", i);

		chdir("..");
	}
	fclose(f);
	

	

	#ifdef debug
	fprintf(stdout, "tileI = %f \n", tileI);
	fprintf(stdout, "Matrix A\n");

	//print tiles of Matrix A
	for(tx = 0; tx <= tileI; tx++){
		for(ty = 0; ty <= tileI; ty++){
			for(i = (tx * b); i < (b* (tx + 1)) && i < matrix_size; i++){
				for(j = (ty * b); j < (b * (ty + 1)) && j < matrix_size; j++){
					fprintf(stdout, "%d ", A[i][j]);
				}
				fprintf(stdout, "\n");
			}
			fprintf(stdout, "\n\n");
		}
		
	}

	fprintf(stdout, "tileI = %f \n", tileI);
	fprintf(stdout, "Matrix B\n");

	//print tiles of Matrix B
	for(tx = 0; tx <= tileI; tx++){
		for(ty = 0; ty <= tileI; ty++){
			for(i = (tx * b); i < (b* (tx + 1)) && i < matrix_size; i++){
				for(j = (ty * b); j < (b * (ty + 1)) && j < matrix_size; j++){
					fprintf(stdout, "%d ", B[i][j]);
				}
				fprintf(stdout, "\n");
			}
			fprintf(stdout, "\n\n");
		}
		
	}
	#endif



	#endif

	return 0;
}
