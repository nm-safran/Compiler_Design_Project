@echo off
REM filepath: c:\Users\Safran\Desktop\Final Year\EEX6363_Compiler Construction\TMAs\DesignProject\TMA3\cleanup.bat

echo ===============================================
echo    TMA3 - File Cleanup Utility
echo ===============================================
echo.

echo === ESSENTIAL FILES (DO NOT DELETE) ===
echo.
echo Source Files:
echo   - ast.h
echo   - ast.c
echo   - symboltable.h
echo   - symboltable.c
echo   - semantic.h
echo   - semantic.c
echo   - parser.y
echo   - lexer.l
echo.
echo Build Scripts:
echo   - build.bat
echo   - setup_windows.bat
echo   - run_tests.bat
echo   - run_all_tests.bat
echo   - view_results.bat
echo   - cleanup.bat (this file)
echo.
echo Documentation:
echo   - README_WINDOWS.md
echo   - Any TMA documentation files
echo.
echo Test Files:
echo   - tests\ directory and all .txt files inside
echo.

echo.
echo === TEMPORARY/GENERATED FILES (SAFE TO DELETE) ===
echo.

set TEMP_COUNT=0

echo Generated Parser/Lexer Files:
if exist "lex.yy.c" (
    echo   [X] lex.yy.c
    set /a TEMP_COUNT+=1
)
if exist "parser.tab.c" (
    echo   [X] parser.tab.c
    set /a TEMP_COUNT+=1
)
if exist "parser.tab.h" (
    echo   [X] parser.tab.h
    set /a TEMP_COUNT+=1
)

echo.
echo Object Files:
for %%f in (*.o) do (
    echo   [X] %%f
    set /a TEMP_COUNT+=1
)

echo.
echo Compiled Executable:
if exist "compiler.exe" (
    echo   [X] compiler.exe
    set /a TEMP_COUNT+=1
)

echo.
echo Output Files (latest run):
if exist "ast.out" (
    echo   [X] ast.out
    set /a TEMP_COUNT+=1
)
if exist "symboltable.out" (
    echo   [X] symboltable.out
    set /a TEMP_COUNT+=1
)
if exist "semantic_errors.out" (
    echo   [X] semantic_errors.out
    set /a TEMP_COUNT+=1
)
if exist "semantic_errors.txt" (
    echo   [X] semantic_errors.txt
    set /a TEMP_COUNT+=1
)

echo.
echo Test Results:
if exist "test_results\" (
    echo   [X] test_results\ directory and contents
    set /a TEMP_COUNT+=1
)

echo.
echo === POTENTIALLY UNWANTED FILES ===
echo.

set UNWANTED_COUNT=0

echo Old/Backup Files:
for %%f in (*.bak *.old *.tmp *~) do (
    echo   [X] %%f
    set /a UNWANTED_COUNT+=1
)

echo.
echo Sample Test Files (if you have your own):
if exist "test1_simple.txt" (
    echo   [?] test1_simple.txt (keep if needed)
    set /a UNWANTED_COUNT+=1
)
if exist "test2_errors.txt" (
    echo   [?] test2_errors.txt (keep if needed)
    set /a UNWANTED_COUNT+=1
)
if exist "test3_arrays.txt" (
    echo   [?] test3_arrays.txt (keep if needed)
    set /a UNWANTED_COUNT+=1
)

echo.
echo Original lexer (if copied):
if exist "lexer_original.l" (
    echo   [?] lexer_original.l (backup from TMA2)
    set /a UNWANTED_COUNT+=1
)

echo.
echo ===============================================
echo    Summary
echo ===============================================
echo Temporary files: %TEMP_COUNT%
echo Potentially unwanted: %UNWANTED_COUNT%
echo.

echo.
echo What would you like to do?
echo [1] Delete all temporary files (safe - can rebuild)
echo [2] Delete temporary + keep compiler.exe
echo [3] Clean everything (full rebuild needed)
echo [4] Delete specific files (manual selection)
echo [5] Show detailed file list
echo [6] Exit without deleting
echo.
set /p CHOICE="Enter choice (1-6): "

if "%CHOICE%"=="1" goto DELETE_TEMP
if "%CHOICE%"=="2" goto DELETE_KEEP_EXE
if "%CHOICE%"=="3" goto DELETE_ALL
if "%CHOICE%"=="4" goto DELETE_MANUAL
if "%CHOICE%"=="5" goto SHOW_DETAILS
if "%CHOICE%"=="6" goto EXIT

echo Invalid choice!
pause
goto EXIT

:DELETE_TEMP
echo.
echo Deleting temporary files...
del /Q lex.yy.c parser.tab.c parser.tab.h *.o 2>nul
del /Q ast.out symboltable.out semantic_errors.out semantic_errors.txt 2>nul
if exist test_results\ (
    rmdir /S /Q test_results
)
echo Done! Compiler executable kept.
echo Run build.bat to regenerate parser/lexer files.
pause
goto EXIT

:DELETE_KEEP_EXE
echo.
echo Deleting temporary files (keeping compiler.exe)...
del /Q lex.yy.c parser.tab.c parser.tab.h *.o 2>nul
del /Q ast.out symboltable.out semantic_errors.out semantic_errors.txt 2>nul
if exist test_results\ (
    rmdir /S /Q test_results
)
echo Done! You can still run tests without rebuilding.
pause
goto EXIT

:DELETE_ALL
echo.
echo WARNING: This will delete ALL generated files!
echo You will need to run build.bat before testing.
echo.
set /p CONFIRM="Are you sure? (yes/no): "
if /i not "%CONFIRM%"=="yes" (
    echo Cancelled.
    pause
    goto EXIT
)
echo.
echo Deleting all generated files...
del /Q lex.yy.c parser.tab.c parser.tab.h *.o compiler.exe 2>nul
del /Q ast.out symboltable.out semantic_errors.out semantic_errors.txt 2>nul
if exist test_results\ (
    rmdir /S /Q test_results
)
del /Q *.bak *.old *.tmp 2>nul
echo Done! Run build.bat to rebuild everything.
pause
goto EXIT

:DELETE_MANUAL
echo.
echo Manual file deletion:
echo.
echo Delete lex.yy.c? (y/n)
set /p DEL1=
if /i "%DEL1%"=="y" del lex.yy.c 2>nul

echo Delete parser.tab.c and parser.tab.h? (y/n)
set /p DEL2=
if /i "%DEL2%"=="y" (
    del parser.tab.c parser.tab.h 2>nul
)

echo Delete all .o files? (y/n)
set /p DEL3=
if /i "%DEL3%"=="y" del *.o 2>nul

echo Delete compiler.exe? (y/n)
set /p DEL4=
if /i "%DEL4%"=="y" del compiler.exe 2>nul

echo Delete output files (ast.out, symboltable.out, etc.)? (y/n)
set /p DEL5=
if /i "%DEL5%"=="y" (
    del ast.out symboltable.out semantic_errors.out semantic_errors.txt 2>nul
)

echo Delete test_results directory? (y/n)
set /p DEL6=
if /i "%DEL6%"=="y" (
    if exist test_results\ rmdir /S /Q test_results
)

echo.
echo Manual cleanup complete!
pause
goto EXIT

:SHOW_DETAILS
echo.
echo ===============================================
echo    Detailed File Listing
echo ===============================================
echo.

echo === Current Directory Contents ===
dir /B

echo.
echo === File Sizes ===
dir *.c *.h *.y *.l *.bat *.exe *.out 2>nul

echo.
pause
goto EXIT

:EXIT
echo.
echo Cleanup utility finished.
