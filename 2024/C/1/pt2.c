#include <stdio.h>
#include <stdlib.h>

/*
Methodology:
1.  Use functions from pt1 to create arrays from the list
2.  Create a function with a nested for loop where the outer loop iterates through the left list and the inner loop iterates through the right list, counting
    up for everytime the current outer loop value is found. At the end of inner loop, multiply the value being searched for by the number of occurances and 
    add that result to an array.
3.  Iterate through the new array, adding each element to find the total similarity score
*/

int getLen(const char* filename){
    FILE *fileP;
    char line[100];
    int length = 0;

    // open file
    fileP = fopen(filename, "r");
    if(fileP == NULL){
        printf("ERROR: file not found (fileP == NULL)");
        exit(EXIT_FAILURE);
    }

    // count number of lines
    // printf("Input: %s\n", filename);
    while(fgets(line, sizeof(line), fileP) != NULL){
        length++;
    }
    // printf("Length of list: %d", length);

    fclose(fileP);
    return length;
}

// populate list with it's respective values
void popL1L2(const char* filename, int* L1, int* L2){
    FILE *fileP;
    char line[100];

    // open file
    fileP = fopen(filename, "r");
    if(fileP == NULL){
        printf("ERROR: file not found (fileP == NULL)");
        exit(EXIT_FAILURE);
    }

    // populate list
    int left, right;
    int i = 0;
    while(fgets(line, sizeof(line), fileP) != NULL){
        // printf(line);
        sscanf(line, "%d%d", &left, &right);
        //// debug left, right
        // printf("\nLeft: %d", left);
        // printf("\nRight: %d\n", right);
        L1[i] = left;
        L2[i] = right;
        i++;
    }

    fclose(fileP);
}

int getTotalSimilarities(const int* L1, const int* L2, int* similarities, const int listLength){
    // find and store the number of instances a left element is found in the right list
    for(int i = 0; i < listLength; i++){
        int curr = L1[i];
        int count = 0;
        for(int j = 0; j < listLength; j++){
            if(curr == L2[j]){
                count++;
            }
        }
        similarities[i] = count;
    }

    // calculate total similarities score (left element * occurances in right)
    int result = 0;
    for(int i = 0; i < listLength; i++){
        result += L1[i]*similarities[i];
    }

    return result;
}

int main(){
    char filename[50] = "input.txt";
    int listLength = getLen(filename);
    printf("Input: %s\n", filename);
    printf("Length of list: %d", listLength);

    // create arrays
    int* L1 = (int*)(malloc(listLength*sizeof(int)));
    int* L2 = (int*)(malloc(listLength*sizeof(int)));
    int* similarities = (int*)(malloc(listLength*sizeof(int)));

    // get L1 and L2
    popL1L2(filename, L1, L2);
    //// debug L1, L2
    // for(int i = 0; i < listLength; i++){
    //     printf("\nL1: %d", L1[i]);
    //     printf("\nL2: %d\n", L2[i]);
    // }

    // calculate total similarities
    int totalSimilarities = getTotalSimilarities(L1, L2, similarities, listLength);
    printf("\nTotal Similarities: %d", totalSimilarities);

    // free memory
    free(L1);
    free(L2);
    free(similarities);

    return 0;
}

/*
Success!
Input: input.txt
Length of list: 1000
Total Similarities: 19437052

Valgrind

*/