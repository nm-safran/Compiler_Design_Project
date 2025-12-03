# Step-by-Step Guide: How Your Compiler Works

This guide explains, in simple terms, how your compiler project works from start to finish. It covers each step involved in compiling and testing your code, and explains the technical requirements.

---

## 1. What is a Compiler?

A compiler is a program that translates source code written in a programming language (like C, Java, or a custom language) into machine code or assembly that a computer can execute.

**Your Compiler's Job**: Read custom language files → Check for errors → Generate assembly code

---

## 2. Project Structure Overview

Your project contains several files and folders:

- **Source Files**:
  - `main.c` - Entry point of the compiler
  - `lexer.l` - Tokenization rules
  - `parser.y` - Grammar rules
  - `ast.c` / `ast.h` - Abstract Syntax Tree creation
  - `semantic.c` / `semantic.h` - Error checking
  - `codegen.c` / `codegen.h` - Assembly code generation
  - `symboltable.c` / `symboltable.h` - Variable tracking
- **Test Files**: In `tests/` folder - sample programs to compile
- **Batch Files**:
  - `build.bat` - Builds the compiler
  - `test_all.bat` - Runs all tests
- **Output Files**:
  - `test_results/` - Generated assembly files
  - `TEST_RESULTS.md` - Test summary

---

## 3. The Build Process (What Happens When You Run build.bat)

### Step 1: Generate Lexer (Tokenizer)

- **Input**: `lexer.l` (rules for recognizing keywords, numbers, operators, etc.)
- **Tool**: Flex/Lex
- **Output**: `lex.yy.c` (C code that can split source code into tokens)
- **Example**: `int x = 5;` becomes → `[INT] [IDENTIFIER:x] [EQUALS] [NUMBER:5] [SEMICOLON]`

### Step 2: Generate Parser

- **Input**: `parser.y` (grammar rules for your language)
- **Tool**: Bison/Yacc
- **Output**: `parser.tab.c` and `parser.tab.h` (C code that checks syntax and builds AST)
- **Example**: Tokens are organized into statements, expressions, declarations

### Step 3: Compile Everything

- **Input**: All `.c` files (generated + hand-written)
- **Tool**: GCC or similar C compiler
- **Output**: `compiler.exe` (your working compiler executable)

---

## 4. Running the Compiler (What Happens When You Test)

When you run `test_all.bat`, each test file goes through these phases:

### Phase 1: Lexical Analysis (Tokenization)

- **File**: `lexer.l` → `lex.yy.c`
- **Job**: Break source code into meaningful pieces (tokens)
- **Example**:
  ```
  x = 10 + 20;
  → IDENTIFIER(x), EQUALS, NUMBER(10), PLUS, NUMBER(20), SEMICOLON
  ```

### Phase 2: Syntax Analysis (Parsing)

- **File**: `parser.y` → `parser.tab.c`
- **Job**: Check if tokens follow grammar rules and build an Abstract Syntax Tree (AST)
- **Example**:
  ```
  Assignment
    ├── Variable: x
    └── BinaryOp: +
         ├── Number: 10
         └── Number: 20
  ```

### Phase 3: Semantic Analysis

- **File**: `semantic.c`
- **Job**: Check for logical errors
  - Is variable declared before use?
  - Are types compatible? (e.g., can't add string + number)
  - Are there duplicate declarations?
- **Symbol Table**: Tracks all variables, their types, and scopes
- **Output**: Error messages if problems found, or annotated AST if correct

### Phase 4: Code Generation

- **File**: `codegen.c`
- **Job**: Convert AST into assembly code
- **Output**: `.s` file (assembly code) in `test_results/` folder

---

## 5. Deep Dive: How Code Generation Works

### Register Allocation Scheme

- **What**: CPU registers (like `eax`, `ebx` in x86) temporarily hold values during computation
- **How Your Compiler Does It**:
  1. Maintains a pool of available registers
  2. When computing `x = a + b`, allocates registers for `a`, `b`, and result
  3. After use, frees registers for reuse
- **Why**: Registers are faster than memory, so good allocation improves performance

### Memory Management Scheme

- **Stack-Based Approach**: Your compiler uses a stack for:

  - Local variables
  - Function parameters
  - Return addresses
  - Temporary values that don't fit in registers

- **How It Works**:

  ```
  Function Call → Creates Stack Frame
    [Return Address]
    [Local Variable 1]
    [Local Variable 2]
    [Temporary Values]
  Function Return → Destroys Stack Frame
  ```

- **Variable Storage**:

  - **Registers**: Fast, limited (typically 6-8 usable)
  - **Stack**: Slower, unlimited
  - **Temporaries**: Stored in registers first, spill to stack if needed

- **Class/Object Members**: Accessed using base pointer + offset
  ```
  class Point { int x; int y; }
  → x is at offset 0, y is at offset 4 (assuming 4-byte integers)
  ```

### Semantic Actions and AST Mapping

- **What**: When parser recognizes a pattern, it triggers an action
- **Example**:
  ```c
  Parser Rule: expr '+' expr
  Semantic Action: Create BinaryOpNode(PLUS, $1, $3)
  ```
- **Each AST Node Type** has a code generation function:
  - `BinaryOpNode` → generates add/subtract/multiply instructions
  - `AssignmentNode` → generates move/store instructions
  - `IfNode` → generates conditional jump instructions
  - `WhileNode` → generates loop and jump instructions

---

## 6. Testing Your Compiler

### Manual Testing

1. Pick a test file (e.g., `tests/test1_simple.txt`)
2. Run: `compiler.exe tests/test1_simple.txt`
3. Check output in `test_results/test1.s`
4. Verify assembly code is correct

### Automatic Testing (`test_all.bat`)

1. Loops through all files in `tests/` folder
2. Runs compiler on each
3. Saves results
4. Compares against expected behavior
5. Generates `TEST_RESULTS.md` summary

### Test Categories

- **Positive Tests**: Valid programs that should compile successfully

  - `test1_simple.txt` - Basic statements
  - `test2_variables.txt` - Variable declarations
  - `test3_arithmetic.txt` - Math operations
  - `test4_class.txt` - Object-oriented features

- **Negative Tests**: Invalid programs that should show errors
  - `test5_errors_duplicate.txt` - Duplicate variable names
  - `test6_errors_undeclared.txt` - Using undeclared variables
  - `test7_type_mismatch.txt` - Type compatibility errors

### What Makes Tests Good

- **Fast**: Run in seconds, not minutes
- **Independent**: Each test doesn't depend on others
- **Clear**: Easy to see what passed/failed
- **Complete**: Cover all language features and error cases

---

## 7. Visual Flow: From Source Code to Assembly

```
INPUT: test1_simple.txt
    ↓
[LEXER] → Tokens
    ↓
[PARSER] → AST (Abstract Syntax Tree)
    ↓
[SEMANTIC ANALYZER] → Validated AST + Symbol Table
    ↓
[CODE GENERATOR] → Assembly Code
    ↓
OUTPUT: test1.s (assembly file)
```

---

## 8. Common Workflow

### Building the Compiler

```cmd
build.bat
```

This creates your compiler executable.

### Testing All Files

```cmd
test_all.bat
```

This runs the compiler on all test files and generates results.

### Testing One File

```cmd
compiler.exe tests/test1_simple.txt
```

This compiles a single test file.

### Checking Results

- Open `TEST_RESULTS.md` for summary
- Open files in `test_results/` to see generated assembly code
- Check `semantic_errors.txt` for any errors found

---

## 9. Understanding Output Files

### Assembly Files (.s)

- Located in `test_results/`
- Contain assembly instructions (mov, add, jmp, etc.)
- Can be assembled and linked to create executable programs

### TEST_RESULTS.md

- Shows which tests passed/failed
- Lists errors for failed tests
- Provides summary statistics

### semantic_errors.txt

- Contains all semantic errors detected
- Shows line numbers and error descriptions

---

## 10. Troubleshooting

### Compiler Won't Build

- Check if flex/bison tools are installed
- Verify all `.c` and `.h` files are present
- Run `build.bat` and check error messages

### Tests Failing

- Read error messages in `semantic_errors.txt`
- Check if test file syntax matches your language grammar
- Verify symbol table is tracking variables correctly

### No Output Generated

- Check if compiler executable exists
- Verify test file path is correct
- Look for error messages during compilation

---

## 11. Summary

Your compiler project works in a pipeline:

1. **Build Phase**: Create the compiler from source files
2. **Lex Phase**: Break input into tokens
3. **Parse Phase**: Build syntax tree from tokens
4. **Semantic Phase**: Check for logical errors
5. **Code Gen Phase**: Produce assembly code
6. **Test Phase**: Validate with test files

Each phase depends on the previous one, and all phases must work correctly for the compiler to function properly.

---

## 12. Quick Reference

| File/Folder       | Purpose                 |
| ----------------- | ----------------------- |
| `lexer.l`         | Token recognition rules |
| `parser.y`        | Grammar rules           |
| `ast.c/h`         | Tree structure creation |
| `semantic.c/h`    | Error checking logic    |
| `codegen.c/h`     | Assembly generation     |
| `symboltable.c/h` | Variable tracking       |
| `main.c`          | Program entry point     |
| `build.bat`       | Build the compiler      |
| `test_all.bat`    | Run all tests           |
| `tests/`          | Sample programs         |
| `test_results/`   | Generated assembly      |
| `TEST_RESULTS.md` | Test summary            |

---

**This comprehensive guide covers everything from basic concepts to detailed technical implementation. You now have a complete understanding of how your compiler works, what each requirement means, and how to use and test it.**
