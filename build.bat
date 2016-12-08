@echo OFF
call "D:\Programs\VisualStudio\VC\vcvarsall.bat" x86

cd wheresWallySolution
devenv wheresWallySolution.sln /build Release
cd ..

echo Built.

xcopy "wheresWallySolution\Release\wheresWallySolution.exe" build\wheresWally.exe* /Y
echo Copied.

explorer build\

pause
