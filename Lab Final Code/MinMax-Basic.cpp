#include <iostream>
#include <algorithm>

int minimax(int values[], int depth, int index, bool isMaximizer) {
    if (depth == 0 || index >= 8) {
        return values[index];
    }

    if (!isMaximizer) { // Modified condition
        int minEval = std::numeric_limits<int>::max();
        for (int i = 0; i < 2; ++i) {
            int eval = minimax(values, depth - 1, index * 2 + i, true); // Flipped isMaximizer to true
            minEval = std::min(minEval, eval);
        }
        return minEval;
    } else {
        int maxEval = std::numeric_limits<int>::min();
        for (int i = 0; i < 2; ++i) {
            int eval = minimax(values, depth - 1, index * 2 + i, false); // Flipped isMaximizer to false
            maxEval = std::max(maxEval, eval);
        }
        return maxEval;
    }
}

int main() {
    // int values[] = {3, 5, 6, 9, 1, 2, 0, -1};
    // int depth = 3; // Depth of the Minimax search tree

    int values[] = {10,5,7,11,12,8,9,8,5,12,11,12,9,8,7,10};
    int depth = 5; 

    int optimalValue = minimax(values, depth, 0, false); // Start with minimizer playing first
    std::cout << "Optimal value: " << optimalValue << std::endl;

    return 0;
}
