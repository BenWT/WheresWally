@echo OFF
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86

cd wheresWallySolution
devenv wheresWallySolution.sln /build Debug
cd ..

echo Built.

xcopy "wheresWallySolution\Debug\wheresWallySolution.exe" build\wheresWally.exe* /Y
echo Copied.

explorer build\

pause
