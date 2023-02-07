#include <QDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "visualizeproblem.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initializeComponents();
}

void MainWindow::handleSubmitBtn() {
    int agents = ui->agentsText->toPlainText().toInt();
    int tasks = ui->tasksText->toPlainText().toInt();

    VisualizeProblem *vp = new VisualizeProblem(agents, tasks);
    vp->show();

}

void MainWindow::initializeComponents() {
    ui->submitBtn->setText("Submit");
    ui->agentsText->setPlaceholderText("Input agents");
    ui->tasksText->setPlaceholderText("Input tasks");
    connect(ui->submitBtn, &QPushButton::released, this, &MainWindow::handleSubmitBtn);
}

MainWindow::~MainWindow()
{
    delete ui;
}


