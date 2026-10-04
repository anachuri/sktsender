#include <stdio.h>
#include <stdbool.h>

// Define the maximim capacity of the stack
#define MAX_SIZE 100

// Define a structure for the stack
typedef struct {
    char *path[MAX_SIZE];  
    int top;       
} Stack;

// Function to initialize the stack
void initialize(Stack *stack) {
    stack->top = -1;  
}

// Function to check if the stack is empty
bool is_empty(Stack *stack) {
    return stack->top == -1;  
}

// Function to check if the stack is full
bool is_full(Stack *stack) {
    return stack->top >= MAX_SIZE - 1;  
}

// Function to push an element onto the stack
void push(Stack *stack, char *value) {
    if (is_full(stack)) {
        printf("Stack Overflow\n");
        return;
    }
    stack->path[++stack->top] = value;
    printf("Pushed %d onto the stack\n", value);
}

// Function to pop an element from the stack
char* pop(Stack *stack) {
    if (is_empty(stack)) {
        printf("Stack Underflow\n");
        return NULL;
    }
    char *popped = stack->path[stack->top];
    stack->top--;
    printf("Popped %p from the stack\n", popped);
    return popped;
}

// Function to peek the top element of the stack
char* peek(Stack *stack) {
    if (is_empty(stack)) {
        printf("Stack is empty\n");
        return NULL;
    }
    return stack->path[stack->top];
}
