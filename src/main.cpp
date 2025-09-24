#include <iostream>
#include <string>
#include <regex>
#include "AVL.h"
using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	AVL tree;
	int N;
	if (!(cin >> N)) return 0;
	string dummy;
	getline(cin, dummy);

	regex insertR("^insert\\s+\"([A-Za-z ]+)\"\\s+([0-9]{8})$");
	regex removeR("^remove\\s+([0-9]{8})$");
	regex searchNameR("^search\\s+\"([A-Za-z ]+)\"$");
	regex searchIdR("^search\\s+([0-9]{8})$");
	regex inorderR("^printInorder$");
	regex preorderR("^printPreorder$");
	regex postorderR("^printPostorder$");
	regex levelR("^printLevelCount$");
	regex removeInorderR("^removeInorder\\s+([0-9]+)$");


	for (int i = 0; i < N; i++) {
		string line;
		getline(cin, line);

		smatch m;
		if (regex_match(line, m, insertR)) {
			tree.insert(m[1], m[2]);
		} else if (regex_match(line, m, removeR)) {
			tree.remove(m[1]);
		} else if (regex_match(line, m, searchNameR)) {
			tree.searchName(m[1]);
		} else if (regex_match(line, m, searchIdR)) {
			tree.searchID(m[1]);
		} else if (regex_match(line, inorderR)) {
			tree.printInorder();
		} else if (regex_match(line, preorderR)) {
			tree.printPreorder();
		} else if (regex_match(line, postorderR)) {
			tree.printPostorder();
		} else if (regex_match(line, levelR)) {
			tree.printLevelCount();
		} else if (regex_match(line, m, removeInorderR)) {
			int idx = stoi(m[1]);
			tree.removeInorder(idx);
		} else {
			cout << "unsuccessful\n";
		}
	}
	return 0;
}
