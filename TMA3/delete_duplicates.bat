@echo off
REM Delete duplicate and unwanted files from TMA3

echo ===============================================
echo    Deleting Duplicate Files
echo ===============================================
echo.

echo The following files will be DELETED:
echo.
echo === Duplicate Symbol Table Files ===
echo   - symbol_table.h
echo   - symbol_table.c
echo.
echo === Duplicate Semantic Analyzer Files ===
echo   - semantic_analyzer.h
echo   - semantic_analyzer.c
echo.
echo === Old Parser Files ===
echo   - parser_tma3.y
echo   - parser_tma3.tab.h
echo   - parser_tma3.tab.c (2MB+ file)
echo   - parser_tma3.output
echo.
echo === Old Build Files ===
echo   - Makefile
echo.
echo === Empty/Old Documentation ===
echo   - README.md (empty)
echo.
echo === Generated Output Files ===
echo   - output.log
echo   - derivation.out
echo.

set /p CONFIRM="Are you sure you want to delete these files? (yes/no): "

if /i not "%CONFIRM%"=="yes" (
    echo Cancelled. No files deleted.
    pause
    exit /b 0
)

echo.
echo Deleting files...

REM Delete duplicate symbol table files
if exist symbol_table.h (
    del symbol_table.h
    echo [X] Deleted symbol_table.h
)
if exist symbol_table.c (
    del symbol_table.c
    echo [X] Deleted symbol_table.c
)

REM Delete duplicate semantic analyzer files
if exist semantic_analyzer.h (
    del semantic_analyzer.h
    echo [X] Deleted semantic_analyzer.h
)
if exist semantic_analyzer.c (
    del semantic_analyzer.c
    echo [X] Deleted semantic_analyzer.c
)

REM Delete old parser files
if exist parser_tma3.y (
    del parser_tma3.y
    echo [X] Deleted parser_tma3.y
)
if exist parser_tma3.tab.h (
    del parser_tma3.tab.h
    echo [X] Deleted parser_tma3.tab.h
)
if exist parser_tma3.tab.c (
    del parser_tma3.tab.c
    echo [X] Deleted parser_tma3.tab.c (large file)
)
if exist parser_tma3.output (
    del parser_tma3.output
    echo [X] Deleted parser_tma3.output
)

REM Delete Makefile
if exist Makefile (
    del Makefile
    echo [X] Deleted Makefile
)

REM Delete empty README
if exist README.md (
    del README.md
    echo [X] Deleted README.md (empty)
)

REM Delete old output files
if exist output.log (
    del output.log
    echo [X] Deleted output.log
)
if exist derivation.out (
    del derivation.out
    echo [X] Deleted derivation.out
)

echo.
echo ===============================================
echo    Cleanup Complete!
echo ===============================================
echo.
echo Duplicate files have been removed.
echo.
echo Files you should KEEP:
echo   ✓ ast.h, ast.c
echo   ✓ symboltable.h, symboltable.c
echo   ✓ semantic.h, semantic.c
echo   ✓ parser.y, lexer.l
echo   ✓ build.bat, run_tests.bat
echo   ✓ tests\ directory
echo.
pause
