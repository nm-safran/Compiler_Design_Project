@echo off
REM ================================================================================
REM Build script for Custom Language Compiler
REM ================================================================================

echo.
echo ================================================================================
echo                     BUILDING CUSTOM LANGUAGE COMPILER
echo ================================================================================
echo.

REM Set paths for flex and bison
set FLEX=C:\Tools\winflexbison\win_flex.exe
set BISON=C:\Tools\winflexbison\win_bison.exe

REM Check if flex exists
if not exist "%FLEX%" (
    echo [ERROR] win_flex.exe not found at %FLEX%
    echo Please install winflexbison or update the path in build.bat
    exit /b 1
)

REM Check if bison exists
if not exist "%BISON%" (
    echo [ERROR] win_bison.exe not found at %BISON%
    echo Please install winflexbison or update the path in build.bat
    exit /b 1
)

REM Clean previous builds
echo [CLEAN] Removing old generated files...
if exist lex.yy.c del lex.yy.c
if exist parser.tab.c del parser.tab.c
if exist parser.tab.h del parser.tab.h
if exist y.tab.c del y.tab.c
if exist y.tab.h del y.tab.h
if exist *.o del *.o
if exist compiler.exe del compiler.exe
echo.

REM ========================================================================
REM STEP 1: Generate Parser
REM ========================================================================
echo [STEP 1] Generating parser from parser.y...
"%BISON%" -d parser.y -o parser.tab.c

if errorlevel 1 (
    echo [ERROR] Parser generation failed!
    exit /b 1
)

if not exist parser.tab.c (
    echo [ERROR] parser.tab.c not generated!
    exit /b 1
)

if not exist parser.tab.h (
    echo [ERROR] parser.tab.h not generated!
    exit /b 1
)

echo [PASS] Parser generated successfully
echo.

REM ========================================================================
REM STEP 2: Generate Lexer
REM ========================================================================
echo [STEP 2] Generating lexer from lexer.l...
"%FLEX%" -o lex.yy.c lexer.l

if errorlevel 1 (
    echo [ERROR] Lexer generation failed!
    exit /b 1
)

if not exist lex.yy.c (
    echo [ERROR] lex.yy.c not generated!
    exit /b 1
)

echo [PASS] Lexer generated successfully
echo.

REM ========================================================================
REM STEP 3: Compile All Modules
REM ========================================================================
echo [STEP 3] Compiling all modules...

echo   [3.1] Compiling parser.tab.c...
gcc -c parser.tab.c -o parser.tab.o
if errorlevel 1 (
    echo [ERROR] Failed to compile parser.tab.c
    exit /b 1
)

echo   [3.2] Compiling lex.yy.c...
gcc -c lex.yy.c -o lex.yy.o
if errorlevel 1 (
    echo [ERROR] Failed to compile lex.yy.c
    exit /b 1
)

echo   [3.3] Compiling ast.c...
gcc -c ast.c -o ast.o
if errorlevel 1 (
    echo [ERROR] Failed to compile ast.c
    exit /b 1
)

echo   [3.4] Compiling symboltable.c...
gcc -c symboltable.c -o symboltable.o
if errorlevel 1 (
    echo [ERROR] Failed to compile symboltable.c
    exit /b 1
)

echo   [3.5] Compiling semantic.c...
gcc -c semantic.c -o semantic.o
if errorlevel 1 (
    echo [ERROR] Failed to compile semantic.c
    exit /b 1
)

echo   [3.6] Compiling codegen.c...
gcc -c codegen.c -o codegen.o
if errorlevel 1 (
    echo [ERROR] Failed to compile codegen.c
    exit /b 1
)

echo   [3.7] Compiling main.c...
gcc -c main.c -o main.o
if errorlevel 1 (
    echo [ERROR] Failed to compile main.c
    exit /b 1
)

echo [PASS] All modules compiled successfully
echo.

REM ========================================================================
REM STEP 4: Link Executable
REM ========================================================================
echo [STEP 4] Linking compiler executable...
gcc -o compiler.exe parser.tab.o lex.yy.o ast.o symboltable.o semantic.o codegen.o main.o

if errorlevel 1 (
    echo [ERROR] Linking failed!
    exit /b 1
)

if not exist compiler.exe (
    echo [ERROR] compiler.exe not created!
    exit /b 1
)

echo [PASS] Executable linked successfully
echo.

REM ========================================================================
REM SUCCESS
REM ========================================================================
echo ================================================================================
echo                     BUILD COMPLETED SUCCESSFULLY
echo ================================================================================
echo.
echo Generated files:
echo   - compiler.exe (main executable)
echo   - parser.tab.c, parser.tab.h (parser)
echo   - lex.yy.c (lexer)
echo   - *.o (object files)
echo.
echo Usage:
echo   compiler.exe input.txt -o output.s
echo   compiler.exe input.txt -all -o output.s
echo.
echo Options:
echo   -o ^<file^>    Specify output assembly file
echo   -ast         Generate AST output
echo   -sym         Generate symbol table output
echo   -sem         Generate semantic errors output
echo   -all         Generate all intermediate outputs
echo ================================================================================
echo.
