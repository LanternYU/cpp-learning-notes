#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// 定义栈结构体
typedef struct {
    int data[MAX_SIZE];
    int top;
} Stack;

// 初始化栈
void initStack(Stack *s) {
    s->top = -1;
}

// 判断栈是否为空
int isEmpty(Stack *s) {
    return s->top == -1;
}

// 判断栈是否已满
int isFull(Stack *s) {
    return s->top == MAX_SIZE - 1;
}

// 入栈操作
void push(Stack *s, int value) {
    if (isFull(s)) {
        printf("栈溢出\n");
        return;
    }
    s->data[++(s->top)] = value;
}

// 出栈操作
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("栈为空\n");
        return -1;
    }
    return s->data[(s->top)--];
}

// 查看栈顶元素
int peak(Stack *s) {
    if (isEmpty(s)) {
        printf("栈为空\n");
        return -1;
    }
    return s->data[s->top];
}

// 获取栈的大小
int size(Stack *s) {
    return s->top + 1;
}

int main() {
    Stack s;
    initStack(&s);

    push(&s, 10);
    push(&s, 20);
    push(&s, 30);

    printf("栈顶元素: %d\n", peak(&s));
    printf("弹出元素: %d\n", pop(&s));
    printf("栈的大小: %d\n", size(&s));
	printf("栈顶元素: %d\n", peak(&s));
	
    return 0;
}
