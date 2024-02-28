#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <malloc.h>
#include <emmintrin.h>

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
	__m128 vT, vF;
	srand(time(NULL) );
	
	float *testArray[rows],*finalArray[rows], *vTest[rows], *vFinal[rows]; // define Arrays
	
    for (int i = 0; i < rows; i++)
        testArray[i] = (float*)aligned_alloc(16, columns * sizeof(float)); // 16 byte align
	for (int i = 0; i < rows; i++)
        finalArray[i] = (float*)aligned_alloc(16, columns * sizeof(float)); // 16 byte align
        
	fill_random(testArray);
	
	for (int i=0; i<rows; i++){ // Store one array to the other so its not empty
		for (int j=0; j<columns; j++){
			finalArray[i][j] = testArray[i][j] ;
		}
	}
		get_walltime(&ts); // start of timer
	
	 
	 float neighbors, center, Kall=0.5, K4=5.0;
	
	for(int i = 0; i < rows; i+=4)            //couldnt find the right type of variable...
    {                                         
        for(int j = 0; j < columns; j++) {
            
                vT = _mm_set1_ps(testArray[i][j]); //load and broadcast
                neighbors = testArray[i-1][j-1] + testArray[ i ][j-1] + testArray[i+1][j-1]
                + testArray[i-1][ j ]                       + testArray[i+1][ j ]
                + testArray[i-1][j+1] + testArray[ i ][j+1] + testArray[i+1][j+1];
                center = testArray[i][j];
                vF = _mm_add_ps(_mm_mul_ps(K4, center), _mm_mul_ps(Kall, neighbors));
	
            
            _mm_store_ps(&finalArray[i][j], vF);
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
	get_walltime(&te); //end of timer
	
	
	printf("Exec Time (sec) = %f\n",te-ts);
	for (int i = 0; i < rows; i++)
        free(testArray[i]);
	for (int i = 0; i < rows; i++)
        free(finalArray[i]);
	
	 return 0;
}

void fill_random(float* arr[rows]){ // random array filler
	
	for (int i=0; i<rows; i++){
		for (int j=0; j<columns; j++){
			arr[i][j] = rand();
		}
	}
}