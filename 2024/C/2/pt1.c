#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Methodology
1.  open file > read each line > perform operations per line, counting up safe integer as result
2.  function isSafe() should check if the line is safe and return a 0 or 1 accordingly. If 1, increment safe integer
3.  isSafe() checks
    a.  Is the number after the first greater than or less than? Set direction int as -1 or 1 accordingly
    b.  At any given location (including first check), is the next number different by at least one and at most three?
        If not, return 0;
    c.  If the number after the first has passed the two tests, repeat the following until end of string is reached:
        -   Does the next number following the direction -1 or 1? If not, return 0
        -   Does the next number fall within the difference requirements? If not return 0
    d.  If the end of the string is reached, return 1
4.  return safe integer as result
*/

int isSafe(char *line){
    // printf("\nLevel: %s", line);
    
    // isSafe()
    int direction = 1; // 1 = forward, -1 = backward
    int i = 0; // use to keep track of iterations for checking only the second number of direction
    int prev = 0; // use to keep track of previous number
    char *numStr = strtok(line, " ");
    // iterate through numbers in string
    while(numStr != NULL){
        int num = atoi(numStr); // convert string to int
        // printf("\ntest: %d", num);
        // get initial direction
        if(i == 1){
            if(num > prev){
                direction = 1;
            }
            else if(num < prev){
                direction = -1;
            }
            // printf("\ndirection: %d", direction);
        }
        // test for directional consistency
        else if(i > 1){
            if(direction == 1){
                if(num < prev){
                    // printf("\nFAILED: Inconsistent direction");
                    return 0;
                }
            }
            if(direction == -1){
                if(num > prev){
                    // printf("\nFAILED: Inconsistent direction");
                    return 0;
                }
            }
        }
        // test adjacent differences
        if(i > 0){
            if(abs(prev-num) < 1 || abs(prev-num) > 3){
                // printf("\nFAILED: abs(prev-num) < 1 || abs(prev-num) > 3");
                return 0;
            }
        }
        
        prev = num;
        numStr = strtok(NULL, " ");
        i++;
    }

    return 1; // return 1 for safe if end of line is reached
}

int main(){
    char filename[]  = "input.txt";
    printf("Input: %s", filename);
    FILE *fileP;
    fileP = fopen(filename, "r");
    char line[100];
    int safeCount = 0;

    // iterate through file line by line
    while(fgets(line, sizeof(line), fileP) != NULL){
        // printf("\n%s", line);
        // safeCount += isSafe(line);
    }
    
    printf("\nSafe report count: %d\n", safeCount);
    return 0;
}

/*
Success!
Input: input.txt
Safe report count: 246

Valgrind
==22756== Memcheck, a memory error detector
==22756== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==22756== Using Valgrind-3.22.0 and LibVEX; rerun with -h for copyright info
==22756== Command: ./pt1.exe
==22756== 
Input: input.txt
Safe report count: 0
==22756== 
==22756== HEAP SUMMARY:
==22756==     in use at exit: 472 bytes in 1 blocks
==22756==   total heap usage: 3 allocs, 2 frees, 5,592 bytes allocated
==22756== 
==22756== LEAK SUMMARY:
==22756==    definitely lost: 0 bytes in 0 blocks
==22756==    indirectly lost: 0 bytes in 0 blocks
==22756==      possibly lost: 0 bytes in 0 blocks
==22756==    still reachable: 472 bytes in 1 blocks
==22756==         suppressed: 0 bytes in 0 blocks
==22756== Reachable blocks (those to which a pointer was found) are not shown.
==22756== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==22756== 
==22756== For lists of detected and suppressed errors, rerun with: -s
==22756== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
*/