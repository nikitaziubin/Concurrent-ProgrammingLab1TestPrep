#include <string>
#include <atomic>

using namespace std;

class Monitor {
private: 
	static string monitor_string;
	static bool monitor_finished;
public:
	static int vowels_count;
	static void add_to_monitor(string letter, string t_name, int t_c);
	static string get_from_monitor();
	static bool get_monitor_status();
};
