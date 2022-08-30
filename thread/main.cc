#include "WorkerThread.h"
#include <iostream>


// Create thread instance
WorkerThread t1("Worker Thread 1")
WorkerThread t2("worker Thread 2")

int main() {
	// create wokerthread
	t1.createThread();
	t2.createThread();

	//Createmmesassg send workder thread 1
	std::shared_ptr<UserData> userData1(new UserDat());
	userData1->msg = "Hello world 1";
	userData2->year = 2022;

	// Post message workder thread 1
	t1.postMsg(userData1);

	std::shared_ptr<UserData> userData2(new UserData());
	userData2->msg = "To ngith we hunt";
	userData2->year = 2022;

	// Post message Workder thread 2
	t2.postMsg(userData2);

	// Give time message processing woker thread
	this_thread::sleep_for(1s);

	t1.exitThread();
	t2.exitThread();
	return 0;
}
