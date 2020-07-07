#ifndef scicalc_h
#define scicalc_h

#include <iostream>
#include <cmath>
#include <vector>
#include <stack>
#include <iomanip>
#include <string>

using namespace std;

//classes
enum class tokenType: char{
    lpar = '(',
    rpar = ')',
    plus = '+',
    bmin = '-', //binary minus, (23-12) = 11
    umin = 'u', //unary minus, -(23+12) = -35
    mulp = '*',
    divd = '/',
    powr = '^',
    numb = 'n'
};

class Token{
    public:
        tokenType type;
        double numVal;
        Token(tokenType tp, double vl);
};

typedef vector<Token> Sequence;

class scanResult{
    public:
        Sequence value;
        string errorMsg;
        bool okay();
        scanResult(Sequence val, string msg);
};

class resultExp{
    public:
        double value;
        string errorMsg;
        bool okay();
        resultExp(double val, string msg);
};

ostream& operator<<(ostream &os,const tokenType& tt);
ostream& operator<<(ostream &os,const Token& tk);
ostream& operator<<(ostream &os,const Sequence& tk);
ostream& operator<<(ostream &os,const scanResult& sr);
ostream& operator<<(ostream &os,const resultExp& re);

//Tokenizer
scanResult scan(const string& s);
bool is_whitespace(char c);
bool is_digit(char c);
string quote(const string& s);
bool isOperator(tokenType tt);
int orderOfOperation(tokenType tt);
void minus_fix(Sequence &seq);

//postfix evaluator
resultExp postfix_eval_helper(const Sequence& tokens);
string raw(const string& s);

//Infix evaluator
scanResult infix_to_postfix(const Sequence& input);
resultExp infix_eval_helper(Sequence input);
resultExp infix_eval(const string& input);

//calculator operation
void sciCalc();
//void calcFeature();

//mathematical functions
void findFunc(string &s, bool toRad);
void funcAppl(string &s, string funcType, bool toRad);

#endif