# Custom Language Compiler - Design Project

## Table of Contents

1. [Overview](#overview)
2. [Compiler Architecture](#compiler-architecture)
3. [Phase 1: Lexical Analysis](#phase-1-lexical-analysis)
4. [Phase 2: Syntax Analysis](#phase-2-syntax-analysis)
5. [Phase 3: Semantic Analysis](#phase-3-semantic-analysis)
6. [Phase 4: Code Generation](#phase-4-code-generation)
7. [Register Allocation Scheme](#register-allocation-scheme)
8. [Memory Management](#memory-management)
9. [AST to Assembly Mapping](#ast-to-assembly-mapping)
10. [Building the Compiler](#building-the-compiler)
11. [Testing](#testing)
12. [Usage Examples](#usage-examples)

---

## Overview

This is a complete compiler for a custom object-oriented programming language. The compiler translates source code through four distinct phases:

```
Source Code → Lexical Analysis → Syntax Analysis → Semantic Analysis → Code Generation → x86-64 Assembly
```

**Language Features:**

- Classes with inheritance
- Functions and methods
- Local variables and class attributes
- Arrays
- Arithmetic expressions
- Control flow (if/while)
- Multiple data types (int, float, string, bool)

**Output:** x86-64 assembly code (AT&T syntax)

---

## Compiler Architecture

### File Structure

```
DesignProject/
├── lexer.l              # Lexical analyzer (Flex)
├── parser.y             # Syntax analyzer (Bison)
├── ast.h / ast.c        # Abstract Syntax Tree
├── symboltable.h / .c   # Symbol table management
├── semantic.h / .c      # Semantic analysis
├── codegen.h / .c       # Code generation
├── main.c               # Compiler driver
├── build.bat            # Build script
└── test_all.bat         # Test framework
```

### Compilation Pipeline

```
┌──────────────┐     ┌──────────────┐     ┌──────────────┐     ┌──────────────┐
│   Source     │────▶│   Tokens     │────▶│     AST      │────▶│   Assembly   │
│    Code      │     │   (lexer)    │     │   (parser)   │     │   (codegen)  │
└──────────────┘     └──────────────┘     └──────────────┘     └──────────────┘
                                                  │
                                                  ▼
                                          ┌──────────────┐
                                          │   Semantic   │
                                          │   Analysis   │
                                          └──────────────┘
```

---

## Phase 1: Lexical Analysis

**File:** `lexer.l`

**Purpose:** Break source code into tokens

**Process:**

1. Read input character by character
2. Recognize patterns (keywords, identifiers, operators, literals)
3. Generate tokens for the parser

**Example:**

```c
int x = 5 + 3;
```

**Tokens Generated:**

```
TYPE (int)
ID (x)
ASSIGN (=)
NUMBER (5)
PLUS (+)
NUMBER (3)
SEMICOLON (;)
```

**Key Features:**

- Keywords: `class`, `extends`, `function`, `if`, `while`, etc.
- Operators: `+`, `-`, `*`, `/`, `==`, `!=`, `<`, `>`, etc.
- Literals: integers, floats, strings, booleans
- Line/column tracking for error reporting

---

## Phase 2: Syntax Analysis

**File:** `parser.y`

**Purpose:** Build Abstract Syntax Tree (AST) from tokens

**Process:**

1. Apply grammar rules to token stream
2. Detect syntax errors
3. Construct hierarchical AST structure

**Grammar Example:**

```yacc
expression:
    expression PLUS term     { $$ = create_node(NODE_ADD, 2, $1, $3); }
  | term                     { $$ = $1; }
  ;

term:
    term TIMES factor        { $$ = create_node(NODE_MUL, 2, $1, $3); }
  | factor                   { $$ = $1; }
  ;
```

**AST Structure:**

```c
typedef struct ASTNode {
    NodeType type;           // NODE_PROGRAM, NODE_FUNCTION, etc.
    char* value;             // Associated value (e.g., variable name)
    int child_count;         // Number of children
    struct ASTNode** children; // Child nodes
} ASTNode;
```

**Example AST for `x = 5 + 3`:**

```
        ASSIGN
       /      \
     ID(x)    ADD
             /   \
          NUM(5) NUM(3)
```

---

## Phase 3: Semantic Analysis

**File:** `semantic.c`, `symboltable.c`

**Purpose:** Check semantic correctness and build symbol tables

### Two-Pass Analysis

**Pass 1: Symbol Table Construction**

- Declare all classes, functions, variables
- Build hierarchical scopes
- Check for duplicate declarations

**Pass 2: Semantic Checking**

- Verify all identifiers are declared before use
- Check type compatibility
- Validate function calls (parameters, return types)
- Ensure class inheritance is valid

### Symbol Table Structure

```c
typedef struct SymbolTable {
    Symbol* symbols[HASH_TABLE_SIZE];  // Hash table of symbols
    struct SymbolTable* parent;        // Parent scope
    struct SymbolTable* children[100]; // Child scopes
    int child_count;
    char* scope_name;                  // Scope identifier
} SymbolTable;
```

**Scope Hierarchy:**

```
Global Scope
├── Class: Person
│   ├── Attribute: name (string)
│   └── Method: getName()
│       └── Local: temp (string)
├── Class: Student (extends Person)
│   └── Attribute: grade (float)
└── Function: main()
    ├── Local: x (int)
    └── Local: y (int)
```

### Error Detection

**Errors (compilation stops):**

- Undeclared variables
- Duplicate declarations in same scope
- Invalid function calls
- Type errors in critical contexts

**Warnings (compilation continues):**

- Type mismatches in assignments
- Unused variables
- Unreachable code

---

## Phase 4: Code Generation

**File:** `codegen.c`

**Purpose:** Generate x86-64 assembly from AST

### Code Generation Strategy

1. **Traverse AST** in post-order
2. **Allocate registers** for temporaries
3. **Manage stack** for local variables
4. **Emit assembly** instructions

### Assembly Output Structure

```asm
    .section .data
    # Global variables and string literals

    .section .text
    .globl main

function_name:
    # Function prologue
    pushq %rbp
    movq %rsp, %rbp
    subq $stack_size, %rsp

    # Function body
    # ... instructions ...

    # Function epilogue
    movq %rbp, %rsp
    popq %rbp
    ret
```

---

## Register Allocation Scheme

### Available Registers (14 total)

| Register | Purpose                   | Caller/Callee Saved |
| -------- | ------------------------- | ------------------- |
| %rax     | Return value, temporaries | Caller              |
| %rbx     | General purpose           | Callee              |
| %rcx     | General purpose           | Caller              |
| %rdx     | General purpose           | Caller              |
| %rsi     | 2nd argument, general     | Caller              |
| %rdi     | 1st argument, general     | Caller              |
| %r8-%r15 | General purpose           | Mixed               |

**Not Used:**

- %rsp (stack pointer - reserved)
- %rbp (base pointer - reserved)

### Allocation Strategy

**Priority Order:**

1. %rax (most frequently used)
2. %rcx, %rdx (caller-saved, no preservation needed)
3. %rsi, %rdi (argument passing)
4. %r8-%r15 (additional temporaries)
5. %rbx (last resort, requires saving)

**Algorithm:**

```c
Register allocate_register(CodeGenContext* ctx) {
    for (int i = 0; i < NUM_REGISTERS; i++) {
        Register reg = register_priority[i];
        if (!ctx->registers[reg].in_use) {
            ctx->registers[reg].in_use = 1;
            return reg;
        }
    }
    // Spill to stack if all registers busy
    return spill_register(ctx);
}
```

**Spilling:** If all registers are in use, the least recently used register is saved to the stack.

---

## Memory Management

### Stack-Based Memory Model

```
High Memory
┌─────────────────┐
│  Return Address │  ← Pushed by CALL
├─────────────────┤
│  Old %rbp       │  ← Saved base pointer
├─────────────────┤  ← %rbp points here
│  Local Var 1    │  [%rbp - 8]
├─────────────────┤
│  Local Var 2    │  [%rbp - 16]
├─────────────────┤
│  Temporary 1    │  [%rbp - 24]
├─────────────────┤
│      ...        │
└─────────────────┘  ← %rsp points here
Low Memory
```

### Function Prologue

```asm
pushq %rbp           # Save old base pointer
movq %rsp, %rbp      # Set new base pointer
subq $N, %rsp        # Allocate N bytes for locals
```

### Function Epilogue

```asm
movq %rbp, %rsp      # Restore stack pointer
popq %rbp            # Restore old base pointer
ret                  # Return to caller
```

### Variable Access

**Local variables:** `[%rbp - offset]`

```asm
movq -8(%rbp), %rax   # Load local variable into %rax
```

**Function parameters:** `[%rbp + offset]`

```asm
movq 16(%rbp), %rax   # Load 1st parameter
```

**Array access:** `base_address + (index * element_size)`

```asm
movq -16(%rbp), %rax  # Load array base
movq $2, %rcx         # Index = 2
imulq $8, %rcx        # Offset = index * 8 (8 bytes per element)
addq %rcx, %rax       # Address = base + offset
movq (%rax), %rax     # Load array[2]
```

---

## AST to Assembly Mapping

### Expressions

**Arithmetic: `a + b`**

AST:

```
    ADD
   /   \
  a     b
```

Assembly:

```asm
movq a(%rbp), %rax    # Load a
movq b(%rbp), %rcx    # Load b
addq %rcx, %rax       # %rax = a + b
```

**Comparison: `x < y`**

AST:

```
    LESS_THAN
      /   \
     x     y
```

Assembly:

```asm
movq x(%rbp), %rax    # Load x
movq y(%rbp), %rcx    # Load y
cmpq %rcx, %rax       # Compare x and y
setl %al              # Set %al if x < y
movzbq %al, %rax      # Zero-extend to 64-bit
```

### Statements

**Assignment: `x = 10`**

AST:

```
  ASSIGN
   /   \
  x    10
```

Assembly:

```asm
movq $10, %rax        # Load immediate 10
movq %rax, x(%rbp)    # Store to x
```

**If Statement:**

AST:

```
     IF
    /  \
 cond  body
```

Assembly:

```asm
    # Evaluate condition
    movq cond(%rbp), %rax
    cmpq $0, %rax
    je .L_else_1          # Jump if false

    # Then body
    # ... instructions ...
    jmp .L_end_1

.L_else_1:
    # Else body (if present)

.L_end_1:
```

**While Loop:**

AST:

```
    WHILE
     /  \
  cond  body
```

Assembly:

```asm
.L_while_start_1:
    # Evaluate condition
    movq cond(%rbp), %rax
    cmpq $0, %rax
    je .L_while_end_1     # Exit if false

    # Loop body
    # ... instructions ...

    jmp .L_while_start_1  # Repeat

.L_while_end_1:
```

### Function Calls

**Call: `foo(5, 10)`**

AST:

```
   CALL
    |
   foo
   / \
  5  10
```

Assembly:

```asm
# Pass arguments (right to left)
movq $10, %rsi        # 2nd argument
movq $5, %rdi         # 1st argument
call foo              # Call function
# Return value in %rax
```

---

## Building the Compiler

### Prerequisites

- **Windows with MinGW** (gcc, make)
- **winflexbison** (Flex/Bison for Windows)
  - Install at `C:\Tools\winflexbison\`
  - Or update paths in `build.bat`

### Build Steps

```cmd
cd DesignProject
build.bat
```

**Build Process:**

1. Clean old files
2. Generate parser (`parser.tab.c`, `parser.tab.h`) from `parser.y`
3. Generate lexer (`lex.yy.c`) from `lexer.l`
4. Compile all `.c` files to `.o` object files
5. Link object files into `compiler.exe`

**Output:**

```
compiler.exe          # Main executable
parser.tab.c / .h     # Generated parser
lex.yy.c              # Generated lexer
*.o                   # Object files
```

---

## Testing

### Manual Testing

**Compile a single file:**

```cmd
compiler.exe input.txt -o output.s
```

**With intermediate outputs:**

```cmd
compiler.exe input.txt -all -o output.s
```

**Generated files:**

- `output.s` - Assembly code
- `ast.out` - Abstract Syntax Tree
- `symboltable.out` - Symbol tables
- `semantic_errors.out` - Semantic analysis report

### Automated Testing

**Run all 8 tests:**

```cmd
test_all.bat
```

**Test Suite:**

1. **test1_simple.txt** - Basic function with variables
2. **test2_variables.txt** - Multiple data types
3. **test3_arithmetic.txt** - Arithmetic expressions
4. **test4_class.txt** - Class with methods
5. **test5_errors_duplicate.txt** - Duplicate declaration errors
6. **test6_errors_undeclared.txt** - Undeclared variable errors
7. **test7_type_mismatch.txt** - Type mismatch warnings
8. **test8_complex.txt** - Arrays, loops, classes

**Results:**

```
Total Tests:   8
Passed:        8
Failed:        0
```

**Output directory:** `test_results/`

---

## Usage Examples

### Example 1: Simple Function

**Source (`example1.txt`):**

```
function main() {
    var int x;
    var int y;
    x = 5;
    y = 10;
    var int sum;
    sum = x + y;
}
```

**Compile:**

```cmd
compiler.exe example1.txt -o example1.s
```

**Generated Assembly (`example1.s`):**

```asm
    .section .text
    .globl main

main:
    pushq %rbp
    movq %rsp, %rbp
    subq $24, %rsp           # 3 variables * 8 bytes

    movq $5, %rax
    movq %rax, -8(%rbp)      # x = 5

    movq $10, %rax
    movq %rax, -16(%rbp)     # y = 10

    movq -8(%rbp), %rax      # Load x
    movq -16(%rbp), %rcx     # Load y
    addq %rcx, %rax          # x + y
    movq %rax, -24(%rbp)     # sum = x + y

    movq %rbp, %rsp
    popq %rbp
    ret
```

### Example 2: Class with Method

**Source (`example2.txt`):**

```
class Person {
    attribute int age;

    method setAge(int a) {
        age = a;
    }

    method int getAge() {
        return age;
    }
}
```

**Features Generated:**

- Constructor function: `Person_constructor`
- Method functions: `Person_setAge`, `Person_getAge`
- Attribute access via object pointer

---

## Error Handling

### Compilation Errors

**Example: Undeclared variable**

```
Error at line 5, column 3: Undeclared variable 'x'
```

**Example: Duplicate declaration**

```
Error at line 8, column 5: Duplicate declaration of 'sum' in current scope
```

### Warnings

**Example: Type mismatch**

```
Warning at line 10, column 7: Type mismatch in assignment (expected int, got float)
```

---

## Viva Preparation

### Key Concepts to Explain

1. **Lexical Analysis:**

   - How tokens are recognized using regular expressions
   - Flex pattern matching

2. **Syntax Analysis:**

   - Grammar rules and derivations
   - AST construction
   - Shift-reduce parsing

3. **Semantic Analysis:**

   - Symbol table organization (hierarchical scopes)
   - Two-pass analysis strategy
   - Error vs. warning distinction

4. **Code Generation:**

   - Register allocation algorithm
   - Stack frame layout
   - AST traversal for code emission

5. **Testing:**
   - Manual vs. automated testing
   - Test coverage (valid programs + error cases)

### Demo Workflow

1. Show source code example
2. Run compiler with `-all` flag
3. Examine AST structure
4. Review symbol table
5. Check semantic analysis results
6. View generated assembly code
7. Explain register usage and stack layout

---

## Summary

This compiler demonstrates a complete translation pipeline from high-level source code to low-level assembly:

- **Lexical Analysis:** Tokenization using Flex
- **Syntax Analysis:** AST construction using Bison
- **Semantic Analysis:** Symbol tables and type checking
- **Code Generation:** x86-64 assembly with register allocation

The system is tested with 8 comprehensive test cases covering both valid programs and error detection scenarios.

**Files Generated by Compilation:**

- `.s` - Assembly code (main output)
- `.out` - Intermediate representations (AST, symbols, errors)

**Build and test with:**

```cmd
build.bat       # Build compiler
test_all.bat    # Run all tests
```

---

## Author & Project Information

**Course:** EEX6363 - Compiler Construction
**Project:** Final Design Project (TMA4)
**Phases Integrated:**

- TMA1: Lexical Analysis
- TMA2: Syntax Analysis
- TMA3: Semantic Analysis
- TMA4: Code Generation

---
