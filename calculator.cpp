#include <iostream>
#include <stack>
#include <cmath>
using namespace std;
typedef stack<double> Stack_double;
typedef stack<char> Stack_char;

Stack_char op;
Stack_double num;

bool less_op(char op1, char op2){ // priority: op1 < op2
    if (op1 == '+' && op2 == '*') {
        return true;
    }else if (op1 == '-' && op2 == '*'){
        return true;
    }else if (op1 == '+' && op2 == '/'){
        return true;
    }else if (op1 == '-' && op2 == '/'){
        return true;
    }else if (op1 == '+' && op2 == '^'){
        return true;
    }else if (op1 == '-' && op2 == '^'){
        return true;
    }else if (op1 == '*' && op2 == '^'){
        return true;
    }else if (op1 == '/' && op2 == '^'){
        return true;
    }else{
        return false;
    }
}

double calculate(double x, double y, char op){
    switch (op) {
        case '+':
            return x + y;
            
        case '-':
            return x - y;
            
        case '*':
            return x * y;
            
        case '/':
            if (y == 0) {
                throw "divided by zero\n";
            }
            return x / y;
            
        case '^':
            if (x == 0) {
                throw "base is zero\n";
            }
            return pow(x, y);
            
        default:
            throw "unknown operator\n";
    }
}

void pop_empty();

void op_handler(char c){
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
        cin.get();
        if (op.empty() || less_op(op.top(), c) || op.top() == '(') {
            op.push(c);
        }else{
            
            while (!op.empty() && !less_op(op.top(), c) && op.top() != '(') {
                if (num.empty()) {
                    throw "missing number\n";
                }
                double y = num.top();
                num.pop();
                
                if (num.empty()) {
                    throw "missing number\n";
                }
                double x = num.top();
                num.pop();
                
                x = calculate(x, y, op.top());
                
                num.push(x);
                op.pop();
            }
            
            op.push(c);
        }
    }else{
        cin.get();
        throw "unknown operator\n";
    }
}

void pop_left_hese();

void pop_empty(){ // TODO
    while (!op.empty()) {
        char c = op.top();
        op.pop();
        
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            if (num.empty()) {
                throw "missing number\n";
            }
            double y = num.top();
            num.pop();
            if (num.empty()) {
                throw "missing number\n";
            }
            double x = num.top();
            num.pop();
            
            x = calculate(x, y, c);
            
            num.push(x);
        }else if (c == '('){
            op.push('(');
            return;
        }else if (c == ')'){
            pop_left_hese();
        }
    }
}

void pop_left_hese(){
    while (!op.empty()) {
        char c = op.top();
        op.pop();
        
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            if (num.empty()) {
                throw "missing number\n";
            }
            double y = num.top();
            num.pop();
            if (num.empty()) {
                throw "missing number\n";
            }
            double x = num.top();
            num.pop();
            
            x = calculate(x, y, c);
            
            num.push(x);
        }else if (c == '('){
            return;
        }else if (c == ')'){
            pop_left_hese();
        }
    }
    
    throw "missing left heses\n";
}

int main() {
    cout << "calculator v0.1\nauthor: yuchenxi\ntype ctrl+D to leave.\nsupported operator: + - * / ^" << endl;
    
Loop:
    op = Stack_char();
    num = Stack_double();
    try {
        bool left_hese = false;
        while (true) {
            int c = cin.peek();
            if (c == EOF) {
                return 0;
            }
            if (c == '\n') {
                cin.get();
                break;
            }
            if ((c <= '9' && c >= '0') || c == '.' || ((c == '-' || c == '+') && (num.empty() || left_hese))) {
                double x;
                cin >> x;
                if (cin.fail()) {
                    cin.clear();
                    throw "number syntax error\n";
                }
                num.push(x);
                left_hese = false;
            }else if (c == ' '){
                cin.get();
                continue;
            }else if (c == '('){
                cin.get();
                op.push(char(c));
                left_hese = true;
            }else if (c == ')'){
                cin.get();
                pop_left_hese();
            }else{
                op_handler(char(c));
            }
        }
        
        pop_empty();
        if (!op.empty() && op.top() == '(') {
            throw "missing right heses\n";
        }
        if (num.empty()) {
            goto Loop;
        }
        if (num.size() > 1) {
            throw "missing operator\n";
        }
        cout << num.top() << endl;
    } catch (const char * e) {
        cerr << e;
        if (strcmp(e, "missing right heses\n") == 0 || strcmp(e, "missing operator\n") == 0) {
            
        }else{
            cin.ignore(numeric_limits<std::streamsize>::max(),'\n');
        }
        goto Loop; // goto makes the program simple. (actually, it's just sth about lazyness...)
    }
    goto Loop;
    
    return 0;
}
