@echo off
REM filepath: c:\Users\Safran\Desktop\Final Year\EEX6363_Compiler Construction\TMAs\DesignProject\TMA3\build.bat

echo ===============================================
echo    TMA3 - Semantic Analyzer Build Script
===============================================

REM Set winflexbison path
set FLEX=C:\Tools\winflexbison\win_flex.exe
set BISON=C:\Tools\winflexbison\win_bison.exe

REM Check if winflexbison exists
if not exist "%FLEX%" (
    echo ERROR: win_flex.exe not found at %FLEX%
    echo Please check your winflexbison installation path
    pause
    exit /b 1
)

if not exist "%BISON%" (
    echo ERROR: win_bison.exe not found at %BISON%
    echo Please check your winflexbison installation path
    pause
    exit /b 1
)

echo.
echo Cleaning previous build files...
if exist lex.yy.c del lex.yy.c
if exist parser.tab.c del parser.tab.c
if exist parser.tab.h del parser.tab.h
if exist *.o del *.o
if exist compiler.exe del compiler.exe

echo.
echo Generating parser...
"%BISON%" -d parser.y
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Bison failed!
    pause
    exit /b 1
)
echo [OK] Parser generated

echo.
echo Generating lexer...
"%FLEX%" -o lex.yy.c lexer.l
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Flex failed!
    pause
    exit /b 1
)
echo [OK] Lexer generated

echo.
echo Compiling AST module...
gcc -c -Wall -g ast.c -o ast.o
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: AST compilation failed!
    pause
    exit /b 1
)
echo [OK] AST compiled

echo Compiling Symbol Table module...
gcc -c -Wall -g symboltable.c -o symboltable.o
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Symbol Table compilation failed!
    pause
    exit /b 1
)
echo [OK] Symbol Table compiled

echo Compiling Semantic Analyzer module...
gcc -c -Wall -g semantic.c -o semantic.o
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Semantic Analyzer compilation failed!
    pause
    exit /b 1
)
echo [OK] Semantic Analyzer compiled

echo Compiling parser...
gcc -c -Wall -g parser.tab.c -o parser.tab.o
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Parser compilation failed!
    pause
    exit /b 1
)
echo [OK] Parser compiled

echo Compiling lexer...
gcc -c -Wall -g -Wno-unused-function lex.yy.c -o lex.yy.o
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Lexer compilation failed!
    pause
    exit /b 1
)
echo [OK] Lexer compiled

echo.
echo Linking compiler...
gcc -o compiler.exe ast.o symboltable.o semantic.o parser.tab.o lex.yy.o
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: Linking failed!
    pause
    exit /b 1
)

echo.
echo ===============================================
echo    Build Successful!
echo ===============================================
echo.
echo Compiler executable: compiler.exe
echo.
echo Usage: compiler.exe input_file.txt
echo.
echo Output files will be generated:
echo   - ast.out (Abstract Syntax Tree)
echo   - symboltable.out (Symbol Table Report)
echo   - semantic_errors.out (Error Report)
echo.
pause
