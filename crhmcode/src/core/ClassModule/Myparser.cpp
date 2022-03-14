#include "Myparser.h"
#include "../InstrumentLogger.h"

Myparser :: Myparser ()
{
InstrumentLogger::instance()->log_instrument_log("<Myparser::Myparser()@@@Myparser.cpp>");
    exp_ptr = NULL;
    for (int i = 0; i < 80; i ++) {
        token [i] = '\0';
    }
InstrumentLogger::instance()->log_instrument_log("</Myparser::Myparser()@@@Myparser.cpp>");
}
void Myparser :: eval_exp (ClassPar * Par)
{
InstrumentLogger::instance()->log_instrument_log("<Myparser::eval_exp(ClassPar * Par)@@@Myparser.cpp>");
    LocalPar = Par;
    double result, Last;
    int stop;
    bool OpenBrkt;
    exp_ptr = Par -> valstr.c_str ();
    row = 0;
    col = 0;
    rowrepeat = 1;
    Bang = 0;
    next: repeat = 1;
    repeatset = false;
    OpenBrkt = false;
    get_token ();
    if (* token == '[')
    {
        result = 0.0;
    }

    else
    if (* token)
    {
        eval_exp2 (result);
        if (result > Par -> maxVal)
        {
            result = Par -> maxVal;
        }

        if (result < Par -> minVal)
        {
            result = Par -> minVal;
        }

        Last = result;
    }

    else
    {
        result = 0.0;
    }

    bool end = ! * exp_ptr;
    switch (* token) {
    case '\0':
        if (col >= Par -> dim)
        {
            break;
        }

        if (Par -> varType == TVar :: Float)
        {
            Par -> layvalues [row] [col ++] = result;
        }

        else
        if (Par -> varType == TVar :: Int)
        {
            Par -> ilayvalues [row] [col ++] = (long) result;
        }

        for (int ll = row; ll < Par -> lay; ++ ll) {
            if (Bang)
            {
                for (int ii = col - 1; ii < Par -> dim; ++ ii) {
                    if (Par -> varType == TVar :: Float)
                    {
                        Par -> layvalues [ll] [ii] = Last;
                    }

                    else
                    if (Par -> varType == TVar :: Int)
                    {
                        Par -> ilayvalues [ll] [ii] = (long) Last;
                    }

                    Last += 1;
                }
            }

            else
            {
                for (int ii = col; ii < Par -> dim; ++ ii)
                    if (Par -> varType == TVar :: Float)
                    {
                        Par -> layvalues [ll] [ii] = 0.0;
                    }

                    else
                    if (Par -> varType == TVar :: Int)
                    {
                        Par -> ilayvalues [ll] [ii] = 0;
                    }

            }

            col = 0;
            ;
        }
        break;
    case '[':
        rowrepeat = repeat;
        repeat = 1;
        repeatset = false;
        OpenBrkt = true;
        goto next;
    case ']':
        OpenBrkt = false;
        while (isspace (* exp_ptr)) ++ exp_ptr;
        if (* exp_ptr == ',')
        {
            ++ exp_ptr;
        }

        stop = col + repeat;
        if (stop > Par -> dim)
        {
            stop = Par -> dim;
        }

        for (int ii = col; ii < stop; ++ ii)
            if (Par -> varType == TVar :: Float)
            {
                Par -> layvalues [row] [col ++] = result;
            }

            else
            if (Par -> varType == TVar :: Int)
            {
                Par -> ilayvalues [row] [col ++] = (long) result;
            }

        for (int ii = col; ii < Par -> dim; ++ ii) {
            Last += Bang;
            if (Par -> varType == TVar :: Float)
            {
                Par -> layvalues [row] [ii] = Last;
            }

            else
            if (Par -> varType == TVar :: Int)
            {
                Par -> ilayvalues [row] [ii] = (long) Last;
            }

        }
        Bang = 0;
        row ++;
        col = 0;
        if (rowrepeat > 1 || end)
        {
            stop = row + rowrepeat - 1;
            if (stop > Par -> lay || end)
            {
                stop = Par -> lay;
            }

            for (int ll = row; ll < stop; ++ ll) {
                for (int ii = col; ii < Par -> dim; ++ ii)
                    if (Par -> varType == TVar :: Float)
                    {
                        Par -> layvalues [ll] [ii] = Par -> layvalues [ll - 1] [ii];
                    }

                    else
                    if (Par -> varType == TVar :: Int)
                    {
                        Par -> ilayvalues [ll] [ii] = Par -> ilayvalues [ll - 1] [ii];
                    }

            }
            row = stop;
            rowrepeat = 1;
        }

        if (row >= Par -> lay)
        {
            break;
        }

        goto next;
    case ',':
        stop = col + repeat;
        if (stop > Par -> dim)
        {
            stop = Par -> dim;
        }

        for (int ii = col; ii < stop; ++ ii)
            if (Par -> varType == TVar :: Float)
            {
                Par -> layvalues [row] [col ++] = result;
            }

            else
            if (Par -> varType == TVar :: Int)
            {
                Par -> ilayvalues [row] [col ++] = (long) result;
            }

        if (col >= Par -> dim)
        if (! OpenBrkt && (row + 1 < Par -> lay))
        {
            col = 0;
            ++ row;
        }

        goto next;
    default:
        serror (0);
        break;
    }
InstrumentLogger::instance()->log_instrument_log("</Myparser::eval_exp(ClassPar * Par)@@@Myparser.cpp>");
}
void Myparser :: eval_exp2 (double & result)
{
InstrumentLogger::instance()->log_instrument_log("<Myparser::eval_exp2(double & result)@@@Myparser.cpp>");
    char op;
    double temp;
    eval_exp3 (result);
    while ((op = * token) == '+' || op == '-') {
        get_token ();
        eval_exp3 (temp);
        switch (op) {
        case '-':
            result = result - temp;
            break;
        case '+':
            result = result + temp;
            break;
        default:
            break;
        }
    }
InstrumentLogger::instance()->log_instrument_log("</Myparser::eval_exp2(double & result)@@@Myparser.cpp>");
}
void Myparser :: eval_exp3 (double & result)
{
InstrumentLogger::instance()->log_instrument_log("<Myparser::eval_exp3(double & result)@@@Myparser.cpp>");
    char op;
    double temp;
    eval_exp4 (result);
    while ((op = * token) == '*' || op == '/' || op == '%') {
        get_token ();
        if (op == '*' && ! repeatset)
        {
            repeat = (int) result;
            repeatset = true;
            if (* token == '[')
            {

InstrumentLogger::instance()->log_instrument_log("</Myparser::eval_exp3(double & result)@@@Myparser.cpp>");
                return;
            }

            eval_exp4 (result);

InstrumentLogger::instance()->log_instrument_log("</Myparser::eval_exp3(double & result)@@@Myparser.cpp>");
            return;
        }

        eval_exp4 (temp);
        switch (op) {
        case '*':
            result = result * temp;
            break;
        case '/':
            result = result / temp;
            break;
        case '%':
            result = (int) result % (int) temp;
            break;
        default:
            break;
        }
    }
InstrumentLogger::instance()->log_instrument_log("</Myparser::eval_exp3(double & result)@@@Myparser.cpp>");
}
void Myparser :: eval_exp4 (double & result)
{
InstrumentLogger::instance()->log_instrument_log("<Myparser::eval_exp4(double & result)@@@Myparser.cpp>");
    double temp;
    eval_exp5 (result);
    if (* token == '^')
    {
        get_token ();
        eval_exp4 (temp);
        if (temp == 0.0)
        {
            result = 1.0;

InstrumentLogger::instance()->log_instrument_log("</Myparser::eval_exp4(double & result)@@@Myparser.cpp>");
            return;
        }

        result = pow (result, temp);
    }

InstrumentLogger::instance()->log_instrument_log("</Myparser::eval_exp4(double & result)@@@Myparser.cpp>");
}
void Myparser :: eval_exp5 (double & result)
{
InstrumentLogger::instance()->log_instrument_log("<Myparser::eval_exp5(double & result)@@@Myparser.cpp>");
    char op;
    op = 0;
    if (((tok_type == DELIMITER) && * token == '+') || * token == '-')
    {
        op = * token;
        get_token ();
    }

    eval_exp6 (result);
    if (op == '-')
    {
        result = - result;
    }

InstrumentLogger::instance()->log_instrument_log("</Myparser::eval_exp5(double & result)@@@Myparser.cpp>");
}
void Myparser :: eval_exp6 (double & result)
{
InstrumentLogger::instance()->log_instrument_log("<Myparser::eval_exp6(double & result)@@@Myparser.cpp>");
    if (* token == '(')
    {
        repeatset = true;
        get_token ();
        eval_exp2 (result);
        if (* token != ')')
        {
            serror (1);
        }

        get_token ();
    }

    else
    {
        atom (result);
    }

InstrumentLogger::instance()->log_instrument_log("</Myparser::eval_exp6(double & result)@@@Myparser.cpp>");
}
void Myparser :: atom (double & result)
{
InstrumentLogger::instance()->log_instrument_log("<Myparser::atom(double & result)@@@Myparser.cpp>");
    switch (tok_type) {
    case NUMBER:
        result = atof (token);
        get_token ();

InstrumentLogger::instance()->log_instrument_log("</Myparser::atom(double & result)@@@Myparser.cpp>");
        return;
    default:
        serror (0);
    }
InstrumentLogger::instance()->log_instrument_log("</Myparser::atom(double & result)@@@Myparser.cpp>");
}
void Myparser :: serror (int error)
{
InstrumentLogger::instance()->log_instrument_log("<Myparser::serror(int error)@@@Myparser.cpp>");
    static string e [] = {"Syntax Error", "Unbalanced Parentheses", "No expression Present"};
    LogError (CRHMException (string (e [error]) + " in module '" + LocalPar -> module + "' parameter '" + LocalPar -> param + "'", TExcept :: WARNING));
    for (int ll = row; ll < LocalPar -> lay; ++ ll) {
        for (int ii = col; ii < LocalPar -> dim; ++ ii)
            if (LocalPar -> varType == TVar :: Float)
            {
                LocalPar -> layvalues [ll] [ii] = 0.0;
            }

            else
            if (LocalPar -> varType == TVar :: Int)
            {
                LocalPar -> ilayvalues [ll] [ii] = 0;
            }

    }
InstrumentLogger::instance()->log_instrument_log("</Myparser::serror(int error)@@@Myparser.cpp>");
}
void Myparser :: get_token ()
{
InstrumentLogger::instance()->log_instrument_log("<Myparser::get_token()@@@Myparser.cpp>");
    char * temp;
    tok_type = 0;
    temp = token;
    * temp = '\0';
    if (! * exp_ptr)
    {

InstrumentLogger::instance()->log_instrument_log("</Myparser::get_token()@@@Myparser.cpp>");
        return;
    }

    while (isspace (* exp_ptr)) ++ exp_ptr;
    if (* exp_ptr == '!')
    {
        Bang = 1;
        ++ exp_ptr;
    }

    if ((* exp_ptr) && strchr ("+-*/%^=(),[]!", * exp_ptr))
    {
        tok_type = DELIMITER;
        * temp ++ = * exp_ptr ++;
    }

    else
    if (isalpha (* exp_ptr))
    {
        while (! isdelim (* exp_ptr)) * temp ++ = * exp_ptr ++;
        tok_type = CRHM :: VARIABLE;
    }

    else
    if (iswdigit (* exp_ptr))
    {
        while ((* exp_ptr) && strchr ("0123456789.", * exp_ptr)) * temp ++ = * exp_ptr ++;
        if ((* exp_ptr) && strchr ("eE", * exp_ptr))
        {
            * temp ++ = * exp_ptr ++;
            while ((* exp_ptr) && strchr ("+- ", * exp_ptr)) * temp ++ = * exp_ptr ++;
            while (! isdelim (* exp_ptr)) * temp ++ = * exp_ptr ++;
        }

        tok_type = NUMBER;
    }

    * temp = '\0';
InstrumentLogger::instance()->log_instrument_log("</Myparser::get_token()@@@Myparser.cpp>");
}
int Myparser :: isdelim (char c)
{
InstrumentLogger::instance()->log_instrument_log("<Myparser::isdelim(char c)@@@Myparser.cpp>");
    if (((* exp_ptr) && strchr (" +-/*%^=(),[]", c)) || c == 9 || c == '\r' || c == 0)
    {

InstrumentLogger::instance()->log_instrument_log("</Myparser::isdelim(char c)@@@Myparser.cpp>");
        return 1;
    }

InstrumentLogger::instance()->log_instrument_log("</Myparser::isdelim(char c)@@@Myparser.cpp>");
    return 0;
InstrumentLogger::instance()->log_instrument_log("</Myparser::isdelim(char c)@@@Myparser.cpp>");
}