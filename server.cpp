#include "client.h"
#include "server.h"
using namespace std;

void server::setCustomer(client c) {
	customer = c;
}
bool server::isFull() {
	if (customer.getNumber()!=-1)
		return true;
	return false;
}
client* server::getCustomer() {
	return &customer;
}
void server::incTransactionT(int a) {
	transactionT += a;
}
bool server::transactionComplete() {
	if (!isFull()) {
		return false;
	}
	if (transactionT == customer.getTransactionT()) {
		return true;
	}
	return false;
}

void server::setTransactionT(int a) {
	transactionT = a;
}

client server::popCustomer() {
	client replace;
	client temp = customer;
	customer = replace;
	return temp;
}

int server::getTimeServing() {
	return timeServing;
}
void server::incTServing(int a) {
	timeServing += a;
}