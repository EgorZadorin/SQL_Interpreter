#include <iostream>
#include <cctype>
#include <string>
#include <stack>
#include <locale>

enum lex_type_t { PLUS, MULT, MINUS, NUMBER, OPEN, CLOSE, IDEN, END };

namespace lexer {
    enum lex_type_t cur_lex_type;
    std::string cur_lex_text;

    int c;
    void init()
    {
        c = std::cin.get();
    }

    void next()
    {
        cur_lex_text.clear();
        enum state_t {H, N, P, MU, MI, O, C, I, OK} state = H;
        while (state != OK) {
            switch (state) {
            case H:
                if (c == '+') {
                    state = P;
                } else if (c == '*') {
                    state = MU;
                } else if (c == '-') {
                    state = MI;
                } else if (c == '(') {
                    state = O;
                } else if (c == ')') {
                    state = C;
                } else if (std::isdigit(c)) {
                    state = N;
                } else if (std::isalpha(c)) {
                    state = I;
                } else if (c == '\n') {
                    cur_lex_type = END;
                    state = OK;
                } else if (std::isspace(c)){
                   // stay in H
                }
                break;

            case N:
                if (std::isdigit(c)) {
                    // stay in N
                } else {
                    cur_lex_type = NUMBER;
                    state = OK;
                }
                break;

            case P:
                cur_lex_type = PLUS;
                state = OK;
                break;

            case MU:
                cur_lex_type = MULT;
                state = OK;
                break;

            case MI:
                cur_lex_type = MINUS;
                state = OK;
                break;

            case O:
                cur_lex_type = OPEN;
                state = OK;
                break;

            case C:
                cur_lex_type = CLOSE;
                state = OK;
                break;
            
            case I:
                cur_lex_type = IDEN;
                state = OK;    
                break;
           
            case OK:
                break;
            }

            if (state != OK) {
                if (!std::isspace(c) && cur_lex_type != END) {
                    cur_lex_text.push_back(c);
                }

                c = std::cin.get();
           }
        }
    }
}

namespace loop_parser {

    void init()
    {
        lexer::init();
        lexer::next();
    }

    std::stack <std::string> pars_stack;

    void E();

    void M();

    void F();

    void E()
    {
        std::string estr;
        std::string estrder;
        M();
        estr = pars_stack.top();
        pars_stack.pop();
        estrder = pars_stack.top();
        pars_stack.pop();
        while (lexer::cur_lex_type == PLUS || lexer::cur_lex_type == MINUS) {
            if (lexer::cur_lex_type == PLUS){
                lexer::next();
                M();
                estr = estr + " " + pars_stack.top() + " +";
                pars_stack.pop();
                estrder = estrder + " " + pars_stack.top() + " +";
            } else {
                lexer::next();
                M();
                estr = estr + " " + pars_stack.top() + " -";
                pars_stack.pop();
                estrder = estrder + " " + pars_stack.top() + " -";
            }
            pars_stack.pop();
        }
        pars_stack.push(estrder);
        pars_stack.push(estr);
    }

    void M()
    {
        std::string mstrder;
        std::string mstr;
        F();
        mstr = pars_stack.top();
        pars_stack.pop();
        mstrder = pars_stack.top();
        pars_stack.pop();
        while (lexer::cur_lex_type == MULT) {
            lexer::next();
            F();
            std::string mstraux = pars_stack.top();
            mstrder = mstrder + " " + pars_stack.top()  +  " *" ;
            pars_stack.pop();
            mstrder = mstrder + " " + mstr + " " + pars_stack.top() + " *" + " +";
            pars_stack.pop();
            mstr = mstr + " " +  mstraux + " *";
        }
        pars_stack.push(mstrder);
        pars_stack.push(mstr);
    }

    void F()
    {
        std::string fstrder;
        std::string fstr;
        if (lexer::cur_lex_type == OPEN) {
            lexer::next();
            E();
            fstr = pars_stack.top();
            pars_stack.pop();
            fstrder = pars_stack.top();
            pars_stack.pop();
            lexer::next();
        } else if (lexer::cur_lex_type == NUMBER) {
            fstr = lexer::cur_lex_text;
            fstrder = "0";
            lexer::next();
        } else if (lexer::cur_lex_type == IDEN) {
            fstr = lexer::cur_lex_text;
            fstrder = "1";
            lexer::next();
        }
        pars_stack.push(fstrder);
        pars_stack.push(fstr);
    }
}

int main(){
    std::string poliz;
    std::string polizder;
    loop_parser::init();
    loop_parser::E();
    poliz = loop_parser::pars_stack.top();
    loop_parser::pars_stack.pop();
    polizder = loop_parser::pars_stack.top();
    loop_parser::pars_stack.pop();
    int x;
    std::cin >> x;
    std::stack <int> stack;
    int num1, num2, num = 0;
    char c = polizder[0];
    int i = 0;
    while(i < polizder.length()){
        if (std::isdigit(c)){
            while(std::isdigit(c) && i < polizder.length()){
                num *= 10;
                num += c - '0';
                i++;
                if (i < polizder.length())
                    c = polizder[i];
            }
            stack.push(num);
            num = 0;
        } else if (std::isalpha(c)){
            stack.push(x);
            i++;
            if (i < polizder.length())
                c = polizder[i];
        } else if (std::isspace(c)){
            i++;
            if (i < polizder.length())
                c = polizder[i];
        } else {
            num2 = stack.top();
            stack.pop();
            num1 = stack.top();
            stack.pop();
            if (c == '+'){
                stack.push(num1 + num2);
            } else if (c == '-') {
                stack.push(num1 - num2);
            } else if (c == '*') {
                stack.push(num1 * num2);
            }
            i++;
            if (i < polizder.length())
                c = polizder[i];
        }
    }
    std::cout << stack.top() << std::endl;
    return 0;
}
