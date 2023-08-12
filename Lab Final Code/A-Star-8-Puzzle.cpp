#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

const int N = 3; // 3x3 puzzle
const int INF = 1e9;

struct State {
    vector<vector<int>> board;
    int cost, heuristic, row, col;

    State(vector<vector<int>>& b, int c, int r, int cl) : board(b), cost(c), row(r), col(cl) {
        heuristic = calculateHeuristic();
    }

    int calculateHeuristic() {
        int h = 0;
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                if (board[i][j] != 0)
                    h += abs(i - (board[i][j] - 1) / N) + abs(j - (board[i][j] - 1) % N);
        return h;
    }

    bool isGoal() {
        vector<vector<int>> goal = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};
        return board == goal;
    }

    bool operator<(const State& other) const {
        return cost + heuristic > other.cost + other.heuristic; // Priority Queue will pop lowest f value
    }
};

bool isValid(int row, int col) {
    return (row >= 0 && row < N && col >= 0 && col < N);
}

vector<State> getNeighbors(State& current) {
    vector<State> neighbors;

    int dr[] = {-1, 0, 1, 0};
    int dc[] = {0, 1, 0, -1};

    for (int d = 0; d < 4; ++d) {
        int newRow = current.row + dr[d];
        int newCol = current.col + dc[d];

        if (isValid(newRow, newCol)) {
            vector<vector<int>> newBoard = current.board;
            swap(newBoard[current.row][current.col], newBoard[newRow][newCol]);
            neighbors.push_back(State(newBoard, current.cost + 1, newRow, newCol));
        }
    }

    return neighbors;
}

void printBoard(const vector<vector<int>>& board) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int solveAStar(State start) {
    priority_queue<State> pq;
    pq.push(start);

    map<vector<vector<int>>, int> visited;
    visited[start.board] = 1;

    while (!pq.empty()) {
        State current = pq.top();
        pq.pop();

        if (current.isGoal())
            return current.cost;

        vector<State> neighbors = getNeighbors(current);
        for (State neighbor : neighbors) {
            if (visited.find(neighbor.board) == visited.end() || neighbor.cost < visited[neighbor.board]) {
                visited[neighbor.board] = neighbor.cost;
                pq.push(neighbor);

                // Print the puzzle configuration after each step
                cout << "After " << neighbor.cost << " move(s):" << endl;
                printBoard(neighbor.board);
                cout << endl;
            }
        }
    }

    return -1; // Solution not found
}

int main() {
    vector<vector<int>> initialBoard(N, vector<int>(N));
    int startRow, startCol;

    cout << "Enter the initial puzzle configuration (0 for empty cell):" << endl;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> initialBoard[i][j];
            if (initialBoard[i][j] == 0) {
                startRow = i;
                startCol = j;
            }
        }
    }

    State startState(initialBoard, 0, startRow, startCol);
    int moves = solveAStar(startState);

    if (moves == -1) {
        cout << "Solution not found!" << endl;
    } else {
        cout << "Minimum number of moves: " << moves << endl;
    }

    return 0;
}


/*
Enter the initial puzzle configuration (0 for empty cell):
1 2 3
8 5 6
4 7 0
After 1 move(s):
1 2 3 
8 5 0 
4 7 6 

After 1 move(s):
1 2 3 
8 5 6 
4 0 7 

After 2 move(s):
1 2 0
8 5 3
4 7 6

After 2 move(s):
1 2 3
8 0 5
4 7 6

After 2 move(s):
1 2 3
8 0 6
4 5 7

After 2 move(s):
1 2 3 
8 5 6
0 4 7

After 3 move(s):
1 0 2
8 5 3
4 7 6

After 3 move(s):
1 0 3
8 2 6
4 5 7

After 3 move(s):
1 2 3
8 6 0
4 5 7

After 3 move(s):
1 2 3
0 8 6
4 5 7

After 3 move(s):
1 2 3
0 5 6
8 4 7 

After 4 move(s):
0 2 3
1 8 6
4 5 7

After 4 move(s):
1 2 3
4 8 6
0 5 7

After 4 move(s):
0 2 3
1 5 6
8 4 7

After 4 move(s):
1 2 3
5 0 6
8 4 7

After 5 move(s):
1 2 3
4 8 6
5 0 7

After 3 move(s):
1 0 3
8 2 5
4 7 6

After 3 move(s):
1 2 3
8 7 5
4 0 6

After 3 move(s):
1 2 3
0 8 5
4 7 6

After 4 move(s):
0 2 3
1 8 5
4 7 6

After 4 move(s):
1 2 3 
4 8 5
0 7 6

After 5 move(s):
1 2 3
4 8 5
7 0 6

After 6 move(s):
1 2 3
4 0 5
7 8 6 

After 6 move(s):
1 2 3
4 8 5
7 6 0

After 7 move(s):
1 0 3
4 2 5
7 8 6

After 7 move(s):
1 2 3
4 5 0
7 8 6

After 7 move(s):
1 2 3
0 4 5
7 8 6

After 8 move(s):
1 2 0
4 5 3
7 8 6

After 8 move(s):
1 2 3
4 5 6
7 8 0

Minimum number of moves: 8
*/