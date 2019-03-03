#include <iostream>
#include <bitset>
using namespace std;
#define CAPCITY (400000)

/*
 * this program solves the 8 puzzle.
 * given a 3 * 3 board. each grid contains a unique number in 0~8.
 * you can swap 0 with its neighbor grid in four directions. (up, down, left, right)
 *
 * can you get the board below?
 * 1 2 3
 * 4 5 6
 * 7 8 0
 *
 * if impossible, print "impossible" to the standard output file.
 *
 * derived from problem 1077 on poj (link: http://poj.org/problem?id=1077 )
 */

/*
 * 876543210_9 = 381367044_10
 *
 */

int base[9] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

/*
 * eq to
 * struct Node {
 *      bool visited;
 *      int state;
 *      Node * parent;
 * };
 * not using struct saves much space.
 *
 */
bitset<876543211> visited;

int queue_parent[CAPCITY]; // the index of parent in queue_state.

int queue_state[CAPCITY];

int head, tail;

int arrangement(int state){
    int a[9];
    int i = 0;
    while (state) {
        a[i] = state % 10;
        state /= 10;
        ++i;
    }
    int j;
    int ans = 0;
    for (i = 0; i < 9; ++i) {
        for (j = i + 1; j < 9; ++j) {
            if (a[i] > a[j]) {
                ++ans;
            }
        }
    }
    return ans;
}

int find_zero_pos(int state){
    int i;
    for (i = 0; i < 10; ++i) {
        if (state % 10) {
            state /= 10;
        }else{
            return i;
        }
    }
    cerr << "state does not contain zero\n";
    exit(EXIT_FAILURE);
}

int get_i(int & state, int i){
    int high = state / base[i];
    return high % 10;
}

void set_i(int & state, int i, int num){
    int high = state / base[i];
    int low = state % base[i];
    high = (high / 10) * 10 + num;
    state = high * base[i] + low;
}

void move_up(int state, int zero_index){
    
    if (zero_index < 6) {
        int num = get_i(state, zero_index + 3);
        set_i(state, zero_index + 3, 0);
        set_i(state, zero_index, num);
    }else{
        return;
    }
    
    queue_state[tail] = state;
    queue_parent[tail] = head;
    ++tail;
    assert(tail < CAPCITY);
}
void move_down(int state, int zero_index){
    
    if (zero_index > 2) {
        int num = get_i(state, zero_index - 3);
        set_i(state, zero_index - 3, 0);
        set_i(state, zero_index, num);
    }else{
        return;
    }
    
    queue_state[tail] = state;
    queue_parent[tail] = head;
    ++tail;
    assert(tail < CAPCITY);
}
void move_left(int state, int zero_index){
    
    if (zero_index < 8) {
        int num = get_i(state, zero_index + 1);
        set_i(state, zero_index + 1, 0);
        set_i(state, zero_index, num);
    }else{
        return;
    }
    
    queue_state[tail] = state;
    queue_parent[tail] = head;
    ++tail;
    assert(tail < CAPCITY);
}
void move_right(int state, int zero_index){
    
    if (zero_index > 0) {
        int num = get_i(state, zero_index - 1);
        set_i(state, zero_index - 1, 0);
        set_i(state, zero_index, num);
    }else{
        return;
    }
    
    queue_state[tail] = state;
    queue_parent[tail] = head;
    ++tail;
    assert(tail < CAPCITY);
}

inline bool done(int state){
    return state == 123456780;
}

void output(int state){
    
    int a[9];
    int i = 0;
    while (i < 9) {
        a[i] = state % 10;
        state /= 10;
        ++i;
    }
    for (i = 8; i >= 0; --i) {
        cout << a[i];
        if (i % 3 == 0) {
            cout << '\n';
        }else{
            cout << ' ';
        }
    }
    cout << "-----\n";
}

int main() {
    
    int i;
    int state = 0;
    for (i = 0; i < 9; ++i) {
        int num;
        cin >> num;
        if (num >= 0 && num <= 9) {
            
        }else{
            cerr << "synax error\n";
            return 0;
        }
        
        state = 10 * state + num;
    }
    
    // the arrangement number of the initial state and 123456780 has different parity. so it's impossible to get 123456780.
    if ((arrangement(state) & 1) != (arrangement(123456780) & 1)) {
        cout << "impossible\n";
        return 0;
    }
    
    head = 0;
    queue_state[0] = state;
    queue_parent[0] = -1;
    visited[0] = 0;
    tail = 1;
    
    while (head != tail) {
        int state = queue_state[head];
        
        if (visited[state]) {
            ++head;
            continue;
        }
        
        if (done(state)) {
            cout << "done\n";
            break;
        }
        
        int index = find_zero_pos(state);
        
        move_up(state, index);
        move_down(state, index);
        move_left(state, index);
        move_right(state, index);
        
        visited[state] = true;
        ++head;
    }
    
    // output in reversed order. To get the normal order, simply store them in an array
    while (head != -1) {
        output(queue_state[head]);
        head = queue_parent[head];
    }
    
    return 0;
}

