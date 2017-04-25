#include <stdio.h>
#include <time.h>

//Forward declerations
long timer();
void sort(float *arr, int* size);


int main(int argc, char **argv)
{
	//set up for find cache line size
	int max_stride = 512;
	int sizeOfArray = (16384 / sizeof(int)); //size of the big array (needs to be > 8MB bc that's the size of my cache) I made it 16MB
	int numOfIterations = 10000;
	findCacheLineSize(max_stride, sizeOfArray, numOfIterations);
}

//Find Cache Block (line) size
void findCacheLineSize(int max_stride, int sizeOfBigArray, int repetitions){
	//Beginning of method to determine cache block(line size)
	long start, end;
	int tmp = 0, lengthMod;
	float times[repetitions]; //Made an Array of floats for storing the times
	int TIMES = 16; //Number of times to time accesses
	
	int tooBigForCache[sizeOfBigArray];
	lengthMod = sizeOfBigArray - 1;

	// repeatedly access/modify tooBigForCache, varying the STRIDE
	for (int i = 4; i <= max_stride/sizeof(int); i*=2)  {
		for (int j = 0; j < TIMES; j++) {
			start = timer();
			// loop to repeatedly read the tooBigForCache in strides i
			for (unsigned int k = 0; k < repetitions; k++) {
				tmp += tooBigForCache[(k * i) & lengthMod];
			}
			end = timer();
			times[j] = ((float)(end - start))/1000000000;
		}
		// we can expect a spike in time (more cache miss) when it exceeds the line size
		// Time to compute the current stats
		int medianIndex = (sizeof(times) / 2);
		//Need to sort times
		sort(times, sizeof(times));
		printf("%d, %1.2f \n", (int)(i * sizeof(int)), times[medianIndex]);
	}
}


//Helper methods
long timer(){
	struct timespec tp;
	clock_gettime(CLOCK_REALTIME, &tp);
	return tp.tv_nsec;
}

void sort(float *arr, int* size) {
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

