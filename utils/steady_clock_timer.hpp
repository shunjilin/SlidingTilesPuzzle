// timer class using chrono steady clock
// reference: Optimized C++ by Kurt Gunteheroth

#ifndef STEADYCLOCKTIMER_HPP
#define STEADYCLOCKTIMER_HPP

#include <chrono>

using namespace std::chrono;

class SteadyClockTimer {
public :
    // clears the timer
    SteadyClockTimer() : m_start(steady_clock::time_point::min()) {}

    // clears the timer
    void clear() {
	m_start = steady_clock::time_point::min();
    }

    // returns true if the timer is running
    bool isStarted() const {
	return m_start.time_since_epoch() != steady_clock::duration(0);
    }

    // start the timer
    void start() {
	m_start = steady_clock::now();
    }

    // get the number of milliseconds since timer started
    template<typename TimeUnit>
    milliseconds::rep getElapsedTime() {
	if (isStarted()) {
	    steady_clock::duration diff;
	    diff = steady_clock::now() - m_start;
	    return duration_cast<TimeUnit>(diff).count();
	}
	return 0;
    }
private:
    steady_clock::time_point m_start;
};

#endif
