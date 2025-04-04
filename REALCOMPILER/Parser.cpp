#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

struct ASTNode {
    string type;
    string value;
    vector<ASTNode> children;
};

class Parser {
private:
    vector<string> tokens;
    int currentToken = 0;

    string nextToken() {
        return tokens[currentToken++];
    }

    bool match(string expected) {
        if (tokens[currentToken] == expected) {
            currentToken++;
            return true;
        }
        return false;
    }

    ASTNode parseExpression() {
        ASTNode node{"Expression", "", {}};
        if (match("KEYWORD: LET")) {
            ASTNode letNode{"VariableDeclaration", "let", {}};
            letNode.children.push_back({"Identifier", nextToken(), {}});
            node.children.push_back(letNode);
        }
        return node;
    }

public:
    ASTNode parse(vector<string> tokenList) {
        tokens = tokenList;
        return parseExpression();
    }
};

int main() {
    ifstream inputFile("tokens.json");
    json tokenJson;
    inputFile >> tokenJson;

    vector<string> tokens = tokenJson["tokens"];
    Parser parser;
    ASTNode ast = parser.parse(tokens);

    cout << "AST built successfully!" << endl;
    return 0;
}
