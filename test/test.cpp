#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>

#include "AVL.h"
using namespace std;

// Gregory Myers - 74883466

TEST_CASE("Incorrect Commands", "[flag]"){
	AVL tree;

	REQUIRE(tree.runCommand("") == false);
	REQUIRE(tree.runCommand("insert \"A11y\" 45679999") == false);
	REQUIRE(tree.runCommand("insert") == false);
	REQUIRE(tree.runCommand("remove string") == false);
	REQUIRE(tree.runCommand("print inorder tooMany") == false);
}

TEST_CASE("Insert & Rotations", "[flag]") {

	SECTION("right rotation") {
		AVL t;
		t.insert(30);
		t.insert(20);
		t.insert(10);
		vector<int> expected{10, 20, 30};
		REQUIRE(t.inorder() == expected);
	}

	SECTION("left rotation") {
		AVL t;
		t.insert(10);
		t.insert(20);
		t.insert(30);
		std::vector<int> expected{10, 20, 30};
		REQUIRE(t.inorder() == expected);
	}

	SECTION("left-right rotation") {
		AVL t;
		t.insert(30);
		t.insert(10);
		t.insert(20);
		std::vector<int> expected{10, 20, 30};
		REQUIRE(t.inorder() == expected);
	}

	SECTION("right-left rotation") {
		AVL t;
		t.insert(10);
		t.insert(30);
		t.insert(20);
		std::vector<int> expected{10, 20, 30};
		REQUIRE(t.inorder() == expected);
	}
}

TEST_CASE("BST Insert", "[flag]"){
	AVL t;
	vector<int> expected, actual;

	for (int i = 0; i < 100; i++) {
		int randomInput = rand();
		if (count(expected.begin(), expected.end(), randomInput) == 0) {
			expected.push_back(randomInput);
			t.insert(randomInput);
		}
	}

	for (int j = 0; j < 10; j++) {
		int idx = rand() % expected.size();
		t.remove(expected[idx]);
		expected.erase(expected.begin() + idx);
	}

	actual = t.inorder();
	REQUIRE(expected.size() == actual.size());
	sort(expected.begin(), expected.end());
	REQUIRE(expected == actual);
}
