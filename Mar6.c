#include <stdio.h>   // Standard I/O library for printf
#include <stdlib.h>  // Standard library for malloc and free
//Head: is a pointer to the address of the first node in the list. 


// Define a Node struct that holds data and a pointer to the next node.
// "Self-referential" because the struct contains a pointer to its own type.
typedef struct Node {
    int data;           // The value stored in this node
    struct Node* next;  // Pointer to the next node in the list (NULL if last)
} Node;

// Allocates and returns a new node with the given value.
Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node)); // Allocate memory for one Node
    new_node->data = value;  // Set the node's data to the given value
    new_node->next = NULL;   // New node points to nothing by default
    return new_node;         // Return a pointer to the newly created node
}

// Inserts a new node at the FRONT of the list.
// Takes a double pointer to head so we can update what head points to.
void insert_front(Node** head, int value) {
    Node* new_node = create_node(value); // Create the new node
    new_node->next = *head;              // New node's next points to current head
    *head = new_node;                    // Head now points to the new node
}

// Inserts a new node at the END of the list.
void insert_back(Node** head, int value) {
    Node* new_node = create_node(value); // Create the new node

    if (*head == NULL) {     // If the list is empty, new node becomes the head
        *head = new_node;
        return;
    }

    Node* current = *head;           // Start at the head
    while (current->next != NULL) {  // Walk until we reach the last node
        current = current->next;
    }
    current->next = new_node;        // Attach the new node at the end
}

// Removes the first node that contains the given value.
void delete_node(Node** head, int value) {
    if (*head == NULL) return; // Nothing to delete if list is empty

    Node* current = *head;   // Start at the head
    Node* prev = NULL;       // Track the previous node

    while (current != NULL && current->data != value) { // Search for the value
        prev = current;           // Move prev forward
        current = current->next; // Move current forward
    }

    if (current == NULL) return; // Value not found, nothing to do

    if (prev == NULL) {          // The node to delete is the head
        *head = current->next;   // Move head to the next node
    } else {
        prev->next = current->next; // Skip over the node being deleted
    }

    free(current); // Free the memory of the deleted node
}

// Searches the list for a value. Returns 1 if found, 0 if not.
int search(Node* head, int value) {
    Node* current = head;            // Start at the head
    while (current != NULL) {        // Walk through every node
        if (current->data == value)  // Check if this node holds the value
            return 1;                // Found it
        current = current->next;     // Move to the next node
    }
    return 0; // Reached end of list without finding the value
}

// Prints all values in the list from head to tail.
void print_list(Node* head) {
    Node* current = head;      // Start at the head
    while (current != NULL) {  // Walk through every node
        printf("%d", current->data);         // Print the current node's value
        if (current->next != NULL)
            printf(" -> ");    // Print arrow between nodes
        current = current->next; // Move to the next node
    }
    printf("\n"); // Newline after the last node
}

// Frees all nodes in the list to prevent memory leaks.
void free_list(Node** head) {
    Node* current = *head;    // Start at the head
    while (current != NULL) { // Walk through every node
        Node* temp = current->next; // Save the next node before freeing current
        free(current);              // Free the current node's memory
        current = temp;             // Move to the saved next node
    }
    *head = NULL; // Set head to NULL so it doesn't point to freed memory
}

int main(void) {
    Node* head = NULL; // Start with an empty list (head points to nothing)

    // Insert values at the front — each new value becomes the new head
    insert_front(&head, 10); // List: 10
    insert_front(&head, 20); // List: 20 -> 10
    insert_front(&head, 30); // List: 30 -> 20 -> 10

    // Insert values at the back
    insert_back(&head, 5);   // List: 30 -> 20 -> 10 -> 5
    insert_back(&head, 1);   // List: 30 -> 20 -> 10 -> 5 -> 1

    printf("List: ");
    print_list(head); // Prints: 30 -> 20 -> 10 -> 5 -> 1

    // Search for a value
    printf("Search 10: %s\n", search(head, 10) ? "Found" : "Not found");
    printf("Search 99: %s\n", search(head, 99) ? "Found" : "Not found");

    // Delete a node from the middle
    delete_node(&head, 10);
    printf("After deleting 10: ");
    print_list(head); // Prints: 30 -> 20 -> 5 -> 1

    // Delete the head node
    delete_node(&head, 30);
    printf("After deleting 30: ");
    print_list(head); // Prints: 20 -> 5 -> 1

    free_list(&head); // Free all remaining nodes before exiting

    return 0; // Program finished successfully
}
