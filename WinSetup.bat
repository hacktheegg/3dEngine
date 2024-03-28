mkdir dependencies
cd dependencies
mkdir GLFW
cd ..

mkdir tempSetup
cd tempSetup

git clone https://github.com/glfw/glfw.git
cd glfw
git reset --hard e2c9264




set WindowsSDKDir=C:\Users\hacktheegg\Downloads\BuildTools\Windows Kits\10
set WindowsSDKVersion=10.0.22621.0
set VCToolsInstallDir=C:\Users\hacktheegg\Downloads\BuildTools\VC\Tools\MSVC\14.39.33519\
set VSCMD_ARG_TGT_ARCH=x64

set MSVC_BIN=C:\Users\hacktheegg\Downloads\BuildTools\VC\Tools\MSVC\14.39.33519\bin\Hostx64\x64
set SDK_BIN=C:\Users\hacktheegg\Downloads\BuildTools\Windows Kits\10\bin\10.0.22621.0\x64;C:\Users\hacktheegg\Downloads\BuildTools\Windows Kits\10\bin\10.0.22621.0\x64\ucrt
set PATH=%MSVC_BIN%;%SDK_BIN%;%PATH%
set INCLUDE=C:\Users\hacktheegg\Downloads\BuildTools\VC\Tools\MSVC\14.39.33519\include;C:\Users\hacktheegg\Downloads\BuildTools\Windows Kits\10\Include\10.0.22621.0\ucrt;C:\Users\hacktheegg\Downloads\BuildTools\Windows Kits\10\Include\10.0.22621.0\shared;C:\Users\hacktheegg\Downloads\BuildTools\Windows Kits\10\Include\10.0.22621.0\um;C:\Users\hacktheegg\Downloads\BuildTools\Windows Kits\10\Include\10.0.22621.0\winrt;C:\Users\hacktheegg\Downloads\BuildTools\Windows Kits\10\Include\10.0.22621.0\cppwinrt
set LIB=C:\Users\hacktheegg\Downloads\BuildTools\VC\Tools\MSVC\14.39.33519\lib\x64;C:\Users\hacktheegg\Downloads\BuildTools\Windows Kits\10\Lib\10.0.22621.0\ucrt\x64;C:\Users\hacktheegg\Downloads\BuildTools\Windows Kits\10\Lib\10.0.22621.0\um\x64




cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -S . -B build
cmake --build build
cmake --install build --prefix install

xcopy /E /I .\install\* .\..\..\dependencies\GLFW\

cd ..\..

rmdir tempSetup /S /Q
