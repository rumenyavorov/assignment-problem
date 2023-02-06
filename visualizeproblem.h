#ifndef VISUALIZEPROBLEM_H
#define VISUALIZEPROBLEM_H

#include <QWidget>
#include <QGridLayout>
#include <QTextEdit>
#include <QTableWidget>
#include <QPushButton>
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsView>
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
    int findLeftZeros();
    void markMostEfficient(int row, int col);
    void markOtherZeros(int row, int col);
private slots:
    void initSubmitButton();
    void submitProblemHandler();

    void initFirstStepButton();
    void firstStepBtnHandler();
    void initSecondStepButton();
    void secondStepBtnHandler();
    void initThirdStepButton();
    void thirdStepBtnHandler();
//    void initFourthStepButton();
//    void fourthStepBtnHandler();

private:
    Ui::VisualizeProblem *ui;

    QGridLayout *problemGrid;
    QTableWidget *tableGrid;
    QPushButton *submitBtn;
    QPushButton *firstStepBtn;
    QPushButton *secondStepBtn;
    QPushButton *thirdStepBtn;
//    QPushButton *fourthStepBtn;

    void initializeGrid(int agents);
    void initializeAgentsAndTasks(int agents);
    void initializeTable(int agents);

    void setCellValues();

    void paintBorder(QTableWidgetItem *item, Qt::GlobalColor color);
    int excludeColumn();
    void markMostEfficient(int row, int col, int ec);
    void markOtherZeros(int row, int col, int ec);
    void paintBorder(QTableWidgetItem *item, Qt::GlobalColor color, QString txt);
};

#endif // VISUALIZEPROBLEM_H
