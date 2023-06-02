#include <stdio.h>
#include <stdlib.h>

// Define struct for linked list node
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Search for an element
int search(Node* head, int element) {
    Node* current = head;
    int position = 1;
    // Check to ensure pointer is not null (ie. pass the last node)
    while (current != NULL) {
        if (current->data == element) {
            return position;
        }
        current = current->next;
        position++;
    }
    // return -1 if not found 
    return -1;
}

// Insert an element at a given position
// Node** is a pointer to a pointer (head)
void insert(Node** head, int element, int position) {
    // Allocate memory to newNode
    Node* newNode = (Node*)malloc(sizeof(Node));
    // Add the element as data of the newNode
    newNode->data = element;

    // If position is one, move all the original elements over one position
    if (position == 1) {
        // Set the 'next' pointer of the newNode to the head
        newNode->next = *head;
        // Assign newNode as the pointer
        *head = newNode;
    } else {
        Node* current = *head;
        int currentPosition = 1;
        // Find the node right before the desired position to insert into
        while (currentPosition < position - 1 && current != NULL) {
            current = current->next;
            currentPosition++;
        }

        if (current == NULL) {
            printf("Invalid position\n");
            return;
        }
        // Set the 'next' pointer of newNode to the the `next` of the `current` we found
        newNode->next = current->next;
        // Set the `current` `next` to the newNode
        current->next = newNode;
    }
}

// Delete a given element
void delete(Node** head, int element) {
    Node* current = *head;
    // The previous node to head is null
    Node* previous = NULL;

    // If user wants to delete the head, set its `next` to `head`
    if (current != NULL && current->data == element) {
        *head = current->next;
        // Free the memory of the `head` that we want to delete
        free(current);
        return;
    }
    // Find the desired item in the list
    while (current != NULL && current->data != element) {
        previous = current;
        current = current->next;
    }
    // If the element is not in the linked list
    if (current == NULL) {
        printf("Element not found\n");
        return;
    }
    // Link the previous node to the next node (of the deleted element)
    previous->next = current->next;
    // Free memory of deleted item
    free(current);
}

// Print the linked list
void printLinkedList(Node* head) {
    // Start at the head
    Node* current = head;

    while (current != NULL) {
        printf("%d ", current->data);
        // Move to the next item
        current = current->next;
    }
    printf("\n");
}

// Initialize the linked list and provide menu to alter it
int main() {
    Node* head = NULL;
    int choice;

    // Create an initial linked list
    insert(&head, 2, 1);
    insert(&head, 4, 2);
    insert(&head, 6, 3);
    insert(&head, 8, 4);
    insert(&head, 10, 5);

    // Print the linked list
    printf("Linked list: ");
    printLinkedList(head);

    while (1) {
        // Menu for the user to alter the linked list
        printf("\n1. Search for an element\n");
        printf("2. Insert an element\n");
        printf("3. Delete an element\n");
        printf("4. Print the linked list\n");
        printf("5. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int searchElement, position;
                printf("Enter an element: ");
                scanf("%d", &searchElement);
                // Find position of given element
                position = search(head, searchElement);
                // If the function does not return 'not found'
                if (position != -1) {
                    printf("Position: %d\n", position);
                } else {
                    printf("Element not found\n");
                }
                break;
            }
            case 2: {
                int insertElement, insertPosition;
                printf("Enter an element: ");
                scanf("%d", &insertElement);
                printf("Enter a position: ");
                scanf("%d", &insertPosition);
                // Insert a given element at a given position
                insert(&head, insertElement, insertPosition);
                printf("Linked list: ");
                printLinkedList(head);
                break;
            }
            case 3: {
                int deleteElement, deletePosition;
                printf("Enter an element: ");
                scanf("%d", &deleteElement);
                // Ensure the given element is found
                deletePosition = search(head, deleteElement);
                if (deletePosition != -1) {
                    // If found, delete the element
                    delete(&head, deleteElement);
                    printf("Linked list: ");
                    printLinkedList(head);
                } else {
                    printf("Element not found\n");
                }
                break;
            }
            case 4:
                printf("Linked list: ");
                // Print the linked list, using the head
                printLinkedList(head);
                break;
            case 5:
                printf("Goodbye!");
                exit(0);
            default:
                printf("Invalid input!\n");
        }
    }
    return 0;
}
