#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};

struct node *head = NULL;
struct node *tail = NULL;

void addq(int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;
    if (tail == NULL) {
        head = tail = new_node;
    } else {
        tail->next = new_node;
        tail = new_node;
    }
}

int delete() {
    if (head == NULL) {
        return -1;
    }
    struct node *temp = head;
    int deleted_data = temp->data;
    head = head->next;
    if (head == NULL) {
        tail = NULL;
    }
    free(temp);
    return deleted_data;
}

void print_queue() {
    struct node *current = head;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int main() {
    float input;
    while (1) {
        if (scanf("%f", &input) != 1) {
            printf("Print queue\n");
            print_queue();
            break;
        }
        if (input > 0 && (int)input == input) {
            addq((int)input);
        } else {
            printf("Print queue\n");
            print_queue();
            break;
        }
    }
    return 0;
}

