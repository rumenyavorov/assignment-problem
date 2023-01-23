#ifndef VISUALIZEPROBLEM_H
#define VISUALIZEPROBLEM_H

#include <QWidget>
#include <QGridLayout>
#include <QTextEdit>
#include <QTableWidget>
#include <QPushButton>
#include <vector>
#include <AssignmentProblem.h>

using namespace std;

namespace Ui {
class VisualizeProblem;
}

class VisualizeProblem : public QWidget
{
    Q_OBJECT

public:
    explicit VisualizeProblem(int agents, QWidget *parent = nullptr);
    ~VisualizeProblem();

    void updateTable();

    void updateTable(int agents, int tasks, vector<vector<int> > matrix);
    AssignmentProblem *ap;

    void graph();
private slots:
    void initSubmitButton();
    void submitProblemHandler();

    void initFirstStepButton();
    void firstStepBtnHandler();
    void initSecondStepButton();
    void secondStepBtnHandler();
//    void initThirthStepButton();
//    void thirthStepBtnHandler();
//    void initFourthStepButton();
//    void fourthStepBtnHandler();

private:
    Ui::VisualizeProblem *ui;

    QGridLayout *problemGrid;
    QTableWidget *tableGrid;
    QPushButton *submitBtn;
    QPushButton *firstStepBtn;
    QPushButton *secondStepBtn;
//    QPushButton *thirthStepBtn;
//    QPushButton *fourthStepBtn;

    void initializeGrid(int agents);
    void initializeAgentsAndTasks(int agents);
    void initializeTable(int agents);

    void setCellValues();

};

#endif // VISUALIZEPROBLEM_H
