// Simple threading example
// Adam Sampson <a.sampson@abertay.ac.uk>

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

// Import things we need from the standard library
using std::chrono::seconds;
using std::cout;
using std::endl;
using std::ofstream;
using std::this_thread::sleep_for;
using std::thread;


std::mutex mtx;

struct threadArgs {
	int foo;
	int bar;
};

struct threadArgs2 {
	int id;
	int delay;
};


void myThreadFunc(threadArgs* args,threadArgs2* args2)
{
	/*sleep_for(seconds(3));
	cout << "I am myThreadFunc\n";
	cout << args->foo << "\n";
	cout << args->bar << "\n";
	(*args).foo = 20;
	(*args).bar = 25;*/

	/*for (int i = 0; i < 10; i++)
	{*/
		sleep_for(std::chrono::milliseconds(args2->delay));
		mtx.lock();
		cout << "id=" << args2->id << ", delay=" << args2->delay << "\n";
		mtx.unlock();
	/*}*/
};


void myThreadFunc2(threadArgs& args, threadArgs2& args2)
{
	sleep_for(seconds(3));
	cout << "I am myThreadFunc2\n";
	cout << args.foo << "\n";
	cout << args.bar << "\n";
	args.foo = 150;
	args.bar = 200;

	for (int i = 0; i < 10; i++)
	{
		cout << args2.id << "\n";
		sleep_for(std::chrono::milliseconds(args2.delay));
	}
};


int main(int argc, char *argv[])
{
	threadArgs t1, t2;

	t1.foo = 10;
	t1.bar = 15;

	t2.foo = 50;
	t2.bar = 100;

	threadArgs2 b1, b2;

	b1.id = 11;
	b1.delay = 1000;

	b2.id = 12;
	b2.delay = 1000;





	std::vector<thread> vThreads;
	std::vector<threadArgs2> gStructs;
	

	

	for (int i = 0; i < 10; i++)
	{
		threadArgs2 tmp;
		tmp.id = i;
		tmp.delay = 500 + i * 100;
		

		gStructs.push_back(tmp);
	}

	for (int i = 0; i < 10; i++)
	{
		vThreads.push_back(thread(myThreadFunc, &t1, &gStructs[i]));
	}

	
	for (int i = 0; i < 10; i++)
	{
		vThreads[i].join();
	}

	


	//pass by pointer
	thread myThread(myThreadFunc, &t1, &b1);
	
	cout << "I am main\n";

	myThread.join();

	/*cout << t1.foo << "\n";
	cout << t1.bar << "\n";*/

	////pass by ref
	//thread myThread2(myThreadFunc2, std::ref(t2), std::ref(b2));
	//myThread2.join();

	//cout << t2.foo << "\n";
	//cout << t2.bar << "\n";


	// Now we just have the initial thread. So it's safe to exit.

	cout << "All done\n";
	sleep_for(seconds(3));

	return 0;
}
