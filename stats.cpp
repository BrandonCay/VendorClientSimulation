
#include "stats.h"
#include "client.h"

int stats::getMaxWaitLine() {
	return maxWaitLine;
}

bool stats::isNewMaxWaitLine(int n) {
	if (n > maxWaitLine) {
		maxWaitLine = n;
		return true;
	}
	return false;
}

int stats::getTotalClients() {
	return store.size();
}

int stats::getTotalClientsServed() {
	int cnt=0;
	for (int i = 0; i < store.size() ; ++i) {
		if (store[i].getServed())
			++cnt;
	}
	return cnt;
}

int stats::getTotalTimeInLine() {
	int sum = 0;
	for (int i = 0; i < store.size(); ++i) {
		sum += store[i].getLineWaitTime();
	}
	return sum;
}

int stats::getAverageWait() {
	int total=getTotalTimeInLine();
	return total / store.size();
}

int stats::totalTellerDutyT(server* arr, int size) {
	int sum = 0;
	for (int i = 0; i < size; ++i) {
		sum+=arr[i].getTimeServing();
	}
	return sum;
}
int stats::totalIdleTime(server* arr, int size, int t) {
	int sum = 0;
	for (int i = 0; i < size; ++i) {
		sum += t - arr[i].getTimeServing();
	}
	return sum;
}
