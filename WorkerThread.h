#ifdef _WORKER_THREAD_H
#define _WORKER_THREAD_H

#include <thread>
#include <queue>
#include <mutex>
#include <atomic>
#include <condition_variable>
#include <string>

struct UserData {
	std::string msg;
	int year
};

struct ThreadMsg;

class WorkerThread final{
public:
	WorkerThread(const std::string threadName);
	~WorkerThread();
	
	// Call once create the workder thread
	bool createThread();

	// Call once program exit to exit worker thread
	void exitThread();

	// Get ID of this thread instance
	std::thread::id GetThreadId();

	// Get ID the currently executing thread
	static std::thread::id GetCurrentThreadId();

	// Add message thread queue
	void postMsg(std::shared_ptr<UserData< msg);

private:
	// Entry point for worker thread
	void Process();

	// Entry point timer thread
	void TimerThread();

	std::unique_ptr<std::thread> m_thread;
	std::queue<std::share_ptr<ThreadMsg>> m_queue;
	std::mutex m_mutex:
	std::condition_variable m_cv;
	std::aomic<bool> m_timerExit;
	std::string thread_name;
}


#endif
