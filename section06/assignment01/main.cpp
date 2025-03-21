#include <iostream>
#include <mutex>
#include <thread>
#include <string>

using namespace std;
using namespace std::chrono;

// Global variables
mutex mut;
string sdata{"Empty"};

auto is_edited {false};
mutex is_edited_mut;

// Waiting thread
void reader() {
    unique_lock<std::mutex> guard(mut);
    while (!is_edited) {
        guard.unlock();
        this_thread::sleep_for(10ms);
        guard.lock();
    }

    guard.unlock();
    cout << "Data is " << sdata << endl;
}

// Modyifing thread
void writer() {
    cout << "Writing data..." << endl;
    {
        lock_guard lck_guard(mut);
        std::this_thread::sleep_for(2s);
        sdata = "Populated";
    }

    lock_guard lck_guard(is_edited_mut);
    is_edited = true;
}

int main() {
	cout << "Data is " << sdata << endl;
	thread read{reader};
    thread write{writer};
	/*
	// If the writer thread finishes before the reader thread starts, the notification is lost
	thread write{writer};
	std::this_thread::sleep_for(500ms);
	thread read{reader};
	*/
	write.join();
	read.join();
}