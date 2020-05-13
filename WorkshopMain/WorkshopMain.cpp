/*
* By :- 
* Ahmad Azri Bin Abd Razak
* B031920045
* 
* Workshop 1 Sem 2 19/20
* First Aid Application
*/
#include "Module.h"
#include "Command.h"
#include<unordered_set>
#include<string>
using namespace std;

int main() {
	Module module;
	Command c;
	unordered_set<string> duplicate;
	c.Connect();
	auto itemList = c.ItemListFilterZero();
	for (auto x : itemList) {
		if (duplicate.insert(x.NAME).second) {
			cout << endl;
			cout << (x.NAME);
			cout << (x.MAX_LIMIT) << endl;
			cout << (3) << endl;
		}

	}
	//module.IndexModule();
	return EXIT_SUCCESS;
}
