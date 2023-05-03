#include <iostream>
using namespace std;

const int N = 4; // size of maze
const int destX = N - 1,  destY = N - 1; // setting destination position of the rat

int maxWeight = -1; // to keep track of longest path weight

bool solutionFound = false; // to check if solution exists or not

void printSolution(int soln[N][N]) { // To print the output (solution) matrix
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << soln[i][j] << " ";
        }
        cout << endl;
    }
}

void solveMaze(int maze[N][N], int output[N][N], int ratX, int ratY, int currWeight) {
    if (ratX >= N || ratY >= N || ratX < 0 || ratY < 0) { // This is to avoid position of rat to become out of the matrix
        return;
    }

    if (maze[ratX][ratY] == 0) { // 0 at any cell of maze represents the dead-end, so return.
        return;
    }

    if (output[ratX][ratY] == 1) { // This means this cell was already visited. And visiting it again and again causes infinite recursion resulting segmentation fault.
        return;
    }

    output[ratX][ratY] = 1; // marking the current position as already visited to avoid unnecessary recursion.

    if (destX == ratX && destY == ratY) { // Cheking if the rat reached the destionation.
        if (currWeight > maxWeight) { // Updating the longest weight.
            maxWeight = currWeight;
        }

        solutionFound = true;

        printSolution(output);

        cout << "Weight of longest path is " << maxWeight << endl;
        
        return;
    }

    // Making recursive calls for all possible jumps from the current position
    for (int i = 1; i <= maze[ratX][ratY]; i++) {
        solveMaze(maze, output, ratX - i, ratY, currWeight + i); // Moving towards left
        solveMaze(maze, output, ratX + i, ratY, currWeight + i); // Moving towards right
        solveMaze(maze, output, ratX, ratY - i, currWeight + i); // Moving towards top
        solveMaze(maze, output, ratX, ratY + i, currWeight + i); // Moving towards bottom
    }

    // Unmark the current cell as part of the path
    output[ratX][ratY] = 0;
}

int main() {
    int maze[N][N] = {
        {1, 3, 2, 0},
        {3, 2, 0, 1},
        {1, 5, 2, 0},
        {0, 1, 3, 4}
    };
    // The 2D array maze represents blocks of maze containing maximum number of jumps that a rat can make.

    int solutionMatrix[N][N] = {0};
    // solution matrix initially filled with 0

    solveMaze(maze, solutionMatrix, 0, 0, 0);

    if (!solutionFound) {
        cout << "Solution not found" << endl;
    }

    return 0;
}