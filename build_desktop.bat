@echo OFF
call "D:\Programs\VisualStudio\VC\vcvarsall.bat" x86

cd wheresWallySolution
devenv wheresWallySolution.sln /build Debug
cd ..

echo Built.

xcopy "wheresWallySolution\Debug\wheresWallySolution.exe" build\wheresWally.exe* /Y
echo Copied.

explorer build\

pause
