#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <string>



/* BOINC API */

#include "boinc_api.h"
#include "diagnostics.h"     
#include "filesys.h"         
#include "str_util.h"		 
#include "mfile.h"
#include "util.h"

// version.h is only used to get BOINC version numbers  
#include "version.h"

#define matrix_size 4000
//tile_size
#define b 2000
#define version version2

//computes matrix C on client	
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

	// return code from various functions
	int rc;        
	// physical file name for files A,B,C,Name
	char resolved_nameA[512];
	char resolved_nameB[512];
	char resolved_nameC[512];
	char resolved_nameN[512];

  	/*
   	 *  Before initializing BOINC itself, intialize diagnostics, so as
   	 *  to get stderr output to the file stderr.txt, and thence back home.
   	 */

  	//boinc_init_diagnostics(BOINC_DIAG_REDIRECTSTDERR|
                         //BOINC_DIAG_MEMORYLEAKCHECKENABLED|
                         //BOINC_DIAG_DUMPCALLSTACKENABLED| 
                         //BOINC_DIAG_TRACETOSTDERR);

	/* BOINC apps that do not use graphics just call boinc_init() */
  	boinc_init();
  	//if (rc){
    		//fprintf(stderr, "APP: boinc_init() failed. rc=%d\n", rc);
    		//fflush(0);
    		//exit(rc);
  	//}

	/*
   	 * Input and output files need to be "resolved" from their logical name
   	 * for the application to the actual path on the client's disk
   	 */
	boinc_resolve_filename("name", resolved_nameN, sizeof(resolved_nameN));
	//if (rc){
    		//fprintf(stderr, "APP: cannot resolve output file name. RC=%d\n", rc);
    		//boinc_finish(rc);    /* back to BOINC core */
  	//}

	//read file name
	f = boinc_fopen(resolved_nameN, "r");
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
	/*
   	 * Input and output files need to be "resolved" from their logical name
   	 * for the application to the actual path on the client's disk
   	 */
	boinc_resolve_filename(fileNameB, resolved_nameB, sizeof(resolved_nameB));
	//if (rc){
    		//fprintf(stderr, "APP: cannot resolve output file name. RC=%d\n", rc);
    		//boinc_finish(rc);    /* back to BOINC core */
  	//}

	f2 = boinc_fopen(fileNameB, "r");	
	nameIndex = 0;
	for(i = 0; i < variable; i++){
		//create fileNameC
		memset(fileNameC, 0, strlen(fileNameC));
		fileNameC[0] = 'C';
		
		sprintf(buffer, "%d", nameIndex);
		strcat(fileNameC, buffer);

		/*
   	 	 * Input and output files need to be "resolved" from their logical name
   	 	 * for the application to the actual path on the client's disk
   	 	 */
		boinc_resolve_filename(fileNameC, resolved_nameC, sizeof(resolved_nameC));
		//if (rc){
    			//fprintf(stderr, "APP: cannot resolve output file name. RC=%d\n", rc);
    			//boinc_finish(rc);    /* back to BOINC core */
  		//}

		/*
   	 	 * Input and output files need to be "resolved" from their logical name
   	 	 * for the application to the actual path on the client's disk
   	 	 */
		boinc_resolve_filename(fileNameA, resolved_nameA, sizeof(resolved_nameA));
		//if (rc){
    			//fprintf(stderr, "APP: cannot resolve output file name. RC=%d\n", rc);
    			//boinc_finish(rc);    /* back to BOINC core */
  		//}

		f3 = boinc_fopen(fileNameC, "a");
		f1 = boinc_fopen(fileNameA, "r");
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
	/*
   	 * Input and output files need to be "resolved" from their logical name
   	 * for the application to the actual path on the client's disk
   	 */
	boinc_resolve_filename(fileNameB, resolved_nameB, sizeof(resolved_nameB));
	//if (rc){
    		//fprintf(stderr, "APP: cannot resolve output file name. RC=%d\n", rc);
    		//boinc_finish(rc);    /* back to BOINC core */
  	//}
	f2 = fopen(fileNameB, "r");
	for(i = 0; i < variable; i++){
		//create fileNameC
		memset(fileNameC, 0, strlen(fileNameC));
		fileNameC[0] = 'C';
		
		sprintf(buffer, "%d", nameIndex);
		strcat(fileNameC, buffer);

		/*
   	 	 * Input and output files need to be "resolved" from their logical name
   	 	 * for the application to the actual path on the client's disk
   	 	 */
		boinc_resolve_filename(fileNameC, resolved_nameC, sizeof(resolved_nameC));
	 	//if (rc){
    			//fprintf(stderr, "APP: cannot resolve output file name. RC=%d\n", rc);
    			//boinc_finish(rc);    /* back to BOINC core */
  		//}

		/*
   	 	 * Input and output files need to be "resolved" from their logical name
   	 	 * for the application to the actual path on the client's disk
   	 	 */
		boinc_resolve_filename(fileNameA, resolved_nameA, sizeof(resolved_nameA));
		//if (rc){
    			//fprintf(stderr, "APP: cannot resolve output file name. RC=%d\n", rc);
    			//boinc_finish(rc);    /* back to BOINC core */
  		//}
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

  	/* All BOINC applications must exit via boinc_finish(rc), not merely exit() */
  	boinc_finish(0);
	return 0;
}
