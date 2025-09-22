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

bool AVL::validID(const string& ID) {
    if (ID.size() != 8) return false;
    for (size_t i = 0; i < ID.size(); i++) {
        char c = ID[i];
        if (!(c >= '0' && c <= '9')) return false;
    }
    return true;
}

AVL::Node* AVL::insertRecursiveHelper(Node* node, const string& name, const string& ID, int id_num, bool& inserted) {
    if (!node) {
        inserted = true;
        return new Node(name, ID, id_num);
    }

    if (id_num < node->ID_num) {
        node->left = insertRecursiveHelper(node->left, name, ID, id_num, inserted);
    } else if (id_num > node->ID_num) {
        node->right = insertRecursiveHelper(node->right, name, ID, id_num, inserted);
    } else {
        inserted = false;
        return node;
    }

    update(node);
    int b = balance(node);

    if (b > 1 && id_num < node->left->ID_num) return rotateRight(node);
    if (b < -1 && id_num > node->right->ID_num) return rotateLeft(node);
    if (b > 1 && id_num > node->left->ID_num) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (b < -1 && id_num < node->right->ID_num) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

void AVL::insert(const string& name, const string& ID) {
    if (!validName(name) || !validID(ID)) {
        cout << "unsuccessful" << endl;
        return;
    }

    int id_num = stoi(ID);
    bool inserted = false;
    root = insertRecursiveHelper(root, name, ID, id_num, inserted);

    if (inserted) cout << "successful" << endl;
    else cout << "unsuccessful" << endl;
}

AVL::Node* AVL::minNode(Node* n) {
    Node* current = n;
    while (current && current->left) current = current->left;
    return current;
}

AVL::Node* AVL::removeRecursiveHelper(Node* node, int id_num, bool& removed) {
    if (!node) return nullptr;

    if (id_num < node->ID_num) {
        node->left = removeRecursiveHelper(node->left, id_num, removed);
        return node;
    } else if {
        node->right = removeRecursiveHelper(node->right, id_num, removed);
        return node;
    } else {
        removed = true;

        if (!node->left && !node->right) {
            delete node;
            return nullptr;
        }

        if (!node->left) {
            Node* r = node->right;
            delete node;
            return r;
        }

        if (!node->right) {
            Node* l = node->left;
            delete node;
            return l;
        }

        Node* successor = minNode(node->right);
        node->name = successor->name;
        node->ID_str = successor->ID_str;
        node->ID_num = successor->ID_num;
        node->right = removeRecursiveHelper(node->right, successor->ID_num, removed);
        return node;
    }
}

void AVL::remove(const string& ID) {
    if (!validID(ID)) {
        cout << "unsuccessful" << endl;
        return;
    }

    int id_num = stoi(ID);
    bool removed = false;
    root = removeRecursiveHelper(root, id_num, removed);
    if (removed) cout << "successful" << endl;
    else cout << "unsuccessful" << endl;
}

void AVL::searchID(const string& ID) {
    if (!validID(ID)) {
        cout << unsuccessful << endl;
        return;
    }

    int id_num = stoi(ID);

    Node* current = root;
    while (current) {
        if (id_num == current->ID_num) {
            cout << current->name << endl;
            return; 
        } else if (id_num < current->ID_num) current -> current->left;
        else current -> current->right;
    }
    cout << "unsuccessful" << endl;
}