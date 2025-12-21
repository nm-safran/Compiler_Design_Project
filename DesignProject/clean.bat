@echo off
REM Cleanup script for compiler project
REM Run this before building to start fresh

echo ================================================================================
echo                    CLEANING COMPILER PROJECT
echo ================================================================================

echo.
echo [1/5] Removing object files...
if exist *.o del /Q *.o

echo [2/5] Removing generated parser and lexer files...
if exist lex.yy.c del /Q lex.yy.c
if exist parser.tab.c del /Q parser.tab.c
if exist parser.tab.h del /Q parser.tab.h

echo [3/5] Removing compiler executable...
if exist compiler.exe del /Q compiler.exe

echo [4/5] Removing intermediate output files...
if exist output.s del /Q output.s
if exist ast.out del /Q ast.out
if exist ast_*.out del /Q ast_*.out
if exist symboltable.out del /Q symboltable.out
if exist semantic_errors.out del /Q semantic_errors.out
if exist semantic_errors_*.txt del /Q semantic_errors_*.txt
if exist symboltable_*.out del /Q symboltable_*.out
if exist tokens_*.txt del /Q tokens_*.txt

echo [5/5] Removing test result files...
if exist test_results\*.s del /Q test_results\*.s
if exist test_results\*.log del /Q test_results\*.log

echo.
echo ================================================================================
echo                    CLEANUP COMPLETE
echo ================================================================================
echo.
echo Ready to build fresh. Run: build.bat
echo.
