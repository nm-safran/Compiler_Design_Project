@echo off
REM filepath: c:\Users\Safran\Desktop\Final Year\EEX6363_Compiler Construction\TMAs\DesignProject\TMA3\list_files.bat

echo ===============================================
echo    TMA3 Directory Contents
echo ===============================================
echo.

echo === SOURCE FILES (Keep) ===
echo.
dir /B ast.h ast.c symboltable.h symboltable.c semantic.h semantic.c parser.y lexer.l 2>nul
echo.

echo === BUILD SCRIPTS (Keep) ===
echo.
dir /B *.bat 2>nul
echo.

echo === GENERATED FILES (Can Delete) ===
echo.
dir /B lex.yy.c parser.tab.c parser.tab.h *.o compiler.exe 2>nul
echo.

echo === OUTPUT FILES (Can Delete) ===
echo.
dir /B *.out *.txt 2>nul
echo.

echo === TEST FILES ===
echo.
if exist tests\ (
    echo tests\ directory:
    dir /B tests\*.txt 2>nul
) else (
    echo No tests\ directory found
)
echo.

echo === ALL FILES ===
echo.
dir /B
echo.

echo === DISK USAGE ===
echo.
dir *.c *.h *.exe *.o 2>nul | find "File(s)"

pause
