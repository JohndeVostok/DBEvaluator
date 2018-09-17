#include "timer.h"

void Timer::tick() {
	gettimeofday(&st, 0);
}

void Timer::tock() {
	gettimeofday(&ed, 0);
}

int Timer::get() {
	if (ed.tv_sec < st.tv_sec) return -1;
	if (ed.tv_sec == st.tv_sec && ed.tv_usec < st.tv_usec) return -1;
	if (ed.tv_sec - st.tv_sec > 1000) return -1;
	return (ed.tv_sec - st.tv_sec) * 1000000 + (ed.tv_usec - st.tv_usec);
}
