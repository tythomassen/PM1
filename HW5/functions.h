/**
 * HW5: Data Structures - Function Prototypes
 * DO NOT MODIFY THIS FILE
 */

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/* ============================================================
 * Problem 1: Linked List
 * ============================================================ */

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
    int size;
} LinkedList;

LinkedList* list_create(void);
void list_destroy(LinkedList *list);
int list_insert_front(LinkedList *list, int value);
int list_insert_back(LinkedList *list, int value);
int list_remove(LinkedList *list, int value);
Node* list_find(LinkedList *list, int value);
void list_reverse(LinkedList *list);
int list_get(LinkedList *list, int index, int *value);
void list_print(const LinkedList *list);
int list_size(const LinkedList *list);

/* ============================================================
 * Problem 2: Stack Implementation
 * ============================================================ */

typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
    int size;
} Stack;

Stack* stack_create(void);
void stack_destroy(Stack *stack);
int stack_push(Stack *stack, int value);
int stack_pop(Stack *stack, int *value);
int stack_peek(const Stack *stack, int *value);
int stack_is_empty(const Stack *stack);
int stack_size(const Stack *stack);
void stack_clear(Stack *stack);
void stack_print(const Stack *stack);

/* ============================================================
 * Problem 3: Queue Implementation
 * ============================================================ */

typedef struct QueueNode {
    int data;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
    int size;
} Queue;

Queue* queue_create(void);
void queue_destroy(Queue *queue);
int queue_enqueue(Queue *queue, int value);
int queue_dequeue(Queue *queue, int *value);
int queue_peek(const Queue *queue, int *value);
int queue_is_empty(const Queue *queue);
int queue_size(const Queue *queue);
void queue_clear(Queue *queue);
void queue_print(const Queue *queue);

/* ============================================================
 * Problem 4: Simple LRU Cache
 * ============================================================ */

typedef struct CacheEntry {
    int key;
    int value;
    struct CacheEntry *prev;
    struct CacheEntry *next;
} CacheEntry;

typedef struct {
    int capacity;
    int size;
    CacheEntry *head;  // Most recently used
    CacheEntry *tail;  // Least recently used
} LRUCache;

LRUCache* lru_create(int capacity);
void lru_destroy(LRUCache *cache);
int lru_get(LRUCache *cache, int key, int *value);
int lru_put(LRUCache *cache, int key, int value);
void lru_print(const LRUCache *cache);

#endif /* FUNCTIONS_H */

