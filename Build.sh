#!/bin/bash
set -e

echo "🔧 Starting SuperCodeX Unified Compiler Build..."

# Compiler and assembler
CXX=g++
ASM=nasm
LD=ld

# Flags
CXXFLAGS="-std=c++17 -O2 -Wall"
LDFLAGS=""
OUTPUT="build/SuperCodeX"

# Create build folder if not exists
mkdir -p build

# Compile all C++ parts
echo "🛠️  Compiling C++ components..."
$CXX $CXXFLAGS -c lexer/lexer.cpp -o build/lexer.o
$CXX $CXXFLAGS -c parser/parser.cpp -o build/parser.o
$CXX $CXXFLAGS -c generator/codegen.cpp -o build/codegen.o
$CXX $CXXFLAGS -c ir/ir_processor.cpp -o build/ir.o
$CXX $CXXFLAGS -c gui/viewer.cpp -o build/viewer.o
$CXX $CXXFLAGS -c main.cpp -o build/main.o

# Assemble assembly parts
echo "⚙️  Assembling ASM backend..."
$ASM -f elf64 backend/asm_gen.asm -o build/backend.o

# Link everything into final binary
echo "🔗 Linking all components..."
$CXX build/*.o -o $OUTPUT $LDFLAGS

# Done
echo "✅ Build Complete! Output: $OUTPUT"
