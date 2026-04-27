# AI Debugging Log - HW5

**Student Name:** [Tyler Thomassen]  
**Assignment:** HW5 - Data Structures  
**Date:** [April 24 2026]

---

## Instructions

Document your AI interactions while working on this assignment. Each section requires at least 50 characters.

---

## 1. Problem Understanding

*What did you ask AI to explain about linked lists, stacks, queues, or LRU caches?*

[How does a doubly linked list in and LRU catch work and why is it it needed, how may pointers dows ir use and what are they called?

How does on reverse a link list and what are some examples of why one would need to do so?

Whats the purpose of stack clear / stack destroy, how do we use each and what are the differences in there use cases

What edge cases would i look for in these linked lists and how can i avoid them
]

---

## 2. Debugging Assistance

*What errors did AI help you understand? (pointer issues, memory leaks, logic errors)*

[Claude helped me to ensure i was using null checks in all the correct places, i was freeing allocated memory after using pointers, i was freeing pointers / structs in the right order, setting removed elements to null before saving, no double free errors, and correct pointer syntax and usage.]

---

## 3. Verification

*How did you verify AI's suggestions were correct?*

[I double verified them with a verification claud sub agent, and also ran built it tests with sanitizers. ]

---

## 4. Learning

*What did you learn about data structures and memory management?*

[This lab tought me the diligence and debugging are king. This lab had more NUll checks than i could count and constanly required me to create, save, and free pointers which would quickly become messy especially with double linked lists and Latches. Also keep count of malloc to free ratio and keep and eye out for dangling pointers that have been freed and make sure theyre locked down with = NULL]

---

## Summary

**Total AI interactions:** [10]  
**Most helpful topic:** [LRU Latch]  
**Key takeaway:** [Tight coding practices are required for linked lists remember: Allocate, Null checks, Pointer logic, free memory, No danglers]

