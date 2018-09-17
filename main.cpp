#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <vector>

#include "timer.h"

using namespace std;

const int LOP = 16, LKEY = 32, LVALUE = 128;

int loadcnt, loadlen, runcnt, runlen;
char loadstr[LOP], runstr[LOP];

Timer timer;

vector <int> loadSetLatency, runSetLatency, runGetLatency;

void getConfig() {
	FILE *pf = fopen("config.txt", "r");
	fscanf(pf, "%s%d%d%s%d%d", loadstr, &loadcnt, &loadlen, runstr, &runcnt, &runlen);
	fclose(pf);
}

void testLatency() {
	char op[LOP], key[LKEY], value[LVALUE];
	FILE *pf = fopen(loadstr, "r");
	loadSetLatency.clear();
	for (int i = 0; i < loadcnt; i++) {
		fscanf(pf, "%s", op);
		if (!strcmp(op, "SET")) {
			fscanf(pf, "%s", key);
			fgetc(pf);
			fgets(value, loadlen + 1, pf);
			timer.tick();
			int t = strlen(value);
			printf("%s|%s|%s %d\n", op, key, value, t);
			timer.tock();
			loadSetLatency.emplace_back(timer.get());
		}
	}
	fclose(pf);
	pf = fopen(runstr, "r");
	for (int i = 0; i < runcnt; i++) {
		fscanf(pf, "%s", op);
		if (!strcmp(op, "SET")) {
			fscanf(pf, "%s", key);
			fgetc(pf);
			fgets(value, runlen + 1, pf);
			timer.tick();
			int t = strlen(value);
			printf("%s|%s|%s %d\n", op, key, value, t);
			timer.tock();
			runSetLatency.emplace_back(timer.get());
		}
		if (!strcmp(op, "GET")) {
			fscanf(pf, "%s", key);
			timer.tick();
			printf("%s %s\n", op, key);
			timer.tock();
			runGetLatency.emplace_back(timer.get());
		}
	}
	fclose(pf);
}

void testThroughput() {

}

int main() {
	getConfig();
	testLatency();
	for (auto &t : loadSetLatency) printf("%d ", t); printf(" totalcnt: %d\n", loadSetLatency.size());
	for (auto &t : runSetLatency) printf("%d ", t); printf(" totalcnt: %d\n", runSetLatency.size());
	for (auto &t : runGetLatency) printf("%d ", t); printf(" totalcnt: %d\n", runGetLatency.size());
}
