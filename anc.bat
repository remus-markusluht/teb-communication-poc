@echo off
setlocal

net session >nul 2>&1
if %errorLevel% neq 0 (
    echo Requesting administrative privileges...
    powershell -Command "Start-Process cmd -Argument '/c \"%~s0\"' -Verb RunAs"
    exit /b
)

cd "C:\Program Files (x86)\Windows Kits\10\bin\10.0.26100.0\x64"
signtool.exe sign /fd SHA256 /f C:\Users\dnfki\OneDrive\Desktop\CERT\nitrogen-studios.pfx /p 7777NitroGenStudios7777 /t http://timestamp.digicert.com C:\Users\dnfki\OneDrive\Desktop\SonosNewJMP\x64\Release\amdvmx86.sys

cd "C:\Users\dnfki\OneDrive\Desktop\SonosNewJMP\CodeCS"
Virtualizer.exe /protect C:\Users\dnfki\OneDrive\Desktop\SonosNewJMP\CodeCS\cs.cv

cd "C:\Program Files (x86)\Windows Kits\10\bin\10.0.26100.0\x64"
signtool.exe sign /fd SHA256 /f C:\Users\dnfki\OneDrive\Desktop\CERT\nitrogen-studios.pfx /p 7777NitroGenStudios7777 /t http://timestamp.digicert.com C:\Users\dnfki\OneDrive\Desktop\SonosNewJMP\x64\Release\amdvmx86_protected.sys