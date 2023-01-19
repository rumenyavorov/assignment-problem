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
    void print();

    int getAgents() const { return agents; }
    int getTasks() const { return tasks; }

    void setAgents(int totalAgents) { this->agents = totalAgents; }
    void setTasks(int totalTasks) { this->tasks = totalTasks; }

    void firstStep();
    int findSmallest(vector<vector<int>> mx_data);

    int findSmallestInRow(int row, vector<vector<int> > data);
private:
    int agents;
    int tasks;
    vector<vector<int>> matrix;
};

#endif // ASSIGNMENTPROBLEM_H
