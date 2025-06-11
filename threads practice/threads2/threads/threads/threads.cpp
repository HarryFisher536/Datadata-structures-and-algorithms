// Simple threading example


#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>


// Import things we need from the standard library
using std::chrono::seconds;
using std::cout;
using std::endl;
using std::ofstream;
using std::this_thread::sleep_for;
using std::thread;
using std::mutex;



std::condition_variable result_cv;
int results;
bool result_ready = false;
mutex result_mutex;

void producer()
{
	sleep_for(seconds(2));
	std::unique_lock<mutex> lock(result_mutex);
	result_ready = true;
	result_cv.notify_one();
}

void consumer()
{
	std::unique_lock<mutex> lock(result_mutex);

	while (!result_ready)
	{
		result_cv.wait(lock);
	}

	cout << "result is " << results << endl;
}





void myThreadFunc()
{
	sleep_for(seconds(3));
	cout << "I am myThreadFunc\n";
}


int main(int argc, char *argv[])
{
	// At the moment our program is only running one thread (the initial one the operating system gave us).

	thread myThread(producer);

	thread myThread2(consumer);

	// Now our program is running two threads in parallel (the initial one, and myThread).
	
	cout << "I am main\n";

	// Wait for myThread to finish.
	myThread.join();
	myThread2.join();

	// Now we just have the initial thread. So it's safe to exit.

	cout << "All done\n";
	sleep_for(seconds(3));

	return 0;
}
