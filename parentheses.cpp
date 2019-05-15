#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<string> vec;
void genHeses(int a, int b, string s) {
    if (a > 0) genHeses(a - 1, b, s + '(');
    if (a < b) genHeses(a, b - 1, s + ')');
    if (a == 0 && b == 0) vec.push_back(s);
}

/*
 * generate all parentheses with n '(' and n ')'
 */
int main(){
    genHeses(3, 3, string());
    for (auto & s : vec)
        cout << s << endl;
}
