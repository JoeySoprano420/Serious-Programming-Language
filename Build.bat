@echo off
echo 🔧 Starting SuperCodeX Unified Compiler Build...

:: Compiler and assembler
set CXX=g++
set ASM=nasm
set OUTPUT=build\SuperCodeX.exe

:: Compiler flags
set CXXFLAGS=-std=c++17 -O2 -Wall

:: Create build directory
if not exist build mkdir build

:: Compile C++ parts
echo 🛠️  Compiling C++ components...
%CXX% %CXXFLAGS% -c lexer\lexer.cpp -o build\lexer.o
%CXX% %CXXFLAGS% -c parser\parser.cpp -o build\parser.o
%CXX% %CXXFLAGS% -c generator\codegen.cpp -o build\codegen.o
%CXX% %CXXFLAGS% -c ir\ir_processor.cpp -o build\ir.o
%CXX% %CXXFLAGS% -c gui\viewer.cpp -o build\viewer.o
%CXX% %CXXFLAGS% -c main.cpp -o build\main.o

:: Assemble backend
echo ⚙️  Assembling ASM backend...
%ASM% -f win64 backend\asm_gen.asm -o build\backend.o

:: Link everything
echo 🔗 Linking all components...
%CXX% build\*.o -o %OUTPUT%

echo ✅ Build Complete! Output: %OUTPUT%
