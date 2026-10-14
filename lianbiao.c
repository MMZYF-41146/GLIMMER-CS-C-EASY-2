#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义链表节点结构体
typedef struct Node {
    int data;           // 数据域，存储节点的数值
    struct Node *next;  // 指针域，指向下一个节点
} Node;

// 创建新节点
// 参数 data：要存入节点的数据
// 返回值：指向新创建节点的指针
Node* createNode(int data) {
    // 动态分配内存，大小为 Node 结构体
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;   // 将数据存入节点
    newNode->next = NULL;   // 新节点的 next 初始化为 NULL
    return newNode;         // 返回新节点地址
}

// 初始化链表
// 创建一个 data 为 0 的节点作为链表起点
Node* initList() {
    return createNode(0);
}

// 头插法插入节点
// 参数 head：当前链表的头指针
// 参数 n：要插入的数据
// 返回值：新的头指针
Node* headInsert(Node *head, int n) {
    Node *newNode = createNode(n); // 创建新节点
    newNode->next = head;          // 新节点指向原来的头节点
    return newNode;                // 新节点成为新的头节点
}

// 尾插法插入节点
// 参数 head：当前链表的头指针
// 参数 n：要插入的数据
// 返回值：头指针（不变）
Node* tailInsert(Node *head, int n) {
    Node *newNode = createNode(n); // 创建新节点
    Node *p = head;                // 临时指针，用于遍历到链表末尾
    
    // 循环直到找到最后一个节点（next 为 NULL 的节点）
    while (p->next != NULL) {
        p = p->next;
    }
    
    p->next = newNode;  // 将最后一个节点的 next 指向新节点
    return head;        // 头指针不变，直接返回
}

// 打印链表
// 参数 head：链表的头指针
void printList(Node *head) {
    Node *p = head;     // 临时指针用于遍历，不修改 head 本身
    
    // 遍历链表，直到 p 为 NULL
    while (p != NULL) {
        printf("%d -> ", p->data); // 输出当前节点数据
        p = p->next;               // 移动到下一个节点
    }
    printf("NULL\n"); // 输出链表结束标志
}

// 按值查找节点
// 参数 head：链表的头指针
// 参数 n：要查找的数据
// 返回值：节点位置（从1开始），找不到返回0
int findNode(Node *head, int n) {
    Node *p = head;
    int pos = 1; // 位置计数器，从第1个节点开始
    
    while (p != NULL) {
        if (p->data == n) {
            return pos; // 找到目标，返回当前位置
        }
        p = p->next; // 未找到，继续向后遍历
        pos++;       // 位置计数器加1
    }
    return 0; // 遍历结束仍未找到，返回0
}

// 删除第 n 个节点
// 参数 headRef：头指针的地址（二级指针），因为头节点可能被删除
// 参数 n：要删除的节点位置（从1开始）
// 返回值：删除成功返回 true，失败返回 false
bool deleteNode(Node **headRef, int n) {
    // 边界检查：链表为空或位置不合法
    if (*headRef == NULL || n <= 0) return false;
    
    Node *curr = *headRef; // curr 指向当前要检查的节点
    Node *prev = NULL;     // prev 指向 curr 的前一个节点
    
    // 循环 n-1 次，让 curr 走到第 n 个节点
    for (int i = 1; i < n && curr != NULL; i++) {
        prev = curr;        // prev 跟随 curr
        curr = curr->next;  // curr 向前移动
    }
    
    // 如果 curr 为 NULL，说明位置超出链表长度
    if (curr == NULL) return false;
    
    // 执行删除操作
    if (prev == NULL) {
        // 特殊情况：删除的是头节点
        *headRef = curr->next; // 头指针指向第二个节点
    } else {
        // 普通情况：跳过 curr，前一个节点直接连到 curr 的下一个
        prev->next = curr->next;
    }
    
    free(curr); // 释放被删除节点的内存，防止内存泄漏
    return true; // 删除成功
}

// 反转链表
// 参数 head：链表的头指针
// 返回值：反转后的新头指针
Node* reverseList(Node *head) {
    Node *prev = NULL;      // prev 指向已反转部分的头（初始为空）
    Node *curr = head;      // curr 指向当前正在处理的节点
    Node *nextTemp = NULL;  // nextTemp 临时保存 curr 的下一个节点
    
    while (curr != NULL) {
        nextTemp = curr->next; // 第一步：保存下一个节点，防止断链
        curr->next = prev;     // 第二步：将 curr 的指针反向，指向前一个节点
        prev = curr;           // 第三步：prev 向前移动一步
        curr = nextTemp;       // 第四步：curr 向前移动一步
    }
    
    return prev; // 循环结束时，prev 指向原链表的最后一个节点，即新头节点
}

// 主函数：测试所有链表操作
int main() {
    // 初始化链表: 0 -> NULL
    Node *head = initList();
    printf("初始状态: ");
    printList(head);

    // 头插 5: 5 -> 0 -> NULL
    head = headInsert(head, 5);
    printf("头插 5: ");
    printList(head);

    // 尾插 10: 5 -> 0 -> 10 -> NULL
    head = tailInsert(head, 10);
    printf("尾插 10: ");
    printList(head);

    // 查找数据 0 的位置
    printf("数据 0 的位置: %d\n", findNode(head, 0));

    // 删除第 2 个节点（数据为 0 的节点）
    deleteNode(&head, 2);
    printf("删除第2个节点后: ");
    printList(head);

    // 反转链表
    head = reverseList(head);
    printf("反转后: ");
    printList(head);

    return 0;
}