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

ASTNode parseForLoop() {
    ASTNode loopNode{"ForLoop", "", {}};

    if (match("KEYWORD: FOR")) {
        // Parse initialization: (let i = 0;)
        match("(");
        loopNode.children.push_back(parseVariableDeclaration());
        match(";");
        
        // Parse loop condition (i < 10)
        loopNode.children.push_back(parseCondition());
        match(";");
        
        // Parse increment (i++)
        loopNode.children.push_back(parseExpression());
        match(")");
        
        // Parse loop body
        loopNode.children.push_back(parseBlock());
    }
    
    return loopNode;
}

ASTNode parseWhileLoop() {
    ASTNode loopNode{"WhileLoop", "", {}};
    
    if (match("KEYWORD: WHILE")) {
        match("(");
        loopNode.children.push_back(parseCondition());
        match(")");
        loopNode.children.push_back(parseBlock());
    }
    
    return loopNode;
}

ASTNode parseFunction() {
    ASTNode funcNode{"FunctionDeclaration", "", {}};
    
    if (match("KEYWORD: FUNC")) {
        funcNode.children.push_back({"Identifier", nextToken(), {}});
        match("(");
        
        // Parse parameter list
        while (!match(")")) {
            funcNode.children.push_back({"Parameter", nextToken(), {}});
            if (!match(",")) break;
        }
        
        funcNode.children.push_back(parseBlock());
    }
    
    return funcNode;
}

ASTNode parseIfElse() {
    ASTNode ifNode{"IfStatement", "", {}};
    
    if (match("KEYWORD: IF")) {
        match("(");
        ifNode.children.push_back(parseCondition());
        match(")");
        ifNode.children.push_back(parseBlock());
        
        if (match("KEYWORD: ELSE")) {
            ifNode.children.push_back(parseBlock());
        }
    }
    
    return ifNode;
}

