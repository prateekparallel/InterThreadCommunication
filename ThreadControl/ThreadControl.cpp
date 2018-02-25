#include "stdafx.h"//remove this header file if you are compiling with different compiler
#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include "windows.h"//remove this header file if you are compiling with different compiler

std::condition_variable _tcond1;
std::condition_variable _tcond2;
std::condition_variable _tcond3;

class SimpleThread1
{
private:
	std::mutex  _lockprint;
	bool isThreadAlive = true;
	
public:
	SimpleThread1(){}
	SimpleThread1(SimpleThread1 &st){};

	void StartProcessing()
	{
		std::unique_lock<std::mutex> locker(_lockprint);
          	//Add your business logic(parallel execution codes)  here
		_tcond1.wait(locker);
		std::cout << "I am thread :1"<<std::endl;
		_tcond3.notify_one();
	}
	void operator()()
	{
		while (isThreadAlive)
		 StartProcessing();
	}

	void stopeThread()
	{
		isThreadAlive = false;
	}
};

class SimpleThread2
{
private:
	std::mutex  _lockprint;
	bool isThreadAlive = true;
	
public:
	SimpleThread2(){}
	SimpleThread2(SimpleThread2 &st) {};

	void StartProcessing()
	{
		std::unique_lock<std::mutex> locker(_lockprint);
              //Add your business logic(parallel execution codes)  here
		_tcond2.wait(locker);
		std::cout << "I am thread :2"<< std::endl;
		_tcond1.notify_one();
	}
	void operator()()
	{
		while (isThreadAlive)
			StartProcessing();
	}

	void stopeThread()
	{
		isThreadAlive = false;
	}
};


class SimpleThread3
{
private:
	std::mutex  _lockprint;
	bool isThreadAlive = true;
	
public:
	SimpleThread3(){}
	SimpleThread3(SimpleThread3 &st) {};

	void StartProcessing()
	{
		std::unique_lock<std::mutex> locker(_lockprint);
		//Add your business logic(parallel execution codes)  here
		_tcond3.wait(locker);
		std::cout << "I am thread :3"<< std::endl;
		_tcond2.notify_one();
	}
	void operator()()
	{
		while (isThreadAlive)
			StartProcessing();
	}

	void stopeThread()
	{
		isThreadAlive = false;
	}
};

int main()
{
	SimpleThread1 st1;
	SimpleThread2 st2;
	SimpleThread3 st3;
	std::thread t1(st1);
	std::thread t2(st2);
	std::thread t3(st3);
	_tcond1.notify_one();
	t1.detach();
	t2.detach();
	t3.detach();
	Sleep(1000);//replace it with sleep(10) for linux/unix
	st1.stopeThread();
	st2.stopeThread();
	st3.stopeThread();
	return 0;
}
