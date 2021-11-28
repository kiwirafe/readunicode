#include <stdio.h>
#include <stdlib.h>
#include "unicode.h"

int *toutf(int *arg, size_t M) {
    int i, parsed;
    int counter = 0; //Counter用来计算有多少个字符
    int *utfs = malloc(M * sizeof(int));
    if (utfs == NULL) {
        puts("Malloc Error!\n");
        exit(-1);
    }

    for (i = 0; i < M; i++) { //每个char做循环
        parsed = 0;
        
        if (arg[i] < 128) //当Unicode只有1个Byte的时候：00xxxxxx
            parsed += arg[i];
        else if (arg[i] >= 192 && arg[i] < 224) { //当Unicode有2个Byte的时候：11xxxxxx 10xxxxxx
            parsed += (arg[i] - 192) * 64; //减去用来表示字符长度的11部分，并乘以2^6(后面有6个有效字节) @1
            parsed += arg[++i] - 128;
        } else if (arg[i] >= 224 && arg[i] < 240) { //当Unicode有3个Byte的时候：111xxxxx 10xxxxxx 10xxxxxx
            parsed += (arg[i] - 224) * 4096; //减去用来表示字符长度的111部分，并乘以2^12(后面有12个有效字节) @2
            parsed += (arg[++i] - 128) * 64; //同@1
            parsed += arg[++i] - 128;
        } else if (arg[i] >= 240) { //当Unicode有4个Byte的时候：1111xxxx 10xxxxxx 10xxxxxx 10xxxxxx
            parsed += (arg[i] - 240) * 262144; //减去用来表示字符长度的1111部分，并乘以2^18(后面有12个有效字节)
            parsed += (arg[++i] - 128) * 4096; //同@2
            parsed += (arg[++i] - 128) * 64; //同@1
            parsed += arg[++i] - 128;
        }
        utfs[counter] = parsed;
        counter++;
    }
    utfs[counter] = -1; //用-1来表示结束
    counter++;
    
    if (counter < M) {
        utfs = (int *) realloc(utfs, (counter + 1) * sizeof(int)); //重新Realloc成真正字符的长度，防止一开始Malloc过多
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
    //Malloc M长度的指针和M*N长度的char
    char **hex = (char **) malloc(M * sizeof(char *) + M * N * sizeof(char));
    if (hex == NULL) {
        puts("Malloc Error!\n");
        exit(-1);
    }
    char *ptr = (char *)(hex + M);
 
    for (j = 0; j < M; j++) { //每个int做循环
        hex[j] = (ptr + N * j); //把相应数量的char赋值给pointer
        counter = 0;

        while (quotient[j] != 0) {
            remain = quotient[j] % 16; //取余
            if (remain < 10) //加入小于10
                hex[j][counter++] = 48 + remain;
            else //加入大于10
                hex[j][counter++] = 55 + remain;
            
            quotient[j] = quotient[j] / 16; //除以16
        }
        
        //逆转数组，因为之前是把最小的赋值给数组最前端
        for (k = 0; k < counter / 2; k++) { 
            temp = hex[j][k];
            hex[j][k] = hex[j][counter - 1 - k];
            hex[j][counter - 1 - k] = temp;
        }
        hex[j][counter] = '\0';

    }
    return hex; // MUST BE FREED
}