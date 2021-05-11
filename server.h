#pragma once
#ifndef server_H
#define server_H
class server {
	client customer=client();
	int transactionT = 0;
	int timeServing=0;
public:
	void setCustomer(client);
	//post: assigns the customer with client
	bool isFull();
	//pre: checks if a client was assigned
	//post: if assigned: returns true otherwise: returns false
	client* getCustomer();
	//post: returns a pointer to the client stored in customer
	bool transactionComplete();
	//pre: checks isFull()
	//post: if true: determines if the serving time of the server matches the expected transaction time of the client
	void incTransactionT(int);
	//post: increse the transactionT by a certain time
	client popCustomer();
	//post: assigns the customer with an empty/dummy client and returns the old client
	void setTransactionT(int);
	//post: assigns a value to transactionT
	int getTimeServing();
	//post: returns total timeServing (time spent serving)
	void incTServing(int);
	//post: increments timeServing for this server
};
#endif