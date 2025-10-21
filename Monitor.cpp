#include "Monitor.h"
#include <string>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <atomic>

using namespace std;

string Monitor::monitor_string = "*"; //append()
mutex mutex_for_monitor;
condition_variable cv_vowel_add;
atomic<bool> Monitor::monitor_finished = false;
atomic<int> Monitor::vowels_count = 0;

bool is_vowel(string st)
{
	if (st == "a" || st == "A") return true;
	else return false;
}


void Monitor::add_to_monitor(string letter, string t_name, int t_c)
{
	unique_lock<mutex> lk(mutex_for_monitor);
	if (monitor_finished) return;
	if (is_vowel(letter)) {
		monitor_string.append(letter);
		vowels_count++;
		cv_vowel_add.notify_all();
	}
	else {
		cv_vowel_add.wait(lk, [] {return vowels_count >= 3 || monitor_finished; });
		if (monitor_finished) return;
		vowels_count = vowels_count - 3;
		monitor_string.append(letter);
	}
	cout << "Iter: " << t_c << " " << t_name << ": added letter: " << letter << endl;
	
	if (t_c == 14 && !monitor_finished) {
		monitor_finished = true;
		std::cout << t_name << "=========reached 15 letters=========" << endl;
		cv_vowel_add.notify_all();
	}
}

string Monitor::get_from_monitor()
{
	unique_lock<mutex> lk(mutex_for_monitor);
	return monitor_string;
}
