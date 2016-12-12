#include "HandlesMap.h"

void HandlesMap::AddPair(HANDLE pid, HANDLE childPid) {

	HANDLE_PAIR newPair;
	newPair.parent = pid;
	newPair.child = childPid;

	procList.push_front(newPair);
}

HANDLE HandlesMap::PopChildByParent(HANDLE parent) {
	HANDLE result = NULL;

	for (HANDLE_PAIR_LIST::iterator it = procList.begin(); (!result) && (it != procList.end()); ++it)
	{
		if (it->parent == parent) {
			result = it->child;
		}
	}

	return result;
}

void HandlesMap::Clear() {
	procList.clear();
}