#include <iostream>
#include <mutex>
#include <string>
#include "Monitor.h"

using namespace std;

void process(string letter, Monitor &monitor, string t_n, int t_count) {
	while (!Monitor::monitor_finished && t_count != 16) {
		monitor.add_to_monitor(letter, t_n, t_count);
		t_count++;
	}
	return;
}

int main() {
	Monitor monitor;
	int tA_count = 0;
	int tB_count = 0;
	int tC_count = 0;
	thread tA(process, "A", ref(monitor), "tA", tA_count);
	thread tB(process, "B", ref(monitor), "tB", tB_count);
	thread tC(process, "C", ref(monitor), "tC", tC_count);

	while (!Monitor::monitor_finished) {
		cout << "Monitor contains: " << monitor.remove_from_monitor() << endl;
	}

	tA.join();
	tB.join();
	tC.join();

	cout << "\n\n\nFinal monitor result: " << monitor.remove_from_monitor() << endl;
	cout << "Final monitor length: " << monitor.remove_from_monitor().length() << endl;
	return 0;
}