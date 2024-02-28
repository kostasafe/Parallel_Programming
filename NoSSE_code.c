#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define rows 800
#define columns 800

void fill_random(float* arr[rows]);

void get_walltime(double *wct) { // given from university labs
  struct timeval tp;
  gettimeofday(&tp,NULL);
  *wct = (double)(tp.tv_sec+tp.tv_usec/1000000.0);
}

int main(void){
	double ts,te;
	srand(time(NULL) );
	
	float *testArray[rows],*finalArray[rows]; // define Arrays
	
    for (int i = 0; i < rows; i++)
        testArray[i] = (float*)malloc(columns * sizeof(float)); // Dynamic 2D allocation of Array
	for (int i = 0; i < rows; i++)
        finalArray[i] = (float*)malloc(columns * sizeof(float));// Dynamic 2D allocation of Array
	
	
	fill_random(testArray); // Fill Array with rand() values
	
	for (int i=0; i<rows; i++){
		for (int j=0; j<columns; j++){
			finalArray[i][j] = testArray[i][j] ;// Store one array to the other so its not empty
		}
	}
		get_walltime(&ts);// start of timer
	
	float Kall=0.5, K4=5.0, neighbors, center; // variable definition
	for (int i=1; i<(rows-1); i++){
		for (int j=1; j<(columns-1); j++){
			neighbors = testArray[i-1][j-1] + testArray[ i ][j-1] + testArray[i+1][j-1]//
                + testArray[i-1][ j ]                       + testArray[i+1][ j ]
                + testArray[i-1][j+1] + testArray[ i ][j+1] + testArray[i+1][j+1];
            center = testArray[i][j];
            finalArray[i][j] = Kall * neighbors + K4 * center;// final edit and give values
		}
	}
	
	/*for (int i=0; i<rows; i++){
		for (int j=0; j<columns; j++){
			printf("%5.2f  ", testArray[i][j]);
		}
		printf("\n");
	} 
	
	printf("\n");
	for (int i=0; i<rows; i++){
		for (int j=0; j<columns; j++){
			printf("%5.2f  ", finalArray[i][j]);
		}
		printf("\n");
	} 	*/
	get_walltime(&te);// end of timer
	
	
	printf("Exec Time (sec) = %f\n",te-ts);// university lab given code
	for (int i = 0; i < rows; i++)
        free(testArray[i]);
	for (int i = 0; i < rows; i++)
        free(finalArray[i]);
	
	 return 0;
}

void fill_random(float* arr[rows]){ //// random array float filler 
	
	for (int i=0; i<rows; i++){
		for (int j=0; j<columns; j++){
			arr[i][j] = rand();
		}
	}
}