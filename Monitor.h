#include <string>
#include <atomic>

using namespace std;

class Monitor {
private: 
	static string monitor_string;
public:
	static atomic<int> vowels_count;
	static atomic<bool> monitor_finished;
	static void add_to_monitor(string letter, string t_name, int t_c);
	static string get_from_monitor();
};
