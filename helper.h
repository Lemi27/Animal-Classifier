#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

int checkOccurance(int data[], int sizeOfData, int num);
void sortArray(float arrayUnsorted[NUM_SAMPLES], int sortedArray[NUM_SAMPLES], int k, int order);
int numberOfOccurances (int data[], int sizeOfData, int value);
int readFromCsvFile(char * fName, struct Animal testData[NUM_TEST_DATA]);