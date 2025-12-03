@echo off
REM ================================================================================
REM Automated Test Suite for Custom Language Compiler
REM ================================================================================

setlocal enabledelayedexpansion

echo.
echo ================================================================================
echo              CUSTOM LANGUAGE COMPILER - TEST SUITE
echo ================================================================================
echo.

REM Check if compiler exists
if not exist compiler.exe (
    echo [ERROR] compiler.exe not found!
    echo Please run build.bat first to build the compiler.
    exit /b 1
)

REM Create tests directory if it doesn't exist
if not exist tests mkdir tests

REM Copy test files from TMA3 if they don't exist here
if not exist tests\test1_simple.txt (
    echo [INFO] Copying test files from TMA3...
    xcopy /Y ..\TMA3\tests\*.txt tests\ >nul 2>&1
    if errorlevel 1 (
        echo [WARN] Could not copy test files from TMA3
        echo [INFO] Will proceed with existing tests
    )
)

REM Test statistics
set TOTAL=0
set PASSED=0
set FAILED=0

REM Create results directory
if not exist test_results mkdir test_results

echo [INFO] Running all tests...
echo.

REM ========================================================================
REM TEST 1: Simple Function
REM ========================================================================
set /a TOTAL+=1
echo --------------------------------------------------------------------------------
echo TEST 1: Simple Function
echo --------------------------------------------------------------------------------
if exist tests\test1_simple.txt (
    compiler.exe tests\test1_simple.txt -o test_results\test1.s -all > test_results\test1.log 2>&1
    if errorlevel 1 (
        echo [FAIL] Test 1 failed during compilation
        type test_results\test1.log
        set /a FAILED+=1
    ) else (
        if exist test_results\test1.s (
            echo [PASS] Test 1 passed - Assembly generated
            set /a PASSED+=1
        ) else (
            echo [FAIL] Test 1 failed - No assembly output
            set /a FAILED+=1
        )
    )
) else (
    echo [SKIP] Test file not found
)
echo.

REM ========================================================================
REM TEST 2: Multiple Variables
REM ========================================================================
set /a TOTAL+=1
echo --------------------------------------------------------------------------------
echo TEST 2: Multiple Variables
echo --------------------------------------------------------------------------------
if exist tests\test2_variables.txt (
    compiler.exe tests\test2_variables.txt -o test_results\test2.s -all > test_results\test2.log 2>&1
    if errorlevel 1 (
        echo [FAIL] Test 2 failed during compilation
        type test_results\test2.log
        set /a FAILED+=1
    ) else (
        if exist test_results\test2.s (
            echo [PASS] Test 2 passed - Assembly generated
            set /a PASSED+=1
        ) else (
            echo [FAIL] Test 2 failed - No assembly output
            set /a FAILED+=1
        )
    )
) else (
    echo [SKIP] Test file not found
)
echo.

REM ========================================================================
REM TEST 3: Arithmetic Expressions
REM ========================================================================
set /a TOTAL+=1
echo --------------------------------------------------------------------------------
echo TEST 3: Arithmetic Expressions
echo --------------------------------------------------------------------------------
if exist tests\test3_arithmetic.txt (
    compiler.exe tests\test3_arithmetic.txt -o test_results\test3.s -all > test_results\test3.log 2>&1
    if errorlevel 1 (
        echo [FAIL] Test 3 failed during compilation
        type test_results\test3.log
        set /a FAILED+=1
    ) else (
        if exist test_results\test3.s (
            echo [PASS] Test 3 passed - Assembly generated
            set /a PASSED+=1
        ) else (
            echo [FAIL] Test 3 failed - No assembly output
            set /a FAILED+=1
        )
    )
) else (
    echo [SKIP] Test file not found
)
echo.

REM ========================================================================
REM TEST 4: Class Definition
REM ========================================================================
set /a TOTAL+=1
echo --------------------------------------------------------------------------------
echo TEST 4: Class Definition
echo --------------------------------------------------------------------------------
if exist tests\test4_class.txt (
    compiler.exe tests\test4_class.txt -o test_results\test4.s -all > test_results\test4.log 2>&1
    if errorlevel 1 (
        echo [FAIL] Test 4 failed during compilation
        type test_results\test4.log
        set /a FAILED+=1
    ) else (
        if exist test_results\test4.s (
            echo [PASS] Test 4 passed - Assembly generated
            set /a PASSED+=1
        ) else (
            echo [FAIL] Test 4 failed - No assembly output
            set /a FAILED+=1
        )
    )
) else (
    echo [SKIP] Test file not found
)
echo.

REM ========================================================================
REM TEST 5: Error Detection - Duplicate Declarations
REM ========================================================================
set /a TOTAL+=1
echo --------------------------------------------------------------------------------
echo TEST 5: Error Detection - Duplicate Declarations
echo --------------------------------------------------------------------------------
if exist tests\test5_errors_duplicate.txt (
    compiler.exe tests\test5_errors_duplicate.txt -o test_results\test5.s -all > test_results\test5.log 2>&1
    if errorlevel 1 (
        findstr /C:"Duplicate" test_results\test5.log >nul
        if errorlevel 1 (
            echo [FAIL] Test 5 failed - Should detect duplicate declarations
            set /a FAILED+=1
        ) else (
            echo [PASS] Test 5 passed - Duplicate declarations detected
            set /a PASSED+=1
        )
    ) else (
        echo [FAIL] Test 5 failed - Should fail but compiled successfully
        set /a FAILED+=1
    )
) else (
    echo [SKIP] Test file not found
)
echo.

REM ========================================================================
REM TEST 6: Error Detection - Undeclared Variables
REM ========================================================================
set /a TOTAL+=1
echo --------------------------------------------------------------------------------
echo TEST 6: Error Detection - Undeclared Variables
echo --------------------------------------------------------------------------------
if exist tests\test6_errors_undeclared.txt (
    compiler.exe tests\test6_errors_undeclared.txt -o test_results\test6.s -all > test_results\test6.log 2>&1
    if errorlevel 1 (
        findstr /C:"Undeclared" test_results\test6.log >nul
        if errorlevel 1 (
            echo [FAIL] Test 6 failed - Should detect undeclared variables
            set /a FAILED+=1
        ) else (
            echo [PASS] Test 6 passed - Undeclared variables detected
            set /a PASSED+=1
        )
    ) else (
        echo [FAIL] Test 6 failed - Should fail but compiled successfully
        set /a FAILED+=1
    )
) else (
    echo [SKIP] Test file not found
)
echo.

REM ========================================================================
REM TEST 7: Type Mismatch Warnings
REM ========================================================================
set /a TOTAL+=1
echo --------------------------------------------------------------------------------
echo TEST 7: Type Mismatch Warnings
echo --------------------------------------------------------------------------------
if exist tests\test7_type_mismatch.txt (
    compiler.exe tests\test7_type_mismatch.txt -o test_results\test7.s -all > test_results\test7.log 2>&1
    REM Type mismatches may generate warnings but still compile
    if exist test_results\test7.s (
        echo [PASS] Test 7 passed - Handled type mismatches
        set /a PASSED+=1
    ) else (
        echo [FAIL] Test 7 failed - Could not handle type mismatches
        set /a FAILED+=1
    )
) else (
    echo [SKIP] Test file not found
)
echo.

REM ========================================================================
REM TEST 8: Complex Program
REM ========================================================================
set /a TOTAL+=1
echo --------------------------------------------------------------------------------
echo TEST 8: Complex Program
echo --------------------------------------------------------------------------------
if exist tests\test8_complex.txt (
    compiler.exe tests\test8_complex.txt -o test_results\test8.s -all > test_results\test8.log 2>&1
    if errorlevel 1 (
        echo [FAIL] Test 8 failed during compilation
        type test_results\test8.log
        set /a FAILED+=1
    ) else (
        if exist test_results\test8.s (
            echo [PASS] Test 8 passed - Complex program compiled
            set /a PASSED+=1
        ) else (
            echo [FAIL] Test 8 failed - No assembly output
            set /a FAILED+=1
        )
    )
) else (
    echo [SKIP] Test file not found
)
echo.

REM ========================================================================
REM SUMMARY
REM ========================================================================
echo ================================================================================
echo                            TEST SUMMARY
echo ================================================================================
echo.
echo Total Tests:   %TOTAL%
echo Passed:        %PASSED%
echo Failed:        %FAILED%
echo.

if %FAILED% equ 0 (
    echo [SUCCESS] All tests passed!
    echo.
    echo Generated outputs in test_results/:
    dir /b test_results\*.s 2>nul
    echo.
    echo Intermediate files:
    echo   - *.out files: AST, symbol tables, semantic reports
    echo   - *.log files: Compilation logs
) else (
    echo [WARNING] Some tests failed!
    echo Check test_results\*.log for details
)

echo.
echo ================================================================================
echo.

if %FAILED% equ 0 (
    exit /b 0
) else (
    exit /b 1
)
