#include <fstream>

void generateAssembly(ASTNode root) {
    ofstream asmFile("output.asm");
    
    asmFile << "section .text" << endl;
    asmFile << "global _start" << endl;
    asmFile << "_start:" << endl;
    
    // Example for handling simple variable assignment
    if (root.type == "VariableDeclaration") {
        asmFile << "mov rax, 10" << endl;  // Example: Loading immediate value
        asmFile << "mov [rbp-4], rax" << endl;  // Storing in stack memory
    }
    
    asmFile << "mov rax, 60" << endl;  // Exit syscall
    asmFile << "xor rdi, rdi" << endl;
    asmFile << "syscall" << endl;
    
    asmFile.close();
}
