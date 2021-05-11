#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <iomanip>
#include "stats.h"
#include "client.h"
#include "server.h"
using namespace std;

void displayQueue(queue<client>q);
//post:prints queue items until empty
void displayStats(stats, server*, int);
//post: contents of a stats object
bool isServersFull(server*, int);
//pre:checks if all servers have a client
//post:takes a server list and returns true if all servers have a client otherwise false 


static int time1 = 0;
int endTime = 0;

int main() {
	int serverCnt;

	cout << "---Simulation is based on time in minutes---" << endl;
	cout << "input end time: ";
	cin >> endTime;
	cout << "input number of servers/tellers: ";
	cin >> serverCnt;
	cout << endl;


	ifstream in("clientTimeTable3.txt",fstream::app);//replacable txt
	queue<client>clientPool;//clients spawn pool
	queue<client>inLine;
	server* servers = new server[serverCnt];
	stats record;
	record.totalTime= endTime;

	while (true) {
		int n, a, t;
		if (in >> n >> a >> t) {
		}
		else{
			if (in.peek())
				break;
		}
		clientPool.push(client(n,a,t));
	}		
//	displayQueue(clientPool);
	while (time1 <= endTime) {
		//checks
		bool inService = false;
		if (!clientPool.empty() && clientPool.front().getArrivalTime() == time1) {
			if (!isServersFull(servers, serverCnt)) {//looks for a spot in the teller first
				for (int i = 0; i < serverCnt; ++i) {
					if (!servers[i].isFull()) {
						record.store.push_back(clientPool.front());
						servers[i].setCustomer(clientPool.front());
						clientPool.pop();
						inService = true;
					}
				}
			}
			else {
				inLine.push(clientPool.front());
				++record.nOfClientsInL;
				record.store.push_back(clientPool.front());//stores client on record
				clientPool.pop();
				record.isNewMaxWaitLine(inLine.size());
			}
			//server check
		}
			for (int i = 0; !inLine.empty() && i < serverCnt; ++i) {
				if (!servers[i].isFull()) {
					servers[i].setCustomer(inLine.front());
					inLine.pop();
				}
			}
				//increment and leaving
			bool needStatInc = true;
				for (int i = 0; i < serverCnt; ++i) {
					if (servers[i].transactionComplete()) {
						record.store[servers[i].getCustomer()->getNumber() - 1].setWaitTime(time1);//sets waittime of the client on record
						record.store[servers[i].getCustomer()->getNumber() - 1].setServed(true);
						record.store[servers[i].getCustomer()->getNumber() - 1].displayInfo(time1);



						servers[i].popCustomer();
						servers->setTransactionT(0);

						if (!inLine.empty()) {//replace
							servers[i].setCustomer(inLine.front());
							servers[i].incTransactionT(1);
							servers[i].incTServing(1);

							if (needStatInc) {
								++record.timeSpentServing;
								needStatInc = false;
							}
							inService = true;
							inLine.pop();
						}
					}
					else if (!servers[i].isFull()) { //no customers
					}
					else {
						servers[i].incTransactionT(1);
						servers[i].incTServing(1);
						inService = true;
					}

				}

					if (!inLine.empty()) {
						++record.timeSpentWaiting;
					}
					if (needStatInc) {
						if (inService)
							++record.timeSpentServing;
					}
					if (!isServersFull(servers, serverCnt) && time1!=endTime) {
						++record.serverIdleTime;
					}
				
		++time1;
	}

	for (int i = 0; i < serverCnt; ++i) {
		if (servers[i].getCustomer() != nullptr) {
			if (servers[i].getCustomer()->getNumber() == -1)//doesn't count dummy
				continue;
			servers[i].getCustomer()->setWaitTime(time1);
			servers[i].getCustomer()->displayInfo(time1);
			servers[i].popCustomer();
		}
	}
	while (!inLine.empty() ) {
		inLine.front().setWaitTime(time1);
		inLine.front().displayInfo(time1);
		inLine.pop();
	}

	displayStats(record, servers, serverCnt);
	return 0;
}

void displayQueue(queue<client>q)
{
	while (!q.empty()) {
		cout << "a: " << q.front().getArrivalTime() << endl;
		cout << "t: " << q.front().getTransactionT() << endl;
		q.pop();
	}
	cout << endl;
}
bool isServersFull(server* s, int size) {
	int cnt = 0;
	for (int i = 0; i < size; ++i) {
		if (s[i].isFull())
			++cnt;
	}
	if (cnt == size)
		return true;
	return false;
}

void displayStats(stats o, server* s, int size) {
	cout << endl<<endl;
	cout << setprecision(2) << showpoint << fixed;
	cout << "-------------------" << endl;
	cout << "Statistics:" << endl;
	cout << "Total Simulation Time in minutes: " << endTime << endl;
	cout << "Total Number of Clients That Entered: " << o.getTotalClients() << endl;
	cout << "Total Number of Clients Served: " << o.getTotalClientsServed()<<endl;
	cout << "Total Number of Clients That Spent Time on the Wait Line: " << o.nOfClientsInL << endl;
	cout << "Total Number of Minutes Spent on Wait Line: " << o.getTotalTimeInLine() << endl;
	cout << "Total Number of Minutes With a Client in Line " <<o.timeSpentWaiting << endl;
	cout << "Average Wait Time of all clients in Minutes: " << static_cast<float>(o.getTotalTimeInLine()) / o.store.size()<<endl;
	cout << "Average Wait Time of clients who waited in Minutes: " << static_cast<float>(o.getTotalTimeInLine()) / o.nOfClientsInL << endl;
	cout << "Max length of Wait Line During Simulation: "<<o.getMaxWaitLine()<<endl;
	cout << "Total Number of Tellers: " << size << endl;
	cout << "Total Time a Teller was on Duty: " << endTime << endl;
	cout << "Total Number of Minutes Tellers had a customer: " << o.totalTellerDutyT(s,size)<<endl;
	cout << "Minutes spent with at least one teller having a customer: " << o.timeSpentServing << endl;
	cout << "Total Idle Time in Minutes of Tellers: " << o.totalIdleTime(s, size, endTime)<<endl;
	cout << "Minutes at least one teller was idle: " << o.serverIdleTime<< endl;
	cout << "Percentage of time the teller is idle (total time idle): " << (static_cast<float>(o.totalIdleTime(s,size,endTime)) / endTime)*100 <<"%"<< endl;
	cout << "Percentage of time at least one teller was idle: " << (static_cast<float>(o.serverIdleTime) / endTime)*100 << "%" << endl;
 
	cout << "-------------------" << endl;
	cout << endl << endl;
}