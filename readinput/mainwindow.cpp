#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
MainWindow::MainWindow(QWidget *parent , mytree * tree) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //ui->submit->move(50,1100);
   // ui->submit->setGeometry(100,50,100,20);
    ui->setupUi(this);
    t = new mytree;
    t = tree;
    vector <string> operands=t->findOperands();
    int size=operands.size();
    QLabel * label= new QLabel(this);
    label->setText("OPERANDS : ");
    label->setGeometry(1100,50,100,20);


    for(int i=0;i<size;i++)
    {
        QLineEdit *line=new QLineEdit(this);
        QString a(operands[i].c_str());
        line->setObjectName(a);
        line->setGeometry(1180,100+i*50,40,20);
        line->setBaseSize(20,300);
        lines.push_back(line);
        QLabel * label= new QLabel(this);
        label->setText(a);
        //label->setBaseSize(30,40);
        label->setGeometry(1150,100+i*50,30,20);

       /* QHBoxLayout * bl=new QHBoxLayout(this);
        bl->addWidget(label);
        bl->addWidget(line);
        QRect * rect=new QRect(1000,100,30,100);
        bl->setGeometry(*rect);
        setLayout(bl);
        */

    }
    repaint();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void MainWindow::paintEvent(QPaintEvent * e)
{
    drawTree(t->root);
    drawWires(t->root);
}

void MainWindow::Draw(Node * root)
{

    if(And *a=dynamic_cast<And *> (root))
    {
        QPixmap apic;
        apic.load("and.png");
        QPainter  painter(this);
        painter.drawPixmap(root->getX(),root->getY(),30,30,apic);
    }
   else if(Nand *a=dynamic_cast<Nand *> (root))
    {
        QPixmap nandPic;
        nandPic.load("nand.png");
        QPainter  painter(this);
        painter.drawPixmap(root->getX(),root->getY(),30,30,nandPic);
    }
   else if(Not *a=dynamic_cast<Not *> (root))
   {
       QPixmap notPic;
       notPic.load("not.png");
       QPainter  painter(this);
       painter.drawPixmap(root->getX(),root->getY(),30,30,notPic);
   }
   else if(Operand *a=dynamic_cast<Operand *> (root))
   {
       QPixmap oPic;
       oPic.load("operand.png");
       QPainter  painter(this);
       painter.drawPixmap(root->getX(),root->getY(),30,30,oPic);
   }
}
void MainWindow::drawTree(Node * root)
{
    Draw(root);
    if(root->getLeft()!=0 && root->getRight()!=0)
    {
        drawTree(root->getLeft());
        drawTree(root->getRight());
    }
    else if(root->getLeft()!=0)
    {
        drawTree(root->getLeft());
    }
}
void MainWindow::drawWires(Node * root){
    if((root->getLeft()!=0) && (root->getRight()!=0)){
       drawWire(root->getX(),root->getY()+10 , root->getLeft()->getX()+30,root->getLeft()->getY()+15);
       drawWire(root->getX(),root->getY()+20 , root->getRight()->getX()+30,root->getRight()->getY()+15);
       drawWires(root->getLeft());
       drawWires(root->getRight());
    }
    else if(root->getLeft()!=0){
        drawWire(root->getX(),root->getY()+15 , root->left->getX()+15,root->left->getY()+15);
        drawWires(root->getLeft());
    }
    else{
        return;
    }
}
void MainWindow::drawWire(int x1 , int y1 , int x2 , int y2){
    QPainter painter(this);
    if(y2!=y1){
        painter.drawLine(x2,y2,(x1+x2)/2,y2);
        painter.drawLine((x1+x2)/2,y2,(x1+x2)/2,y1);
        painter.drawLine((x1+x2)/2,y1,x1,y1);
    }
    else{
        painter.drawLine(x2,y2,x1,y1);
    }
}

void MainWindow::on_pushButton_clicked()
{
   for(int i=0;i<lines.size();i++)
  {
       QString te=lines[i]->text();
       int value=te.toInt();
       QString n=lines[i]->objectName();
       string name=n.toStdString();
       t->setOperator(name,value,t->root);
  }

}
