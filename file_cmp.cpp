#include <iostream>
#include <cstring>
using namespace std;
int main(int argc, const char * argv[]) {
    if (argc == 1) {
        cout << "usage:\nthis program compares two files\' content.\nfile name should be the 2nd and 3rd argument\n";
        return 0;
    }else if (argc == 2){
        if (strcmp(argv[0], "-h") == 0) {
            cout << "usage:\nthis program compares two files\' content.\nfile name should be the 2nd and 3rd argument\n";
            return 0;
        }else{
            cerr << "unexpected argument. use -h for help.\n";
            return 1;
        }
    }else if (argc != 3){
        cerr << "unexpected argument. use -h for help.\n";
        return 1;
    }
    FILE * fp1 = fopen(argv[1], "rb");
    FILE * fp2 = fopen(argv[2], "rb");
    
    if (fp1 == NULL || fp2 == NULL) {
        if (fp1 == NULL) {
            cout << "failed to open file1" << endl;
        }
        if (fp2 == NULL) {
            cout << "failed to open file2" << endl;
        }
        return 1;
    }
    
    unsigned char buf1[128];
    unsigned char buf2[128];
    
    memset(buf1, 0, sizeof(buf1));
    memset(buf2, 0, sizeof(buf2));
    
    int line = 1;
    
    int position = 1;
    
    while (true) {
        
        size_t size1 = fread(buf1, sizeof(unsigned char), 128, fp1);
        size_t size2 = fread(buf2, sizeof(unsigned char), 128, fp2);
        
        if (size1 == 0 || size2 == 0) { // EOF
            if (size1 == 0 && size2 == 0) {
                cout << "contents are the same" << endl;
            }else{
                cout << "different at line " << line << ", position " << position << ":\n";
                if (size1 != 0) {
                    cout << "file1: (char)" << int(buf1[0]) << endl;
                }else{
                    cout << "file1: EOF" << endl;
                }
                if (size2 != 0) {
                    cout << "file2: (char)" << int(buf2[0]) << endl;
                }else{
                    cout << "file2: EOF" << endl;
                }
            }
            return 0;
        }
        
        int i;
        for (i = 0; i < size1 && i < size2; ++i) {
            if (buf1[i] == buf2[i]) {
                if (buf1[i] == '\n') {
                    position = 1;
                    ++line;
                }else{
                    ++position;
                }
            }else{
                cout << "different at line " << line << ", position " << position << ":\n";
                cout << "file1: (char)" << int(buf1[i]) << endl;
                cout << "file2: (char)" << int(buf2[i]) << endl;
                return 0;
            }
        }
        
        if (size1 == i && size2 > i) { // file 1 EOF
            cout << "different at line " << line << ", position " << position << ":\n";
            cout << "file1: EOF" << endl;
            cout << "file2: (char)" << int(buf2[size1]) << endl;
            return 0;
        }else if (size2 == i && size1 > i) { // file 2 EOF
            cout << "different at line " << line << ", position " << position << ":\n";
            cout << "file1: (char)" << int(buf1[size2]) << endl;
            cout << "file2: EOF" << endl;
            return 0;
        }
        
    }
    
    return 0;
}
