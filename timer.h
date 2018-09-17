#include <sys/time.h>

class Timer {
private:
	struct timeval st, ed;
public:
	void tick();
	void tock();
	int get();
};
