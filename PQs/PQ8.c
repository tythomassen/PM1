#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* create_node(int data) {
    Node *n = malloc(sizeof(Node));
    n->data = data;
    n->next = NULL;
    return n;
}

Node* build_list(int arr[], int n) {
    if (n == 0) return NULL;
    Node *head = create_node(arr[0]);
    Node *curr = head;
    for (int i = 1; i < n; i++) {
        curr->next = create_node(arr[i]);
        curr = curr->next;
    }
    return head;
}

void free_list(Node *head) {
    while (head) { Node *t = head; head = head->next; free(t); }
}
/* END PROVIDED */

// TODO: Implement this function
int find_value(Node *head, int target) {
    // Your code here - return 1 if found, 0 if not
    while (head) {
        if (head->data == target) 
            return 1;
        head = head->next;
    }
    return 0;
}

int main(void) {
    int n;
    scanf("%d", &n);
    int arr[100];
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);
    int target;
    scanf("%d", &target);
    
    Node *list = build_list(arr, n);
    printf("%d\n", find_value(list, target));
    free_list(list);
    return 0;
}