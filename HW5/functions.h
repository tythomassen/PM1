#ifndef FUNCTIONS_H   // include guard: prevents this header from being processed twice
#define FUNCTIONS_H

// ── Problem 1: Linked List ────────────────────────────────────────────────────

typedef struct Node {
    int data;           // integer value stored in this node
    struct Node *next;  // pointer to the next node, NULL if this is the last
} Node;

typedef struct {
    Node *head;  // pointer to the first node in the list
    Node *tail;  // pointer to the last node in the list
    int size;    // count of nodes currently in the list
} LinkedList;

LinkedList *list_create(void);
void        list_destroy(LinkedList *list);
int         list_insert_front(LinkedList *list, int value);
int         list_insert_back(LinkedList *list, int value);
int         list_remove(LinkedList *list, int value);
Node       *list_find(LinkedList *list, int value);
void        list_reverse(LinkedList *list);
int         list_get(LinkedList *list, int index, int *value);
void        list_print(const LinkedList *list);
int         list_size(const LinkedList *list);

// ── Problem 2: Stack ──────────────────────────────────────────────────────────

typedef struct StackNode {
    int data;               // integer value stored in this stack node
    struct StackNode *next; // pointer to the node immediately below this one
} StackNode;

typedef struct {
    StackNode *top;  // pointer to the topmost node (most recently pushed)
    int size;        // count of elements currently on the stack
} Stack;

Stack *stack_create(void);
void   stack_destroy(Stack *stack);
int    stack_push(Stack *stack, int value);
int    stack_pop(Stack *stack, int *value);
int    stack_peek(const Stack *stack, int *value);
int    stack_is_empty(const Stack *stack);
int    stack_size(const Stack *stack);
void   stack_clear(Stack *stack);
void   stack_print(const Stack *stack);

// ── Problem 3: Queue ──────────────────────────────────────────────────────────

typedef struct QueueNode {
    int data;               // integer value stored in this queue node
    struct QueueNode *next; // pointer to the node added just after this one
} QueueNode;

typedef struct {
    QueueNode *front;  // pointer to the node at the dequeue (removal) end
    QueueNode *rear;   // pointer to the node at the enqueue (insertion) end
    int size;          // count of elements currently in the queue
} Queue;

Queue *queue_create(void);
void   queue_destroy(Queue *queue);
int    queue_enqueue(Queue *queue, int value);
int    queue_dequeue(Queue *queue, int *value);
int    queue_peek(const Queue *queue, int *value);
int    queue_is_empty(const Queue *queue);
int    queue_size(const Queue *queue);
void   queue_clear(Queue *queue);
void   queue_print(const Queue *queue);

// ── Problem 4: LRU Cache ──────────────────────────────────────────────────────

typedef struct CacheEntry {
    int key;                  // lookup key for this entry
    int value;                // value associated with the key
    struct CacheEntry *prev;  // pointer toward the most-recently-used end
    struct CacheEntry *next;  // pointer toward the least-recently-used end
} CacheEntry;

typedef struct {
    int capacity;     // maximum number of entries the cache can hold
    int size;         // current number of entries in the cache
    CacheEntry *head; // pointer to the most recently used entry
    CacheEntry *tail; // pointer to the least recently used entry
} LRUCache;

LRUCache *lru_create(int capacity);
void      lru_destroy(LRUCache *cache);
int       lru_get(LRUCache *cache, int key, int *value);
int       lru_put(LRUCache *cache, int key, int value);
void      lru_print(const LRUCache *cache);

#endif // FUNCTIONS_H
