#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include "AVL.h"
#include "AVL.cpp"
using namespace std;

// Gregory Myers - 74883466

TEST_CASE("Incorrect Commands", "[flag]") {  // Tests invalid commands and inputs to insure the AVL tree rejects them.
	AVL tree;

	tree.insert("", "12345678");
	REQUIRE(tree.inorder().empty());
	tree.insert("A11y", "45679999");
	REQUIRE(tree.inorder().empty());
	tree.insert("Alice", "123");
	REQUIRE(tree.inorder().empty());
	tree.insert("Bob", "ABCDEFGH");
	REQUIRE(tree.inorder().empty());
	tree.remove("notanid");
	REQUIRE(tree.inorder().empty());
}

TEST_CASE("Edge Cases", "[flag]") {  //  Tests removing from an empty tree, attempting to insert a duplicate id, and removing a non-existent index.
	AVL t;

	t.remove("99999999");
	REQUIRE(t.inorder().empty());

	t.insert("Alice", "00000100");
	vector<int> snapshot = t.inorder();
	t.insert("Bob", "00000100");
	REQUIRE(t.inorder() == snapshot);

	t.removeInorder(5);
	REQUIRE(t.inorder() == snapshot);
}

TEST_CASE("Rotations", "[flag]") {  // Tests all four AVL rotation cases.

	SECTION("right rotation") {
		AVL t;
		t.insert("G", "00000070");
		t.insert("F", "00000060");
		t.insert("E", "00000050");
		t.insert("D", "00000040");
		t.insert("C", "00000030");
		t.insert("B", "00000020");
		t.insert("A", "00000010");

		vector<int> expected{10, 20, 30, 40, 50, 60, 70};
		REQUIRE(t.inorder() == expected);
	}

	SECTION("left rotation") {
		AVL t;
		t.insert("A", "00000010");
		t.insert("B", "00000020");
		t.insert("C", "00000030");
		t.insert("D", "00000040");
		t.insert("E", "00000050");
		t.insert("F", "00000060");
		t.insert("G", "00000070");

		vector<int> expected{10, 20, 30, 40, 50, 60, 70};
		REQUIRE(t.inorder() == expected);
	}

	SECTION("left-right rotation") {
		AVL t;
		t.insert("C", "00000030");
		t.insert("A", "00000010");
		t.insert("B", "00000020");
		t.insert("Z", "00000005");
		t.insert("Y", "00000015");
		t.insert("X", "00000025");
		t.insert("D", "00000035");

		vector<int> expected{5, 10, 15, 20, 25, 30, 35};
		REQUIRE(t.inorder() == expected);
	}

	SECTION("right-left rotation") {
		AVL t;
		t.insert("A", "00000010");
		t.insert("C", "00000030");
		t.insert("B", "00000020");
		t.insert("Z", "00000005");
		t.insert("Y", "00000015");
		t.insert("X", "00000025");
		t.insert("D", "00000035");

		vector<int> expected{5, 10, 15, 20, 25, 30, 35};
		REQUIRE(t.inorder() == expected);
	}
}

TEST_CASE("3 Deletion Cases", "[flag]") {  // Tests deleting a leaf node, a node with one child, and a node with two children.
	AVL t;

	t.insert("A", "00000020");
	t.insert("B", "00000010");
	t.insert("C", "00000030");
	t.insert("D", "00000005");
	t.insert("E", "00000015");
	t.insert("F", "00000025");
	t.insert("G", "00000035");
	t.insert("H", "00000040");


	t.remove("00000005");
	vector<int> exp1{10, 15, 20, 25, 30, 35, 40};
	REQUIRE(t.inorder() == exp1);


	t.remove("00000035");
	vector<int> exp2{10, 15, 20, 25, 30, 40};
	REQUIRE(t.inorder() == exp2);

	t.remove("00000020");
	vector<int> exp3{10, 15, 25, 30, 40};
	REQUIRE(t.inorder() == exp3);
}

TEST_CASE("BST Insert", "[flag]"){ // Inserts 100 unique random IDs and removes 10.
	AVL t;
	vector<int> expected, actual;

	while (expected.size() < 100) {
		int randomInput = 10000000 + (rand() % 90000000);
		if (count(expected.begin(), expected.end(), randomInput) == 0) {
			expected.push_back(randomInput);
			t.insert("A", to_string(randomInput));
		}
	}


	for (int j = 0; j < 10; j++) {
		int idx = rand() % expected.size();
		t.remove(to_string(expected[idx]));
		expected.erase(expected.begin() + idx);
	}

	actual = t.inorder();
	REQUIRE(expected.size() == actual.size());
	sort(expected.begin(), expected.end());
	REQUIRE(expected == actual);
}
