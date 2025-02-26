#include <stdlib.h>
#include <stdio.h>

/*
Methodology: 
1.      iterate through input.txt to find length of lists L
2.      create array1 and array2--each of length L
3.      create function for sorting lists: should take array and create a tempArray of length L. After the smallest is found
        replace that value in the list with X. Repeat until entire list is X.
4.      iterate through both lists--each time performing an absolute value subtraction and storing that value in a results array
5.      iterate through restults array, adding the number each time
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

int compare_integers(const void *a, const void *b){
    return (*(int*)a-*(int*)b);
}

int getDistance(int* L1, int* L2, int length){
    int distance = 0;
    for(int i = 0; i < length; i++){
        distance += abs(L1[i]-L2[i]);
    }
    return distance;
}

int main(){
    char filename[50] = "input.txt";
    int listLength = getLen(filename);
    printf("Input: %s\n", filename);
    printf("Length of list: %d", listLength);

    // create arrays 1 and 2
    int* L1 = (int*)malloc(listLength*sizeof(int));
    int* L2 = (int*)malloc(listLength*sizeof(int));
    
    // get L1 and L2
    popL1L2(filename, L1, L2);
    //// debug L1, L2
    // for(int i = 0; i < listLength; i++){
    //     printf("\nL1: %d", L1[i]);
    //     printf("\nL2: %d\n", L2[i]);
    // }

    // sort lists
    qsort(L1, listLength, sizeof(int), compare_integers);
    qsort(L2, listLength, sizeof(int), compare_integers);
    // // debug L1, L2
    // for(int i = 0; i < listLength; i++){
    //     printf("\n%d   %d", L1[i], L2[i]);
    // }

    // get distance
    int distance = getDistance(L1, L2, listLength);
    printf("\nTotal Distance: %d", distance);

    free(L1);
    free(L2);

    return 0;
}

// Success!
/*
Input: input.txt
Length of list: 1000
Total Distance: 1882714
*/