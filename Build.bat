@echo OFF 
call "C:\Program Files (x86)\Microsoft Visual Studio 14.0\VC\vcvarsall.bat" x86
echo "Starting Build for all Projects with proposed changes"
echo .  
devenv "wheresWallySolution\wheresWallySolution.sln" /build Debug 
echo . 
echo All builds completed.
start "wheresWallySolution\Debug" wheresWallySolution\Debug\wheresWallySolution.exe
exit