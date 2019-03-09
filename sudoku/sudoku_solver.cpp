#include <iostream>
#include <set>
#include <cstring>
using namespace std;
typedef set<int> Set;

int indices[81];

int board[81];
bool filled[81];
Set contradict[81];

Set sequence[81];

int start, current;

void init(){
    memset(indices, 0, sizeof(indices));
    memset(board, 0, sizeof(board));
    memset(filled, 0, sizeof(filled));
    start = 0;
    current = 0;
    for (int i = 0; i < 81; ++i) {
        contradict[i] = Set();
        sequence[i] = Set();
    }
}

void input(){
    int i = 0;
    while (i < 81) {
        char c;
        bool eof = !(cin >> c);
        if (eof) {
            exit(0);
        }
        if (c <= '9' && c >= '0') {
            board[i] = c - '0';
            if (c != '0') {
                filled[i] = true;
                sequence[start].insert(int(c - '0'));
                indices[start] = i;
                ++start;
            }
            ++i;
        }else if (c == '\n' || c == ' '){
            continue;
        }else{
            exit(0);
        }
    }
    current = start;
}

bool pre_check(){
    int i, j, k;
    for (i = 0; i < start; ++i) {
        int pos = indices[i];
        int num = board[pos];
        
        int x = pos % 9;
        int y = pos / 9;
        
        for (j = x; j < 81; j += 9) {
            if (j != pos && filled[j] && board[j] == num) {
                return false;
            }
        }
        for (j = 9 * y; j < 9 * y + 9; ++j) {
            if (j != pos && filled[j] && board[j] == num) {
                return false;
            }
        }
        
        int block_x = (x / 3) * 3;
        int block_y = (y / 3) * 3;
        
        for (j = block_x; j < block_x + 3; ++j) {
            for (k = block_y; k < block_y + 3; ++k) {
                int position = 9 * k + j;
                if (position != pos && filled[position] && board[position] == num) {
                    return false;
                }
            }
        }
    }
    
    return true;
}

void opt(){
    for (int i = 0; i < 81; ++i) {
        contradict[i] = Set();
    }
    
    int i, j, k;
    for (i = 0; i < current; ++i) {
        int pos = indices[i];
        int num = board[pos];
        
        int x = pos % 9;
        int y = pos / 9;
        
        for (j = x; j < 81; j += 9) {
            if (!filled[j]) {
                contradict[j].insert(num);
            }
        }
        for (j = 9 * y; j < 9 * y + 9; ++j) {
            if (!filled[j]) {
                contradict[j].insert(num);
            }
        }
        
        int block_x = (x / 3) * 3;
        int block_y = (y / 3) * 3;
        
        for (j = block_x; j < block_x + 3; ++j) {
            for (k = block_y; k < block_y + 3; ++k) {
                int position = 9 * k + j;
                if (!filled[position]) {
                    contradict[position].insert(num);
                }
            }
        }
    }
    
}

void output(){
    int j;
    for (j = 0; j < 81; ++j) {
        cout << char(board[j] + '0');
        if ( j % 9 == 8) {
            cout << "\n";
        }
    }
}

int main(int argc, const char * argv[]) {
Restart:
    while (true) {
        init();
        input();
        if (!pre_check()) {
            cout << "impossible\n\n";
            goto Restart;
        }
    Outer:
        while (current != 81) {
            opt();
            int max = -1;
            int index = -1;
            int j;
            for (j = 0; j < 81; ++j) {
                if (!filled[j]) {
                    int size = (int)contradict[j].size();
                    if (size == 9) {
                    Loop:
                        --current;
                        
                        if (current < start) {
                            cout << "impossible\n\n";
                            goto Restart;
                        }
                        
                        Set & set = sequence[current];
                        board[indices[current]] = 0;
                        
                        set.erase(set.begin());
                        if (!set.empty()) {
                            board[indices[current]] = *set.begin();
                            ++current;
                            goto Outer;
                        }else{
                            filled[indices[current]] = false;
                            indices[current] = 0;
                            goto Loop;
                        }
                        
                    }else if (max < size){
                        max = size;
                        index = j;
                    }
                }
            }
            
            if (index == -1) {
                cout << "impossible\n\n";
                goto Restart;
            }
            
            Set & set = contradict[index];
            for (j = 1; j <= 9; ++j) {
                if (set.find(j) == set.end()) {
                    sequence[current].insert(j);
                }
            }
            
            board[index] = *sequence[current].begin();
            indices[current] = index;
            filled[index] = true;
            
            ++current;
            
        }
        
        output();
        cout << endl;
    }
    
    return 0;
}
