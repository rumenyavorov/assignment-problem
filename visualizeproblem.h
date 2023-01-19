#ifndef VISUALIZEPROBLEM_H
#define VISUALIZEPROBLEM_H

#include <QWidget>
#include <QGridLayout>
#include <QTextEdit>
#include <QTableWidget>
#include <QPushButton>

namespace Ui {
class VisualizeProblem;
}

class VisualizeProblem : public QWidget
{
    Q_OBJECT

public:
    explicit VisualizeProblem(int agents, QWidget *parent = nullptr);
    ~VisualizeProblem();


private slots:
    void submitProblem();
    void initSubmitButton();
private:
    Ui::VisualizeProblem *ui;

    QGridLayout *problemGrid;
    QTableWidget *tableGrid;
    QPushButton *submitBtn;

    void initializeGrid(int agents);
    void initializeAgentsAndTasks(int agents);
    void initializeTable(int agents);

    void setCellValues();
};

#endif // VISUALIZEPROBLEM_H
