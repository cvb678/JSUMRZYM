#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convertFromRoman (char* number, size_t size) {
    static const char roman[] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
    static const int decimal[] = {1, 5, 10, 50, 100, 500, 1000};
    const size_t romanSize = 7;

    int i, j, index1, index2, currentSum;
    index1 = 0;
    index2 = 0;
    currentSum = 0;

    for(i=0; i<size-1; i++) {
        index1=0;
        index2=0;

        for(j=0; j<romanSize; j++) {
            if(number[i] == roman[j]) {
                index1 = j;
            }
            if(number[i+1] == roman[j]) {
                index2 = j;
            }
        }

        if(index1>=index2) {
            currentSum += decimal[index1];
        } else {
            currentSum += decimal[index2]-decimal[index1];
            i++;
        }
    }

    return currentSum;
};

void printRomanFromArabic(int num) {
    static const char* roman[] = {"M\0", "CM\0", "D\0", "CD\0", "C\0", "XC\0", "L\0", "XL\0", "X\0", "IX\0", "V\0", "IV\0", "I\0"};
    static const int decimal[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    const size_t decimalSize = 13;
    int i = 0;

    for(i=0; i<decimalSize; i++) {
        while(num%decimal[i] < num) {
            printf("%s", roman[i]);
            num-=decimal[i];
        }
    }
    printf("\n");
};

int main (int argc, char* argv[]) {

    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int i = 0;
    int j = 0;
    char* num1;
    char* num2;
    size_t num1Size;
    size_t num2Size;
    int num1Arabic;
    int num2Arabic;

    while((read = getline(&line, &len, stdin)) != -1) {

        num1Arabic = 0;
        num2Arabic = 0;
        num1Size = 0;
        num2Size = 0;

        //check how long are number strings
        for(i=0; i<read-1; i++) {
            if(line[i] == ' ') {
                num1Size = i+1;
                num2Size = read-(i+1);
            }
        }

        //there must be 2 numbers to allocate
        if(num2Size < 2) {
            exit(EXIT_FAILURE);
        }

        num1 = malloc(sizeof(char)*num1Size);
        num2 = malloc(sizeof(char)*num2Size);

        strncpy(num1, line, num1Size-1);
        strncpy(num2, line+num1Size, num2Size-1);

        num1Arabic = convertFromRoman(num1, num1Size);
        num2Arabic = convertFromRoman(num2, num2Size);

        printRomanFromArabic(num1Arabic+num2Arabic);

        free(num1);
        free(num2);
    }

    free(line);

    exit(EXIT_SUCCESS);
};
