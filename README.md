# wsh
A multi-platform shell written in C

## Third-Party Tools
*  CMake (Version 2.8 or newer)
*  Visual Studio 2013 (Windows only)

## Installation
```
git clone https://github.com/robert-w-gries/wsh
cd wsh
mkdir build
cd build
cmake ..
```

## Usage

### Unix
```
make
./wsh
```

### Windows
```
Run Visual Studio 2013
File -> Open -> Project/Solution -> wsh/build/WSH.sln
Right-click on 'wsh' in the solution explorer -> Set as StartUp Project
Build Solution
Run via Visual Studio Debugger or run wsh.exe in wsh/build/Debug or wsh/build/Release
```
