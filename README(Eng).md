# ReadUnicode

### A tool to read Chinese and UTF-8 characters
ReadUnicode is a library of two functions for reading Chinese and UTF-8 characters.

## Download and install
Github installation:
```sh
git clone https://github.com/kiwirafe/readunicode.git
```

### Version v1.0.0
  - Support two functions, `toutf()` and `tohex()`

## Instructions
All functions are in `"unicode.h"`, please include `unicode.c` when compiling

### `toutf()`
Convert from UTF-8 characters to `int`(Read each `char` from a file and convert them to Unicode standard `int`)

#### Definition
```c
int *toutf(int *arg, size_t M);
// The result must be freed
```
#### Demo
Assume that `example.txt` contains `云台二十八将，孔门七十二贤`
```c
#import "unicode.h"
int main() {
    FILE *fp = fopen("example.txt", "r"); // Open example.txt
    if (fp == NULL) {
        puts("Error opening file!\n");
        exit(-1);
    }
    int sentence[100];
    int c;
    int counter = 0, i = 0;
    
    while ((c = fgetc(fp)) != EOF){
        sentence[counter] = c; // Save the read char into the sentence varaible (c is actually incomplete Unicode character)
        counter += 1;
    }

    int *result = toutf(sentence, counter);
    while (result[i] != -1) { //If not terminator -1
        printf("Unicode %d:\t %d\n", i, result[i]);
        i++;
    }
   
    free(result);
    fclose(fp);
    return 0;
}
```
Result:`20113 21488 20108 21313 20843 23558 65292 23380 38376 19971 21313 20108 36132`

### `tohex()`
Convert from `int` to `hex` (the Unicode standard is hexadecimal)
#### Definitions
```c
char **tohex(int *quotient, size_t M);
// The result must be freed
```
#### Demo
```c
#import "unicode.h"
int main() {
    int sentence[3] = {12345, 234567, 1000000}; //Assuming the numbers in an array after reading a file
    char **result = tohex(sentence, 3);

    for (int i = 0; i < 3; i++) {
        printf("%s\n", result[i]); //Print out every Hex string
    }

    free(result); 
    return 0;
}
```
Result: `3039 39447 F4240`

## MIT License
Copyright (c) [2021] [Kiwirafe]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.