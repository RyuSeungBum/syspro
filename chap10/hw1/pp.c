#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *top = NULL;

void push(int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = top;
    top = new_node;
}

int pop() {
    if (top == NULL) {
        printf("Stack is empty!\n");
        return -1;
    }
    struct node *temp = top;
    int popped_data = temp->data;
    top = top->next;
    free(temp);
    return popped_data;
}

void print_stack() {
    struct node *current = top;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int main() {
    float input;
    while (1) {
        if (scanf("%f", &input) != 1) {
            print_stack();
            break;
        }
        if (input > 0 && (int)input == input) {
            push((int)input);
        } else {
			printf("Print stack\n");
            printf("%d\n", (int)input);
            print_stack();
            break;
        }
    }
    return 0;
}

