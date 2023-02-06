#include "visualizeproblem.h"
#include "ui_visualizeproblem.h"
#include <AssignmentProblem.h>

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
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

//    resize(QGuiApplication::primaryScreen()->availableGeometry().size() * 0.4);

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

    ap = new AssignmentProblem(agents, agents);

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

    connect(submitBtn, &QPushButton::clicked, this, &VisualizeProblem::submitProblemHandler);
}

//function to handle button actions
void VisualizeProblem::submitProblemHandler() {
    qInfo() << "SubmitButton CLICKED!!!!!!";
    setCellValues();
    tableGrid->update();
    problemGrid->removeWidget(submitBtn);
    submitBtn->deleteLater();

    initFirstStepButton();
}

void VisualizeProblem::firstStepBtnHandler() {
    qInfo() << "Step button clicked";
    ap->firstStep();
    ap->printMatrix();
    updateTable(ap->getAgents(), ap->getTasks(),ap->getMatrix());

    problemGrid->removeWidget(firstStepBtn);
    firstStepBtn->deleteLater();

    initSecondStepButton();
}

void VisualizeProblem::secondStepBtnHandler() {
    secondStepBtn->setText("Step 2");
    ap->secondStep();
    ap->printMatrix();
    updateTable(ap->getAgents(), ap->getTasks(),ap->getMatrix());

    problemGrid->removeWidget(secondStepBtn);
    secondStepBtn->deleteLater();

    initThirdStepButton();
}

void VisualizeProblem::thirdStepBtnHandler() {
    thirdStepBtn->setText("Step 3");

    ap->thirdStep();
    vector<vector<int>> optimalMatrix = ap->getMatrix();
    for(int i = 0; i < ap->getAgents(); i++) {
        for(int j = 0; j < ap->getTasks(); j++) {
            if(optimalMatrix[i][j] == -1) {
                paintBorder(tableGrid->item(i, j), Qt::yellow, QString("O"));
            } else if(optimalMatrix[i][j] == -2) {
                paintBorder(tableGrid->item(i, j), Qt::red, QString("X"));
            }
        }
    }

//    problemGrid->removeWidget(thirdStepBtn);
//    thirdStepBtn->deleteLater();
}

int VisualizeProblem::findLeftZeros() {
    int z = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(tableGrid->item(i, j)->text() == "0") {
                z++;
            }
        }
    }

    return z;
}

// Initialize submit button
void VisualizeProblem::initSubmitButton() {
    submitBtn = new QPushButton("Submit values");
    problemGrid->addWidget(submitBtn);
}

void VisualizeProblem::initFirstStepButton() {
    firstStepBtn = new QPushButton("Step 1");
    problemGrid->addWidget(firstStepBtn);
    connect(firstStepBtn, &QPushButton::clicked, this, &VisualizeProblem::firstStepBtnHandler);
}

void VisualizeProblem::initSecondStepButton() {
    secondStepBtn = new QPushButton("Step 2");
    problemGrid->addWidget(secondStepBtn);
    connect(secondStepBtn, &QPushButton::clicked, this, &VisualizeProblem::secondStepBtnHandler);
}

void VisualizeProblem::initThirdStepButton() {
    thirdStepBtn = new QPushButton("Step 3");
    problemGrid->addWidget(thirdStepBtn);
    connect(thirdStepBtn, &QPushButton::clicked, this, &VisualizeProblem::thirdStepBtnHandler);
}

void VisualizeProblem::updateTable(int agents, int tasks, vector<vector<int>> matrix) {
    for (int row = 0; row < agents; row++) {
        for (int col = 0; col < tasks; col++) {
            QTableWidgetItem* item = new QTableWidgetItem(QString::number(matrix[row][col]));
            tableGrid->setItem(row, col, item);
        }
    }
}

//set initial cell values based on input
void VisualizeProblem::setCellValues() {
    int rows = tableGrid->rowCount();
    int cols = tableGrid->columnCount();

    //EXAMPLE 1 4x4 - SUCCESS
//    vector<vector<int>> matrix = {{10,12,19,11}, {5,10,7,8}, {12,14,13,11}, {8,15,11,9}};
//    ap->setMatrixData(matrix);
//    updateTable(rows, cols, matrix);

    //EXAMPLE 2 5x5 - SUCCESS
//    vector<vector<int>> matrix = {{8,4,2,6,1}, {0,9,5,5,4}, {3,8,9,2,6}, {4,3,1,0,3}, {9,5,8,9,5}};
//    ap->setMatrixData(matrix);
//    updateTable(rows, cols, matrix);

    //EXAMPLE 3 4x3 - SUCCESS
    //UNBALANCED
//    vector<vector<int>> matrix = {{9, 26, 15, 0}, {13,27,6,0}, {35,20,15,0}, {18,30,20,0}};
//    ap->setMatrixData(matrix);
//    updateTable(rows, cols, matrix);

//    for(int row = 0; row < rows; row++) {
//        for(int col = 0; col < cols; col++) {
//            QString item = tableGrid->item(row, col)->data(Qt::DisplayRole).toString();
//            int itemVal = item.toInt();


//            ap->set(row, col, itemVal);
//        }
//    }
}

void VisualizeProblem::paintBorder(QTableWidgetItem *item, Qt::GlobalColor color, QString txt) {
    QBrush brush;

    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    item->setText(txt);
    item->setBackground(brush);
}


