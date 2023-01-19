#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QPlainTextEdit>
#include <QPushButton>
#include "assignment.h"
#include "secondwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    SecondWindow *secondWin;
private slots:
    void initializeComponents();
    void handleSubmitBtn();

private:
    Ui::MainWindow *ui;

    QPushButton *submitBtn;
    QPlainTextEdit *agentsText;
    QPlainTextEdit *costsText;

    Assignment *assignment;

    void createVisualMatrix(int agents);

};
#endif // MAINWINDOW_H
