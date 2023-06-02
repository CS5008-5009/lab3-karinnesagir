#include <stdio.h>
#include <stdlib.h>

// Define struct for doubly linked list node
typedef struct Node {
    int data;
    struct Node* next;
    // Include prev node bc this is double linked
    struct Node* prev;
} Node;

// Search for an element
int search(Node* head, int element) {
    Node* current = head;
    int position = 1;

    while (current != NULL) {
        if (current->data == element) {
            return position;
        }
        current = current->next;
        position++;
    }
    // Return -1 if element is not found
    return -1;
}

// Insert a given element at a given position
void insert(Node** head, int element, int position) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    // Add the element as data of the newNode
    newNode->data = element;
    // If given position is 1
    if (position == 1) {
        newNode->next = *head;
        newNode->prev = NULL;

        if (*head != NULL) {
            (*head)->prev = newNode;
        }
        // assign the newNode as the head
        *head = newNode;
    } else {
        Node* current = *head;
        int currentPosition = 1;
        // Go through each node and find the position right before the desired position
        while (currentPosition < position - 1 && current != NULL) {
            current = current->next;
            currentPosition++;
        }
        // Make sure the position is valid
        if (current == NULL) {
            printf("Invalid position\n");
            return;
        }
        // Place new node after the `current` node
        newNode->next = current->next;
        newNode->prev = current;
        // Update the prev node of the old `current` next node as the newNode
        if (current->next != NULL) {
            current->next->prev = newNode;
        }
        // Place the `current` node before the newNode
        current->next = newNode;
    }
}

// Delete a given element 
void delete(Node** head, int element) {
    Node* current = *head;
    // Go through the nodes until the desired element is found
    while (current != NULL && current->data != element) {
        current = current->next;
    }
    // Check to make sure element was found
    if (current == NULL) {
        printf("Element not found\n");
        return;
    }
    // If not the head, set the prev node to go to next node (based on `current`)
    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        // If head, just make the next node head
        *head = current->next;
    }
    // If not the last node, make the next node go to its prev node (based on `current`)
    if (current->next != NULL) {
        current->next->prev = current->prev;
    }
    // Free memory of the node we removed
    free(current);
}

// Print the doubly linked list
void printLinkedList(Node* head) {
    Node* current = head;

    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }

    printf("\n");
}

// Print in reverse order
void printReverse(Node* head) {

    Node* current = head;
    // Traverse to the last node
    while (current->next != NULL) {
        current = current->next;
    }

    // Move backwards to print from the last node to the head
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->prev;
    }

    printf("\n");
}

// Initialize the doubly linked list and provide menu to alter it
int main() {
    Node* head = NULL;
    int choice;

    // Create a doubly linked list
    insert(&head, 1, 1);
    insert(&head, 3, 2);
    insert(&head, 5, 3);
    insert(&head, 7, 4);
    insert(&head, 9, 5);

    // Print the doubly linked list at the start
    printf("Doubly linked list: ");
    printLinkedList(head);

    while (1) {
        // Menu
        printf("\n1. Search for an element\n");
        printf("2. Insert an element\n");
        printf("3. Delete an element\n");
        printf("4. Print the doubly linked list\n");
        printf("5. Print in reverse order\n");
        printf("6. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int searchElement, position;
                printf("Enter an element: ");
                scanf("%d", &searchElement);
                // Find the position of the given element
                position = search(head, searchElement);
                // Check if element was found
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
                // Insert the element using the insert function
                insert(&head, insertElement, insertPosition);
                printf("Doubly linked list: ");
                printLinkedList(head);
                break;
            }
            case 3: {
                int deleteElement;
                printf("Enter an element: ");
                scanf("%d", &deleteElement);
                // Delete the element using the delete function
                delete(&head, deleteElement);
                printf("Doubly linked list: ");
                printLinkedList(head);
                break;
            }
            case 4:
                printf("Doubly linked list: ");
                printLinkedList(head);
                break;
            case 5:
                printf("Doubly linked list in reverse order: ");
                printReverse(head);
                break;
            case 6:
                printf("Goodbye!");
                exit(0);
            default:
                printf("Invalid input!\n");
        }
    }

    return 0;
}
