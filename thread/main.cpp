#include <iostream>
#include <chrono>
#include <thread>
#include "workerthread.h"

int main()
{
	std::cout << "Hi, Welcome to demo of worker thread" << std::endl;

	{
		WorkerThread thread;
		WorkerThread thread2;
		thread.doSync([]{	std::cout << "First - blocking call" << std::endl;	});

		for (int i = 1; i < 100; i++)
		{
			auto& t = i % 2 == 0 ? thread : thread2;
			if (i == 10)
				thread.doSync([]{	std::cout << "Second - blocking call" << std::endl;	});

			t.doAsync([i]
			{
				std::this_thread::sleep_for(std::chrono::duration<int, std::milli>(200));
				std::cout << (i % 2 == 0 ? "thread-" : "thread2-") << "iteration number: " << i << std::endl;
			});
		}
		thread.wait();
		thread2.wait();

		thread.doSync([]{	std::cout << "Last - blocking call";	});
	}
	std::cout << "This must be last line\n";


}