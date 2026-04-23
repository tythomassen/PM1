#include <stdio.h>      // printf
#include <stdlib.h>     // malloc, free
#include "functions.h"  // all struct definitions and function prototypes

// ══════════════════════════════════════════════════════════════════════════════
// Problem 1: Linked List
// ══════════════════════════════════════════════════════════════════════════════

LinkedList *list_create(void) {
    LinkedList *list = malloc(sizeof(LinkedList));  // allocate the list control struct
    if (list == NULL) return NULL;                  // return NULL if allocation failed
    list->head = NULL;                              // no nodes yet, so head is NULL
    list->tail = NULL;                              // no nodes yet, so tail is NULL
    list->size = 0;                                 // list starts with zero elements
    return list;                                    // return the newly created list
}

void list_destroy(LinkedList *list) {
    if (list == NULL) return;         // nothing to free if the pointer is NULL
    Node *curr = list->head;          // start at the front of the list
    while (curr != NULL) {            // walk every node until we pass the last one
        Node *next = curr->next;      // save the successor before freeing curr
        free(curr);                   // release this node's memory
        curr = next;                  // advance to the saved successor
    }
    free(list);                       // release the list control struct itself
}

int list_insert_front(LinkedList *list, int value) {
    if (list == NULL) return -1;                  // reject a NULL list
    Node *node = malloc(sizeof(Node));            // allocate the new node
    if (node == NULL) return -1;                  // allocation failed
    node->data = value;                           // store the caller's value in the node
    node->next = list->head;                      // new node's successor is the old head
    list->head = node;                            // new node is now the head
    if (list->tail == NULL) list->tail = node;    // if list was empty, tail also = node
    list->size++;                                 // one more element in the list
    return 0;                                     // success
}

int list_insert_back(LinkedList *list, int value) {
    if (list == NULL) return -1;          // reject a NULL list
    Node *node = malloc(sizeof(Node));    // allocate the new node
    if (node == NULL) return -1;          // allocation failed
    node->data = value;                   // store the caller's value in the node
    node->next = NULL;                    // new node is the last, so no successor
    if (list->tail == NULL) {             // list is currently empty
        list->head = node;                // the only node is both head and tail
        list->tail = node;
    } else {
        list->tail->next = node;          // link the old tail forward to the new node
        list->tail = node;                // new node is the new tail
    }
    list->size++;                         // one more element in the list
    return 0;                             // success
}

int list_remove(LinkedList *list, int value) {
    if (list == NULL || list->head == NULL) return -1;  // empty list, nothing to remove
    Node *prev = NULL;        // trails one step behind curr
    Node *curr = list->head;  // begin scanning from the head
    while (curr != NULL) {    // walk until we exhaust the list
        if (curr->data == value) {          // found the node to delete
            if (prev == NULL) {             // deleting the head node
                list->head = curr->next;    // head advances to the next node
            } else {
                prev->next = curr->next;    // bypass the node being deleted
            }
            if (curr->next == NULL) {       // deleting the tail node
                list->tail = prev;          // tail moves back to the previous node
            }
            free(curr);                     // release the deleted node's memory
            list->size--;                   // one fewer element
            return 0;                       // success
        }
        prev = curr;          // advance prev before stepping curr
        curr = curr->next;    // move to the next node
    }
    return -1;                // value was not found in the list
}

Node *list_find(LinkedList *list, int value) {
    if (list == NULL) return NULL;          // NULL list can contain nothing
    Node *curr = list->head;                // start scanning from the head
    while (curr != NULL) {                  // walk every node
        if (curr->data == value) return curr;  // return a pointer to the matching node
        curr = curr->next;                  // advance to the next node
    }
    return NULL;                            // value was not found
}

void list_reverse(LinkedList *list) {
    if (list == NULL || list->size <= 1) return;  // 0 or 1 nodes need no reversal
    list->tail = list->head;   // current head will become the new tail after reversal
    Node *prev = NULL;         // predecessor of curr in the reversed order
    Node *curr = list->head;   // current node being re-linked
    while (curr != NULL) {     // walk every node
        Node *next = curr->next;  // save the original successor before overwriting
        curr->next = prev;        // flip this link to point backwards
        prev = curr;              // advance prev to the current node
        curr = next;              // advance curr using the saved successor
    }
    list->head = prev;         // after the loop, prev landed on the last original node
}

int list_get(LinkedList *list, int index, int *value) {
    if (list == NULL || index < 0 || index >= list->size) return -1;  // out of bounds
    Node *curr = list->head;              // start at index 0
    for (int i = 0; i < index; i++) {    // walk forward to the requested index
        curr = curr->next;
    }
    *value = curr->data;                  // write the value through the output pointer
    return 0;                             // success
}

void list_print(const LinkedList *list) {
    if (list == NULL) return;             // nothing to print
    printf("[");                          // opening bracket
    Node *curr = list->head;             // start at the head
    while (curr != NULL) {               // walk every node
        printf("%d -> ", curr->data);    // print value followed by arrow separator
        curr = curr->next;               // advance to the next node
    }
    printf("NULL]\n");                   // terminate with the NULL sentinel
}

int list_size(const LinkedList *list) {
    if (list == NULL) return 0;  // NULL list has no elements
    return list->size;           // return the tracked element count
}

// ══════════════════════════════════════════════════════════════════════════════
// Problem 2: Stack  (implemented with a singly linked list)
// ══════════════════════════════════════════════════════════════════════════════

Stack *stack_create(void) {
    Stack *stack = malloc(sizeof(Stack));  // allocate the stack control struct
    if (stack == NULL) return NULL;        // return NULL on allocation failure
    stack->top  = NULL;                    // empty stack has no top node
    stack->size = 0;                       // zero elements initially
    return stack;                          // return the newly created stack
}

void stack_destroy(Stack *stack) {
    if (stack == NULL) return;   // nothing to free
    stack_clear(stack);          // free all nodes first
    free(stack);                 // then release the control struct
}

int stack_push(Stack *stack, int value) {
    if (stack == NULL) return -1;                   // reject a NULL stack
    StackNode *node = malloc(sizeof(StackNode));    // allocate the new top node
    if (node == NULL) return -1;                    // allocation failed
    node->data  = value;                            // store the caller's value
    node->next  = stack->top;                       // new node sits on top of the old top
    stack->top  = node;                             // new node becomes the new top
    stack->size++;                                  // one more element on the stack
    return 0;                                       // success
}

int stack_pop(Stack *stack, int *value) {
    if (stack == NULL || stack->top == NULL) return -1;  // stack is empty
    StackNode *node = stack->top;    // capture the current top node
    *value = node->data;             // write its value through the output pointer
    stack->top = node->next;         // top advances to the node below
    free(node);                      // release the popped node
    stack->size--;                   // one fewer element
    return 0;                        // success
}

int stack_peek(const Stack *stack, int *value) {
    if (stack == NULL || stack->top == NULL) return -1;  // stack is empty
    *value = stack->top->data;  // read the top value without removing the node
    return 0;                   // success
}

int stack_is_empty(const Stack *stack) {
    if (stack == NULL) return 1;   // NULL stack is treated as empty
    return stack->size == 0;       // 1 if empty, 0 if not
}

int stack_size(const Stack *stack) {
    if (stack == NULL) return 0;  // NULL stack has no elements
    return stack->size;           // return the tracked element count
}

void stack_clear(Stack *stack) {
    if (stack == NULL) return;              // nothing to do
    StackNode *curr = stack->top;          // start at the top
    while (curr != NULL) {                 // free every node
        StackNode *next = curr->next;      // save successor before freeing
        free(curr);                        // release this node
        curr = next;                       // step to the saved successor
    }
    stack->top  = NULL;                    // stack is now empty
    stack->size = 0;                       // reset the element count
}

void stack_print(const Stack *stack) {
    if (stack == NULL) return;                        // nothing to print
    printf("[TOP: ");                                  // header label
    StackNode *curr = stack->top;                     // start at the top (most recent)
    while (curr != NULL) {                            // walk downward through the stack
        printf("%d", curr->data);                     // print this element's value
        if (curr->next != NULL) printf(" ");          // space between elements
        curr = curr->next;                            // step to the node below
    }
    printf("]\n");                                    // closing bracket
}

// ══════════════════════════════════════════════════════════════════════════════
// Problem 3: Queue  (implemented with a singly linked list)
// ══════════════════════════════════════════════════════════════════════════════

Queue *queue_create(void) {
    Queue *queue = malloc(sizeof(Queue));  // allocate the queue control struct
    if (queue == NULL) return NULL;        // return NULL on allocation failure
    queue->front = NULL;                   // empty queue has no front node
    queue->rear  = NULL;                   // empty queue has no rear node
    queue->size  = 0;                      // zero elements initially
    return queue;                          // return the newly created queue
}

void queue_destroy(Queue *queue) {
    if (queue == NULL) return;   // nothing to free
    queue_clear(queue);          // free all nodes first
    free(queue);                 // then release the control struct
}

int queue_enqueue(Queue *queue, int value) {
    if (queue == NULL) return -1;                    // reject a NULL queue
    QueueNode *node = malloc(sizeof(QueueNode));     // allocate the new rear node
    if (node == NULL) return -1;                     // allocation failed
    node->data = value;                              // store the caller's value
    node->next = NULL;                               // new node is the rear, no successor
    if (queue->rear == NULL) {                       // queue is currently empty
        queue->front = node;                         // single node is both front and rear
        queue->rear  = node;
    } else {
        queue->rear->next = node;                    // link old rear forward to new node
        queue->rear = node;                          // new node is the new rear
    }
    queue->size++;                                   // one more element in the queue
    return 0;                                        // success
}

int queue_dequeue(Queue *queue, int *value) {
    if (queue == NULL || queue->front == NULL) return -1;  // queue is empty
    QueueNode *node = queue->front;    // capture the current front node
    *value = node->data;               // write its value through the output pointer
    queue->front = node->next;         // front advances to the next node
    if (queue->front == NULL) {        // queue just became empty
        queue->rear = NULL;            // rear must also be NULL when queue is empty
    }
    free(node);                        // release the dequeued node
    queue->size--;                     // one fewer element
    return 0;                          // success
}

int queue_peek(const Queue *queue, int *value) {
    if (queue == NULL || queue->front == NULL) return -1;  // queue is empty
    *value = queue->front->data;  // read the front value without removing the node
    return 0;                     // success
}

int queue_is_empty(const Queue *queue) {
    if (queue == NULL) return 1;   // NULL queue is treated as empty
    return queue->size == 0;       // 1 if empty, 0 if not
}

int queue_size(const Queue *queue) {
    if (queue == NULL) return 0;  // NULL queue has no elements
    return queue->size;           // return the tracked element count
}

void queue_clear(Queue *queue) {
    if (queue == NULL) return;               // nothing to do
    QueueNode *curr = queue->front;         // start at the front
    while (curr != NULL) {                  // free every node
        QueueNode *next = curr->next;       // save successor before freeing
        free(curr);                         // release this node
        curr = next;                        // step to the saved successor
    }
    queue->front = NULL;                    // queue is now empty
    queue->rear  = NULL;                    // rear is also NULL when queue is empty
    queue->size  = 0;                       // reset the element count
}

void queue_print(const Queue *queue) {
    if (queue == NULL) return;                    // nothing to print
    printf("[FRONT: ");                           // header label
    QueueNode *curr = queue->front;              // start at the front
    while (curr != NULL) {                       // walk toward the rear
        printf("%d", curr->data);                // print this element's value
        if (curr->next != NULL) printf(" ");     // space between elements
        curr = curr->next;                       // advance toward the rear
    }
    printf(" :REAR]\n");                         // footer label
}

// ══════════════════════════════════════════════════════════════════════════════
// Problem 4: LRU Cache  (doubly linked list; head = MRU end, tail = LRU end)
// ══════════════════════════════════════════════════════════════════════════════

// remove an entry from wherever it currently sits in the doubly linked list
static void lru_detach(LRUCache *cache, CacheEntry *entry) {
    if (entry->prev != NULL) {              // entry has a predecessor
        entry->prev->next = entry->next;    // predecessor now skips over entry
    } else {
        cache->head = entry->next;          // entry was head; its successor is the new head
    }
    if (entry->next != NULL) {              // entry has a successor
        entry->next->prev = entry->prev;    // successor's back-link now skips over entry
    } else {
        cache->tail = entry->prev;          // entry was tail; its predecessor is the new tail
    }
    entry->prev = NULL;                     // clear entry's own pointers after detach
    entry->next = NULL;
}

// insert an entry at the head (most-recently-used position)
static void lru_push_front(LRUCache *cache, CacheEntry *entry) {
    entry->next = cache->head;              // entry's forward link points to the old head
    entry->prev = NULL;                     // entry has no predecessor — it is the new head
    if (cache->head != NULL) {             // list was non-empty
        cache->head->prev = entry;          // old head's back-link now points to entry
    }
    cache->head = entry;                    // entry is the new head
    if (cache->tail == NULL) {             // list was empty before this insert
        cache->tail = entry;               // entry is also the tail
    }
}

LRUCache *lru_create(int capacity) {
    if (capacity <= 0) return NULL;               // capacity must be at least 1
    LRUCache *cache = malloc(sizeof(LRUCache));   // allocate the cache control struct
    if (cache == NULL) return NULL;               // return NULL on allocation failure
    cache->capacity = capacity;                   // store the maximum entry limit
    cache->size     = 0;                          // cache starts empty
    cache->head     = NULL;                       // no MRU entry yet
    cache->tail     = NULL;                       // no LRU entry yet
    return cache;                                 // return the newly created cache
}

void lru_destroy(LRUCache *cache) {
    if (cache == NULL) return;               // nothing to free
    CacheEntry *curr = cache->head;         // start at the MRU end
    while (curr != NULL) {                  // walk every entry
        CacheEntry *next = curr->next;      // save successor before freeing
        free(curr);                         // release this entry
        curr = next;                        // step to the saved successor
    }
    free(cache);                            // release the cache control struct
}

int lru_get(LRUCache *cache, int key, int *value) {
    if (cache == NULL || value == NULL) return -1;  // reject NULL arguments
    CacheEntry *curr = cache->head;        // scan from the MRU end
    while (curr != NULL) {                 // walk every entry
        if (curr->key == key) {            // found the requested key
            *value = curr->value;          // write the stored value through the pointer
            lru_detach(cache, curr);       // remove entry from its current position
            lru_push_front(cache, curr);   // reinsert at the MRU end
            return 0;                      // cache hit
        }
        curr = curr->next;                 // advance toward the LRU end
    }
    return -1;                             // cache miss: key not present
}

int lru_put(LRUCache *cache, int key, int value) {
    if (cache == NULL) return -1;          // reject a NULL cache

    // scan to see if the key already exists in the cache
    CacheEntry *curr = cache->head;        // start at the MRU end
    while (curr != NULL) {                 // walk every entry
        if (curr->key == key) {            // key found — this is an update
            curr->value = value;           // overwrite the stored value
            lru_detach(cache, curr);       // remove from its current position
            lru_push_front(cache, curr);   // move to the MRU end
            return 0;                      // success (update, no eviction needed)
        }
        curr = curr->next;                 // advance toward the LRU end
    }

    // key is new; evict the LRU entry if the cache has reached capacity
    if (cache->size == cache->capacity) {  // cache is full
        CacheEntry *lru = cache->tail;     // tail is the least recently used entry
        lru_detach(cache, lru);            // unlink it from the list
        free(lru);                         // release its memory
        cache->size--;                     // one slot is now free
    }

    // allocate and initialize a brand-new cache entry
    CacheEntry *entry = malloc(sizeof(CacheEntry));  // allocate the new entry
    if (entry == NULL) return -1;                    // allocation failed
    entry->key   = key;                              // store the key
    entry->value = value;                            // store the value
    entry->prev  = NULL;                             // will be set by lru_push_front
    entry->next  = NULL;                             // will be set by lru_push_front
    lru_push_front(cache, entry);                    // insert at the MRU end
    cache->size++;                                   // one more entry in the cache
    return 0;                                        // success
}

void lru_print(const LRUCache *cache) {
    if (cache == NULL) return;                          // nothing to print
    printf("[MRU: ");                                   // header label
    CacheEntry *curr = cache->head;                    // start at the MRU end
    while (curr != NULL) {                             // walk toward the LRU end
        printf("(%d,%d)", curr->key, curr->value);     // print the key-value pair
        if (curr->next != NULL) printf(" -> ");        // separator between entries
        curr = curr->next;                             // advance toward the LRU end
    }
    printf(" :LRU]\n");                                // footer label
}
