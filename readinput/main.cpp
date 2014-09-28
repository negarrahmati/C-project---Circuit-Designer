#include <QtGui/QApplication>
#include <QtGui>
#include "mainwindow.h"
#include "ui_readinput.h"
#include "readinput.h"
#include <string>
#include <vector>
#include "mytree.h"


using namespace QtConcurrent;

const int iterations = 20;

void spin(int &iteration)
{
    const int work = 1000 * 1000 * 40;
    volatile int v = 0;
    for (int j = 0; j < work; ++j)
        ++v;

    qDebug() << "iteration" << iteration << "in thread" << QThread::currentThreadId();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDialog * readDialog = new QDialog;
    ReadInput * ri = new ReadInput(readDialog);
    string input ;
    vector<string> operands;
   while(true){
    ri->exec();
    if(ri->is_accepted == 1){
        input=ri->EnterExpression->text().toStdString();
        input=ri->removeSpaces(input);
        if(ri->checkValidity(input)== -1){
            QMessageBox correctInput ;
            correctInput.setText(ri->EnterExpression->text());
            correctInput.exec();
            break;
        }
        else if(ri->checkValidity(input)==-2){
             QMessageBox wrongInput ;
             wrongInput.setText("Wrong Input");
             wrongInput.exec();
        }
        else{
            int wrongIndex = ri->checkValidity(input);
            QMessageBox wIndexInput;
            QString warning = ri->EnterExpression->text().at(wrongIndex);
            wIndexInput.setText(warning);
            wIndexInput.exec();
        }
    }
    else
        break;
}   

   // Prepare the vector.
       QVector<int> vector;
       for (int i = 0; i < iterations; ++i)
           vector.append(i);

       // Create a progress dialog.
       QProgressDialog dialog;
       dialog.setLabelText(QString("Progressing using %1 thread(s)...").arg(QThread::idealThreadCount()));

       // Create a QFutureWatcher and conncect signals and slots.
       QFutureWatcher<void> futureWatcher;
       QObject::connect(&futureWatcher, SIGNAL(finished()), &dialog, SLOT(reset()));
       QObject::connect(&dialog, SIGNAL(canceled()), &futureWatcher, SLOT(cancel()));
       QObject::connect(&futureWatcher, SIGNAL(progressRangeChanged(int,int)), &dialog, SLOT(setRange(int,int)));
       QObject::connect(&futureWatcher, SIGNAL(progressValueChanged(int)), &dialog, SLOT(setValue(int)));

       // Start the computation.
       futureWatcher.setFuture(QtConcurrent::map(vector, spin));

       // Display the dialog and start the event loop.
       dialog.exec();

       futureWatcher.waitForFinished();

       // Query the future to check if was canceled.
       qDebug() << "Canceled?" << futureWatcher.future().isCanceled();

       mytree tree;
       tree.makeTree(input,&(tree.root));
       //operands=tree.findOperands();
       tree.setCoordination(tree.root,1000,350,1000/tree.getHight(tree.root),350);
       MainWindow window(0,&tree);
       window.show();

       return a.exec();
}
