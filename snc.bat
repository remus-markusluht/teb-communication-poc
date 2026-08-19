@echo off
:: Generate a random GUID using PowerShell
for /f "delims=" %%i in ('powershell -Command "[guid]::NewGuid().ToString()"') do set RANDOM_KEY=%%i

set /a min = 7
set /a max = 10
set /a rnd=( %RANDOM% %% (%max% - %min% + 1) ) + %min%

:: Split the GUID into parts
set PART1=%RANDOM_KEY:~0,8%
set PART2=%RANDOM_KEY:~9,4%
set PART3=%RANDOM_KEY:~14,4%
set PART4=%RANDOM_KEY:~19,4%
set PART5=%RANDOM_KEY:~24,12%

set RP1=%RANDOM_KEY:~1,3%
set RP2=%RANDOM_KEY:~4,4%
set RP3=%RANDOM_KEY:~2,5%
set RP4=%RANDOM_KEY:~32,18%

:: Create or overwrite the header file with the split GUID parts and random number
echo #define KCCKeyPart1 "%PART1%" > key.h
echo #define KCCKeyPart2 "%PART2%" >> key.h
echo #define KCCKeyPart3 "%PART3%" >> key.h
echo #define KCCKeyPart4 "%PART4%" >> key.h
echo #define KCCKeyPart5 "%PART5%" >> key.h

:: Add the random number to the key.h file
echo #define RANDOM_NUMBER %rnd% >> key.h

:: Output the generated parts and the random number for confirmation
echo Generated random key parts:
echo Part1: %PART1%
echo Part2: %PART2%
echo Part3: %PART3%
echo Part4: %PART4%
echo Part5: %PART5%
echo Random Number: %rnd%

input
:: Exit the script
exit /b