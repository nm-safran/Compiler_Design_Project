@echo off
REM filepath: c:\Users\Safran\Desktop\Final Year\EEX6363_Compiler Construction\TMAs\DesignProject\TMA3\quick_test.bat

echo Testing all 8 test files...
echo.

for %%f in (tests\test*.txt) do (
    echo ========================================
    echo Testing: %%f
    echo ========================================
    compiler.exe %%f
    echo.
    if exist semantic_errors.out (
        type semantic_errors.out | findstr /C:"Total Errors:" /C:"Total Warnings:"
    )
    echo.
)

echo.
echo All tests completed!
pause
