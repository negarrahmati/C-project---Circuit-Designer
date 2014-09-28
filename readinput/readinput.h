#ifndef READINPUT_H
#define READINPUT_H

#include <QDialog>
#include "ui_readinput.h"
#include <iostream>

using namespace std;

class ReadInput : public QDialog , public Ui::Dialog
{
    Q_OBJECT
public:
    ReadInput(QWidget * parent = 0);
    int is_accepted;
    int checkValidity(string input);
    string removeSpaces(string input);
private slots:
    void on_cancelButton_clicked();
    void enableOkButton(QString );
    void bottunPressed(){
        this->is_accepted = 1;
    }
};
#endif // READINPUT_H
