#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>

// Abstract class for the Parser
class Parser {
public:
    virtual void parse(const std::string &sourceCode) = 0;
    virtual ~Parser() = default;
};

#endif // PARSER_H
