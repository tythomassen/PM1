# AI Log - Lab 11

## 1. Problem Understanding
This lab involves evaluating AI-generated C code for correctness, identifying bugs and missing best practices (such as null checks and memory management), and refining prompts to get more precise output. The goal is to understand how to work effectively with AI tools by both critiquing their output and improving the prompts we give them.

## 2. Debugging Assistance

### Exercise 1: AI Code Evaluation

**Prompt used:**
1. "Create an int n and than allocate n blocks of memory for each int in a pointer"
2. "Write the code to count from 0 to 10 though all members of the array adding one to each and mutiplying by 10."
3. "Add all elements in an array and print the sum."

**AI-generated code issues found:**
1. No null check after malloc and memory was never freed
2. Loop condition used `i =< n` instead of `i < n`

**Fixes applied:**
- Added null check using `if (arr == NULL)`
- Added memory deallocation using `free(arr)`
- Changed `i =< n` to `i < n` in the loop condition

### Exercise 2: Prompt Refinement

**Original prompt:**
"Write the code to print the string 'hello world' followed by the code required to reverse the string"

**Problems with original output:**
- Lacked detail on the expected output formatting
- Did not specify how the original and reversed strings should be labeled

**Refined prompt:**
"Write the code to print the string 'hello world' printing 'Original: Hello World' followed by the code required to reverse the string where you are printing 'Reversed: (reversed Hello World)'"

**Result:** The refined prompt produced output with the exact formatting expected, labeling both the original and reversed strings clearly.

## 3. Verification
- Compiled and ran each corrected code snippet to confirm expected output
- Verified the loop bounds fix produced correct array iteration without out-of-bounds access
- Confirmed memory is properly allocated and freed with no leaks

## 4. Learning Key takeaways:
- Honestly, some of these errors are a stretch. Models like Claude, GPT, and Gemini are correct around 99% of the time for this level of code — the training data coverage is extensive
- The biggest source of error is the human not being specific enough with what they are looking for
- These models are often better at debugging their own code than humans are
- Prompt specificity is the most impactful lever: vague prompts produce technically correct but contextually wrong output
