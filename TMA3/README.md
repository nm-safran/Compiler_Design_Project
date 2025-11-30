# TMA3 - Semantic Analyzer for Custom Programming Language

**Course:** EEX6363 - Compiler Construction
**Assignment:** TMA3 - Semantic Analysis Implementation
**Language:** Custom Object-Oriented Programming Language

## 📋 Table of Contents

1. [Overview](#overview)
2. [Three-Phase Compilation Architecture](#three-phase-compilation-architecture)
3. [Implementation Details](#implementation-details)
4. [File Structure](#file-structure)
5. [Building and Running](#building-and-running)
6. [Test Suite](#test-suite)
7. [Semantic Analysis Features](#semantic-analysis-features)
8. [Output Files](#output-files)
9. [Error Reporting](#error-reporting)
10. [Examples](#examples)

---

## 🎯 Overview

This project implements a **complete compiler front-end** for a custom object-oriented programming language, progressing through three distinct phases:

```
Source Code → [Lexical Analysis] → Tokens
            → [Syntax Analysis] → Abstract Syntax Tree (AST)
            → [Semantic Analysis] → Annotated AST + Symbol Tables + Error Reports
```

### What This Compiler Does

✅ **Lexical Analysis** - Tokenizes source code into meaningful units
✅ **Syntax Analysis** - Validates grammatical structure and builds AST
✅ **Semantic Analysis** - Verifies type correctness, scope, and program semantics
✅ **Symbol Table Management** - Tracks declarations across scopes
✅ **Type Checking** - Ensures type safety in expressions and assignments
✅ **Error Reporting** - Provides detailed error and warning messages

---

## 🏗️ Three-Phase Compilation Architecture

### Phase 1️⃣: Lexical Analysis (Scanning)

**Purpose:** Convert source code into a stream of tokens

**Implementation:** `lexer.l` (Flex specification)

**Process:**

```
Input: "local x : integer;"
       ↓
Tokens: [LOCAL] [ID:x] [COLON] [INTEGER_TYPE] [SEMI]
```

**Key Components:**

- **Pattern Matching:** Regular expressions for identifiers, keywords, literals
- **Token Creation:** Each lexeme mapped to token type with position tracking
- **Position Tracking:** Line and column numbers for error reporting
- **Comment Handling:** Single-line (`//`) and multi-line (`/* */`) comments removed

**Token Categories:**

| Category        | Examples                                                     |
| --------------- | ------------------------------------------------------------ |
| **Keywords**    | `class`, `func`, `if`, `while`, `return`, `integer`, `float` |
| **Identifiers** | `myVar`, `calculateSum`, `Student`                           |
| **Literals**    | `42`, `3.14`, `0`, `1.5e-10`                                 |
| **Operators**   | `:=`, `==`, `+`, `-`, `*`, `/`, `<`, `>`                     |
| **Delimiters**  | `(`, `)`, `{`, `}`, `[`, `]`, `;`, `,`, `.`                  |

**Example Lexical Rules:**

```lex
"class"             { return CLASS; }
"func"              { return FUNC; }
[a-zA-Z][a-zA-Z0-9]* { return ID; }
[0-9]+              { return INTLIT; }
```

---

### Phase 2️⃣: Syntax Analysis (Parsing)

**Purpose:** Verify grammatical structure and build Abstract Syntax Tree (AST)

**Implementation:** `parser.y` (Bison specification)

**Process:**

```
Tokens → [Parser] → AST
         Grammar Rules
         ↓
    Valid Structure?
```

**Grammar Structure (CFG):**

```bnf
<prog> ::= <classOrImplOrFunc_list>

<funcDef> ::= <funcHead> <funcBody>

<funcHead> ::= "func" ID "(" <params> ")" "=>" <type>

<statement> ::= <assignment>
              | <ifStatement>
              | <whileStatement>
              | <returnStatement>

<expr> ::= <term> ( ("+" | "-") <term> )*

<term> ::= <factor> ( ("*" | "/") <factor> )*
```

**AST Node Types:**

```c
typedef enum {
    NODE_PROG,           // Program root
    NODE_CLASS_DECL,     // Class declaration
    NODE_FUNC_DEF,       // Function definition
    NODE_VAR_DECL,       // Variable declaration
    NODE_ASSIGN_STAT,    // Assignment statement
    NODE_IF_STAT,        // If statement
    NODE_WHILE_STAT,     // While loop
    NODE_EXPR,           // Expression
    NODE_INTLIT,         // Integer literal
    NODE_FLOATLIT,       // Float literal
    NODE_ID,             // Identifier
    // ... more types
} NodeType;
```

**AST Example:**

For code: `x := 10 + y;`

```
ASSIGN_STAT
├── VARIABLE (x)
└── ADD_EXPR
    ├── INTLIT (10)
    └── VARIABLE (y)
```

---

### Phase 3️⃣: Semantic Analysis

**Purpose:** Verify program correctness beyond syntax

**Implementation:** `semantic.c`, `symboltable.c`

**Two-Pass Semantic Analysis:**

#### **Pass 1: Symbol Table Generation**

**Objective:** Build hierarchical symbol tables for scope management

**Process:**

```
AST → Traverse → Build Symbol Tables
                     ↓
              Global Scope
                  ↓
            Class/Function Scopes
                  ↓
             Block Scopes
```

**Symbol Table Structure:**

```c
typedef struct SymbolTable {
    char* scope_name;           // "global", "Matrix", "init"
    int level;                  // Nesting level (0 = global)
    Symbol** symbols;           // Hash table of symbols
    struct SymbolTable* parent; // Parent scope
    struct SymbolTable* child;  // First child scope
    struct SymbolTable* next;   // Sibling scope
} SymbolTable;
```

**Symbol Entry:**

```c
typedef struct Symbol {
    char* name;              // Identifier name
    SymbolKind kind;         // VARIABLE, FUNCTION, CLASS, PARAMETER
    Type* type;              // Data type information
    int line;                // Declaration line
    int column;              // Declaration column
    VisibilityType visibility; // PUBLIC, PRIVATE
    SymbolTable* class_scope; // For classes
} Symbol;
```

**Scope Resolution:**

```
Variable 'x' referenced at line 15:
    1. Search current function scope
    2. Search parent class scope (if any)
    3. Search global scope
    4. If not found → ERROR: Undeclared variable
```

#### **Pass 2: Type Checking & Semantic Validation**

**Checks Performed:**

1. **Declaration Checking**

   - ✅ All variables declared before use
   - ✅ No duplicate declarations in same scope
   - ✅ Function parameter names unique

2. **Type Checking**

   - ✅ Assignment type compatibility
   - ✅ Expression type consistency
   - ✅ Function return type matches
   - ✅ Function call argument types match parameters

3. **Scope Validation**

   - ✅ Variable accessible from current scope
   - ✅ Function/class visibility respected
   - ✅ 'self' used only in class methods

4. **Control Flow Validation**
   - ✅ Return statements in non-void functions
   - ✅ Break/continue only in loops (if implemented)

**Type Checking Example:**

```c
// Source code:
local x : integer;
local y : float;
x := y;  // Type mismatch!

// Semantic analysis:
check_assign(ASSIGN_NODE) {
    lhs_type = get_type(x) = "integer"
    rhs_type = get_type(y) = "float"

    if (lhs_type != rhs_type)
        report_error("Type mismatch: cannot assign float to integer")
}
```

**Symbol Table Traversal:**

```c
void generate_symbol_tables(ASTNode* node, SemanticContext* ctx) {
    switch(node->type) {
        case NODE_CLASS_DECL:
            // Create new scope for class
            SymbolTable* class_scope = create_scope(class_name);
            enter_scope(ctx, class_scope);
            // Process class members
            traverse_children(node, ctx);
            exit_scope(ctx);
            break;

        case NODE_FUNC_DEF:
            // Create function scope
            SymbolTable* func_scope = create_scope(func_name);
            enter_scope(ctx, func_scope);
            // Add parameters to scope
            // Process function body
            traverse_children(node, ctx);
            exit_scope(ctx);
            break;

        case NODE_VAR_DECL:
            // Check for duplicate in current scope
            if (lookup_current_scope(var_name))
                report_error("Duplicate variable");
            else
                add_symbol(ctx->current_scope, var_name);
            break;
    }
}
```

---

## 📁 File Structure

```
TMA3/
├── 📄 Core Implementation
│   ├── lexer.l              # Lexical analyzer specification (Flex)
│   ├── parser.y             # Syntax analyzer specification (Bison)
│   ├── ast.h / ast.c        # Abstract Syntax Tree implementation
│   ├── symboltable.h / .c   # Symbol table management
│   └── semantic.h / .c      # Semantic analysis engine
│
├── 🔧 Build & Test Scripts
│   ├── build.bat            # Complete build process
│   ├── run_all_tests.bat    # Run all test cases
│   ├── test_individual.bat  # Interactive test runner
│   ├── quick_test.bat       # Quick test all files
│   ├── cleanup.bat          # Clean generated files
│   └── delete_duplicates.bat # Remove duplicate files
│
├── 📝 Test Suite
│   └── tests/
│       ├── test1_simple.txt          # Basic function
│       ├── test2_variables.txt       # Variable types
│       ├── test3_arithmetic.txt      # Expressions
│       ├── test4_class.txt           # Class declaration
│       ├── test5_errors_duplicate.txt # Duplicate errors
│       ├── test6_errors_undeclared.txt # Undeclared errors
│       ├── test7_type_mismatch.txt   # Type errors
│       └── test8_complex.txt         # Complex program
│
├── 📊 Generated Files (after compilation)
│   ├── lex.yy.c             # Generated lexer
│   ├── parser.tab.c/h       # Generated parser
│   ├── compiler.exe         # Final executable
│   ├── ast.out              # AST visualization
│   ├── symboltable.out      # Symbol table report
│   └── semantic_errors.out  # Error/warning report
│
└── 📖 Documentation
    ├── README.md            # This file
    └── README_WINDOWS.md    # Windows setup guide
```

---

## 🔨 Building and Running

### Prerequisites

1. **GCC Compiler** (MinGW for Windows)
2. **Flex** (Lexical analyzer generator)
3. **Bison** (Parser generator)

### Installation (Windows)

```batch
# Install via Chocolatey
choco install mingw flex-win bison-win

# Or use WinFlexBison
# Download from: https://github.com/lexxmark/winflexbison
```

### Build Process

```batch
# Full build from scratch
build.bat

# This script performs:
#   1. Generates lexer (lex.yy.c) from lexer.l
#   2. Generates parser (parser.tab.c/h) from parser.y
#   3. Compiles AST module
#   4. Compiles symbol table module
#   5. Compiles semantic analyzer
#   6. Links everything into compiler.exe
```

**Build Steps in Detail:**

```batch
@echo off
echo Building TMA3 Semantic Analyzer...

REM Step 1: Generate parser files
win_bison -d parser.y
if %ERRORLEVEL% NEQ 0 exit /b 1

REM Step 2: Generate lexer
win_flex -o lex.yy.c lexer.l
if %ERRORLEVEL% NEQ 0 exit /b 1

REM Step 3: Compile modules
gcc -c -Wall -g ast.c -o ast.o
gcc -c -Wall -g symboltable.c -o symboltable.o
gcc -c -Wall -g semantic.c -o semantic.o
gcc -c -Wall -g parser.tab.c -o parser.tab.o
gcc -c -Wall -g lex.yy.c -o lex.yy.o

REM Step 4: Link executable
gcc -o compiler.exe ast.o symboltable.o semantic.o ^
    parser.tab.o lex.yy.o

echo Build successful!
```

---

## 🧪 Test Suite

### Running Tests

#### **Option 1: Run All Tests**

```batch
run_all_tests.bat

# Output:
# Testing: test1_simple.txt
# [PASS] Compilation successful
# Testing: test2_variables.txt
# [PASS] Compilation successful
# ...
```

#### **Option 2: Interactive Testing**

```batch
test_individual.bat

# Menu:
# [1] test1_simple.txt - Simple function
# [2] test2_variables.txt - Multiple variables
# [3] test3_arithmetic.txt - Arithmetic expressions
# ...
```

#### **Option 3: Single File**

```batch
compiler.exe tests\test1_simple.txt

# Generates:
#   - ast.out
#   - symboltable.out
#   - semantic_errors.out
```

### Test Cases Overview

| Test      | Description                          | Expected Result |
| --------- | ------------------------------------ | --------------- |
| **test1** | Simple function with local variables | ✅ No errors    |
| **test2** | Multiple variable types              | ✅ No errors    |
| **test3** | Arithmetic expressions               | ✅ No errors    |
| **test4** | Class with methods                   | ✅ No errors    |
| **test5** | Duplicate declarations               | ❌ 4 errors     |
| **test6** | Undeclared variables                 | ❌ 2 errors     |
| **test7** | Type mismatches                      | ⚠️ 1 warning    |
| **test8** | Complex program with arrays          | ✅ No errors    |

---

## 🔍 Semantic Analysis Features

### 1. Symbol Table Management

**Hierarchical Scope Structure:**

```
Global Scope
├── class Matrix
│   ├── attribute data : integer[10][10]
│   ├── attribute rows : integer
│   └── method init(r: integer)
│       ├── parameter r : integer
│       └── local i : integer
│
└── function main() : integer
    └── local m : Matrix
```

**Symbol Lookup Algorithm:**

```c
Symbol* lookup_symbol_recursive(SymbolTable* table, const char* name) {
    // 1. Check current scope
    Symbol* sym = lookup_in_table(table, name);
    if (sym) return sym;

    // 2. Check parent scopes
    if (table->parent)
        return lookup_symbol_recursive(table->parent, name);

    // 3. Not found
    return NULL;
}
```

### 2. Type System

**Supported Types:**

- **Primitive Types:** `integer`, `float`, `void`
- **User-Defined Types:** Classes
- **Array Types:** Multi-dimensional arrays `integer[10][20]`

**Type Compatibility Rules:**

```c
// Integer ← Integer  ✅ OK
x : integer := 10;

// Float ← Float  ✅ OK
y : float := 3.14;

// Integer ← Float  ⚠️ WARNING (precision loss)
x : integer := 3.14;

// Float ← Integer  ⚠️ WARNING (implicit conversion)
y : float := 10;
```

### 3. Error Detection

**Compile-Time Errors:**

1. **Undeclared Identifier**

   ```
   x := 10;  // ERROR: 'x' not declared
   ```

2. **Duplicate Declaration**

   ```
   local x : integer;
   local x : float;  // ERROR: 'x' already declared
   ```

3. **Type Mismatch**

   ```
   x : integer := "hello";  // ERROR: type mismatch
   ```

4. **Invalid Function Call**

   ```
   result := undefinedFunc();  // ERROR: function not declared
   ```

5. **Array Dimension Mismatch**
   ```
   arr : integer[10];
   arr[10] := 5;  // ERROR: index out of bounds (if checked)
   ```

### 4. Scope Rules

**Variable Shadowing:**

```c
local x : integer;  // Global x

func test() => void {
    local x : float;  // Shadows global x
    x := 3.14;        // Refers to local x
}
```

**Class Member Access:**

```c
class Point {
    private attribute x : integer;

    public func getX() => integer {
        return (x);     // ✅ OK: access private member
    }
}

func main() => integer {
    local p : Point;
    return (p.x);       // ❌ ERROR: private member
}
```

---

## 📊 Output Files

### 1. Abstract Syntax Tree (ast.out)

**Example Output:**

```
PROGRAM (program) [line: 1]
  LIST (list) [line: 3]
    FUNC_DEF (funcDef) [line: 3]
      FUNC_DEF (funcHead) [line: 3]
        ID (main) [line: 3]
        TYPE (integer) [line: 3]
      LIST (funcBody) [line: 3]
        LIST (stmts) [line: 4]
          VAR_DECL (varDecl) [line: 4]
            ID (x) [line: 4]
            TYPE (integer) [line: 4]
          LIST (stmts) [line: 5]
            ASSIGN (:=) [line: 5]
              VARIABLE (var) [line: 5]
                ID (x) [line: 5]
              INTLIT (10) [line: 5]
          LIST (stmts) [line: 6]
            RETURN (return) [line: 6]
              VARIABLE (var) [line: 6]
                ID (x) [line: 6]
```

**Tree Visualization:**

```
PROG
└── FUNC_DEF (main)
    ├── RETURN_TYPE (integer)
    └── FUNC_BODY
        ├── VAR_DECL (x: integer)
        ├── ASSIGN
        │   ├── VAR (x)
        │   └── INTLIT (10)
        └── RETURN
            └── VAR (x)
```

### 2. Symbol Table (symboltable.out)

**Example Output:**

```
================================================================================
                        SYMBOL TABLE REPORT
================================================================================

========================================
SCOPE: global (Level 0)
========================================

Name        Kind      Type      Visibility  Line  Details
----------------------------------------------------------------
Matrix      class     Matrix    -           3
init        function  void      -           11    params: (r:integer)
main        function  integer   -           23    params: ()

========================================
SCOPE: Matrix (Level 1)
========================================

Name        Kind      Type            Visibility  Line  Details
----------------------------------------------------------------
data        variable  integer[10][10] private     4
rows        variable  integer         private     5
init        function  void            public      7

========================================
SCOPE: init (Level 2) [parent: Matrix]
========================================

Name        Kind      Type      Visibility  Line  Details
----------------------------------------------------------------
r           parameter integer   -           11
i           variable  integer   -           12
```

### 3. Semantic Errors (semantic_errors.out)

**Example Output:**

```
================================================================================
                        SEMANTIC ERROR REPORT
================================================================================

Total Errors: 2
Total Warnings: 1

[ERROR] Line 15, Column 5: Undeclared variable 'y'
[ERROR] Line 18, Column 5: Duplicate declaration of variable 'x'
[WARNING] Line 22, Column 9: Type mismatch in assignment: float to integer
```

---

## ⚠️ Error Reporting

### Error Categories

#### **Errors (Compilation Fails)**

- Undeclared identifier
- Duplicate declaration
- Type incompatibility
- Invalid function call
- Scope violation

#### **Warnings (Compilation Succeeds)**

- Implicit type conversion
- Unused variable
- Unreachable code (if implemented)

### Error Message Format

```
[ERROR/WARNING] Line <N>, Column <M>: <Description>

Example:
[ERROR] Line 15, Column 5: Undeclared variable 'count'
```

### Error Recovery

The compiler continues after finding errors to report multiple issues in one pass.

---

## 💡 Examples

### Example 1: Valid Program

**Input (test1_simple.txt):**

```c
func main() => integer {
    local x : integer;
    local y : integer;
    x := 10;
    y := 20;
    return (x);
}
```

**Output:**

```
=== Parse completed successfully! ===
AST written to ast.out

=== Phase 1: Symbol Table Generation ===
=== Phase 2: Type Checking ===

Total Errors: 0
Total Warnings: 0

No semantic errors or warnings found.
```

### Example 2: Undeclared Variable Error

**Input (test6_errors_undeclared.txt):**

```c
func testUndeclared() => void {
    local x : integer;

    x := 10;
    y := 20;  // ERROR: y not declared
}
```

**Output:**

```
Total Errors: 1
Total Warnings: 0

[ERROR] Line 5, Column 5: Undeclared variable 'y'
```

### Example 3: Type Mismatch Warning

**Input (test7_type_mismatch.txt):**

```c
func testTypes() => void {
    local x : integer;
    local y : float;

    x := 10;
    y := 3.14;
    x := y;  // WARNING: float to integer
}
```

**Output:**

```
Total Errors: 0
Total Warnings: 1

[WARNING] Line 7, Column 5: Type mismatch: cannot assign float to integer
```

### Example 4: Class with Scoping

**Input (test4_class.txt):**

```c
class Point {
    public attribute x : integer;
    public attribute y : integer;

    public func getX() => integer;
};

implement Point {
    func getX() => integer {
        return (x);  // ✅ Access to class member
    }
}
```

**Symbol Table Output:**

```
SCOPE: global
  Point (class)

SCOPE: Point
  x (attribute, integer, public)
  y (attribute, integer, public)
  getX (function, integer, public)

SCOPE: getX [parent: Point]
  (no local symbols)
```

---

# TMA3 – Compiler Front-End up to Semantic Analysis

## 1. Scope of TMA3

TMA3 extends the TMA2 parser by:

- Reusing / importing lexer.l and parser.y from TMA2 (then enhanced here).
- Adding an Abstract Syntax Tree (AST) builder.
- Building hierarchical Symbol Tables.
- Performing Semantic Analysis (declarations, scope, types, basic validation).
- Producing compiler front-end outputs (ast.out, symboltable.out, semantic_errors.out).

No code generation yet (reserved for later stages).

## 2. Flow Overview

```
 SOURCE (.txt)
    │
    ├─(Flex)──> Tokens (lex.yy.c)
    │
    ├─(Bison)─> parse tree + semantic actions (parser.tab.c)
    │
    ├─ AST construction (ast.c)
    │
    ├─ Symbol table population (symboltable.c / semantic.c pass 1)
    │
    ├─ Semantic checks (semantic.c pass 2)
    │
    └─ Output:
        • ast.out
        • symboltable.out
        • semantic_errors.out
```

## 3. Imported From TMA2

- lexer.l (token rules, line/column tracking)
- parser.y (grammar rules)
  These were copied/merged, then extended with AST node creation and semantic integration hooks.

## 4. Build Environment (Windows)

Prerequisites (installed or available in PATH):

- win_flex / win_bison
- gcc (MinGW)

Directory:
`c:\Users\Safran\Desktop\Final Year\EEX6363_Compiler Construction\TMAs\DesignProject\TMA3`

## 5. Build Steps

From TMA3 folder:

```
cd TMA3
build.bat
```

build.bat performs:

1. Cleans previous artifacts.
2. Runs win_bison → parser.tab.c / parser.tab.h.
3. Runs win_flex → lex.yy.c.
4. Compiles: ast.c, symboltable.c, semantic.c, parser.tab.c, lex.yy.c.
5. Links → compiler.exe.

## 6. Running Tests

After successful build:

```
compiler.exe tests\test1_simple.txt
compiler.exe tests\test2_variables.txt
compiler.exe tests\test3_arithmetic.txt
compiler.exe tests\test4_class.txt
compiler.exe tests\test5_errors_duplicate.txt
compiler.exe tests\test6_errors_undeclared.txt
compiler.exe tests\test7_type_mismatch.txt
compiler.exe tests\test8_complex.txt
```

Each run generates (overwrites):

- ast.out
- symboltable.out
- semantic_errors.out

## 7. Phase Details

### 7.1 Lexical Analysis (lexer.l)

- Recognizes keywords (class, func, integer, float, etc.)
- Distinguishes IDENTIFIER, CONSTANT (INTLIT / FLOATLIT), DELIMITER tokens.
- Tracks line / column for precise error attribution.
- Creates token structs with category and lexeme.

### 7.2 Syntax Analysis (parser.y)

- Bison grammar for:
  - Classes, inheritance, implementations.
  - Function declarations & definitions.
  - Variable / attribute / parameter declarations.
  - Statements: assignment, if-then-else, while, read, write, return, calls.
  - Expressions (logical, relational, arithmetic, unary).
  - Qualified access & array indexing.
- Semantic actions construct AST nodes (create_node + add_child).

### 7.3 AST (ast.c / ast.h)

- Generic node type with:
  - NodeType enum (PROGRAM, FUNC_DEF, VAR_DECL, ASSIGN, IF, WHILE, etc.).
  - Children vector (dynamic expansion).
  - Source position (line/column).
- Printed hierarchically to ast.out for inspection.

### 7.4 Symbol Tables (symboltable.c/.h)

- Global scope + nested scopes (classes, functions).
- Each symbol entry: name, kind (class/function/variable/parameter), type string, visibility, declaration line.
- Lookup uses current scope then climbs to parents.

### 7.5 Semantic Analysis (semantic.c/.h)

Two passes:

1. Pass 1 – Declaration collection:
   - Registers classes, attributes, methods, local variables, parameters.
   - Detects duplicate declarations in same scope.
2. Pass 2 – Usage validation:
   - Undeclared variable usage.
   - Type assignments (basic integer vs float mismatch).
   - Return type consistency in non-void functions.
   - Member access validity (basic check).
     Produces error + warning counts → semantic_errors.out.

### 7.6 Error File (semantic_errors.out)

Format:

```
================================================================================
SEMANTIC ERROR REPORT
================================================================================
Total Errors: N
Total Warnings: M
[ERROR] Line X, Column Y: Message
[WARNING] Line A, Column B: Message
```

## 8. Output Files

| File                | Purpose                            |
| ------------------- | ---------------------------------- |
| ast.out             | Hierarchical AST dump              |
| symboltable.out     | All scopes with their symbols      |
| semantic_errors.out | Collected semantic errors/warnings |

## 9. Test Expectations

| Test                    | Purpose                      | Expected  |
| ----------------------- | ---------------------------- | --------- |
| test1_simple            | Basic function               | No errors |
| test2_variables         | Mixed types                  | No errors |
| test3_arithmetic        | Expression precedence        | No errors |
| test4_class             | Class + implement            | No errors |
| test5_errors_duplicate  | Duplicate locals             | Errors    |
| test6_errors_undeclared | Missing variable usage       | Errors    |
| test7_type_mismatch     | Assign float→integer         | Warning   |
| test8_complex           | Arrays + loop + class method | No errors |

## 10. Troubleshooting

| Issue                                  | Action                                               |
| -------------------------------------- | ---------------------------------------------------- |
| build.bat fails (Bison/Flex not found) | Confirm win_flex.exe / win_bison.exe paths in script |
| compiler.exe missing                   | Re-run build.bat                                     |
| semantic_errors.out empty              | No semantic issues found                             |
| All symbols appear only in global      | Check AST construction / scope entry logic           |
| Line numbers off                       | Ensure lexer updates line/column for every lexeme    |

## 11. Extensibility Points

- Add richer type system (arrays dimension semantics).
- Add inheritance-based symbol merging.
- Add function overloading resolution.
- Add constant folding / simple optimizations in expressions.
- Prepare for IR code generation (next assignment).

## 12. Minimal Internal Data Flow Example

Source snippet:

```
func main() => integer {
    local x : integer;
    x := 10;
    return (x);
}
```

1. Tokens: FUNC ID(main) LPAREN RPAREN ARROW INTEGER_TYPE LBRACE LOCAL ID(x) COLON INTEGER_TYPE SEMI ID(x) ASSIGN INTLIT(10) SEMI RETURN LPAREN ID(x) RPAREN SEMI RBRACE
2. Parser builds AST nodes (FUNC_DEF → VAR_DECL → ASSIGN → RETURN).
3. Symbol table:
   - global: main (function)
   - main: x (local variable)
4. Semantic pass:
   - Declaration ok
   - Assignment type matches
   - Return type matches function signature
5. Output: zero errors.

## 13. Command Recap

```
cd TMA3
build.bat
compiler.exe tests\test1_simple.txt
compiler.exe tests\test2_variables.txt
compiler.exe tests\test3_arithmetic.txt
compiler.exe tests\test4_class.txt
compiler.exe tests\test5_errors_duplicate.txt
compiler.exe tests\test6_errors_undeclared.txt
compiler.exe tests\test7_type_mismatch.txt
compiler.exe tests\test8_complex.txt
```

## 14. Cleanup

Use cleanup.bat to remove generated artifacts safely (choose mode).

## 15. Summary

TMA3 delivers a functioning front-end up to semantic integrity checking. The next phase can build on these stable artifacts for intermediate representation and code generation.

---

**Last Updated:** 2024
**Version:** 1.0
**Author:** Student (EEX6363 Course)
