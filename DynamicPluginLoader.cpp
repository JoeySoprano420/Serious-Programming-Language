#include <dlfcn.h>
#include <iostream>

class PluginLoader {
    void* handle;

public:
    PluginLoader(const std::string& pluginPath) {
        handle = dlopen(pluginPath.c_str(), RTLD_LAZY);
        if (!handle) {
            std::cerr << "Failed to load plugin: " << dlerror() << std::endl;
        }
    }

    ~PluginLoader() {
        if (handle) {
            dlclose(handle);
        }
    }

    template <typename T>
    T getFunction(const std::string& funcName) {
        return reinterpret_cast<T>(dlsym(handle, funcName.c_str()));
    }
};

int main() {
    PluginLoader loader("plugin.so");

    auto pluginFunction = loader.getFunction<void(*)()>("pluginEntry");
    pluginFunction();  // Call the plugin function
    return 0;
}
