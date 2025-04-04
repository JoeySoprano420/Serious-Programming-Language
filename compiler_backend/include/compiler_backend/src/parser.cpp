#include "parser.h"
#include <iostream>

class SimpleParser : public Parser {
public:
    void parse(const std::string &sourceCode) override {
        std::cout << "Parsing source code: " << sourceCode << std::endl;
    }
};

// Factory function to return the correct parser
Parser* createParser() {
    return new SimpleParser();
}
