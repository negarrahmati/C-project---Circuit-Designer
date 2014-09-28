#include "readinput.h"
#include <string>
#include <QObject>

ReadInput::ReadInput(QWidget *parent){
    this->setupUi(this);
    this->is_accepted = 0;
    connect(this->EnterExpression,SIGNAL(textChanged(QString)),this,SLOT(enableOkButton(QString)));
    connect(this->acceptButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(this->acceptButton,SIGNAL(clicked()),this,SLOT(bottunPressed()));
    connect(this->cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
//    connect(this->cancelButton,SIGNAL(clicked()),this,SLOT(is_accept()));
}
void ReadInput::enableOkButton(QString st){
    if(st.isEmpty())
        this->acceptButton->setEnabled(false);
    else
        this->acceptButton->setEnabled(true);
}
int ReadInput::checkValidity(string input){

        // if correct , return -1 , if not correct , return -2 or index
            if((input.at(0)=='.')||(input.at(0)=='|'))		//.a |a
                    return 0;
            for(int i = 0 ; i < input.size() ; i++){		//!.
                   // if( ((input.at(i)=='|')||(input.at(i)=='.')) && ((input.at(i-1)<'A') || (input.at(i-1)>'z')) && input[i-1]!='|' && input [i-1]!='~' )
                    //        return i ;
                if(input[i]=='[')
                {
                    i++;
                    while(input[i]!=']')
                    {
                        if(input[i]<'0' || input[i]>'9')
                            return i;
                        i++;
                    }
                }
                if((input.at(i)<'A') || (input.at(i)>'z'))
                {
                    if(input[i]!='(' && input[i]!=')' && input[i]!='[' && input[i]!=']' && input[i]!='.' && input[i]!='~.' && input[i]!='~' && input[i]!='|' && input[i]!='||' && input[i]!='~|' && input[i]!='~||')
                        return i;
                }
            }
            int count=0;
            for(int i=0;input[i]!=NULL;i++){
                    if(input[i]=='(')
                            count++;
                    if(input[i]==')')
                            count--;
                    if(count<0)
                            return i;
            }
            if(count!=0)
                    return -2;
            for(int i=0;input[i]!=NULL;i++){
                    if(input[i]==')' && input[i+1]=='(')
                            return i;
                    if((input.at(i)=='(') && ((input[i+1]=='|') || (input[i+1]=='.') ||(input[i+1]==')')) )
                            return i ;
            }
            for(int i = 0 ; i < input.size() ; i++){  
                    if(((input.at(i)=='.') && (input[i+1]=='.')) || ((input.at(i)=='~') && (input[i+1]=='~')) ||
                            ((input.at(i) == '|')&&(input[i+1]=='|')&&(input[i+2]=='|')))
                            return i ;
            }
            count=0;
            for(int i = 0 ; i < input.size() ; i++){
                    if((input.at(i)=='[')&&(input[i+1]==']'))
                            return i;
                    //if((input.at(i)=='[')&&(input.at(i+2)!=']'))
                    //	return i;
                    if((input.at(i)=='[')&&(input.at(i+1)<'0'))
                            return i ;
                    if(input[i]=='[')
                            count++;
                    if(input[i]==']')
                            count--;
                    if(count<0)
                            return i;
            }
            if(count!=0)
                    return -2;
            return -1;
    
}

void ReadInput::on_cancelButton_clicked()
{
    is_accepted = 0;
}

string ReadInput::removeSpaces(string input)
{
    string temp1;
    string temp2;
    for(int i=0;i<input.size();i++)
    {
        if(input[i]==' ')
        {
            temp1=input.substr(0,i);
            temp2=input.substr(i+1);
            temp1.append(temp2);
            input=temp1;
            i--;			//if there was more than one space in a row
        }
    }
    return input;
}
