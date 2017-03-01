@echo off
set ARGS=/A /SE /SW /SA
if "%PROCESSOR_ARCHITECTURE%" == "AMD64" (
  drivers\dpinst-amd64.exe %ARGS%
  drivers\dpinst-amd64.exe %ARGS% /path drivers\x64
) ELSE IF "%PROCESSOR_ARCHITEW6432%" == "AMD64" (
  drivers\dpinst-amd64.exe %ARGS%
  drivers\dpinst-amd64.exe %ARGS% /path drivers\x64
) ELSE (
  drivers\dpinst-x86.exe %ARGS%
  drivers\dpinst-x86.exe %ARGS% /path drivers\x86
)
exit /b 0