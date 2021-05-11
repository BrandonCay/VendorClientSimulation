#include <iostream>
#include "math.h"
#include <string>
#include "client.h"
using namespace std;

client client::operator =(client& obj) {
	if (this == &obj) {
		return *this;
	}
	number = obj.number;
	transactionT = obj.transactionT;
	arrivalTime = obj.arrivalTime;
	waitTime = obj.waitTime;
	served = obj.served;
	return *this;
}
int client::getTransactionT() {
	return transactionT;
}

int client::getArrivalTime() {
	return arrivalTime;
}
int client::getNumber() {
	return number;
}


int client::getLineWaitTime() {
	if (!served)
		return waitTime;
	if (!waitTime)
		return waitTime;
	int diff = waitTime - transactionT;
	return diff;
}


void client::setWaitTime(int t) {
	waitTime = t - arrivalTime;
}
int client::getWaitTime() {
	return waitTime;
}

bool client::getServed() {
	return served;
}
void client::setServed(bool f) {
	served = f;
}

void client::displayInfo(int t) {
	cout << "Client: " << number << "; Arrived at: " << arrivalTime ;
	if (served)
		cout << " finshed transaction at: " << t << " minutes; ";
	else {
		cout << " didn't finish transaction; ";
	}
	cout << "wait time is : " << getLineWaitTime() << endl;
}