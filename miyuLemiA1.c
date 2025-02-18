#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "givenA1.h"
#include "helper.h"

/**********************************************************
*@author: Lemi Miyu
*@description: Reads the information from a text file called a1Data.txt
*and stores them in an array of struct Animal
*@param: char fName[30], struct Animal dataZoo[NUM_SAMPLES]
*@return: 1 if file is successfully read, -1 if an error occurs
**********************************************************/
int readFromFile(char fName[30], struct Animal dataZoo[NUM_SAMPLES])
{
    FILE * fptr = fopen(fName, "r");
    
    // checks if file is empty/if there is trouble accessing file
    if (fptr == NULL)
    {
        return -1;
    }

    // loops for NUM_SAMPLES to get all data
    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        fscanf(fptr, "%s", dataZoo[i].animalName);

        // loops for NUM_FEATURES to get all features for each Animal
        for (int j = 0; j < NUM_FEATURES; j++)
        {
            fscanf(fptr, "%d", &dataZoo[i].features[j]);
        }

        fscanf(fptr, "%d", &dataZoo[i].classLabel);
    }

    fclose(fptr);

    return 1;
}

/**********************************************************
*@author: Lemi Miyu
*@description: Takes two vectors and calculates their Euclidean
*distance, Hamming distance, and Jaccard similarity. They are returned
*via call by reference.
*@param: int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES], float * euclidean, int * hamming, float * jaccard
*@return: N/A
**********************************************************/
void distanceFunctions (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES], float * euclidean, int * hamming, float * jaccard)
{
    * euclidean = 0;
    * hamming = 0;
    * jaccard = 0;
    int jaccard1 = 0;
    int jaccard0 = 0;

    // loops for NUM_FEATURES to perform operations on each row
    for (int i = 0; i < NUM_FEATURES; i++)
    {
        * euclidean += pow(vector1[i] - vector2[i], 2);

        // checks if the corresponding rows in vector1 and vector2 are equal for hamming distance
        if (!(vector1[i] == vector2[i]))
        {
            (* hamming)++;
        }

        // checks if corresponding rows in vector1 and vector 2 are 1 for 1-1 matches in jaccard similarity
        else if (vector1[i] == 1 && vector2[i] == 1)
        {
            jaccard1++;
        }

        // checks if corresponding rows in vector1 and vector 2 are 1 for 0-0 matches in jaccard similarity
        else if (vector1[i] == 0 && vector2[i] == 0)
        {
            jaccard0++;
        }
    }

    * euclidean = sqrt(* euclidean);
    * jaccard = (float)(jaccard1) / (NUM_FEATURES - jaccard0);
}

/**********************************************************
*@author: Lemi Miyu
*@description: Finds the indices of the k nearest neighbors of newSample
*and stores them in the kNearestNeighbors array
*@param: struct Animal dataZoo [NUM_SAMPLES], int newSample [NUM_FEATURES], int k, int whichDistanceFunction, int kNearestNeighbors [NUM_SAMPLES]
*@return: N/A
**********************************************************/
void findKNearestNeighbors (struct Animal dataZoo [NUM_SAMPLES], int newSample [NUM_FEATURES], int k, int whichDistanceFunction, int kNearestNeighbors [NUM_SAMPLES])
{
    float euclidean = 0;
    int hamming = 0;
    float jaccard = 0;
    float allNeighbors[NUM_SAMPLES];

    // loops for NUM_SAMPLES to store calculated appropriate distance function for all samples
    for (int i = 0; i < NUM_SAMPLES; i++)
    {
        distanceFunctions(dataZoo[i].features, newSample, &euclidean, &hamming, &jaccard);

        // calculates euclidean distance
        if (whichDistanceFunction == 1)
        {
            allNeighbors[i] = euclidean;
        }

        // calculates hamming distance
        else if (whichDistanceFunction == 2)
        {
            allNeighbors[i] = hamming;
        }

        // calculates jaccard similarity
        else
        {
            allNeighbors[i] = jaccard;
        }
    }

    sortArray(allNeighbors, kNearestNeighbors, k, whichDistanceFunction);
}

/**********************************************************
*@author: Lemi Miyu
*@description: Calculates the predicted class by finding the most
*frequent class among the k neighbor(s)
*@param: struct Animal dataZoo [NUM_SAMPLES], int newSample [NUM_FEATURES], int whichDistanceFunction, int k
*@return: int predictedClass
**********************************************************/
int predictClass (struct Animal dataZoo [NUM_SAMPLES], int newSample [NUM_FEATURES], int whichDistanceFunction, int k)
{
    int neighbors[NUM_SAMPLES];
    int classLabel[NUM_SAMPLES];
    int maxFrequency = 0;
    int predictedClass = 0; 
    int count = 0;

    findKNearestNeighbors(dataZoo, newSample, k, whichDistanceFunction, neighbors);

    // Extract class labels of the k nearest neighbors
    for (int i = 0; i < k; i++)
    {
        classLabel[i] = dataZoo[neighbors[i]].classLabel;
    }

    // Count occurrences of each class label
    for (int i = 0; i < k; i++)
    {
        count = numberOfOccurances(classLabel, k, classLabel[i]);

        // If this class appears more frequently, update the predicted class
        if (count > maxFrequency)
        {
            maxFrequency = count;
            predictedClass = classLabel[i];
        }

        // If there is a tie, select the smallest class label
        else if (count == maxFrequency && classLabel[i] < predictedClass)
        {
            predictedClass = classLabel[i];
        }
    }

    return predictedClass;
}

/**********************************************************
*@author: Lemi Miyu
*@description: Predicts the class of each data given in the testData.csv
*file and uses them to compute the accuracy of the k-nearest neighbor(s)
*algorithm used.
*@param: struct Animal dataZoo [NUM_SAMPLES], int whichDistanceFunction, struct Animal testData [NUM_TEST_DATA], int k
*@return: the accuracy using the formula correct / total
**********************************************************/
float findAccuracy (struct Animal dataZoo [NUM_SAMPLES], int whichDistanceFunction, struct Animal testData [NUM_TEST_DATA], int k)
{
    int correct = 0;
    int predictedClass = 0;
    int class = 0;

    // loops for NUM_TEST_DATA to obtain predicted class and actual class for each testData element
    for (int i = 0; i < NUM_TEST_DATA; i++)
    {
        predictedClass = predictClass(dataZoo, testData[i].features, whichDistanceFunction, k);
        class = testData[i].classLabel;

        printf("%d ", predictedClass);

        // adds to the number of correct predictions if applicable
        if (predictedClass == class)
        {
            correct++;
        }
    }

    printf("\n%d\n%d\n", correct, NUM_TEST_DATA);

    return (float)correct / NUM_TEST_DATA;
}

/**********************************************************
*@author: Lemi Miyu
*@description: Checks if a given number is in a given array.
*(taken from my assignment 3 in CIS1300)
*@param: int data[], int sizeOfData, int num
*@return: 1 if their is an occurance, 0 otherwise
**********************************************************/
int checkOccurance(int data[], int sizeOfData, int num)
{
    // iterates for the length of the given array
    for (int i = 0; i < sizeOfData; i++)
    {
        // returns 1 if the given number is found inside of the given array
        if (data[i] == num)
        {
            return 1;
        }
    }

    return 0;
}

/**********************************************************
*@author: Lemi Miyu
*@description: Sorts an array from greatest to least or from
*least to greatest.
*Citation: used code from ranking method in assignment 3 from CIS1300.
*@param: float arrayUnsorted[NUM_SAMPLES], int sortedArray[NUM_SAMPLES], int k, int order
*@return: N/A
**********************************************************/
void sortArray(float arrayUnsorted[NUM_SAMPLES], int sortedArray[NUM_SAMPLES], int k, int order)
{
    int lowestIndex = 0;
    float lowestDistance = arrayUnsorted[0];
    int greatestIndex = 0;
    float greatestDistance = arrayUnsorted[0];

    // sorts from least to greatest for euclidean and hamming distances
    if (order == 1 || order == 2)
    {
        // iterates for number of least wanted
        for (int i = 0; i < k; i++)
        {
            lowestIndex = -1;
            lowestDistance = INT_MAX;

            // iterates for NUM_SAMPLES to compare all data
            for (int j = 0; j < NUM_SAMPLES; j++)
            {
                // overwrites the least index if not already recorded
                if (arrayUnsorted[j] < lowestDistance && !(checkOccurance(sortedArray, i, j)))
                {
                    lowestIndex = j;
                    lowestDistance = arrayUnsorted[j];
                } 
            }

            // records lowest index if found
            if (lowestIndex != -1)
            {
                sortedArray[i] = lowestIndex;
            }
        }
    }

    // sorts from greatest to least for jaccard similarity
    else
    {
        // iterates for number of greatest wanted
        for (int i = 0; i < k; i++)
        {
            greatestIndex = -1;
            greatestDistance = 0;

            // iterates for NUM_SAMPLES to compare all data
            for (int j = 0; j < NUM_SAMPLES; j++)
            {
                // overwrites the greatest index if not already recorded
                if (arrayUnsorted[j] > greatestDistance && !(checkOccurance(sortedArray, i, j)))
                {
                    greatestIndex = j;
                    greatestDistance = arrayUnsorted[j];
                } 
            }

            // records greatest index if found
            if (greatestIndex != -1)
            {
                sortedArray[i] = greatestIndex;
            }
        }    
    }
}

/**********************************************************
*@author: Lemi Miyu
*@description: Returns the number of occurances of a given
*value in an array.
*@param: int data[], int sizeOfData, int value
*@return: int count
**********************************************************/
int numberOfOccurances (int data[], int sizeOfData, int value)
{
    int counter = 0;

    // iterates over all elements of given array
    for (int i = 0; i < sizeOfData; i++)
    {
        // adds to the count if the element of the current iteration matches the desired value
        if (data[i] == value)
        {
            counter++;
        }
    }

    return counter;
}

/**********************************************************
*@author: Lemi Miyu
*@description: Reads data from a csv file.
*Citation: https://stackoverflow.com/questions/60589015/i-am-trying-to-read-from-a-csv-file-with-fscanf
*@param: char * fName, struct Animal testData[NUM_TEST_DATA]
*@return: 1 if file is read to the end, -1 if file is empty
**********************************************************/
int readFromCsvFile(char * fName, struct Animal testData[NUM_TEST_DATA])
{
    FILE * fptr = fopen(fName, "r");
    
    // checks if file is empty/if there is trouble accessing file
    if (fptr == NULL)
    {
        return -1;
    }

    // loops for NUM_TEST_DATA to get all data
    for (int i = 0; i < NUM_TEST_DATA; i++)
    {
        // reads and checks if name is read
        if (fscanf(fptr, "%[^,],", testData[i].animalName) != 1) // see citation in function header
        {
            break;
        }

        // loops for NUM_FEATURES to get all features for each Animal
        for (int j = 0; j < NUM_FEATURES; j++)
        {
            // reads and checks if feature is read
            if (fscanf(fptr, "%d,", &testData[i].features[j]) != 1)
            {
                break;
            }
        }

        // reads and checks if class label is read
        if (fscanf(fptr, "%d", &testData[i].classLabel) != 1)
        {
            break;
        }
    }

    fclose(fptr);

    return 1;
}