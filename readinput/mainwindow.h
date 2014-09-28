#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mytree.h"
#include <QtGui>
#include <vector>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0, mytree * t = 0);
    ~MainWindow();
    mytree * t;
    QList<QLineEdit*> lines;
    //vector<QLineEdit *> lines;
protected:
    void changeEvent(QEvent *e);
    void paintEvent(QPaintEvent * e);
    void Draw(Node * root);
    void drawTree(Node * root);
    void drawWires(Node * root);
    void drawWire(int , int , int , int);
private:
    Ui::MainWindow *ui;

private slots:
//    void on_DrawCircuit_clicked();

private slots:
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
