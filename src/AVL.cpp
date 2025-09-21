#include "AVL.h"
#include <iostream>
#include <algorithm>
using namespace std;

int AVL::height(Node* n) {
    if (!n) return 0;
    else return n->height;
}

void AVL::update(Node* n) {
    if (!n) return;
    
    int lh = height(n->left);
    int rh = height(n->right);

    if (lh > rh) {
        n->height = lh + 1;
    } else {
        n->height = rh + 1;
    }
}

int AVL::balance(Node* n) {
    if (!n) return 0;
    else return height(n->left) - height(n->right);
}

AVL::Node* AVL::rotateRight(Node* y) {
    Node* x = y->left;
    Node* z = nullptr;
    if (x) z = x->right;
    x->right = y;
    y->left = z;
    update(y);
    update(x);
    return x;
}

AVL::Node* AVL::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* z = nullptr;
    if (y) z = y->left;
    y->left = x;
    x->right = z;
    update(x);
    update(y);
    return y;
}

bool AVL::validName(const string& name) {
    if (name.empty()) return false;
    for (size_t i = 0; i < name.size(); i++) {
        char c = name[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ')) return false;
    }
    return true;
}

bool AVL:validID(const string& ID) {
    if (ID.size() != 8) return false;
    for (size_t = 0; i < ID.size(); i++) {
        char c = ID[i];
        if (!(c >= '0' && c <= '9')) return false;
    }
    return true;
}

void AVL::insert(const string& name, const string& ID) {

}