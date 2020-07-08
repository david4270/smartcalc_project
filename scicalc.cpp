#define _USE_MATH_DEFINES

//all the headers are included in scicalc.h
#include "scicalc.h"

using namespace std;

//Constructor and operator<< of classes

Token::Token(tokenType tp, double vl){
    type = tp;
    numVal = vl;
}

scanResult::scanResult(Sequence val, string msg){
    value = val;
    errorMsg = msg;
}

resultExp::resultExp(double val, string msg){
    value = val;
    errorMsg = msg;
}

storeRes::storeRes(string ei, double ans){
    equationInput = ei;
    answer = ans;
}

ostream& operator<<(ostream &os,const tokenType& tt){
    os << "'" << char(tt) <<"'";
    return os;
}

ostream& operator<<(ostream &os,const Token& tk){
    if(tk.type == tokenType::numb){
        os << "<" << tk.numVal << ">";
    }
    else{
        os << "<" << char(tk.type) << ">";
    }
    return os;
}

ostream& operator<<(ostream &os,const Sequence& sq){
    int n = sq.size();
    if(n==0){
        os << "{}";
    }
    else if (n==1){
        os << "{" << sq[0] << "}";
    }
    else{
        os << "{" << sq[0];
        for(int i = 1; i < n; ++i){
            os<<", "<<sq[i];
        }
        os << "}";
    }
    return os;
}

ostream& operator<<(ostream &os,const scanResult& sr){
    os << "scanResult{"<<sr.value<<","<<quote(sr.errorMsg)<<"}";
    return os;
}

ostream& operator<<(ostream &os,const resultExp& re){
    os << "resultExp{"<<re.value<<","<<quote(re.errorMsg)<<"}";
    return os;
}

bool scanResult::okay(){
    return errorMsg.empty();
}

bool resultExp::okay(){
    return errorMsg.empty();
}

//tokenizer
scanResult scan(const string& s){
    Sequence tokenSeq;
    for(int i=0; i<s.size(); ++i){

        //if there is whitespace
        if(is_whitespace(s[i])){
            i++;
            while (i<s.size() && is_whitespace(s[i])) i++;
            if(i < s.size()) i--;
        }
        else if(is_digit(s[i])){
            string num = string(1,s[i]);
            i++;
            while (i<s.size() && is_digit(s[i])){
                num += string(1,s[i]);
                i++;
            }
            if(i < s.size()) i--;
            tokenSeq.push_back(Token(tokenType::numb, stod(num)));
        }
        else if(s[i] == '(') tokenSeq.push_back(Token(tokenType::lpar,0));
        else if(s[i] == ')') tokenSeq.push_back(Token(tokenType::rpar,0));
        else if(s[i] == '+') tokenSeq.push_back(Token(tokenType::plus,0));
        else if(s[i] == '-') tokenSeq.push_back(Token(tokenType::bmin,0));
        else if(s[i] == '*') tokenSeq.push_back(Token(tokenType::mulp,0));
        else if(s[i] == '/') tokenSeq.push_back(Token(tokenType::divd,0));
        else if(s[i] == '^') tokenSeq.push_back(Token(tokenType::powr,0));
        else{
            string msg = "Scanner encountered unknown character "+string(1,s[i]);
            return scanResult(Sequence{},msg);
        }
    }
    return scanResult(tokenSeq,"");
}

bool is_whitespace(char c){
    return (c==' ' || c=='\n' || c=='\t' || c == '\r');
}

bool is_digit(char c){
    return (c == '.' || (c >= '0' && c <= '9'));
}

string quote(const string& s){
    return "\"" + s + "\"";
}

bool isOperator(tokenType tt){
    if(tt == tokenType::plus || 
    tt == tokenType::divd || 
    tt == tokenType::powr || 
    tt == tokenType::bmin || 
    tt == tokenType::umin || 
    tt == tokenType::mulp){
        return true;
    }
    return false;
}

int orderOfOperation(tokenType tt){
    if(tt == tokenType::umin) return 5;
    else if (tt == tokenType::powr) return 4;
    else if (tt == tokenType::mulp || tt == tokenType::divd) return 3;
    else if (tt == tokenType::plus || tt == tokenType::bmin) return 2;
    else return -1;
}

void minus_fix(Sequence &seq){
    if (seq.empty()) {
        return;
    }
    if(seq[0].type == tokenType::bmin){
        seq[0].type = tokenType::umin;
    }
    for(int i=1; i<seq.size(); ++i){
        tokenType prev = seq[i-1.0].type;
        if(seq[i].type == tokenType::bmin){
            if(prev == tokenType::lpar || isOperator(prev)){
                seq[i].type = tokenType::umin;
            }
        }
    }
}

//postfix evaluator
template <class tpl>
tpl pop(vector<tpl>& stack){
    tpl result = stack.back();
    stack.pop_back();
    return result;
}

resultExp postfix_eval_helper(const Sequence& tokens){
    vector <double> stack;
    bool ok = true;
    for(Token tok:tokens){
        if(tok.type == tokenType::numb){
            stack.push_back(tok.numVal);
        }
        else if(tok.type == tokenType::umin){
            if(stack.size()<1){
                ok = false;
                break;
            }
            double a = pop(stack);
            stack.push_back(-a);
        }
        else{
            if(stack.size()<2){
                ok = false;
                break;
            }
            double a = pop(stack);
            double b = pop(stack);

            switch(tok.type){
                case tokenType::plus: stack.push_back(a+b); break;
                case tokenType::bmin: stack.push_back(b-a); break;
                case tokenType::mulp: stack.push_back(a*b); break;
                case tokenType::divd:
                    if(a == 0.0){
                        return resultExp(0,"division by 0");
                    }
                    stack.push_back(b/a);
                    break;
                case tokenType::powr: stack.push_back(pow(b,a)); break;
                default: return resultExp(0, "Error in program");
            }
        }
    }
    if(ok && stack.size()>0) return resultExp(stack[0],"");
    else return resultExp(0,"Not enough numbers to pop");
}

string raw(const string& s){
    string separator = "@";
    string result;
    for (char c : s){
        switch(c){
            case '\n': result += "\\n"; break;
            case '\t': result += "\\t"; break;
            case '\r': result += "\\r"; break;
            case ' ': result += separator; break;
            default: result += c;
        }
    }
    return result;
}

//Infix evaluator
scanResult infix_to_postfix(const Sequence& input){
    Sequence output;
    Sequence stack;
    for (const Token& tok: input){
        switch(tok.type){
            case tokenType::numb:
                output.push_back(tok);
                break;
            case tokenType::plus:
            case tokenType::bmin:
            case tokenType::umin:
            case tokenType::mulp:
            case tokenType::divd:
            case tokenType::powr:
                while((!stack.empty()) && 
                (isOperator(stack.back().type)) && 
                (orderOfOperation(stack.back().type) >= orderOfOperation(tok.type))){
                    output.push_back(pop(stack));
                }
                stack.push_back(tok);
                break;
            case tokenType::lpar:
                stack.push_back(tok);
                break;
            case tokenType::rpar:
                while(!stack.empty() && (stack.back().type != tokenType::lpar)){
                    output.push_back(pop(stack));
                }
                if(stack.empty()){
                    return scanResult(Sequence{},"Mis-matched parenthesis");
                }
                else if(stack.back().type == tokenType::lpar){
                    pop(stack);
                }
                else{
                    cout << "Logic error in right parenthesis" <<endl;
                }
                break;
            default: cout << "tok.type" << char(tok.type) << endl;
        }
    }
    while(!stack.empty()){
        Token tk = pop(stack);
        if(tk.type == tokenType::lpar || tk.type == tokenType::rpar){
            return scanResult(Sequence{},"Mis-matched parenthesis");
        }
        output.push_back(tk);
    }
    return scanResult(output,"");
}

resultExp infix_eval_helper(Sequence input){
    minus_fix(input);
    scanResult postfix = infix_to_postfix(input);
    if(postfix.okay()) return postfix_eval_helper(postfix.value);
    else return resultExp(0,postfix.errorMsg);
}

resultExp infix_eval(const string& input){
    scanResult tokens = scan(input);
    if(tokens.okay()) return infix_eval_helper(tokens.value);
    else return resultExp(0, tokens.errorMsg);
}

//calculator operation
void sciCalc(){
    cout << "Scientific Calculator" <<endl;
    cout << endl;
    cout << "Commands" <<endl;
    cout << "exit - return back to main menu" <<endl;
    cout << "read - read saved file" <<endl;
    cout << "readDB - read database" <<endl;
    cout << "restore - restore calculation data from previous operation, should be performed before first calculation" <<endl;
    cout << "remove - remove certain calculation from history" <<endl;
    cout << "clear - clear calculation history" <<endl;
    cout << "exitclr - clear and exit" <<endl;
    cout << endl;
    cout << "Conversion of angle units" <<endl;
    cout << "rad - switch to radian calculation" <<endl;
    cout << "deg - switch to degree calculation" <<endl;
    cout << endl;
    cout << "Mathematical Functions" <<endl;
    cout << "sin - sine"<<endl;
    cout << "cos - cosine"<<endl;
    cout << "tan - tangent"<<endl;
    cout << "sec - secant" << endl;
    cout << "csc - cosecant"<<endl;
    cout << "cot - cotangent"<<endl;
    cout << "asin - arcsine"<<endl;
    cout << "acos - arccosine"<<endl;
    cout << "atan - arctangent"<<endl;
    cout << "asec - arcsecant"<<endl;
    cout << "acsc - arccosecant"<<endl;
    cout << "acot - arccotangent"<<endl;
    cout << "sinh - hyperbolic sine"<<endl;
    cout << "cosh - hyperbolic cosine"<<endl;
    cout << "tanh - hyperbolic tangent"<<endl;
    cout << "asinh - arc hyperbolic sine"<<endl;
    cout << "acosh - arc hyperbolic cosine"<<endl;
    cout << "atanh - arc hyperbolic tangent"<<endl;
    cout << "exp - e^()"<<endl;
    cout << "twop - 2^()"<<endl;
    cout << "expmo - (-1)^()"<<endl;
    cout << "ln - natural log"<<endl;
    cout << "log OR logten - log base 19"<<endl;
    cout << "logtwo - log base 2"<<endl;
    cout << "sqrt - square root"<<endl;
    cout << "cbrt - cubic root"<<endl;
    bool cont = true;
    bool toRad = false;
    string input;
    vector <storeRes> solStore;
    const string fileName = "scicalclog.txt";

    while(cont){
        cout << "Insert your operation: ";
        getline(cin, input);
        if (input.empty()) {
            getline(cin, input);
        }
        
        if (input.compare("exit") == 0){
            cout << "Closing Scientific calculator..."<<endl;
            cont = false;
            break;
        }

        else if (input.compare("rad") == 0){
            cout << "Performing radian calcuations..." <<endl;
            toRad = true;
            continue;
        }
        else if (input.compare("deg") == 0){
            cout << "Performing degree calcuations..." <<endl;
            toRad = false;
            continue;
        }
        else if (input.compare("read") == 0){
            cout << "Reading information..."<<endl;
            readFile(fileName);
            continue;
        }
        else if (input.compare("readDB") == 0){
            cout << "Reading database..."<<endl;
            readsolStore(solStore);
            continue;
        }
        else if (input.compare("restore") == 0){
            cout << "Restoring file..." <<endl;
            restoreData(fileName,solStore);
            writeFile(fileName,solStore);
            continue;
        }
        else if (input.compare("remove") == 0){
            cout << "You have following calculations in history: " << endl;
            readFile(fileName);
            deleteLine(solStore);
            cout << "Update information..." <<endl;
            writeFile(fileName,solStore);
            continue;
        }
        else if (input.compare("clear") == 0){
            cout << "Clearing information..."<<endl;
            solStore.clear();
            writeFile(fileName,solStore);
            continue;
        }
        else if (input.compare("exitclr") == 0){
            cout << "Clearing information and closing scientific calcuator..."<<endl;
            solStore.clear();
            writeFile(fileName,solStore);
            cont = false;
            break;
        }
        else{
            sciCalcHelper(input,toRad,solStore);
            writeFile(fileName,solStore);
        } 
    }
    solStore.clear();
}

void sciCalcHelper(string & input, bool toRad, vector <storeRes>& solStore){
    string rawInput = input;
    findFunc(input,toRad);

    resultExp result = infix_eval(input);
    if(result.okay()){
        if(result.value < 10.0){
            cout << "val = " << setprecision(3) << result.value << endl;
        }
        else cout << "val = " << setprecision(5) << result.value << endl;
        solStore.push_back(storeRes(rawInput,result.value));
    }
    else cout << "Error: " << result.errorMsg <<endl;
}


//mathematical functions
void findFunc(string &s, bool toRad){
    vector <string> funcSet;

    funcSet= {"acosh","asinh","atanh",
    "cosh","sinh","tanh","acos", "asin",
    "atan","sin","cos","tan","asec",
    "acsc","acot","sec","csc","cot",
    "exp","twop","expmo","ln","logten",
    "log","logtwo","sqrt","cbrt"};
    for (auto it = 0; it != funcSet.size(); ++it){
        funcAppl(s,funcSet[it], toRad);
    }
    funcSet.clear();
}

void funcAppl(string &s, string funcType, bool toRad){
    double num=0.0;
    size_t found;
    int i;
    bool changeFinished = false;
    found = s.find(funcType);

    while(!changeFinished){
        if(found != string::npos){
            i = found + funcType.length();
            if(is_digit(s[i])){
                string numRead = string(1,s[i]);
                i++;
                while(i<s.size() && is_digit(s[i])){
                    numRead += string(1,s[i]);
                    i++;
                }
                if (i<s.size()) i--;
                if(funcType == "sin"){
                    if(!toRad) num = sin(stod(numRead)* M_PI / 180); 
                    else num = sin(stod(numRead));
                }
                else if(funcType == "cos"){
                    if(!toRad) num = cos(stod(numRead)* M_PI / 180); 
                    else num = cos(stod(numRead));
                }
                else if(funcType == "tan"){
                    if(!toRad) num = tan(stod(numRead)* M_PI / 180); 
                    else num = tan(stod(numRead));
                }
                else if(funcType == "asin"){
                    if(!toRad) num = asin(stod(numRead))*180/M_PI; 
                    else num = asin(stod(numRead));
                }
                else if(funcType == "acos"){
                    if(!toRad) num = acos(stod(numRead))*180/M_PI; 
                    else num = acos(stod(numRead));
                }
                else if(funcType == "atan"){
                    if(!toRad) num = atan(stod(numRead))*180/M_PI; 
                    else num = atan(stod(numRead));
                }
                if(funcType == "sinh"){
                    if(!toRad) num = sinh(stod(numRead)* M_PI / 180); 
                    else num = sinh(stod(numRead));
                }
                else if(funcType == "cosh"){
                    if(!toRad) num = cosh(stod(numRead)* M_PI / 180); 
                    else num = cosh(stod(numRead));
                }
                else if(funcType == "tanh"){
                    if(!toRad) num = tanh(stod(numRead)* M_PI / 180); 
                    else num = tanh(stod(numRead));
                }
                else if(funcType == "asinh"){
                    if(!toRad) num = asinh(stod(numRead))*180/M_PI; 
                    else num = asinh(stod(numRead));
                }
                else if(funcType == "acosh"){
                    if(!toRad) num = acosh(stod(numRead))*180/M_PI; 
                    else num = acosh(stod(numRead));
                }
                else if(funcType == "atanh"){
                    if(!toRad) num = atanh(stod(numRead))*180/M_PI; 
                    else num = atanh(stod(numRead));
                }
                else if(funcType == "exp") num = exp(stod(numRead));
                else if(funcType == "twop") num = exp2(stod(numRead));
                else if(funcType == "expmo") num = expm1(stod(numRead));
                else if(funcType == "ln") num = log(stod(numRead));
                else if(funcType == "log" || funcType == "logten") num = log10(stod(numRead));\
                else if(funcType == "logtwo") num = log(stod(numRead))/log(2);
                else if(funcType == "sqrt") num = sqrt(stod(numRead));
                else if(funcType == "cbrt") num = cbrt(stod(numRead));
                else if(funcType == "sec"){
                    if(!toRad) num = 1/cos(stod(numRead)* M_PI / 180); 
                    else num = 1/cos(stod(numRead));
                }
                else if(funcType == "csc"){
                    if(!toRad) num = 1/sin(stod(numRead)* M_PI / 180); 
                    else num = 1/sin(stod(numRead));
                }
                else if(funcType == "cot"){
                    if(!toRad) num = 1/tan(stod(numRead)* M_PI / 180); 
                    else num = 1/tan(stod(numRead));
                }
                else if(funcType == "asec"){
                    if(stod(numRead)<1){
                        cout << "Wrong operation!" <<endl;
                        return;
                    }
                    else{
                        if(!toRad) num = acos(1/stod(numRead)) * 180 / M_PI;
                        else num = acos(1/stod(numRead));
                    }
                }
                else if(funcType == "acsc"){
                    if(stod(numRead)<1){
                        cout << "Wrong operation!" <<endl;
                        return;
                    }
                    else{
                        if(!toRad) num = asin(1/stod(numRead)) * 180 / M_PI;
                        else num = asin(1/stod(numRead));
                    }
                }
                else if(funcType == "acot"){
                    if(!toRad) num = atan(1/stod(numRead)) * 180 / M_PI;
                    else num = atan(1/stod(numRead));
                }
                s.replace(found,funcType.length(),to_string(num));
            }
        }
        else{
            changeFinished = true;
        }
        found = s.find(funcType,found+1);
    }
}

//filestream
void writeFile(string fileName, vector<storeRes>& solStore){
    ofstream myFile(fileName);
    if(myFile.is_open()){
        for(auto it = 0; it<solStore.size(); ++it){
            myFile << solStore[it].equationInput << " = "<< solStore[it].answer << endl;
        }
        myFile.close();
    }
    else cout << "Error: Unable to write " << fileName <<"!"<<endl;
}

void readFile(string fileName){
    string line;
    ifstream myFileR(fileName);
    if(myFileR.is_open()){
        while(getline(myFileR,line)){
            cout << line << endl;
        }
        myFileR.close();
    }
    else cout << "Error: Unable to read " << fileName <<"!"<<endl;
}

void deleteLine(vector<storeRes>& solStore){
    int lineNo;
    cout << "Which line do you want to remove?: ";
    cin >> lineNo;
    if(lineNo <= solStore.size()){
        solStore.erase(solStore.begin()+lineNo-1);
        cout <<"Deleted line "<<lineNo<<endl;
    }
    else cout << "Failed to delete line " << lineNo <<endl;
}

void restoreData(string fileName, vector <storeRes> & solStore){
    string line;
    string eqn;
    string answer;
    ifstream myFileR(fileName);
    if(!solStore.empty()){
        cout << "The restore cannot be performed!" <<endl;
        return;
    }
    if(myFileR.is_open()){
        while(getline(myFileR,line)){
            cout << line << endl;
            for(int i = 0; i < line.find("=");++i){
                eqn += string(1,line[i]);
            }
            for(int i = line.find("=")+1; i < line.size();++i){
                answer += string(1,line[i]);
            }
            cout << eqn << " = " << answer <<endl;
            solStore.push_back(storeRes(eqn,stod(answer)));
            eqn.clear();
            answer.clear();
        }
        myFileR.close();
    }
    else cout << "Error: Unable to read " << fileName <<"!"<<endl;
}

void readsolStore(vector<storeRes>& solStore){
    for(auto it = 0; it<solStore.size(); ++it){
        cout << solStore[it].equationInput << " = "<< solStore[it].answer << endl;
    }
}

