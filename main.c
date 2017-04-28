#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Forward declerations
long timer();
void sort(float *arr, int size);
void findCacheLineSize(int max_stride, int sizeOfBigArray, int repetitions);


int main(int argc, char **argv)
{
	//set up for find cache line size
	int max_stride = 128;
	int sizeOfArray = (16384 / sizeof(int)); //size of the big array (needs to be > 8MB bc that's the size of my cache) I made it 16MB
	int numOfIterations = 100000;
	
	
		findCacheLineSize(max_stride, sizeOfArray, numOfIterations);
	
	/*
	Testing the sort method
	printf("Sorting helper test \n");
	int test[10] = {5, 7, 2, 4, 8, 1, 2, 0, 7, 5};
	sort(&test, 10);
	for (int i=0; i<10; i++){
		printf("%d", test[i]);
	}
	*/
}

//Find Cache Block (line) size
void findCacheLineSize(int max_stride, int sizeOfBigArray, int repetitions){
	//Beginning of method to determine cache block(line size)
	long start, end;
	int lengthMod; 
	//int arraySize=(((max_stride/sizeof(int))/4)-1);
	//float times[max_stride/sizeof(int)/4]; //Made an Array of floats for storing the times
	//int strides[max_stride/sizeof(int)/4]; //Made an Array of ints to record strides should match with times at the same index so we can do analytics later
	
	//Here I create an array and fill it with random data (between 0 - 100)
	int tooBigForCache[sizeOfBigArray];
	srand(0);
	for (int i = 0; i < sizeOfBigArray; i++){
		tooBigForCache[i] = rand();
	}
	lengthMod = sizeOfBigArray - 1;

	// repeatedly access/modify data, varying the STRIDE
	for (int s = 4; s <= max_stride/sizeof(int); s++) {
		start = timer();
		for (unsigned int j = 0; j < repetitions; j++) {
			tooBigForCache[(j * s) & lengthMod]++;
		}
		end = timer();
		float timeTaken = ((float)(end - start));
		//store the timeTaken to an array to view later
		//strides[arraySize] = s;
		//times[arraySize] = timeTaken;
		
		printf("Stride Size: %d, Recorded Time(ns): %1.2f \n", ((int)(s * sizeof(int))), timeTaken/CLOCKS_PER_SEC);
	}
}


//Helper methods
long timer(){
	struct timespec tp;
	clock_gettime(CLOCK_MONOTONIC, &tp);
	return tp.tv_nsec;
}

void sort(float *arr, int size) {
	//just a quick bubble sort for sorting the array of times.
	float value = 0.0f;
	for(int i=0;i<size-1;i++){
		for(int j=0;j<size-i-1;j++){
			if(arr[j]>arr[j+1]){
				value=arr[j+1];
				arr[j+1]=arr[j];
				arr[j]=value;
			}
		}
	}
}

