#include "workerthread.h"

#include <windows.h>

WorkerThread::WorkerThread() :isRunning(false)
{
	thread.reset(new std::thread([this]
	{
		isRunning = true;
		this->startThread();
	}));
}

WorkerThread::~WorkerThread()
{
	stop();	
}

void WorkerThread::startThread()
{
	std::unique_lock<std::mutex> l(mutex);

	do
	{
		while (isRunning && tasks.empty())
			itemInQueue.wait(l);

		while (!tasks.empty())
		{
			auto size = tasks.size();
			printf("Number of pending task are %d\n", size);
			const std::function<void()> t = tasks.front();
			tasks.pop_front();
			l.unlock();
			t();
			l.lock();
		}
		itemInQueue.notify_all();


	} while (isRunning);
	itemInQueue.notify_all();
}

void WorkerThread::doAsync(const std::function<void()>& t)
{
	std::lock_guard<std::mutex> _(mutex);
	tasks.push_back(t);
	itemInQueue.notify_one();

}

void WorkerThread::doSync(const std::function<void()>& t)
{
	std::condition_variable event;
	bool finished = false;

	std::unique_lock<std::mutex> l(mutex);
	auto lambda = [this, &t, &finished, &event]
	{
		t();
		std::lock_guard<std::mutex> l(mutex);

		finished = true;
		event.notify_one();
	};
	tasks.push_back(lambda);
	itemInQueue.notify_one();

	while (!finished)
		event.wait(l);

}

void WorkerThread::wait()
{
	std::unique_lock<std::mutex> l(mutex);
	while (!tasks.empty())
		itemInQueue.wait(l);
}

void WorkerThread::stop()
{
	{
		std::lock_guard<std::mutex> l(mutex);
		isRunning = false;
		itemInQueue.notify_one();
	}
	thread->join();
}