@echo off
REM filepath: c:\Users\Safran\Desktop\Final Year\EEX6363_Compiler Construction\TMAs\DesignProject\TMA3\test_individual.bat

echo ===============================================
echo    Testing Individual Files
echo ===============================================

if not exist compiler.exe (
    echo ERROR: compiler.exe not found!
    echo Please run build.bat first.
    pause
    exit /b 1
)

:MENU
echo.
echo Select a test to run:
echo [1] test1_simple.txt - Simple function
echo [2] test2_variables.txt - Multiple variables
echo [3] test3_arithmetic.txt - Arithmetic expressions
echo [4] test4_class.txt - Class declaration
echo [5] test5_errors_duplicate.txt - Duplicate errors
echo [6] test6_errors_undeclared.txt - Undeclared errors
echo [7] test7_type_mismatch.txt - Type mismatch
echo [8] test8_complex.txt - Complex program
echo [A] Run ALL tests
echo [Q] Quit
echo.
set /p CHOICE="Enter your choice: "

if /i "%CHOICE%"=="1" goto TEST1
if /i "%CHOICE%"=="2" goto TEST2
if /i "%CHOICE%"=="3" goto TEST3
if /i "%CHOICE%"=="4" goto TEST4
if /i "%CHOICE%"=="5" goto TEST5
if /i "%CHOICE%"=="6" goto TEST6
if /i "%CHOICE%"=="7" goto TEST7
if /i "%CHOICE%"=="8" goto TEST8
if /i "%CHOICE%"=="A" goto ALL
if /i "%CHOICE%"=="Q" goto END

echo Invalid choice!
goto MENU

:TEST1
echo.
echo === Test 1: Simple Function ===
compiler.exe tests\test1_simple.txt
goto SHOW_OUTPUT

:TEST2
echo.
echo === Test 2: Multiple Variables ===
compiler.exe tests\test2_variables.txt
goto SHOW_OUTPUT

:TEST3
echo.
echo === Test 3: Arithmetic Expressions ===
compiler.exe tests\test3_arithmetic.txt
goto SHOW_OUTPUT

:TEST4
echo.
echo === Test 4: Class Declaration ===
compiler.exe tests\test4_class.txt
goto SHOW_OUTPUT

:TEST5
echo.
echo === Test 5: Duplicate Errors ===
compiler.exe tests\test5_errors_duplicate.txt
goto SHOW_OUTPUT

:TEST6
echo.
echo === Test 6: Undeclared Errors ===
compiler.exe tests\test6_errors_undeclared.txt
goto SHOW_OUTPUT

:TEST7
echo.
echo === Test 7: Type Mismatch ===
compiler.exe tests\test7_type_mismatch.txt
goto SHOW_OUTPUT

:TEST8
echo.
echo === Test 8: Complex Program ===
compiler.exe tests\test8_complex.txt
goto SHOW_OUTPUT

:ALL
echo.
echo Running all tests...
echo.

for %%t in (1 2 3 4 5 6 7 8) do (
    echo.
    echo ========================================
    echo Test %%t
    echo ========================================
    compiler.exe tests\test%%t_*.txt
    echo.
    pause
)
goto MENU

:SHOW_OUTPUT
echo.
echo Generated files:
if exist ast.out (
    echo   ✓ ast.out
) else (
    echo   ✗ ast.out not generated
)
if exist symboltable.out (
    echo   ✓ symboltable.out
) else (
    echo   ✗ symboltable.out not generated
)
if exist semantic_errors.out (
    echo   ✓ semantic_errors.out
    echo.
    echo === Semantic Errors Summary ===
    type semantic_errors.out | findstr /C:"Total Errors:" /C:"Total Warnings:"
) else (
    echo   ✗ semantic_errors.out not generated
)
echo.
set /p VIEW="View detailed results? (y/n): "
if /i "%VIEW%"=="y" (
    echo.
    echo === Symbol Table ===
    type symboltable.out 2>nul
    echo.
    echo === Semantic Errors ===
    type semantic_errors.out 2>nul
)
echo.
pause
goto MENU

:END
echo.
echo Goodbye!
