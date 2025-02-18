#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include "givenA1.h"
#include "helper.h"

int main(int argc, char * argv[])
{
    struct Animal dataZoo[NUM_SAMPLES];
    float euclidean = 0;
    int hamming = 0;
    float jaccard = 0;
    int menuChoice;
    int vector1[] = {1,1,1,0,1,0,1,1,1,0,0,0,0,1,1,1};
    int vector2[] = {1,0,0,1,0,0,1,1,1,1,0,0,4,0,0,1};
    int neighbors[NUM_SAMPLES];
    int fileRead = 0;
    int fileRead2 = 0;
    struct Animal testData[NUM_TEST_DATA];

    // keeps program running as long as a valid menu entry is entered
    do 
    {
        printf("Here is the menu - enter a number between 1 and 5\n");

        printf("\nEnter your choice: ");
        scanf("%d", &menuChoice);

        // all menu options
        switch (menuChoice)
        {
        // Task 1: readFromFile()
        case 1:
            fileRead = readFromFile(argv[1], dataZoo);

            // breaks out if there is an error reading the file
            if (fileRead != 1)
            {
                printf("Error reading file\n\n");
                break;
            }

            // loops over all elements to print out extracted data
            for (int i = 0; i < NUM_SAMPLES; i++) 
            {
                printf("%s ", dataZoo[i].animalName);

                // loops over all features for each animal to print it out
                for (int j = 0; j < NUM_FEATURES; j++) 
                {
                    printf("%d ", dataZoo[i].features[j]);
                }

                printf("%d\n", dataZoo[i].classLabel);
            }

            printf("\n");
            break;

        // Task 2: distanceFunctions()
        case 2:
            distanceFunctions(vector1, vector2, &euclidean, &hamming, &jaccard);
            printf("Euclidean Distance: %f\n", euclidean);
            printf("Hamming Distance: %d\n", hamming);
            printf("Jaccard Similarity: %f\n\n", jaccard);
            break;

        // Task 3: findKNearestNeighbors()
        case 3:
            // ends program if run before data is read
            if (fileRead != 1)
            {
                printf("Please run option 1 first\n\n");
                menuChoice = 6;
                break;
            }

            findKNearestNeighbors(dataZoo, vector1, 5, 1, neighbors);
            printf("Nearest neighbors for new sample with Euclidean Distance: ");
            // prints out nearest samples
            for (int i = 0; i < 5; i++)
            {
                printf("%d ", neighbors[i]);
            }
            printf("\n");

            findKNearestNeighbors(dataZoo, vector1, 5, 2, neighbors);
            printf("Nearest neighbors for new sample with Hamming Distance: ");
            // prints out nearest samples
            for (int i = 0; i < 5; i++)
            {
                printf("%d ", neighbors[i]);
            }
            printf("\n");

            findKNearestNeighbors(dataZoo, vector1, 5, 3, neighbors);
            printf("Nearest neighbors for new sample with Jaccard Similarity: ");
            // prints out nearest samples
            for (int i = 0; i < 5; i++)
            {
                printf("%d ", neighbors[i]);
            }
            printf("\n\n");

            break;

        // Task 4: predictClass()
        case 4:
            // ends program if run before data is read
            if (fileRead != 1)
            {
                printf("\nPlease run option 1 first\n\n");
                menuChoice = 6;
                break;
            }

            printf("\nThe predicted class is: %d\n\n", predictClass(dataZoo, vector1, 1, 5));
            printf("The predicted class is: %d\n\n", predictClass(dataZoo, vector1, 2, 5));
            printf("The predicted class is: %d\n\n", predictClass(dataZoo, vector1, 3, 5));
            break;

        //Task 5: findAccuracy()
        case 5:
            // ends program if run before data is read
            if (fileRead != 1)
            {
                printf("Please run option 1 first\n\n");
                menuChoice = 6;
                break;
            }

            fileRead2 = readFromCsvFile("testData.csv", testData);

            // terminates program if data is unsuccessfully read
            if (fileRead2 != 1)
            {
                printf("Error reading file\n\n");
                menuChoice = 6;
                break;
            }

            printf("The accuracy for the test data is %f\n\n", findAccuracy(dataZoo, 1, testData, 5));
            printf("The accuracy for the test data is %f\n\n", findAccuracy(dataZoo, 2, testData, 5));
            printf("The accuracy for the test data is %f\n\n", findAccuracy(dataZoo, 3, testData, 5));
            
            break;
        
        default:
            break;
        }
    } while (menuChoice == 1 || menuChoice == 2 || menuChoice == 3 || menuChoice == 4 || menuChoice == 5);

    return 0;
}