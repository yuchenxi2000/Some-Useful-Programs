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
    FILE * fp1 = fopen(argv[1], "r");
    FILE * fp2 = fopen(argv[2], "r");
    
    char buf1[128];
    char buf2[128];
    
    memset(buf1, 0, sizeof(buf1));
    memset(buf2, 0, sizeof(buf2));
    
    int line = 1;
    
    int position = 1;
    
    while (true) {
        char * p1 = fgets(buf1, 128, fp1);
        char * p2 = fgets(buf2, 128, fp2);
        
        if (p1 == 0 || p2 == 0) { // EOF
            if (p1 == 0 && p2 == 0) {
                cout << "contents are the same" << endl;
            }else{
                cout << "different at line " << line << ", position " << position << ":\n";
                if (p1 != 0) {
                    cout << "file1: (char)" << int(buf1[0]) << endl;
                }else{
                    cout << "file1: EOF" << endl;
                }
                if (p2 != 0) {
                    cout << "file2: (char)" << int(buf2[0]) << endl;
                }else{
                    cout << "file2: EOF" << endl;
                }
            }
            return 0;
        }
        
        for (int i = 0; i < 128; ++i) {
            if (buf1[i] == buf2[i]) {
                if (buf1[i] == 0) {
                    break;
                }else if (buf1[i] == '\n') {
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
    }
    
    return 0;
}
