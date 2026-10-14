#include <stdio.h>

void swap(int *a, int *b) {
    if (a == NULL || b == NULL) return; // 安全防御
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main() {
    int a = 1, b = 2;
    swap(&a, &b);
    printf("a=%d, b=%d\n", a, b); // 输出 a=2, b=1
    return 0;
}