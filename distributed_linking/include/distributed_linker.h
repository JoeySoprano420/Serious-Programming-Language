#ifndef DISTRIBUTED_LINKER_H
#define DISTRIBUTED_LINKER_H

#include <string>

class DistributedLinker {
public:
    void linkToCloudService(const std::string &serviceURL, const std::string &sourceCode);
};

#endif // DISTRIBUTED_LINKER_H
