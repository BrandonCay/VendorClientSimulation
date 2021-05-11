#pragma once
#ifndef client_H
#define client_H
#include <vector>

class client {
	int number;
	int transactionT;
	int arrivalTime;
	int waitTime=0;
	bool served=false;
	//to maintain transaction T for statics
	public:
		client(int n = -1, int aT = 0, int tT = 0) :number(n), arrivalTime(aT), transactionT(tT){}
		int getTransactionT();
		//post:returns transactionT
		int getArrivalTime();
		//post: returns arrivalTime
		int getLineWaitTime();
		//post: calculates wait in line time when waitTime is defined then returns it
		int getNumber();
		//post:returns client number
		void setWaitTime(int);
		//post: calculates wait time and sets the client's member
		int getWaitTime();
		//post: returns waitTime
		bool getServed();
		//post: returns served member
		void setServed(bool);
		//post: sets served member
		void displayInfo(int);
		//post: displays client's number,transaction, arrival and wait
		client operator =(client& obj);
		//post: assignment is overloaded to accept member
};
#endif