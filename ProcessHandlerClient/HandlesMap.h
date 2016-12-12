#pragma once

#include <Windows.h>

#include <list>
using namespace std;

class HandlesMap {
public:
	void AddPair(HANDLE pid, HANDLE childPid);
	HANDLE PopChildByParent(HANDLE pid);
	void Clear();

private:
	typedef struct _HANDLE_PAIR {
		HANDLE parent;
		HANDLE child;
	} HANDLE_PAIR;

	typedef list<HANDLE_PAIR> HANDLE_PAIR_LIST;

	HANDLE_PAIR_LIST procList;
};
