# AI Assistance Log

**Project:** LogLite  
**Name:** [Tyler Thomassen]  
**NetID:** [tmt141]  
**Date:** [April 24, 2026]

---

## Instructions

Document any significant AI assistance (ChatGPT, Copilot, Claude, etc.) you used for this project. For each session where AI helped you, fill out a section below.

**If you didn't use AI:** Replace the sessions below with:
```
No AI tools were used for this project.
```

---

## Session 1: [04/22/26]

### What I Asked
["If you were writing a filter by date function that took in 6 inputs all numbers SY,SM,SD and EY,EM,ED and converted them into two outputs S and E with each data type being an int how would you do that"]

### What It Said
[  The trick: Turn the date into one big integer.                  
  2024-01-15  →  2024 * 10000 + 01 * 100 + 15  →  20240115                                                             
  2024-03-22  →  20240322                                                                                               
  Now comparing dates is just comparing regular integers. If 20240115 <= 20240322, the date is in range. That's it.    
                                                                                                                       
  Writing the function:                                                                                                
                  
  1. Convert your start date to one integer                                                                            
  2. Convert your end date to one integer
  3. Loop through every entry in the store                                                                             
  4. Convert that entry's date to one integer
  5. If it falls between start and end, print it   ]

### What I Changed
[I took the advice and added it into my code structure, initially forgetting the multipliers for the year and month, which I corrected with "start_year * 10000 + start_month * 100 + start_day"]

### How I Verified
[I ran the code in the final script and it gave me no trouble further verified by an AI Sub Agent built with skills in code verification]

---

## Session 2: [04/23/26]

### What I Asked
["I need help with the dynamic arrays, and resizing in parser.c can you ensure my pointers are allocating the correct amounts of memory, there are no memory leaks, and no dangling pointers "]

### What It Said
[                                                                                                                       
  1. Memory allocation amount — bug in add_entry (line 43)                                                             
                                                                                                                       
  Your realloc was using the old capacity instead of the new one:                                                      
  // Wrong                                                                                                             
  LogEntry *new_entries = realloc(store->entries, store->capacity * sizeof(LogEntry));
                                                                                                                       
  // Corrected
  LogEntry *new_entries = realloc(store->entries, new_capacity * sizeof(LogEntry));                                    
  This would allocate the same amount of memory you already had, meaning the array never actually grew and writing past
   the end would corrupt memory.                                                                                       
                                                                                                                       
  ---                                                                                                                  
  2. Memory leak — realloc failure case (line 43-45)                                                                   
                                                                                                                       
  You were assigning realloc directly back to store->entries:
                                                                                                                       
  store->entries = realloc(store->entries, new_capacity * sizeof(LogEntry));
                                                                                                                       
  // Corrected — save to temp first
  LogEntry *new_entries = realloc(store->entries, new_capacity * sizeof(LogEntry));                                    
  if (new_entries == NULL) return -1;                                              
  store->entries = new_entries;                                                                                        
  If realloc fails and returns NULL, you'd overwrite store->entries with NULL, losing the original pointer entirely and
   leaking all that memory.
                                                                                                                       
  ---
  3. Dangling pointer — missing NULL after free (line 34-37)                                                           
                                                            
  After freeing, the pointer still pointed at the freed memory:
  // Wrong — entries still points at freed memory                                                                      
  free(store->entries);                          
  store->count = 0;                                                                                                    
  store->capacity = 0;                                                                                                 
                      
  // Corrected — NULL the pointer after freeing                                                                        
  free(store->entries);                        
  store->entries = NULL;
  store->count = 0;                                                                                                    
  store->capacity = 0;
                                                                                                                       
  ---             
  4. Missing +1 for null terminator (line 84)
                                                                                                                       
  // Wrong — no room for '\0'
  entry->message = malloc(strlen(message_buf));                                                                        
                  
  // Corrected                                                                                                         
  entry->message = malloc(strlen(message_buf) + 1);
  strlen doesn't count the null terminator, so without +1 the strcpy on the next line writes one byte past the         
  allocated memory. ]

### What I Changed
[Added null checks, added memory frees, corrected malloc sizes]

### How I Verified
[Claude code verification sub agent + Compilation]

---

## Session 3: [03/23/26]

### What I Asked
["I need help with the parsing logic in query.c, do you think you could lay out a more specific commented process for me to follow through with an example to help"]

### What It Said
[                    
  Step 1 — Read the first word                                                                                         
  char cmd[32];                                                                                                        
  sscanf(command, "%31s", cmd);  // cmd = "FILTER"
                                                                                                                       
  Step 2 — Match it to a known command                                                                                 
  if (strcmp(cmd, "FILTER") == 0) {
      // we know it's a FILTER command, now read what comes after                                                      
  }                                                                                                                    
                                                                                                                       
  Step 3 — Read the subcommand                                                                                         
  The %*s tells sscanf to skip a word without storing it. So to get the second word:                                   
  char sub[16];                                                                                                        
  sscanf(command, "%*s %15s", sub);  // skips "FILTER", sub = "level"                                                  
                                                                                                                       
  Step 4 — Read the argument                                                                                           
  To get the third word, skip two words:                                                                               
  char level_str[16];                                                                                                  
  sscanf(command, "%*s %*s %15s", level_str);  // skips "FILTER" "level", level_str = "ERROR"
                                                                                                                    
                                                                    ]

### What I Changed
[I didn't have the correct strcmp functions so I added the ones I was missing and more or less used parallel structure between the branches, using buffers, scanf, and fprintfs.]

### How I Verified
[Claude code verification sub agent + Compilation]

---

*Add more sessions as needed. Delete unused session templates before submitting.*

