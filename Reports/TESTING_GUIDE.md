# Quick Testing Guide

## Fresh Build Process

### Step 1: Clean Everything

```cmd
clean.bat
```

This removes:

- Object files (\*.o)
- Generated lexer/parser (lex.yy.c, parser.tab.c/h)
- Compiler executable (compiler.exe)
- Old output files (output.s, ast.out, etc.)
- Test result files (test_results/\*.s)

### Step 2: Build Compiler

```cmd
build.bat
```

This compiles everything fresh.

### Step 3: Test Individual Files

```cmd
compiler.exe tests\test1_simple.txt
compiler.exe tests\test2_variables.txt
compiler.exe tests\test3_arithmetic.txt
```

### Step 4: Check Results

Assembly files are now in `test_results/` folder:

```cmd
dir test_results\*.s
type test_results\test1_simple.s
```

## What Changed

### 1. Assembly Output Location

- **Before:** `output.s` (overwrites each time)
- **After:** `test_results/test1_simple.s`, `test_results/test2_variables.s`, etc.

### 2. Automatic Naming

The compiler now automatically names output files based on input:

- `tests/test1_simple.txt` → `test_results/test1_simple.s`
- `tests/test5_errors_duplicate.txt` → `test_results/test5_errors_duplicate.s`

### 3. Clean Script

Run `clean.bat` before building to remove all generated files for a fresh start.

## Testing Workflow

```cmd
REM Clean and rebuild
clean.bat
build.bat

REM Test all files
compiler.exe tests\test1_simple.txt
compiler.exe tests\test2_variables.txt
compiler.exe tests\test3_arithmetic.txt
compiler.exe tests\test4_class.txt
compiler.exe tests\test5_errors_duplicate.txt
compiler.exe tests\test6_errors_undeclared.txt
compiler.exe tests\test7_type_mismatch.txt
compiler.exe tests\test8_complex.txt

REM View results
dir test_results\*.s
```

## Expected Results

✅ **Should Generate .s Files:**

- test1_simple.s
- test2_variables.s (after fixing syntax)
- test3_arithmetic.s

❌ **Should NOT Generate .s (Intentional Errors):**

- test5_errors_duplicate.txt → Reports duplicate declaration error
- test6_errors_undeclared.txt → Reports undeclared variable error
- test7_type_mismatch.txt → Reports type mismatch error

⚠️ **May Have Issues (Need Fixes):**

- test4_class.txt → Class member scope issues
- test8_complex.txt → Array/complex structure issues
