#include "Monitor.h"
#include <string>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <atomic>

using namespace std;

string Monitor::monitor_string = "*"; //append()
mutex mutex_for_monitor;
condition_variable cv_add;
condition_variable cv_remove;
atomic<bool> Monitor::monitor_finished = false;

void Monitor::add_to_monitor(string letter, string t_name, int t_c)
{
	unique_lock<mutex> lk(mutex_for_monitor);
	monitor_string.append(letter);
	if (t_c >= 15) {
		monitor_finished = true;
		std::cout << t_name << "=========reached 15 letters=========" << endl;
	}
	cout << "Iter: " << t_c << " " << t_name << ": added letter: " << letter << endl;
	cv_remove.notify_one();
}

string Monitor::remove_from_monitor()
{
	unique_lock<mutex> lk(mutex_for_monitor);
	cv_add.notify_all();
	return monitor_string;
}
