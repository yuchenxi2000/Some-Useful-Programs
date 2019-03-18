#include <iostream>
#include <cstring>
using namespace std;
inline void out_char(unsigned char c){
    if (c >= 33 && c <= 126) {
        cout << c;
    }else if (c == 32){ // space
        cout << "\\space ";
    }else if (c == 10){
        cout << "\\n\n";
    }else if (c == 11){
        cout << "\\t ";
    }else if (c == 12){
        cout << "\\lf" << char(12);
    }else{
        cout << "\\" << int(c) << ' ';
    }
}

int main(int argc, const char * argv[]) {
    if (argc == 1) {
        cout << "usage:\nthis program displays the invisible character in file\' content.\nfile name should be the 2nd argument\n";
        return 0;
    }else if (argc == 2){
        if (strcmp(argv[0], "-h") == 0) {
            cout << "usage:\nthis program displays the invisible character in file\' content.\nfile name should be the 2nd argument\n";
            return 0;
        }
    }else{
        cerr << "unexpected argument. use -h for help.\n";
        return 1;
    }
    FILE * fp = fopen(argv[1], "rb");
    
    if (fp == NULL) {
        cout << "failed to open file1" << endl;
        return 1;
    }
    
    unsigned char buf[128];
    
    memset(buf, 0, sizeof(buf));
    
    while (true) {
        
        size_t size = fread(buf, sizeof(unsigned char), 128, fp);
        
        if (size == 0) { // EOF
            return 0;
        }
        
        int i;
        for (i = 0; i < size; ++i) {
            out_char(buf[i]);
        }
        
    }
    
    return 0;
}
