// Race conditions example
// Adam Sampson <a.sampson@abertay.ac.uk>

#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <complex>
#include <chrono>
#include <mutex>
#include "account.h"
#include <condition_variable>

// Import things we need from the standard library
using std::cout;
using std::endl;
using std::thread;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::complex;
using std::mutex;

typedef std::chrono::steady_clock the_clock;

Account bill;
mutex bill_mutex;
std::condition_variable result_cv;

//void myThreadFunc() {
//	for (int i = 0; i < 100000; i++) {
//		bill_mutex.lock();
//		bill.add(17, 29);
//		bill_mutex.unlock()
//	}
//}

//void myThreadFunc() {
//	for (int i = 0; i < 100000; i++) {
//		std::unique_lock<std::mutex> lock(bill_mutex);
//		bill.add(17, 29);
//	}
//}

void myThreadFunc() {

	std::this_thread::sleep_for(std::chrono::milliseconds(2));

	for (int i = 0; i < 100000; i++) {
		std::unique_lock<std::mutex> lock(bill_mutex);
		bill.add(17, 29);
		result_cv.notify_one();
	}
}

void printFuntion() {
	while (true) {
		std::unique_lock<std::mutex> lock(bill_mutex);
		cout << "Total: " << bill.total() << "\n";
		result_cv.wait(lock);
	}
}



int main(int argc, char *argv[])
{
	cout << "Initial: " << bill.total() << "\n";

	//the_clock::time_point start = the_clock::now();

	thread myThread(myThreadFunc);
	thread myThread2(printFuntion);
	myThread.join();
	myThread2.join();
	
	
	//cout << "Total: " << bill.total() << "\n";

	//the_clock::time_point end = the_clock::now();

	//auto time_taken = duration_cast<milliseconds>(end - start).count();

	//cout << "time taken " << time_taken << " ms." << endl;

	return 0;
}