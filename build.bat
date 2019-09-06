@echo off
echo Generating Windows project...
premake5.exe --os=windows --file=projects/premake5.lua --sourcesdk=../../../sourcesdk-minimal vs2017
echo.
pause