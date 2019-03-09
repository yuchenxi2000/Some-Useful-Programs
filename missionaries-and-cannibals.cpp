#include <iostream>
#include <queue>
#include <bitset>
using namespace std;
#define CAPCITY (400000)
#define LEFT (1)
#define RIGHT (0)
struct State;

typedef queue<State> Queue;

int M, N;

//
// state: (3, 3, 1)
// left 3 Ms, 3 Cs, with a boat.
// (3, 3, 1) -> (3, 1, 0) : ship 2 Cs to right.
//

//
// M <= 1000, N <= 100
// 10 bit, 10 bit, 1 bit
// 21 -> int
// 2^21 : hash set
//

bitset<6002> visit; // 0, c: c; m, 0: m + M; i, i: i + 2 * M.

struct State {
    int M, C;
    bool boat;
    int depth;
    
    State() {}
    
    void operator() (int m, int c, bool b) {
        M = m;
        C = c;
        boat = b;
    }
    
    State(int m, int c, bool b, int depth) : M(m), C(c), boat(b), depth(depth) {}
};

inline bool done(int m, int c){
    return m == 0 && c == 0;
}

inline bool done(State & state){
    return state.M == 0 && state.C == 0;
}

inline bool valid_state(int m, int c, bool b){ // M = m > c >= 0 , 0 = m < c <= M , m = c
    if (m < 0 || c < 0 || m > M || c > M) {
        return false;
    }
    return (m >= c || m == 0) && (m <= c || m == M);
}

Queue state_queue;

inline bool visited(int m, int c, bool b){
    if (m == 0) {
        return visit[(c << 1) - b];
    }else if (m == M){
        return visit[((c + M) << 1) - b];
    }else{
        return visit[((m + (M << 1)) << 1) - b];
    }
    
}

void set_visited(int m, int c, int b){
    if (m == 0) {
        visit[(c << 1) - b] = true;
    }else if (m == M){
        visit[((c + M) << 1) - b] = true;
    }else{
        visit[((m + (M << 1)) << 1) - b] = true;
    }
}

void set_visited(State state){
    set_visited(state.M, state.C, state.boat);
}

void bfs(){
    state_queue.push(State(M, M, LEFT, 0));
    set_visited(M, M, LEFT);
    while (!state_queue.empty()) {
        State & state = state_queue.front();
        
        if (done(state)) {
            cout << state.depth << endl;
            return;
        }
        
        int m = state.M;
        int c = state.C;
        int b = state.boat;
        int depth = state.depth;
        
        if (b == LEFT) {
            int i, j; // i : M on boat; j : C on boat
            for (j = 0; j <= N / 2; ++j) {
                for (i = j; i <= N; ++i) {
                    if (i + j == 0) {
                        
                    }else if (i + j <= N) {
                        if (valid_state(m - i, c - j, RIGHT) && !visited(m - i, c - j, RIGHT)) {
                            state_queue.push(State(m - i, c - j, RIGHT, depth + 1));
                            set_visited(m - i, c - j, RIGHT);
                        }
                    }
                }
            }
            for (j = 1; j <= N; ++j) {
                if (valid_state(m, c - j, RIGHT) && !visited(m, c - j, RIGHT)) {
                    state_queue.push(State(m, c - j, RIGHT, depth + 1));
                    set_visited(m, c - j, RIGHT);
                }
            }
            
        }else{
            int i, j; // i : M on boat; j : C on boat
            for (j = 0; j <= N / 2; ++j) {
                for (i = j; i <= N; ++i) {
                    if (i + j == 0) {
                        continue;
                    }else if (i + j <= N) {
                        if (valid_state(m + i, c + j, LEFT) && !visited(m + i, c + j, LEFT)) {
                            state_queue.push(State(m + i, c + j, LEFT, depth + 1));
                            set_visited(m + i, c + j, LEFT);
                        }
                    }
                }
            }
            for (j = 1; j <= N; ++j) {
                if (valid_state(m, c + j, LEFT) && !visited(m, c + j, LEFT)) {
                    state_queue.push(State(m, c + j, LEFT, depth + 1));
                    set_visited(m, c + j, LEFT);
                }
            }
        }
        
        state_queue.pop();
    }
    cout << -1 << endl;
}

int main(int argc, const char * argv[]) {
    cin >> M >> N;
    bfs();
    return 0;
}
