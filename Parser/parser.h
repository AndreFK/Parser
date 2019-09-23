#ifndef PARSER__
#define PARSER__

#include <FlexLexer.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "tokens.h"

using namespace std;

class parser
{

private:
    yyFlexLexer *lexer;
    ifstream in;
    int lookahead_token;
    string lookahead_token_content;

public:
    parser()
    {
        cout << "Parse:\n";
        this->in = ifstream("input.txt");
        this->lexer = new yyFlexLexer(&in);

        this->lookahead_token = this->lexer->yylex();

        if (this->lookahead_token != 0)
        {
            this->lookahead_token_content = this->lexer->YYText();
        }
    }

    ~parser()
    {
        cout << "Parse Completado\n";
        delete this->lexer;
    }

    void Error(string error)
    {
        cout << "Error: " + error << endl;
    }

    void init();

    bool Check(yytokentype token);

    void Consume_Token();

    bool Program();
    bool opt_funct_decl();
    bool funct_head();
    bool funct_name();
    bool funct_type();
    bool decl_type();
    bool param_list_opt();
    bool param_list();
    bool decl_param();
    bool body();
    bool stmt_list_opt();
    bool stmt_list();
    bool stmts();
    bool stmt();
    bool compount_stmt();
    bool if_stmt();
    bool while_stmt();
    bool return_stmt();
    bool expr_stmt();
    bool assign_stmt();
    bool function_stmt();
    bool bool_expr();
    bool constant();
};

#endif