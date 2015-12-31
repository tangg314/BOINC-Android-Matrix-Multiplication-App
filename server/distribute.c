#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
	
//Distributes Matrix A,B tiles into workload folders.
int main(int argc, char *argv[])
{
	//indices
	int i, j;
	//used in computing max tile index
	double variable = ((double) matrix_size) / b;
	int numA = variable * variable;
	int jobIndex = 0;
	//B#
	int h=0;
	char buffer[33];
	char command1[33];
	//move matrix tiles into workunit folders
	for(i = 0; i < numA; i++){
		for (j = 0; j < variable; j++){
			//move A#i to jobIndex folder
			memset(command1, 0, strlen(command1));
			strcpy(command1, "cp A");

			sprintf(buffer, "%d", i);
			strcat(command1, buffer);

			strcat(command1, " ");

			sprintf(buffer, "%d", jobIndex);
			strcat(command1, buffer);
					
			//rename A#i to A#jobIndex
			strcat(command1, "/A");
			strcat(command1, buffer);
			
			fprintf(stdout, "%s\n", command1);
			system(command1);


			//move B#h to jobIndex folder
			memset(command1, 0, strlen(command1));
			strcpy(command1, "cp B");

			sprintf(buffer, "%d", h);
			strcat(command1, buffer);

			strcat(command1, " ");

			sprintf(buffer, "%d", jobIndex);
			strcat(command1, buffer);

			//rename B#i to B#jobIndex
			strcat(command1, "/B");
			strcat(command1, buffer);

			fprintf(stdout, "%s\n", command1);
			system(command1);

			//increment indices
			jobIndex++;

			//B# cannot be larger than number of B files
			if(h < numA - 1){
				h++;
			}
			
			else{
				h = 0;
			}		
		}
	}
}
