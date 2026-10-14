#include <stdio.h>

// 引用上面定义的结构体
typedef struct PerInfo {
    char name[10];   
    char gender;     
    int age;         
    double height;   
} Person;            

int main() {
    // 打印结构体占用的字节数
    printf("Size of Person: %lu\n", sizeof(Person)); 
    
    // 预期输出：24
    // 原因简述：
    // name[10]: 0-9 (10字节)
    // gender: 10 (1字节) -> 填充3字节(11-13)以对齐int
    // age: 12-15 (4字节)
    // height: 16-23 (8字节) -> 总长24是8的倍数
    return 0;
}