@echo off
REM filepath: c:\Users\Safran\Desktop\Final Year\EEX6363_Compiler Construction\TMAs\DesignProject\TMA3\run_tests.bat

echo ===============================================
echo    Running All Test Cases
echo ===============================================

if not exist compiler.exe (
    echo ERROR: compiler.exe not found!
    echo Please run build.bat first.
    pause
    exit /b 1
)

echo.
echo === Test 1: Simple Program ===
echo Input file: test1_simple.txt
echo.
compiler.exe test1_simple.txt
echo.
echo Generated files:
if exist ast.out echo   - ast.out (AST)
if exist symboltable.out echo   - symboltable.out (Symbol Table)
if exist semantic_errors.out echo   - semantic_errors.out (Errors/Warnings)
echo.
pause

echo.
echo === Test 2: Semantic Errors ===
echo Input file: test2_errors.txt
echo.
compiler.exe test2_errors.txt
echo.
echo Generated files:
if exist ast.out echo   - ast.out (AST)
if exist symboltable.out echo   - symboltable.out (Symbol Table)
if exist semantic_errors.out echo   - semantic_errors.out (Errors/Warnings)
echo.
pause

echo.
echo === Test 3: Arrays and Complex Structures ===
echo Input file: test3_arrays.txt
echo.
compiler.exe test3_arrays.txt
echo.
echo Generated files:
if exist ast.out echo   - ast.out (AST)
if exist symboltable.out echo   - symboltable.out (Symbol Table)
if exist semantic_errors.out echo   - semantic_errors.out (Errors/Warnings)
echo.
pause

echo.
echo ===============================================
echo    All Tests Complete
echo ===============================================
echo.
echo You can view the output files:
echo   - ast.out
echo   - symboltable.out
echo   - semantic_errors.out
echo.
pause
