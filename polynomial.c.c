#include <stdio.h>
#include <stdlib.h>

// Structure
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Create new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

//  insert a digit at the end of the linked list
void insert(Node** head, int digit) {
    printf("%d",digit);
    Node* newNode = createNode(digit);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to add two linked lists representing big integers
Node* add(Node* num1, Node* num2) {
    int carry = 0;
    Node* result = NULL;
    Node* current = NULL;

    while (num1 || num2 || carry) {
        int sum = carry;
        if (num1) {
            sum += num1->data;
            num1 = num1->next;
        }
        if (num2) {
            sum += num2->data;
            num2 = num2->next;
        }

        carry = sum / 10;
        sum = sum % 10;

        insert(&result, sum);
        if (current == NULL) {
            current = result;
        } else {
            current = current->next;
        }
    }

    return result;
}

// Function to subtract two linked lists representing big integers
Node* subtract(Node* num1, Node* num2) {
    int borrow = 0;
    Node* result = NULL;
    Node* current = NULL;

    while (num1 || num2) {
        int diff = borrow;
        if (num1) {
            diff += num1->data;
            num1 = num1->next;
        }
        if (num2) {
            diff -= num2->data;
            num2 = num2->next;
        }

        if (diff < 0) {
            diff += 10;
            borrow = -1;
        } else {
            borrow = 0;
        }

        insert(&result, diff);
        if (current == NULL) {
            current = result;
        } else {
            current = current->next;
        }
    }

    return result;
}

// Function to multiply a linked list representing a big integer by a single-digit integer
Node* multiply(Node* num, int digit) {
    int carry = 0;
    Node* result = NULL;
    Node* current = NULL;

    while (num || carry) {
        int product = carry;
        if (num) {
            product += (num->data * digit);
            num = num->next;
        }

        carry = product / 10;
        product = product % 10;

        insert(&result, product);
        if (current == NULL) {
            current = result;
        } else {
            current = current->next;
        }
    }

    return result;
}

// Function to print a linked list
void printLinkedList(Node* head) {
    while (head) {
        printf("%d", head->data);
        head = head->next;
    }
    printf("\n");
}

// Function to free the memory allocated for a linked list
void freeLinkedList(Node* head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* num1 = NULL;
    Node* num2 = NULL;

    // Input two big integers into linked lists
    char input1[] = "1098712345678900987";
    char input2[] = "6543897204835748954389";

    for (int i = 0; input1[i] != '\0'; i++) {
        insert(&num1, input1[i] - '0');
    }
    printf("\n");
    for (int i = 0; input2[i] != '\0'; i++) {
        insert(&num2, input2[i] - '0');
    }

    printf("\n");
    // Perform addition
    Node* sum = add(num1, num2);
    printf("Addition result: ");
    printLinkedList(sum);

    // Perform subtraction (assuming num1 >= num2)
    Node* difference = subtract(num1, num2);
    printf("Subtraction result: ");
    printLinkedList(difference);

    // Perform multiplication
    Node* product = multiply(num1, 3); // Multiply by 3
    printf("Multiplication result: ");
    printLinkedList(product);

    // Free memory
    freeLinkedList(num1);
    freeLinkedList(num2);
    freeLinkedList(sum);
    freeLinkedList(difference);
    freeLinkedList(product);

    return 0;
}
