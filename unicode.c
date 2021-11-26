#include <stdio.h>
#include <stdlib.h>
#include "unicode.h"

int *toutf(int *arg, size_t M) {
    int i, parsed;
    int counter = 0;
    int *utfs = malloc(M * sizeof(int));
    if (utfs == NULL) {
        puts("Malloc Error!\n");
        exit(-1);
    }

    for (i = 0; i < M; i++) {
        parsed = 0;
        
        if (arg[i] < 128) // This is when it's one byte. 00000000
            parsed += arg[i];
        else if (arg[i] >= 192 && arg[i] < 224) { // This is when it's two bytes. 11000000 10000000
            parsed += (arg[i] - 192) * 64; // Add the first byte.
            parsed += arg[++i] - 128;
        } else if (arg[i] >= 224 && arg[i] < 240) { // This is when it's three bytes. 11100000 10000000 10000000
            parsed += (arg[i] - 224) * 4096;
            parsed += (arg[++i] - 128) * 64; 
            parsed += arg[++i] - 128;
        } else if (arg[i] >= 240) { // This is when it's four bytes. 11110000 10000000 10000000 10000000
            parsed += (arg[i] - 240) * 262144;
            parsed += (arg[++i] - 128) * 4096;
            parsed += (arg[++i] - 128) * 64;
            parsed += arg[++i] - 128;
        }
        utfs[counter] = parsed;
        counter++;
    }
    
    if (counter < M) {
        utfs = (int *) realloc(utfs, (counter + 1) * sizeof(int));
        if (utfs == NULL) {
            puts("Realloc Error!\n");
            exit(-1);
        }
    }
    return utfs; // MUST BE FREED
}


char **tohex(int *quotient, size_t M) {
    int remain, temp;
    int counter = 0, N = 10, j = 0, k = 0;
    char **hex = (char **) malloc(M * sizeof(char *) + M * N * sizeof(char));
    if (hex == NULL) {
        puts("Malloc Error!\n");
        exit(-1);
    }
    char *ptr = (char *)(hex + M);
 
    for (j = 0; j < M; j++) {
        hex[j] = (ptr + N * j);
        counter = 0;

        while (quotient[j] != 0) {
            remain = quotient[j] % 16;
            if (remain < 10)
                hex[j][counter++] = 48 + remain;
            else
                hex[j][counter++] = 55 + remain;
            
            quotient[j] = quotient[j] / 16;
        }
        
        for (k = 0; k < counter / 2; k++) { // Reverse String
            temp = hex[j][k];
            hex[j][k] = hex[j][counter - 1 - k];
            hex[j][counter - 1 - k] = temp;
        }
        hex[j][counter] = '\0';

    }
    return hex; // MUST BE FREED
}