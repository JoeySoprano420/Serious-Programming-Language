typedef int (*mathFunc)(int);

int main() {
    // Lazy load 'sqrt' function from shared library
    void* handle = dlopen("libmath.so", RTLD_LAZY);
    mathFunc sqrtFunc = (mathFunc)dlsym(handle, "sqrt");

    int result = sqrtFunc(16);  // Load symbol when function is first called
    dlclose(handle);
    return result;
}
