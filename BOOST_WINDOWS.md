# Installing boost libraries for GCC (MinGW|MSVC)

## Folder setup
1. Extract downloaded boost source, e.g. `C:\boost_1_80_0`.
2. Create a folder for Boost.Build installation, e.g. `C:\boost_1_80_0\boost-build`.
2. Create a folder within for building, i.e. `C:\boost_1_80_0\build`.
3. Create a folder for x64|x32 installation, e.g. `C:\boost(64|32)`.

## GCC setup
1. Open Command Prompt.
2. Run `g++ --version`.
3. If the output contains g++ version number then GCC should be set up properly to run from command line and you can continue.

## Boost.Build setup
1. Open Command Prompt and navigate to `C:\boost_1_80_0\tools\build`.
2. Run `bootstrap.bat mingw|vc142`.
3. Run `b2 install --prefix="C:\boost_1_80_0\boost-build"`.
4. Add `C:\boost_1_80_0\boost-build` to Windows PATH.

## boost building
1. Open Command Prompt and navigate to `C:\boost_1_80_0`.
2. Run for x64 build
```
b2 --build-dir="C:\boost_1_80_0\build" --prefix="C:\boost64" toolset=gcc|msvc install address-model=64
```
3. Run for x32 build
```
b2 --build-dir="C:\boost_1_80_0\build" --prefix="C:\boost32" toolset=gcc|msvc install address-model=32
```

## Project setup
1. Add include folder, i.e. `C:\boost(64|32)\include\boost_1_80_0`.
2. Add linker folder, i.e. `C:\boost(64|32)\lib`.
3. Link required libraries, e.g. `libboost_regex-mgw48-mt-1_80.a`.