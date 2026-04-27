/**
 * HW5: Data Structures - Main Driver Program
 * DO NOT MODIFY THIS FILE
 */

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

void test_linked_list(void);
void test_stack(void);
void test_queue(void);
void test_lru_cache(void);

int main(void) {
    int choice;
    
    printf("===========================================\n");
    printf("         HW5: Data Structures Tests       \n");
    printf("===========================================\n\n");
    
    printf("Select a problem to test:\n");
    printf("1. Linked List\n");
    printf("2. Stack\n");
    printf("3. Queue\n");
    printf("4. LRU Cache\n");
    printf("5. Run All\n");
    printf("0. Exit\n");
    printf("\nEnter choice: ");
    
    if (scanf("%d", &choice) != 1) {
        printf("Invalid input\n");
        return 1;
    }
    
    printf("\n");
    
    switch (choice) {
        case 1: test_linked_list(); break;
        case 2: test_stack(); break;
        case 3: test_queue(); break;
        case 4: test_lru_cache(); break;
        case 5:
            test_linked_list();
            printf("\n-------------------------------------------\n\n");
            test_stack();
            printf("\n-------------------------------------------\n\n");
            test_queue();
            printf("\n-------------------------------------------\n\n");
            test_lru_cache();
            break;
        case 0:
            printf("Goodbye!\n");
            break;
        default:
            printf("Invalid choice\n");
    }
    
    return 0;
}

void test_linked_list(void) {
    printf("===== Problem 1: Linked List =====\n\n");
    
    LinkedList *list = list_create();
    if (!list) {
        printf("Failed to create list\n");
        return;
    }
    
    printf("Empty list: ");
    list_print(list);
    printf("Size: %d\n\n", list_size(list));
    
    printf("Inserting 1, 2, 3 at back...\n");
    list_insert_back(list, 1);
    list_insert_back(list, 2);
    list_insert_back(list, 3);
    printf("List: ");
    list_print(list);
    printf("Size: %d\n\n", list_size(list));
    
    printf("Inserting 0 at front...\n");
    list_insert_front(list, 0);
    printf("List: ");
    list_print(list);
    
    printf("\nFinding 2...\n");
    Node *found = list_find(list, 2);
    printf("Found: %s\n", found ? "Yes" : "No");
    
    printf("\nGetting element at index 2...\n");
    int val;
    if (list_get(list, 2, &val) == 0) {
        printf("Value at index 2: %d\n", val);
    }
    
    printf("\nReversing list...\n");
    list_reverse(list);
    printf("Reversed: ");
    list_print(list);
    
    printf("\nRemoving 2...\n");
    list_remove(list, 2);
    printf("After removal: ");
    list_print(list);
    printf("Size: %d\n", list_size(list));
    
    list_destroy(list);
    printf("\nList destroyed.\n");
}

void test_stack(void) {
    printf("===== Problem 2: Stack =====\n\n");
    
    Stack *stack = stack_create();
    if (!stack) {
        printf("Failed to create stack\n");
        return;
    }
    
    printf("Empty stack: ");
    stack_print(stack);
    printf("Is empty: %s\n\n", stack_is_empty(stack) ? "Yes" : "No");
    
    printf("Pushing 10, 20, 30, 40...\n");
    stack_push(stack, 10);
    stack_push(stack, 20);
    stack_push(stack, 30);
    stack_push(stack, 40);
    printf("Stack: ");
    stack_print(stack);
    printf("Size: %d\n\n", stack_size(stack));
    
    int val;
    printf("Peek: ");
    if (stack_peek(stack, &val) == 0) {
        printf("%d\n", val);
    }
    
    printf("\nPopping twice...\n");
    if (stack_pop(stack, &val) == 0) printf("Popped: %d\n", val);
    if (stack_pop(stack, &val) == 0) printf("Popped: %d\n", val);
    
    printf("Stack after pops: ");
    stack_print(stack);
    printf("Size: %d\n", stack_size(stack));
    
    printf("\nClearing stack...\n");
    stack_clear(stack);
    printf("After clear: ");
    stack_print(stack);
    printf("Is empty: %s\n", stack_is_empty(stack) ? "Yes" : "No");
    
    stack_destroy(stack);
    printf("\nStack destroyed.\n");
}

void test_queue(void) {
    printf("===== Problem 3: Queue =====\n\n");
    
    Queue *queue = queue_create();
    if (!queue) {
        printf("Failed to create queue\n");
        return;
    }
    
    printf("Empty queue: ");
    queue_print(queue);
    printf("Is empty: %s\n\n", queue_is_empty(queue) ? "Yes" : "No");
    
    printf("Enqueuing 1, 2, 3, 4...\n");
    queue_enqueue(queue, 1);
    queue_enqueue(queue, 2);
    queue_enqueue(queue, 3);
    queue_enqueue(queue, 4);
    printf("Queue: ");
    queue_print(queue);
    printf("Size: %d\n\n", queue_size(queue));
    
    int val;
    printf("Peek: ");
    if (queue_peek(queue, &val) == 0) {
        printf("%d\n", val);
    }
    
    printf("\nDequeuing twice...\n");
    if (queue_dequeue(queue, &val) == 0) printf("Dequeued: %d\n", val);
    if (queue_dequeue(queue, &val) == 0) printf("Dequeued: %d\n", val);
    
    printf("Queue after dequeues: ");
    queue_print(queue);
    printf("Size: %d\n", queue_size(queue));
    
    printf("\nClearing queue...\n");
    queue_clear(queue);
    printf("After clear: ");
    queue_print(queue);
    
    queue_destroy(queue);
    printf("\nQueue destroyed.\n");
}

void test_lru_cache(void) {
    printf("===== Problem 4: LRU Cache =====\n\n");
    
    LRUCache *cache = lru_create(3);
    if (!cache) {
        printf("Failed to create cache\n");
        return;
    }
    
    printf("Adding (1, 100)...\n");
    lru_put(cache, 1, 100);
    printf("Cache: ");
    lru_print(cache);
    
    printf("\nAdding (2, 200)...\n");
    lru_put(cache, 2, 200);
    printf("Cache: ");
    lru_print(cache);
    
    printf("\nAdding (3, 300)...\n");
    lru_put(cache, 3, 300);
    printf("Cache: ");
    lru_print(cache);
    
    int val;
    printf("\nGetting key 1...\n");
    if (lru_get(cache, 1, &val) == 0) {
        printf("Got: %d (key 1 now MRU)\n", val);
    } else {
        printf("Cache miss\n");
    }
    printf("Cache: ");
    lru_print(cache);
    
    printf("\nAdding (4, 400) - should evict key 2 (LRU)...\n");
    lru_put(cache, 4, 400);
    printf("Cache: ");
    lru_print(cache);
    
    printf("\nTrying to get key 2...\n");
    if (lru_get(cache, 2, &val) == 0) {
        printf("Got: %d\n", val);
    } else {
        printf("Cache miss (key 2 was evicted)\n");
    }
    
    printf("\nUpdating key 3 to 333...\n");
    lru_put(cache, 3, 333);
    printf("Cache: ");
    lru_print(cache);
    
    lru_destroy(cache);
    printf("\nCache destroyed.\n");
}

