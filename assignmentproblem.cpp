#include "assignmentproblem.h"
#include <QDebug>
#include <VisualizeProblem.h>
#include <iostream>

using namespace std;

AssignmentProblem::AssignmentProblem()
{

}

AssignmentProblem::AssignmentProblem(int rows, int cols) : agents(rows), tasks(cols), matrix(agents, vector<int>(tasks)){}

AssignmentProblem::~AssignmentProblem(){}

int AssignmentProblem::at(int row, int col) const {
//    if(row < 0 || col > 0) {
//        throw out_of_range("Index out of range");
//    }
    return matrix[row][col];
}

/**
 * @brief AssignmentProblem::set
 * @param row
 * @param col
 * @param value
 */
void AssignmentProblem::set(int row, int col, int value) {
//    if(row < 0 || col > 0) {
//        throw out_of_range("Index out of range");
//    }
    matrix[row][col] = value;
}

/**
 * @brief AssignmentProblem::print
 * print the 2D array in "matrix" like format
 */
void AssignmentProblem::printMatrix() {
    qInfo() << QString("Matrix[%1][%2]").arg(agents).arg(tasks);
    for(int i = 0; i < agents; i++) {
        for(int j = 0; j < tasks; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-----------------------------" << endl;
}

void AssignmentProblem::startAlgorithm() {
    firstStep();
}

/**
 * @brief AssignmentProblem::findSmallestInRow
 *  return smallest element in row
 * @param row - row to search for smallest value
 * @param data - matrix data
 * @return
 */
int AssignmentProblem::findSmallestInRow(int row, vector<vector<int>> data) {
    //set first element so we can compare to others
    int leastElement = data[row][0];
    for(int i = 0; i < tasks; i++) {
        if(data[row][i] < leastElement) {
            leastElement = data[row][i];
        }
    }

    return leastElement;
}

int AssignmentProblem::findSmallestInColumn(int column, vector<vector<int>> data) {
    //set first element so we can compare to others
    int leastElement = data[0][column];
    for(int i = 0; i < tasks; i++) {
        if(data[i][column] < leastElement) {
            leastElement = data[i][column];
        }
    }

    return leastElement;
}

void printVector(vector<int> data) {
    for(int e : data) {
        qInfo() << e;
    }
}


/**
 * @brief AssignmentProblem::firstStep
 * first step of the algorithm
 * find lowest element in each row
 * and subtract it from all elements of that row
 */
void AssignmentProblem::firstStep() {

    vector<int> smallestElements;
    for(int i = 0; i < agents; i++) {
        int smallestElement = findSmallestInRow(i, matrix);
        smallestElements.push_back(smallestElement);
        subtractFromRow(i, smallestElement);
    }

}

/**
 * @brief AssignmentProblem::secondStep
 * second step
 * find lowest element in each column
 * and subtract it from all elements of that column
 */
void AssignmentProblem::secondStep() {
    vector<int> smallestElements;
    for(int i = 0; i < tasks; i++) {
        int smallestElement = findSmallestInColumn(i, matrix);
        smallestElements.push_back(smallestElement);
        subtractFromColumn(i, smallestElement);
    }
}

void AssignmentProblem::subtractFromRow(int row, int smallestElement) {
    for(int i = 0; i < agents; i++) {
        matrix[row][i] = matrix[row][i] - smallestElement;
    }
}

void AssignmentProblem::subtractFromColumn(int col, int smallestElement) {
    for(int i = 0; i < tasks; i++) {
        matrix[i][col] = matrix[i][col] - smallestElement;
    }
}

vector<vector<int>> AssignmentProblem::getMatrix() {
    return matrix;
}
