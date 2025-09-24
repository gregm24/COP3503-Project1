#include "AVL.h"
#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;

int AVL::height(Node* n) {  // Returns the stored height of a node.
    if (!n) return 0;
    else return n->height;
}

void AVL::update(Node* n) {  // Recomputes a node's height from its children.
    if (!n) return;
    
    int lh = height(n->left);
    int rh = height(n->right);

    if (lh > rh) {
        n->height = lh + 1;
    } else {
        n->height = rh + 1;
    }
}

int AVL::balance(Node* n) {  // Returns balance factor.
    if (!n) return 0;
    else return height(n->left) - height(n->right);
}

AVL::Node* AVL::rotateRight(Node* y) { // Performs an AVL right rotation rooted at y; returns new subtree root.
    Node* x = y->left;
    Node* z = nullptr;
    if (x) z = x->right;
    x->right = y;
    y->left = z;
    update(y);
    update(x);
    return x;
}

AVL::Node* AVL::rotateLeft(Node* x) {  // Performs an AVL left rotation rooted at x; returns new subtree root.
    Node* y = x->right;
    Node* z = nullptr;
    if (y) z = y->left;
    y->left = x;
    x->right = z;
    update(x);
    update(y);
    return y;
}

bool AVL::validName(const string& name) {  // Validates that name is non-empty and contains only letters and spaces.
    if (name.empty()) return false;
    for (size_t i = 0; i < name.size(); i++) {
        char c = name[i];
        if (!((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == ' ')) return false;
    }
    return true;
}

bool AVL::validID(const string& ID) {  // Validates that ID is exactly 8 numeric digits.
    if (ID.size() != 8) return false;
    for (size_t i = 0; i < ID.size(); i++) {
        char c = ID[i];
        if (!(c >= '0' && c <= '9')) return false;
    }
    return true;
}

AVL::Node* AVL::insertRecursiveHelper(Node* node, const string& name, const string& ID, int id_num, bool& inserted) {  // Recursive BST insert with AVL rebalancing.
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

    // Four standard AVL cases
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

void AVL::insert(const string& name, const string& ID) {  // Validates inputs, inserts into AVL, prints success/unsuccessful.
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

AVL::Node* AVL::minNode(Node* n) {  // Returns pointer to minimum node in a subtree.
    Node* current = n;
    while (current && current->left) current = current->left;
    return current;
}

AVL::Node* AVL::removeRecursiveHelper(Node* node, int id_num, bool& removed) {  // Recursive BST delete by ID, uses inorder sucessor for two-childen case.
    if (!node) return nullptr;

    if (id_num < node->ID_num) {
        node->left = removeRecursiveHelper(node->left, id_num, removed);
        return node;
    } else if (id_num > node->ID_num){
        node->right = removeRecursiveHelper(node->right, id_num, removed);
        return node;
    } else {
        removed = true;

        // No children
        if (!node->left && !node->right) {
            delete node;
            return nullptr;
        }

        // Only right child
        if (!node->left) {
            Node* r = node->right;
            delete node;
            return r;
        }

        // Only left child
        if (!node->right) {
            Node* l = node->left;
            delete node;
            return l;
        }

        // Two children
        Node* successor = minNode(node->right);
        node->name = successor->name;
        node->ID_str = successor->ID_str;
        node->ID_num = successor->ID_num;
        node->right = removeRecursiveHelper(node->right, successor->ID_num, removed);
        return node;
    }
}

void AVL::remove(const string& ID) {  // Validates ID, deletes node by ID, prints success/unsuccesful.
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

void AVL::searchID(const string& ID) {  // Searches by ID and prints the matching name or "unsuccessful".
    if (!validID(ID)) {
        cout << "unsuccessful" << endl;
        return;
    }

    int id_num = stoi(ID);

    Node* current = root;
    while (current) {
        if (id_num == current->ID_num) {
            cout << current->name << endl;
            return; 
        } else if (id_num < current->ID_num) current = current->left;
        else current = current->right;
    }
    cout << "unsuccessful" << endl;
}

void AVL::searchName(const string& name) {  // Searches for all nodes whose name exactly matches and prints IDs in preorder order or "unsuccessful" if none.

    if (!validName(name)) {
        cout << "unsuccessful" << endl;
        return;
    }

    stack<Node*> s;
    if (root) s.push(root);
    
    bool found = false;
    while (!s.empty()) {
        Node* n = s.top();
        s.pop();

        if (n->name == name) {
            cout << n->ID_str << endl;
            found = true;
        }

        if (n->right) s.push(n->right);
        if (n->left) s.push(n->left);
    }
    
    if (!found) cout << "unsuccessful" << endl;
}

void AVL::printInorderHelper(Node* node, bool& first) {  // Inorder traversal to print names with comma seperation.
    if (!node) return;

    printInorderHelper(node->left, first);
    
    if (!first) cout << ", ";
    cout << node->name;
    first = false;

    printInorderHelper(node->right, first);
}

void AVL::printInorder() {  // Prints comma-seperated inorder traversal of names.
    bool first = true;
    printInorderHelper(root, first);
    cout << endl;
}

void AVL::printPreorderHelper(Node* node, bool& first) {  // Preorder traversal to print names with comma separation.
    if (!node) return;

    if (!first) cout << ", ";
    cout << node->name;
    first = false;

    printPreorderHelper(node->left, first);
    printPreorderHelper(node->right, first);
}

void AVL::printPreorder() {  // Prints comma-seperated preorder traversal of names.
    bool first = true;
    printPreorderHelper(root, first);
    cout << endl;
}

void AVL::printPostorderHelper(Node* node, bool& first) {  // Postorder traversal to print names with comma seperation.
    if (!node) return;

    printPostorderHelper(node->left, first);
    printPostorderHelper(node->right, first);

    if (!first) cout << ", ";
    cout << node->name;
    first = false;
}

void AVL::printPostorder() {  // Prints comma-seperated postorder traversal of names.
    bool first = true;
    printPostorderHelper(root, first);
    cout << endl;
}

void AVL::printLevelCount() {  // Prints the number of levels in the tree.
    if (!root) cout << 0 << endl;
    else cout << root->height << endl;
}

AVL::Node* AVL::removeInorderHelper(Node* node, int& n) {  // Returns pointer to the nth node (0-based) in inorder traversal.
    if (!node) return nullptr;

    Node* left = removeInorderHelper(node->left, n);
    if (left) return left;

    if (n == 0) return node;
    n -= 1;

    return removeInorderHelper(node->right, n);
}

void AVL::removeInorder(int n) {  // Removes the nth node (by inorder index) if it exists and prints success/unsuccesful.
    if (n < 0) {
        cout << "unsuccessful" << endl;
        return;
    }

    int k = n;
    Node* target = removeInorderHelper(root, k);

    if (!target) {
        cout << "unsuccessful" << endl;
        return;
    }

    bool removed = false;
    root = removeRecursiveHelper(root, target->ID_num, removed);

    if (removed) cout << "successful" << endl;
    else cout << "unsuccessful" << endl;
}

void AVL::inorderHelper(Node *node, vector<int>& result) {  // Inorder traversal that collects IDs into 'result'.
    if (!node) return;
    inorderHelper(node->left, result);
    result.push_back(node->ID_num);
    inorderHelper(node->right, result);
}

vector<int> AVL::inorder() {  // Returns the inorder traversal of IDs
    vector<int> result;
    inorderHelper(root, result);
    return result;
}

AVL::~AVL() {  // Destructor
    function<void(Node*)> clear = [&](Node* n) {
        if (!n) return;
        clear(n->left);
        clear(n->right);
        delete n;
    };
    clear(root);
    root = nullptr;
}