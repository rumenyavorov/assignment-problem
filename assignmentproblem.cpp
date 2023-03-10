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
/**
 * @brief AssignmentProblem::thirdStep
 * find the only zero(optimal) in row and mark it
 * with '-1', then mark the other zeros(nonoptimal) in the column with '-2'
 * @return
 */
void AssignmentProblem::thirdStep() {

    while(zerosLeft() > 0) {
        int row = findZeroInRow();
        if(row != -1) {
            int col = markOnlyZeroInRow(row);
            if(col != -1) {
                markZerosInColumn(col);
            }
        }
        printMatrix();
        if(zerosLeft() == 0) {
            break;
        }
    }
}

/**
 * @brief AssignmentProblem::subtractFromRow
 * @param row index to subtract from
 * @param smallestElement to subtract from row?
 */
void AssignmentProblem::subtractFromRow(int row, int smallestElement) {
    for(int i = 0; i < agents; i++) {
        matrix[row][i] = matrix[row][i] - smallestElement;
    }
}

/**
 * @brief AssignmentProblem::subtractFromColumn
 * @param col
 * @param smallestElement
 */
void AssignmentProblem::subtractFromColumn(int col, int smallestElement) {
    for(int i = 0; i < tasks; i++) {
        matrix[i][col] = matrix[i][col] - smallestElement;
    }
}

/**
 * @brief AssignmentProblem::findZeroInRow
 * @return find only zero in row
 */
int AssignmentProblem::findZeroInRow() {
    int row = -1;
    for(int i = 0; i < agents; i++) {
        int zeroCounter = 0;

        for(int j = 0; j < tasks; j++) {
            if(matrix[i][j] == 0) {
                zeroCounter++;
            }
        }
        if(zeroCounter == 1) {
            row = i;
        }
    }

    return row;
}

/**
 * @brief AssignmentProblem::markOnlyZeroInRow
 * @param row
 * @return
 */
int AssignmentProblem::markOnlyZeroInRow(int row) {
    int col = -1;

    for(int i = 0; i < agents; i++) {
        if(matrix[row][i] == 0) {
            matrix[row][i] = -1;
            col = i;
        }
    }

    return col;
}

/**
 * @brief AssignmentProblem::markZerosInColumn
 * @param col - which column to mark zeros as nonoptimal
 */
void AssignmentProblem::markZerosInColumn(int col) {
    for(int i = 0; i < tasks; i++) {
        if(matrix[i][col] == 0) {
            matrix[i][col] = -2;
        }
    }
}

/**
 * @brief AssignmentProblem::zerosLeft
 * @return count all zeros left in matrix
 */
int AssignmentProblem::zerosLeft() {

    int zerosLeft = 0;

    for(int i = 0; i < agents; i++) {
        for(int j = 0; j < tasks; j++) {
            if(matrix[i][j] == 0) {
                zerosLeft++;
            }
        }
    }

    return zerosLeft;
}

/**
 * @brief AssignmentProblem::getMatrix
 * @return matrix data
 */
vector<vector<int>> AssignmentProblem::getMatrix() {
    return matrix;
}
