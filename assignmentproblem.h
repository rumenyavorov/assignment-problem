#ifndef ASSIGNMENTPROBLEM_H
#define ASSIGNMENTPROBLEM_H

#include <vector>

using namespace std;

class AssignmentProblem
{
public:
    AssignmentProblem();
    AssignmentProblem(int row, int col);
    ~AssignmentProblem();


    int at(int row, int col) const;
    void set(int row, int col, int value);
    void printMatrix();

    int getAgents() const { return agents; }
    int getTasks() const { return tasks; }

    void setAgents(int totalAgents) { this->agents = totalAgents; }
    void setTasks(int totalTasks) { this->tasks = totalTasks; }

    void firstStep();
    void secondStep();

    int findSmallest(vector<vector<int>> mx_data);
    int findSmallestInRow(int row, vector<vector<int> > data);
    int findSmallestInColumn(int column, vector<vector<int> > data);

    void subtractFromRow(int row, int smallestElements);
    void subtractFromColumn(int col, int smallestElement);

    void startAlgorithm();

    vector<vector<int>> getMatrix();

    void setMatrixData(vector<vector<int>> mx_data) {
        matrix = mx_data;
    }
private:
    int agents;
    int tasks;
    vector<vector<int>> matrix;
};

#endif // ASSIGNMENTPROBLEM_H
