#ifndef NODE_H
#define NODE_H

#include <iostream>

//#define width 100
//#define length 200
using namespace std;

class Node{
public:
	Node * left;
	Node * right;
	int output;
	int timer;
	int delay ;
	int change ;
	string name;
	int Cx;  //mokhtasat dar safhe
	int Cy;  
public:
        Node(int d = 0):left(0),right(0),output(0),delay(d),change(0),name("0"),Cx(0),Cy(0){
		timer = delay;
	};
	~Node(){
		delete left;
		delete right;
	}
	int getOutput(){
		return output ;
	}
	Node* getLeft(){
		return left;
	}
	Node* getRight(){
		return right;
	}
	void setOutPut(int a){
		output = a;
	}
	
	void setTimer(int t){
		timer = t;
	}
	int getTimer(){
		return timer;
	}
	bool checkTimer(){
		if(timer>0)
			return false;
		return true;
	}
	void setChange(int c){
		change = c;
	}
	int getChange(){
		return change;
	}
	int getOutPut(){
		return output;
	}
	void setName(string n){
		name = n;
	}
	string getName(){
		return name;
	}
	virtual int getResult(int l, int r){
		return 0;
	}
	virtual int getDelay(){
		return delay ;
	}
	virtual void setDelay(int d){
		delay = d;
	}
	int getX(){
		return Cx;
	}
	int getY(){
		return Cy;
	}
	void setX(int c){
		Cx=c;
	}
	void setY(int c){
		Cy=c;
	}
};

#endif
