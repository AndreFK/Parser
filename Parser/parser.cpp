#include "parser.h"

void parser::init()
{
    if (Program())
        cout << "SUCCESS\n";
    else
    {
        cout << "FAILURE\n";
    }
}

bool parser::Check(yytokentype token)
{
    if (token == this->lookahead_token)
    {
        this->lookahead_token = this->lexer->yylex();
        this->lookahead_token_content = this->lexer->YYText();
        return true;
    }

    return false;
}

void parser::Consume_Token()
{
    this->lookahead_token = this->lexer->yylex();
    this->lookahead_token_content = this->lexer->YYText();
}

bool parser::Program()
{
    cout<<"PROGRAM:="<<endl;
    return opt_funct_decl();
}

bool parser::opt_funct_decl()
{
    cout<<"opt_funct_decl:="<<endl;
    if (funct_head())
    {
        cout<<"funct_head:="<<endl;
        return body();
    }
    else
    {
        return false;
    }
}

bool parser::funct_head()
{
    if (funct_name())
    {
        cout<<"funct_name:="<<endl;
        if (!Check(PAR_OP))
        {
            string error_token = lexer->YYText();
            Error("ERROR: se esperaba '(', se encontro: " + error_token);
            return false;
        }

        if (!param_list_opt())
        {
            return false;
        }

        if (!Check(PAR_CL))
        {
            string error_token = lexer->YYText();
            Error("ERROR: se esperaba ')', se encontro: " + error_token);
            return false;
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool parser::funct_name()
{
    if (funct_type())
    {
        cout<<"funct_type:="<<endl;
        if (!Check(ID))
        {
            string error_token = lexer->YYText();
            Error("ERROR: se esperaba un identificador, se encontro: " + error_token);
            return false;
        }

        return true;
    }
    else
    {
        return false;
    }
}

bool parser::funct_type()
{
    if (!Check(STATIC_TKN))
    {
        string error_token = lexer->YYText();
        Error("ERROR: se esperaba la palabra 'static', se encontro: " + error_token);
        return false;
    }

    if (decl_type())
    {
        cout<<"decl_type:="<<endl;
        return true;
    }
    else
    {
        string error_token = lexer->YYText();
        Error("ERROR: se esperaba tipo de declaracion, se encontro: " + error_token);
        return false;
    }
}

bool parser::decl_type()
{
    string error_token = lexer->YYText();
    switch (lookahead_token)
    {
    case VOID_TYPE:
        cout<<"VOID_TYPE"<<endl;
        Consume_Token();
        return true;
        break;
    case INT_TYPE:
        cout<<"INT_TYPE"<<endl;
        Consume_Token();
        return true;
        break;
    case ANYTYPE_TYPE:
        cout<<"ANYTYPE_TYPE"<<endl;
        Consume_Token();
        return true;
        break;
    case BOOLEAN_TYPE:
        cout<<"BOOLEAN_TYPE"<<endl;
        Consume_Token();
        return true;
        break;
    case REAL_TYPE:
        cout<<"REAL_TYPE"<<endl;
        Consume_Token();
        return true;
        break;
    case DATE_TYPE:
        cout<<"DATE_TYPE"<<endl;
        Consume_Token();
        return true;
        break;
    case STRING_TYPE:
        cout<<"STRING_TYPE"<<endl;
        Consume_Token();
        return true;
        break;
    default:
        Error("ERROR: declaracion invalida: " + error_token);
        return false;
        break;
    }
}

bool parser::param_list_opt()
{
    if (lookahead_token == PAR_CL)
    {

        return true;
    }

    if (decl_param())
    {
        cout<<"DECL_PARAM:="<<endl;
        if (lookahead_token == PAR_CL) 
        {
    
            return true;
        }

        if (!Check(COMA))
        {
            string error_token = lexer->YYText();
            Error("ERROR: Se esperaba un coma entre parametros, se encontro: " + error_token);
            return false;
        }

        if (lookahead_token != PAR_CL)
        {
            return param_list_opt();
        }
        else
        {
            string error_token = lexer->YYText();
            Error("ERROR: coma seguido de un parentesis");
            return false;
        }
    }
    else
    {
        return false;
    }
}

bool parser::decl_param()
{
    if (decl_type())
    {
        cout<<"DECL_TYPE:="<<endl;
        if (!Check(ID))
        {
            string error_token = lexer->YYText();
            Error("ERROR: se esperaba identificador luego de tipo de variable, se encontro: " + error_token);
            return false;
        }

        return true;
    }
    else
    {
        string error_token = lexer->YYText();
        Error("ERROR: se esperaba tipo de declaracion, se encontro: " + error_token);
        return false;
    }
}

bool parser::body()
{
    cout<<"BODY:="<<endl;
    if (!Check(BRACK_OP))
    {
        string error_token = lexer->YYText();
        Error("ERROR: se esperaba '{', se encontro: " + error_token);
        return false;
    }

    if (compount_stmt())
    {
        if(!Check(BRACK_CL))
        {
            string error_token = lexer->YYText();
            Error("ERROR: se esperaba '}', se encontro: " + error_token);
            return false;
        }

        return true;
    }
    else
    {
        return false;
    }
}

bool parser::compount_stmt()
{
    if(lookahead_token == BRACK_CL)
    {
        return true;
    }
    return stmt_list_opt();
}

bool parser::stmt_list_opt()
{
    return stmt_list();
}

bool parser::stmt_list()
{
    if(stmts())
    {
        return true;
    }
    if(decl_type())
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool parser::stmts()
{
    if (lookahead_token == BRACK_CL) //Epsilon
    {
        return true;
    }

    return stmt();
}

bool parser::stmt()
{    if (lookahead_token == WHILE)
    {
        cout<<"WHILE_STMT:="<<endl;
        return while_stmt();
    }
    if (lookahead_token == IF)
    {
        cout<<"IF_STMT:="<<endl;
        return if_stmt();
    }

    if (lookahead_token == RETURN)
    {
        cout<<"RETURN_STMT:="<<endl;
        return return_stmt();
    }
    if (expr_stmt())
    {
        if (lookahead_token != BRACK_CL) 
            return stmt();

        return true;
    }
    else
    {
        return false;
    }
}

bool parser::if_stmt()
{
    if (!Check(IF))
    {
        string error_token = lexer->YYText();
        Error("ERROR: se esperaba un statement, se encontro: " + error_token);
        return false;
    }

    if (!Check(PAR_OP))
    {
        string error_token = lexer->YYText();
        Error("ERROR: se esperaba '(' luego del if, se encontro: " + error_token);
        return false;
    }

    if (bool_expr())
    {
        if (!Check(PAR_CL))
        {
            string error_token = lexer->YYText();
            Error("ERROR: se esperaba ')' despues del if, se encontro: " + error_token);
            return false;
        }

        return body();
    }
    else
    {
        return false;
    }
}

bool parser::while_stmt()
{
    if (!Check(WHILE))
    {
        string error_token = lexer->YYText();
        Error("ERROR: se esperaba un statement, se encontro: " + error_token);
        return false;
    }

    if (!Check(PAR_OP))
    {
        string error_token = lexer->YYText();
        Error("ERROR: se esperaba '(' luego del while, se encontro: " + error_token);
        return false;
    }

    if (bool_expr())
    {
        if (!Check(PAR_CL))
        {
            string error_token = lexer->YYText();
            Error("ERROR: se esperaba ')' despues del while, se encontro:  "+ error_token);
            return false;
        }

        return body();
    }
    else
    {
        return false;
    }
}

bool parser::return_stmt()
{
    if (!Check(RETURN))
    {
        string error_token = lexer->YYText();
        Error("ERROR: se esperaba un statement, se encontro: " + error_token);
        return false;
    }

    if (lookahead_token == SEMICOLON)
    {
        Consume_Token();
        return true;
    }
    else
    {
        if (constant())
        {
            cout<<"CONSTANT"<<endl;
            if (!Check(SEMICOLON))
            {
                string error_token = lexer->YYText();
                Error("ERROR: missing ';', se encontro: " + error_token);
                return false;
            }

            return true;
        }
        else
        {
            return false;
        }
    }
}

bool parser::expr_stmt()
{
    if (assign_stmt())
    {
        cout<<"ASSIGN_STMT"<<endl;
        if (!Check(SEMICOLON))
        {
            string error_token = lexer->YYText();
            Error("ERROR: missing ';', se encontro: " + error_token);
            return false;
        }

        return true;
    }
    else
    {
        return false;
    }
}

bool parser::assign_stmt()
{
    if (decl_type())
    {
        cout<<"DECL_TYPE:="<<endl;
        if (!Check(ID))
        {
            string error_token = lexer->YYText();
            Error("ERROR: se esperaba identificador, se encontro: " + error_token);
            return false;
        }

        if (!Check(ASSIGN))
        {
            string error_token = lexer->YYText();
            Error("ERROR: missing ':=', se encontro: " + error_token);
            return false;
        }

        return constant();
    }
    else
    {
        string error_token = lexer->YYText();
        Error("ERROR: se esperaba declaracion de tipo, se encontro: " + error_token);
        return false;
    }
}

bool parser::function_stmt()
{
    if (decl_type())
    {
        cout<<"DECL_TYPE:="<<endl;
        if (!Check(ID))
        {
            string error_token = lexer->YYText();
            Error("ERROR: se esperaba un indentificador luego de tipo de funcion, se encontro: " + error_token);
            return false;
        }

        if (!Check(PAR_OP))
        {
            string error_token = lexer->YYText();
            Error("ERROR: se esperaba '(' luego de nombre de funcion, se encontro:" + error_token);
            return false;
        }

        if (param_list_opt())
        {
            if (!Check(PAR_CL))
            {
                string error_token = lexer->YYText();
                Error("ERROR: se esperaba ')' luego de parentesis de funcion, se encontro: " + error_token);
                return false;
            }

            if (!Check(SEMICOLON))
            {
                string error_token = lexer->YYText();
                Error("ERROR: missing ';', se encontro: " + error_token);
                return false;
            }

            return true;
        }
        return false;
    }
    else
    {
        string error_token = lexer->YYText();
        Error("ERROR: se esperaba tipo de declaracion de funcion, se encontro: " + error_token);
        return false;
    }
}

bool parser::bool_expr()
{
    if (lookahead_token == TRUE){
        cout<<"FALSE"<<endl;
        Consume_Token();
        return true;
    }
    if(lookahead_token == FALSE)
    {
        cout<<"FALSE"<<endl;
        Consume_Token();
        return true;
    }

    if (constant())
    {
        cout<<"CONSTANT"<<endl;
        if (!Check(LOG_OP))
        {
            string error_token = lexer->YYText();
            Error("ERROR: se esperaba '&&' o '||', se encontro:  " + error_token);
            return false;
        }

        return constant();
    }
    else
    {
        return false;
    }
}

bool parser::constant()
{
    if (lookahead_token == INT_LITERAL){
        cout<<"INT_LITERAL"<<endl;
        Consume_Token();
        return true;
    }
    if(lookahead_token == REAL_LITERAL){
        cout<<"REAL_LITERAL"<<endl;
        Consume_Token();
        return true;
    } 
    if(lookahead_token == DATE_LITERAL){
        cout<<"DATE_LITERAL"<<endl;
        Consume_Token();
        return true;
    }
    if(lookahead_token == STRING_LITERAL)
    {
        cout<<"STRING_LITERAL"<<endl;
        Consume_Token();
        return true;
    }
    else
    {
        return false;
    }
}
