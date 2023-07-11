#pragma once

#include <string>

using namespace std;

enum class token_type
{
    Identifier,
    MainOperator,
    SecondaryOperator,
    constant,
    separators
};

class Token
{
private:
    string name;
    int type;
public:
    Token(string tkn) { name = tkn; };
};

