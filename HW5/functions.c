/**
 * HW5: Data Structures - Function Implementations
 *
 * Complete all TODO sections below.
 */

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

/* ============================================================
 * Problem 1: Linked List
 * ============================================================ */

LinkedList* list_create(void) {
    LinkedList *list = malloc(sizeof(LinkedList));  // allocate memory 
    if (list == NULL) return NULL;// Null check
    list->head = NULL;// no first node yet
    list->tail = NULL;// no last node yet
    list->size = 0;//  empty
    return list;
}

void list_destroy(LinkedList *list) {
    if (list == NULL) return;//Null check
    Node *curr = list->head;// start at first
    while (curr != NULL) {// walk every node 
        Node *next = curr->next;// save the next pointer before freeing
        free(curr);// free the current node
        curr = next; // move to the saved next node
    }
    free(list);          
}

int list_insert_front(LinkedList *list, int value) {
    if (list == NULL) return -1;// Null check
    Node *node = malloc(sizeof(Node));// Mem allocation
    if (node == NULL) return -1;
    node->data = value;// store the value in  node
    node->next = list->head;// new node points to  old head
    list->head = node;// new node becomes the new head
    if (list->tail == NULL) list->tail = node;  
    list->size++;// increment  count
    return 0;// success
}

int list_insert_back(LinkedList *list, int value) {
    if (list == NULL) return -1; // Null check
    Node *node = malloc(sizeof(Node));   // allocate mem
    if (node == NULL) return -1; //  -1 if failed
    node->data = value; // store  value in  node
    node->next = NULL;// new node is the last
    if (list->tail == NULL) {// list is  empty
        list->head = node;// new node is both head and tail
        list->tail = node;
    } else {
        list->tail->next = node;      
        list->tail = node;            
    }
    list->size++;// increment  count
    return 0; // success
}

int list_remove(LinkedList *list, int value) {
    if (list == NULL || list->head == NULL) return -1;  // empty list, nothing to remove
    Node *prev = NULL;       // tracks the node before curr
    Node *curr = list->head; // start scanning from the head
    while (curr != NULL) {
        if (curr->data == value) {// found the node to delete
            if (prev == NULL) {// deleting the head node
                list->head = curr->next;    // head advances to next node
            } else {
                prev->next = curr->next;    
            }
            if (curr->next == NULL) {
                list->tail = prev;// tail moves back to prev
            }
            free(curr); // free the deleted node
            list->size--; // decrement  count
            return 0;
        }
        prev = curr;// advance prev
        curr = curr->next;// advance curr
    }
    return -1;           
}

Node* list_find(LinkedList *list, int value) {
    if (list == NULL) return NULL;// NULL check
    Node *curr = list->head;// start at the head
    while (curr != NULL) {// walk every node
        if (curr->data == value) return curr;  // return pointer to matching node
        curr = curr->next; //  next node
    }
    return NULL;                  
}
void list_reverse(LinkedList *list) {
    if (list == NULL || list->size <= 1) return; // 0 or 1 nodes need no reversal
    list->tail = list->head;  // current head will become the new tail
    Node *prev = NULL;// will trail behind curr as links are flipped
    Node *curr = list->head;  // start at the head
    while (curr != NULL) {
        Node *next = curr->next;  // save the original 
        curr->next = prev;// flip the link to point backwards
        prev = curr;// advance prev
        curr = next;// advance curr using saved next
    }
    list->head = prev;     
}

int list_get(LinkedList *list, int index, int *value) {
    if (list == NULL || index < 0 || index >= list->size) return -1;  //Edge check
    Node *curr = list->head; // start at 0
    for (int i = 0; i < index; i++) {   // walk forward 
        curr = curr->next;
    }
    *value = curr->data;// write the value to pointer
    return 0;                    
}

void list_print(const LinkedList *list) {
    if (list == NULL) {// Null check
        printf("[NULL]\n");
        return;
    }
    printf("[");
    Node *curr = list->head;// start at the head
    while (curr != NULL) {// walk every node
        printf("%d -> ", curr->data);// print value and arrow
        curr = curr->next;
    }
    printf("NULL]\n");         
}

int list_size(const LinkedList *list) {
    if (list == NULL) return 0;  // NULL check
    return list->size; // return the tracked count
}


/* ============================================================
 * Problem 2: Stack Implementation
 * ============================================================ */

Stack* stack_create(void) {
    Stack *stack = malloc(sizeof(Stack));  // allocate the stack struct
    if (stack == NULL) return NULL; // Null check
    stack->top = NULL; // no nodes yet
    stack->size = 0;  // stack starts empty
    return stack;  // return the ready-to-use stack
}

void stack_destroy(Stack *stack) {
    if (stack == NULL) return;  // Null check
    stack_clear(stack);  // free all nodes 
    free(stack); //  free  stack 
}

int stack_push(Stack *stack, int value) {
    if (stack == NULL) return -1;  // Null Check
    StackNode *node = malloc(sizeof(StackNode));  // Memory for  node
    if (node == NULL) return -1; // Null check
    node->data = value;  // store  value
    node->next = stack->top; // new node sits on top of old top
    stack->top = node;    // new node becomes the new top
    stack->size++; //Count though                          
    return 0; // Success                                    
}

int stack_pop(Stack *stack, int *value) {
    if (stack == NULL || stack->top == NULL) return -1;  // Null Check
    StackNode *node = stack->top;   // top node
    *value = node->data; // write val though pointer
    stack->top = node->next;   // top becomes next
    free(node);  
    stack->size--; // go down list
    return 0;  // success
}

int stack_peek(const Stack *stack, int *value) {
    if (stack == NULL || stack->top == NULL) return -1;  // Null check
    *value = stack->top->data;  // read top
    return 0; // success
}

int stack_is_empty(const Stack *stack) {
    if (stack == NULL) return 1;   // Null check
    return stack->size == 0;
}

int stack_size(const Stack *stack) {
    if (stack == NULL) return 0;  // NULL Check
    return stack->size;   
}

void stack_clear(Stack *stack) {
    if (stack == NULL) return; // Null Check
    StackNode *curr = stack->top;  // start at  top
    while (curr != NULL) {  // free every node
        StackNode *next = curr->next;     
        free(curr); // free this node
        curr = next;  // move to saved next
    }
    stack->top = NULL;   // dangling pointer
    stack->size = 0; // reset count
}

void stack_print(const Stack *stack) {
    if (stack == NULL) return;// Null check
    printf("[TOP: ");
    StackNode *curr = stack->top;// start at top
    while (curr != NULL) { 
        printf("%d", curr->data);  // print  element going down
        if (curr->next != NULL) printf(" ");  // space between elements
        curr = curr->next;
    }
    printf("]\n");
}


/* ============================================================
 * Problem 3: Queue Implementation
 * ============================================================ */

Queue* queue_create(void) {
    Queue *queue = malloc(sizeof(Queue));  //  queue struct memory
    if (queue == NULL) return NULL;   // Null check 
    queue->front = NULL; // initilize
    queue->rear = NULL; 
    queue->size = 0;                     
    return queue;  
}

void queue_destroy(Queue *queue) {
    if (queue == NULL) return;  // Null check
    queue_clear(queue); // free all nodes first
    free(queue); // then free the struct
}

int queue_enqueue(Queue *queue, int value) {
    if (queue == NULL) return -1; // Null check
    QueueNode *node = malloc(sizeof(QueueNode));    // memory alloc
    if (node == NULL) return -1; // Null check
    node->data = value; // store the value
    node->next = NULL;// new node goes to the back FILO
    if (queue->rear == NULL) {  // queue is currently empty
        queue->front = node;     // new node is front
        queue->rear = node;  // new node is rear
    } else {
        queue->rear->next = node; // old rear points to the new node
        queue->rear = node; // new node becomes the new rear
    }
    queue->size++; //  element count
    return 0;// success
}

int queue_dequeue(Queue *queue, int *value) {
    if (queue == NULL || queue->front == NULL) return -1;  // NUll check
    QueueNode *node = queue->front;   // grab the front node
    *value = node->data;// write value through pointer
    queue->front = node->next; // front advances to next 
    if (queue->front == NULL) {// queue just became empty
        queue->rear = NULL;// rear must also be NULL
    }
    free(node); 
    queue->size--;// decrement 
    return 0;// success
}

int queue_peek(const Queue *queue, int *value) {
    if (queue == NULL || queue->front == NULL) return -1;  // queue is empty
    *value = queue->front->data;  // read the front value without removing it
    return 0;// success
}

int queue_is_empty(const Queue *queue) {
    if (queue == NULL) return 1;   // Null Check
    return queue->size == 0; // 1 if empty, 0 if not
}

int queue_size(const Queue *queue) {
    if (queue == NULL) return 0;  // NULL check
    return queue->size;// return the tracked count
}

void queue_clear(Queue *queue) {
    if (queue == NULL) return;// Null Check
    QueueNode *curr = queue->front;// start at the front
    while (curr != NULL) {// free every node
        QueueNode *next = curr->next;// save next before freeing
        free(curr);// free this node
        curr = next;// move to saved next
    }
    queue->front = NULL;// queue is now empty
    queue->rear = NULL; // rear is also NULL when empty
    queue->size = 0; // reset count
}

void queue_print(const Queue *queue) {
    if (queue == NULL) return;// Null Check
    printf("[FRONT: ");
    QueueNode *curr = queue->front;// start at the front
    while (curr != NULL) { // walk to back
        printf("%d", curr->data);    
        if (curr->next != NULL) printf(" ");  
        curr = curr->next;
    }
    printf(" :REAR]\n");
}


/* ============================================================
 * Problem 4: Simple LRU Cache
 * ============================================================ */

LRUCache* lru_create(int capacity) {
    if (capacity <= 0) return NULL;// capacity must be at least 1
    LRUCache *cache = malloc(sizeof(LRUCache));   // Mem Alloc
    if (cache == NULL) return NULL; // Null checl
    cache->capacity = capacity; // store the max entry limit
    cache->size = 0; // cache starts empty
    cache->head = NULL;// no MRU entry yet
    cache->tail = NULL;// no LRU entry yet
    return cache; 
}

void lru_destroy(LRUCache *cache) {
    if (cache == NULL) return;// null check
    CacheEntry *curr = cache->head; // start at the MRU end
    while (curr != NULL) { // walk every entry and free
        CacheEntry *next = curr->next; // save next before freeing
        free(curr);
        curr = next;
    }
    free(cache);
}

/* Helper: Move an existing entry to the front (most recently used) */
static void lru_move_to_front(LRUCache *cache, CacheEntry *entry) {
    if (cache->head == entry) return;  // already at the front, nothing to do

    /* Detach entry from its current position */
    if (entry->prev != NULL) entry->prev->next = entry->next; 
    if (entry->next != NULL) {
        entry->next->prev = entry->prev;
    } else {
        cache->tail = entry->prev;
    }

    /* Insert at head */
    entry->prev = NULL;
    entry->next = cache->head;      
    if (cache->head != NULL) cache->head->prev = entry;  // old head's back-link = entry
    cache->head = entry;                   // entry is the new head
    if (cache->tail == NULL) cache->tail = entry;  // edge case: was only entry
}

/* Helper: Remove least recently used entry (tail) */
static void lru_evict(LRUCache *cache) {
    if (cache->tail == NULL) return;// Null check
    CacheEntry *lru = cache->tail; // tail is the least recently used
    if (lru->prev != NULL) {
        lru->prev->next = NULL; // second-to-last becomes new tail
    } else {
        cache->head = NULL; // lidt is empty
    }
    cache->tail = lru->prev; // update tail pointer
    free(lru); // free the evicted entry
    cache->size--;
}

int lru_get(LRUCache *cache, int key, int *value) {
    if (cache == NULL || value == NULL) return -1;  // reject bad arguments
    CacheEntry *curr = cache->head;// scan from the MRU end
    while (curr != NULL) {// walk every entry
        if (curr->key == key) {// found the key
            *value = curr->value;// write the value through the output pointer
            lru_move_to_front(cache, curr); // mark as most recently used
            return 0;
        }
        curr = curr->next;// advance toward LRU end
    }
    return -1;
}

int lru_put(LRUCache *cache, int key, int value) {
    if (cache == NULL) return -1;  // Null check

    /* Check if key already exists; update it if so */
    CacheEntry *curr = cache->head;
    while (curr != NULL) {
        if (curr->key == key) {// key found
            curr->value = value;// overwrite the stored value
            lru_move_to_front(cache, curr); // mark as most recently used
            return 0;// success
        }
        curr = curr->next;
    }

    /* Key is new; evict LRU entry if the cache is full */
    if (cache->size == cache->capacity) {
        lru_evict(cache);  // remove the least recently used entry
    }

    /* Allocate and insert a new entry at the front */
    CacheEntry *entry = malloc(sizeof(CacheEntry));  // allocate memory
    if (entry == NULL) return -1;// NULL CHECK
    entry->key = key;// store the key
    entry->value = value;// store the value
    entry->prev = NULL;// will be the new head
    entry->next = cache->head;// points to the old head
    if (cache->head != NULL) cache->head->prev = entry;  // old head's back-
    cache->head = entry;// entry is the new head
    if (cache->tail == NULL) cache->tail = entry;// edge case: first entry ever
    cache->size++;// increment entry count
    return 0;// success
}

void lru_print(const LRUCache *cache) {
    if (cache == NULL) return;// NULL CHECK
    printf("[MRU: ");
    CacheEntry *curr = cache->head;// start at the MRU end
    while (curr != NULL) {// walk toward the LRU end
        printf("(%d,%d)", curr->key, curr->value);  // print key-value pair
        if (curr->next != NULL) printf(" ");// space between entries
        curr = curr->next;
    }
    printf(" :LRU]\n");
}
