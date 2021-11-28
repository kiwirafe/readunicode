# ReadUnicode

### 读取中文及UTF-8字符的工具
ReadUnicode是一个读取中文及UTF-8字符的两个函数库。

## 下载与安装
Github安装：
```sh
git clone https://github.com/kiwirafe/readunicode.git
```

### 版本v1.0.0
  - 支持两个函数，`toutf()`和`tohex()`

## 使用方法
所有函数都在`"unicode.h"`里面，请在编译时加上`unicode.c`

### `toutf()`
从UTF-8字符转换为`int`(从一个文档里读出每个`char`并把它们转换成Unicode标准的`int`)
#### 定义
```c
int *toutf(int *arg, size_t M);
//结果必须释放
```
#### 实战
假设`example.txt`里面是`云台二十八将，孔门七十二贤`
```c
#import "unicode.h"
int main() {
    FILE *fp = fopen("example.txt", "r"); //打开example.txt
    if (fp == NULL) {
        puts("Error opening file!\n");
        exit(-1);
    }
    int sentence[100]; //先分配100个空间给读取的char
    int c;
    int counter = 0, i = 0;
    
    while ((c = fgetc(fp)) != EOF){
        sentence[counter] = c; //把读取的char录入sentence里面(c实际上是不完整的Unicode)
        counter += 1;
    }

    int *result = toutf(sentence, counter); //调用函数
    while (result[i] != -1) { //如果不是结束符-1
        printf("Unicode %d:\t %d\n", i, result[i]);
        i++;
    }
   
    free(result);
    fclose(fp); 
    return 0;
}
```
结果：`20113 21488 20108 21313 20843 23558 65292 23380 38376 19971 21313 20108 36132`

### `tohex()`
从`int`转换为`hex`(Unicode标准的标准就是十六进制)
#### 定义
```c
char **tohex(int *quotient, size_t M);
//结果必须释放
```
#### 实战
```c
#import "unicode.h"
int main() {
    int sentence[3] = {12345, 234567, 1000000}; //假设一个读取完文件的数组
    char **result = tohex(sentence, 3); //调用函数

    for (int i = 0; i < 3; i++) {
        printf("%s\n", result[i]); //打印每个Hex
    }

    free(result); 
    return 0;
}
```
结果：`3039 39447 F4240`

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