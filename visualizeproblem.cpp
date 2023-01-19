#include "visualizeproblem.h"
#include "ui_visualizeproblem.h"
#include "assignmentproblem.h"

#include <QLabel>
#include <QPushButton>
#include <QTextEdit>

VisualizeProblem::VisualizeProblem(int agents, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::VisualizeProblem)
{
    ui->setupUi(this);
    problemGrid = new QGridLayout(this);
    tableGrid = new QTableWidget(this);

    initializeGrid(agents);
}

VisualizeProblem::~VisualizeProblem()
{
    delete ui;
}

void VisualizeProblem::initializeAgentsAndTasks(int agents)
{
    for(int i = 0; i < agents; i++) {
        QString str = QString::number(i + 1);
        QLabel *lbl = new QLabel("Agent - " + str);
        problemGrid->addWidget(lbl, i + 1, 0, 1, 1);
    }

    for(int j = 0; j < agents; j++) {
        QString str = QString::number(j + 1);
        QLabel *lbl = new QLabel("Task - " + str);
        problemGrid->addWidget(lbl, 0, j + 1, 1, 2);
    }
}

QStringList initializeTableRowHeaders(int agents) {
    QStringList list;

    for(int i = 1; i <= agents; i++) {
        list.append("Agent - " + QString::number(i));
    }

    return list;
}

QStringList initializeTableColumnHeaders(int agents) {
    QStringList list;

    for(int i = 1; i <= agents; i++) {
        list.append("Task - " + QString::number(i));
    }

    return list;
}

//initialize table with NxN (agents * tasks (tasks = agents))
void VisualizeProblem::initializeTable(int agents) {

    int matrix[agents][agents];

    QStringList agentHeaderList = initializeTableRowHeaders(agents);
    QStringList taskHeaderList = initializeTableColumnHeaders(agents);

    tableGrid->setVerticalHeaderLabels(agentHeaderList);
    tableGrid->setHorizontalHeaderLabels(taskHeaderList);


    for (int row = 0; row < agents; row++) {
            for (int col = 0; col < agents; col++) {
                QTableWidgetItem* item = new QTableWidgetItem(QString::number(matrix[row][col]));
                item->setText("Please set cost");
                tableGrid->setItem(row, col, item);
            }
    }
}

//initialize GridLayout
void VisualizeProblem::initializeGrid(int agents) {
    qInfo() << "In VisualizeProblem with agents - " + QString::number(agents);
    tableGrid->setRowCount(agents);
    tableGrid->setColumnCount(agents);

    initializeTable(agents);

    problemGrid->addWidget(tableGrid);

    initSubmitButton();

    connect(submitBtn, &QPushButton::clicked, this, &VisualizeProblem::submitProblem);
}

//function to handle button actions
void VisualizeProblem::submitProblem() {
    qInfo() << "SubmitButton CLICKED!!!!!!";
    setCellValues();
}

// Initialize submit button
void VisualizeProblem::initSubmitButton() {
    qInfo() << "Initialize SubmitButton";
    submitBtn = new QPushButton("Submit values");
    problemGrid->addWidget(submitBtn);
}

void VisualizeProblem::setCellValues() {
    int rows = tableGrid->rowCount();
    int cols = tableGrid->columnCount();

    AssignmentProblem *ap = new AssignmentProblem(rows, cols);

    for(int row = 0; row < rows; row++) {
        for(int col = 0; col < cols; col++) {
            QString item = tableGrid->item(row, col)->data(Qt::DisplayRole).toString();
            int itemVal = item.toInt();

            ap->set(row, col, itemVal);
        }
    }

    ap->print();
}


