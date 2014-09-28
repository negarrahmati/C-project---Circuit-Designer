#pragma once

#include <string>
#include "And.h"
#include "Nand.h"
#include "Or.h"
#include "Nor.h"
#include "Xnor.h"
#include "operand.h"
#include <vector>
//#include <windows.h>

//#define width 100
//#define length 200

using namespace std;

class mytree
{
public:
    Node* root ;
    string input ;
public:
    mytree(){
        input='0' ;
        root = 0 ;
    }
    ~mytree(){
        delete root;
    }
    void makeTree(string input,Node ** root){
        int delay;
        int index;
        string op;
        if(input.at(0) == '['){
            int i = 0;
            while(input.at(i) != ']')
                i++;
            input = input.substr(i+1,input.size()-i-1);
        }
        if(hasPAround(input))		//checks if input is in paranthesis
            input=input.substr(1,input.size()-2);
        if(!hasOperator(input)){
            if(input.at(0)=='('){
                input = input.substr(1,input.size()-2);
            }
            (*root)=new Operand();
            (*root)->setName(input);
            (*root)->right=0;
            (*root)->left=0;
            return ;
        }
        delay=findOperator(input,op,index);		// find operator with min priority & return delay of operator
        //(*root)=new Node();

        if(op=="."){
            /*And and;
			and.setDelay(delay);
			*root = &and;
			*/
            (*root)=new And();
            (*root)->setDelay(delay);
        }
        else if(op=="|")
        {
            (*root)=new Or();
            (*root)->setDelay(delay);
        }
        else if(op=="~")
        {
            (*root)=new Not();
            (*root)->setDelay(delay);
            (*root)->right=0;		//******
        }
        else if(op=="~.")
        {
            (*root)=new Nand();
            (*root)->setDelay(delay);
        }
        else if(op=="~|")
        {
            (*root)=new Nor();
            (*root)->setDelay(delay);
        }
        else if(op=="||")
        {
            (*root)=new Xor();
            (*root)->setDelay(delay);
        }
        else if(op=="~||")
        {
            (*root)=new Xnor();
            (*root)->setDelay(delay);
        }
        if(op=="~")
        {
            makeTree(input.substr(1,input.size()-1),(&(*root)->left));
        }
        else
        {

            makeTree(input.substr(0,index),(&(*root)->left));
            makeTree(input.substr(index+op.size(),input.size()-(index+op.size())),(&(*root)->right));
        }
    }
    int calculate(Node * root){
        if((root->getLeft() == 0) && (root->getRight() == 0) )
            return root->getOutput();

        int leftResult = 0 ;
        int rightResult = 0 ;

        root->setTimer(root->getTimer()-1);

        if(root->getLeft()!= 0)
            leftResult = calculate(root->getLeft());

        if(root->getRight() != 0)
            rightResult = calculate(root->getRight());

        if(root->checkTimer())
        {
            root->setOutPut(root->getResult(leftResult , rightResult));				// baraye not operand lefte
            root->setChange(1);
            if(root->getRight()!=0)
            {
                if((root->getLeft())->getChange() || (root->getRight())->getChange())
                {
                    root->setTimer(root->getDelay());
                    root->getLeft()->setChange(0);
                    root->getRight()->setChange(0);
                }
            }
            else
            {
                if((root->getLeft())->getChange() )
                {
                    root->setTimer(root->getDelay());
                    root->getLeft()->setChange(0);
                }
            }
        }
        else
        {
            root->setOutPut(root->getOutPut());
            if(root->getLeft()->getChange() || root->getRight()->getChange())
            {
                root->setTimer(root->getDelay());
                root->getLeft()->setChange(0);
                root->getRight()->setChange(0);
            }
        }
        return root->output;
    }
    void update(Node * root){
        while(true){
            //Sleep(100);
            calculate(root);
        }
    }
    bool hasOperator(string input){
        for(int i = 0 ; i < input.size() ; i++)
            if( ( input.at(i)=='.' || input.at(i)=='~' || input.at(i)=='|') )
                return true;
        return false;
    }
    int findOperator(string input,string &op, int &index)
    {
        int numOfP=0;		//be ezaye har '(' ++ va be ezaye har ')' -- mishavad
        op = "0";				//operator
        int delay=0;
        for(int i=0; i<input.size();i++)
        {
            if(input[i]=='(')		//in sharta vase ine ke amalgar e kharej e parantez o be dast biarim
            {
                numOfP++;
                continue;
            }
            else if(input[i]==')')
            {
                numOfP--;
                continue;
            }
            else if(numOfP==0)
            {
                if(input[i]=='.')
                {
                    if(op!=".")
                    {
                        op=prior(op,".");
                        if(op==".")
                        {
                            index=i;
                            delay=findDelay(input,i);
                        }
                    }
                }
                else if(input[i]=='|')
                {
                    if(input[i+1]=='|')
                    {
                        if(op!="||")
                        {
                            op=prior(op,"||");
                            if(op=="||")
                            {
                                index=i;
                                delay=findDelay(input,i);
                            }
                        }
                        i++;
                    }
                    else
                        if(op!="|")
                        {
                        op=prior(op,"|");
                        if(op=="|")
                        {
                            index=i;
                            delay=findDelay(input,i);
                        }
                    }
                }
                else if(input[i]=='~')
                {
                    if(input[i+1]=='.')
                    {
                        if(op!="~.")
                        {
                            op=prior(op,"~.");
                            if(op=="~.")
                            {
                                index=i;
                                delay=findDelay(input,i);
                            }
                        }
                        i++;
                    }
                    else if(input[i+1]=='|')
                    {

                        if(input[i+2]=='|')
                        {
                            if(op!="~||")
                            {
                                op=prior(op,"~||");
                                if(op=="~||")
                                {
                                    index=i;
                                    delay=findDelay(input,i);
                                }
                            }
                            i++;
                        }
                        else if(op!="~|")
                        {
                            op=prior(op,"~|");
                            if(op=="~|")
                            {
                                index=i;
                                delay=findDelay(input,i);
                            }
                        }
                        i++;
                    }
                    else
                    {
                        if(op!="~")
                        {
                            op=prior(op,"~");
                            if(op=="~")
                            {
                                index=i;
                                delay=findDelay(input,i);
                            }
                        }
                    }
                }

            }

        }
        return delay;
    }
    string prior(string a,string b)
    {
        if(a=="0")
            return b;
        if(b=="0")
            return a;
        int aP=0,bP=0;
        aP=findPriority(a);			//yek adad az 1 ta 3 be har amalgar nesbat midahad:  ~ -> 1 , and->2 ,...
        bP=findPriority(b);
        return (aP<=bP ? b : a);
    }
    int findPriority(string op)
    {
        if(op=="0")
            return 4;
        if(op=="~")
            return 1;
        if(op=="." || op=="~.")
            return 2;
        if(op=="||" || op=="~||" || op=="|" || op=="~|")
            return 3;
    }
    /*int validate(string input){		// if correct , return -1 , if not correct , return -2 or index
		if((input.at(0)=='.')||(input.at(0)=='|'))		//.a |a
			return 0;
		for(int i = 0 ; i < input.size() ; i++){		//!.
			if( ((input.at(i)=='|')||(input.at(i)=='.')||(input.at(i)=='~')) && ((input.at(i-1)<'A') || (input.at(i-1)>'z')) )
				return i ;
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
			if((input.at(i)=='(') && ((input.at(i+1)=='|') || (input.at(i+1)=='.') ||(input[i+1]==')')) )
				return i ;
		}
		for(int i = 0 ; i < input.size() ; i++){  
			if(((input.at(i)=='.') && (input.at(i+1)=='.')) || ((input.at(i)=='~') && (input.at(i+1)=='~')) ||
				((input.at(i) == '|')&&(input.at(i+1)=='|')&&(input.at(i+2)=='|')))
				return i ;
		}
		count=0;
		for(int i = 0 ; i < input.size() ; i++){
			if((input.at(i)=='[')&&(input.at(i+1)==']'))
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
        */
    int findDelay(string input,int i)
    {
        string temp;
        int delay=0;
        if(input[i]=='~' && input[i+1]=='|' && input [i+2] == '|')
        {
            if(input[i+3]=='[')
            {
                int j = i+4;
                while(j<input.size())
                {
                    if(input[j]==']')
                        break;
                    j++;
                }
                string temp = input.substr(i+4,j-i-4);
                delay=atoi(temp.c_str());
                return delay;
            }

        }
        else if((input[i]=='~' && input[i+1] =='|') || (input[i]=='~' && input[i+1]=='.') || (input[i]=='|' && input[i+1]=='|'))
        {
            if(input[i+2]=='[')
            {
                int j = i+3;
                while(j<input.size())
                {
                    if(input[j]==']')
                        break;
                    j++;
                }
                temp=input.substr(i+3,j-i-3);
                delay=atoi(temp.c_str());
                return delay;
            }
        }
        else if(input[i]=='~' || input[i]=='|' || input[i]=='.')
        {
            if(input[i+1]=='[')
            {
                int j = i+2;
                while(j<input.size())
                {
                    if(input[j]==']')
                        break;
                    j++;
                }
                temp = input.substr(i+2,j-i-2);
                delay=atoi(temp.c_str());
                return delay;
            }
        }
        else
            return 0;

    }
    bool hasPAround(string input)
    {
        int numP1=0; //number of (
        int numP2=0; //number of )

        if(input[0]!='(')
            return false;
        else
        {
            for(int i=0;i<input.size();i++)
            {
                if(input[i]=='(')
                    numP1++;
                else if(input[i]==')')
                    numP2++;
                if(numP1==numP2 && i==input.size()-1)
                    return true;
                else if(numP1==numP2)
                    return false;
            }
        }
    }
    int getHight(Node *root)		//omgh e derakht
    {
        if(root==0)
            return 0;
        return(1+Max(getHight(root->getLeft()),getHight(root->getRight())));
    }
    int Max(int a , int b)
    {
        return (a>b ? a : b);
    }
    int getWidth()		//arz e safhe
    {
        return (2^(getHight(root)-1));
    }
    void setOperator(string name,int value,Node * root)     //vorudi ra meghdardehi mokonad
    {
        if( root->getLeft()==0 && root->getRight()==0)
        {
            if( root->getName()==name)
                root->setOutPut(value);
            return;
        }
        if( root->getRight()==0)
            setOperator(name,value,root->getLeft());
        else
        {
            setOperator(name,value,root->getLeft());
            setOperator(name,value,root->getRight());
        }
    }
    void setCoordination(Node *root, int l, int w,double lh,int wh) //w->width , l->length , lh->page length/ tree height ,wh->w/2^n
    {
        root->setX(l);
        root->setY(w);
        if(Not *n=dynamic_cast<Not *> (root))
        {
            if(root->getLeft()!= 0)
                setCoordination(root->getLeft(),l-lh,w,lh,wh/2);

        }
        else
        {
            if(root->getLeft()!=0 && root->getRight()!=0)
            {
                setCoordination(root->getLeft(),l-lh,w-wh/2,lh,wh/2);
                setCoordination(root->getRight(),l-lh,w+wh/2,lh,wh/2);

            }
        }
    }
    vector<string> findAllOperands(Node * root)		//tekrari ha ro hazv nemikone
    {	vector<string> operands,temp;
        if(root->getLeft()==0 && root->getRight()==0)
        {
            operands.push_back(root->getName());
            return operands;
        }
        if(root->getLeft()!=0 && root->getRight()!=0)
        {
            operands=(findAllOperands(root->getLeft()));
            temp=(findAllOperands(root->getRight()));
            for(int i=0;i<temp.size();i++)
                operands.push_back(temp[i]);
        }
        else if(root->getLeft()!=0)
        {
            operands=(findAllOperands(root->getLeft()));

        }
        return operands;
    }
    vector<string> findOperands()
    {
        vector<string> operands=findAllOperands(root);
        for(int i=0;i<operands.size();i++)
        {
            for(int j=0; j<operands.size();j++)
            {
                if(i==j)
                    continue;
                if(operands[i]==operands[j])
                    operands.erase(operands.begin()+i);
            }
        }
        return operands;
    }
};
