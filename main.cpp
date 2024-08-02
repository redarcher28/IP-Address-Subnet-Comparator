#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

int* string_to_int(char target[]) {
    char temp[100] = "";  // 确保 temp 是一个字符串数组并且初始化为空字符串
    char* point = target;
    int* integar = (int*)malloc(5 * sizeof(int));  // 动态分配内存以存储结果
    int i = 0;
    while(*point != '\0') {
        // 将 temp 数组清零
        memset(temp, 0, sizeof(temp));  // 这里的 sizeof(temp) 表示 temp 数组的大小，即 100

        while(*point != '.' && *point != '\0' && *point != '/') {
            // 使用 strncat 函数将 *point 加到 temp 中，每次追加一个字符
            strncat(temp, point, 1);
            point++;  // 移动指针到下一个字符
        }
        int d = atoi(temp);
        integar[i++] = d;
        // 如果当前字符不是字符串末尾，则继续移动指针
        if (*point != '\0') {
            point++;
        }
    }
    return integar;
}

char* print_binary(int n, int bits) {
    char* binary = (char*)malloc(bits + 1);  // 分配足够的内存
    int j = 0;
    for (int i = bits - 1; i >= 0; i--) {
        binary[j++] = 48 + ((n >> i) & 1);
    }
    binary[j] = '\0';  // 添加字符串结束符
    return binary;
}

char* int_to_binary(int* target, int bits) {
    char* target_binary_char = (char*)malloc(33 * sizeof(char));  // 分配足够的内存来存储32位二进制字符串
    target_binary_char[0] = '\0';  // 初始化为空字符串
    for (int i = 0; i < 4; i++) {
        char* binary = print_binary(target[i], bits);
        strcat(target_binary_char, binary);
        free(binary);  // 释放临时分配的内存
    }
    return target_binary_char;
}

void binary_compare(char* target, char* test, int bits){
    if(strncmp(target, test, bits) == 0)
        printf("YES\n");
    else
        printf("NO\n");
}

int main() {
    char inputString[33] = {};
    scanf("%s", inputString);

    char* subnet_mask = strchr(inputString, '/');  // 找到 '/' 的位置
    if (subnet_mask != NULL) {
        *subnet_mask = '\0';  // 将 '/' 替换为字符串结束符
        subnet_mask++;  // 移动到子网掩码部分
    }

    int* network_address = string_to_int(inputString);
    int mask_length = atoi(subnet_mask);

    char* network_binary = int_to_binary(network_address, 8);

    int n;
    scanf("%d", &n);

    char targetString[33] = {};
    for(; n > 0; n--){
        scanf("%s", targetString);
        int* target_address = string_to_int(targetString);
        char* target_binary = int_to_binary(target_address, 8);
        binary_compare(network_binary, target_binary, mask_length);
        free(target_binary);  // 释放动态分配的内存
        free(target_address);   // 释放动态分配的内存
    }

    free(network_binary);  // 释放动态分配的内存
    free(network_address);   // 释放动态分配的内存
    return 0;
}
