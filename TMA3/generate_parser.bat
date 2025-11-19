@echo off
REM filepath: c:\Users\Safran\Desktop\Final Year\EEX6363_Compiler Construction\TMAs\DesignProject\TMA3\generate_parser.bat

echo ===============================================
echo    Generating Parser Files from TMA2
echo ===============================================

set TMA2_PATH=..\TMA2\TMA2Qc^&Qe

if not exist "%TMA2_PATH%" (
    echo ERROR: TMA2 directory not found!
    echo Expected path: %TMA2_PATH%
    pause
    exit /b 1
)

echo.
echo Copying lexer.l from TMA2...
if exist "%TMA2_PATH%\lexer.l" (
    copy "%TMA2_PATH%\lexer.l" lexer.l
    echo [OK] lexer.l copied
) else (
    echo [ERROR] lexer.l not found in TMA2
)

echo.
echo You now need to:
echo 1. Install Flex/Bison (see README_WINDOWS.md)
echo 2. Run: flex -o lex.yy.c lexer.l
echo 3. Run: bison -d parser.y
echo 4. Run: build.bat
echo.
echo OR use online Flex/Bison compiler:
echo - Upload lexer.l and parser.y to https://www.jdoodle.com/
echo - Download generated lex.yy.c and parser.tab.c/h
echo.
pause
