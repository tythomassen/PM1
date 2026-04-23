#include <stdio.h>      // printf
#include "functions.h"  // all struct and function declarations

int main(void) {
    // ── Problem 1: Linked List ─────────────────────────────────────────────

    printf("=== Linked List ===\n");
    LinkedList *list = list_create();           // create an empty linked list
    list_insert_back(list, 1);                  // append 1
    list_insert_back(list, 2);                  // append 2
    list_insert_back(list, 3);                  // append 3
    list_print(list);                           // [1 -> 2 -> 3 -> NULL]

    list_reverse(list);                         // reverse the list in place
    list_print(list);                           // [3 -> 2 -> 1 -> NULL]

    list_remove(list, 2);                       // remove the first occurrence of 2
    list_print(list);                           // [3 -> 1 -> NULL]

    int val = 0;                                // holds value retrieved by list_get
    list_get(list, 0, &val);                    // get the value at index 0
    printf("list_get(0) = %d\n", val);          // should print 3

    printf("size = %d\n", list_size(list));     // should print 2
    list_destroy(list);                         // free all list memory

    // ── Problem 2: Stack ───────────────────────────────────────────────────

    printf("\n=== Stack ===\n");
    Stack *stack = stack_create();              // create an empty stack
    stack_push(stack, 1);                       // push 1
    stack_push(stack, 2);                       // push 2
    stack_push(stack, 3);                       // push 3
    stack_print(stack);                         // [TOP: 3 2 1]

    int sv = 0;                                 // holds popped or peeked value
    stack_pop(stack, &sv);                      // pop the top element
    printf("popped = %d\n", sv);               // should print 3
    stack_peek(stack, &sv);                     // peek without removing
    printf("peek   = %d\n", sv);               // should print 2
    printf("empty? = %d\n", stack_is_empty(stack));  // should print 0
    stack_destroy(stack);                       // free all stack memory

    // ── Problem 3: Queue ───────────────────────────────────────────────────

    printf("\n=== Queue ===\n");
    Queue *queue = queue_create();              // create an empty queue
    queue_enqueue(queue, 1);                    // enqueue 1
    queue_enqueue(queue, 2);                    // enqueue 2
    queue_enqueue(queue, 3);                    // enqueue 3
    queue_print(queue);                         // [FRONT: 1 2 3 :REAR]

    int qv = 0;                                 // holds dequeued or peeked value
    queue_dequeue(queue, &qv);                  // dequeue the front element
    printf("dequeued = %d\n", qv);             // should print 1
    queue_peek(queue, &qv);                     // peek without removing
    printf("peek     = %d\n", qv);             // should print 2
    printf("size     = %d\n", queue_size(queue));  // should print 2
    queue_destroy(queue);                       // free all queue memory

    // ── Problem 4: LRU Cache ───────────────────────────────────────────────

    printf("\n=== LRU Cache ===\n");
    LRUCache *cache = lru_create(3);            // create a cache with capacity 3
    lru_put(cache, 1, 100);                     // insert key=1, value=100
    lru_put(cache, 2, 200);                     // insert key=2, value=200
    lru_put(cache, 3, 300);                     // insert key=3, value=300
    lru_print(cache);                           // [MRU: (3,300) -> (2,200) -> (1,100) :LRU]

    int cv = 0;                                 // holds retrieved cache value
    lru_get(cache, 1, &cv);                     // access key=1 (moves it to MRU)
    printf("get(1) = %d\n", cv);               // should print 100
    lru_print(cache);                           // [MRU: (1,100) -> (3,300) -> (2,200) :LRU]

    lru_put(cache, 4, 400);                     // insert key=4 (evicts LRU = key=2)
    lru_print(cache);                           // [MRU: (4,400) -> (1,100) -> (3,300) :LRU]
    lru_destroy(cache);                         // free all cache memory

    return 0;  // signal success to the OS
}
