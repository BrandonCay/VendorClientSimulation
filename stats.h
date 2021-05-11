#pragma once
#ifndef stats_H
#define stats_H
#include "client.h"
#include "server.h"
#include <vector>
#include <string>

class stats {
public:
	typedef std::vector<client> T;

	int timeSpentWaiting = 0;
	//time a customer was in line
	int timeSpentServing = 0;
	//time a teller had a customer
	int nOfClientsInL = 0;
	//number of clients that had to wait in line
	int serverIdleTime=0;
	//total number of 
	T store;
	//client storage
	int maxWaitLine=-1;
	int totalTime;
	//functions:
	int getMaxWaitLine();
	//post: returns maxWaitLine
	bool isNewMaxWaitLine(int);
	//post: determines a new maxWaitLine and assigns it to maxWaitLine
	int getTotalClients();
	//post:returns T size;
	int getTotalClientsServed();
	//post: returns number of clients with the served flag as true
	int getTotalTimeInLine();
	//post: calculates the total time clients waited in line then returns it
	int getAverageWait();//wait on Line
	//post: calcualtes the average wait on Line and returns it
	int totalTellerDutyT(server*, int);
	//post: calculates the total time the teller(s) was on duty and returns it
	int totalIdleTime(server*, int, int);
	//post: calculates the total time the teller(s) was idle and returns it
	
};


#endif