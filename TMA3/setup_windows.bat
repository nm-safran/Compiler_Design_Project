@echo off
REM filepath: c:\Users\Safran\Desktop\Final Year\EEX6363_Compiler Construction\TMAs\DesignProject\TMA3\setup_windows.bat

echo ===============================================
echo    TMA3 Setup for Windows
echo ===============================================
echo.

REM Check for GCC
echo Checking for GCC...
where gcc >nul 2>nul
if %ERRORLEVEL% NEQ 0 (
    echo ERROR: GCC not found!
    echo.
    echo Please install MinGW or TDM-GCC:
    echo   - MinGW: https://sourceforge.net/projects/mingw/
    echo   - TDM-GCC: https://jmeubank.github.io/tdm-gcc/
    echo.
    echo After installation, add to PATH:
    echo   C:\MinGW\bin or C:\TDM-GCC-64\bin
    echo.
    pause
    exit /b 1
)
echo [OK] GCC found:
gcc --version | findstr "gcc"

REM Check for winflexbison
echo.
echo Checking for winflexbison...
if exist "C:\Tools\winflexbison\win_flex.exe" (
    echo [OK] win_flex.exe found at C:\Tools\winflexbison
) else (
    echo [ERROR] win_flex.exe not found at C:\Tools\winflexbison
    echo Please verify your winflexbison installation
    pause
    exit /b 1
)

if exist "C:\Tools\winflexbison\win_bison.exe" (
    echo [OK] win_bison.exe found at C:\Tools\winflexbison
) else (
    echo [ERROR] win_bison.exe not found at C:\Tools\winflexbison
    echo Please verify your winflexbison installation
    pause
    exit /b 1
)

echo.
echo ===============================================
echo    Copying lexer from TMA2...
echo ===============================================

REM Copy lexer from TMA2
if exist "..\TMA2\TMA2Qc&Qe\lexer.l" (
    echo Copying lexer.l...
    copy "..\TMA2\TMA2Qc&Qe\lexer.l" lexer_original.l >nul
    echo [OK] Original lexer copied to lexer_original.l
    echo Note: Using modified lexer.l for TMA3
) else (
    echo [WARNING] TMA2 lexer.l not found, using current lexer.l
)

echo.
echo ===============================================
echo    Creating test input files...
echo ===============================================

if not exist test1_simple.txt (
    echo Creating test1_simple.txt...
    echo // Simple test program> test1_simple.txt
    echo.>> test1_simple.txt
    echo func main() =^> integer {>> test1_simple.txt
    echo     local x : integer;>> test1_simple.txt
    echo     x := 42;>> test1_simple.txt
    echo     return (x);>> test1_simple.txt
    echo }>> test1_simple.txt
    echo [OK] test1_simple.txt created
)

echo.
echo ===============================================
echo    Setup Complete!
echo ===============================================
echo.
echo System configuration:
echo   - GCC: Found and ready
echo   - win_flex.exe: C:\Tools\winflexbison\win_flex.exe
echo   - win_bison.exe: C:\Tools\winflexbison\win_bison.exe
echo.
echo Next steps:
echo   1. Run: build.bat
echo   2. Test: compiler.exe test1_simple.txt
echo.
pause
