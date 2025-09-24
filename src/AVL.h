//
// Created by Greg Myers on 9/19/25.
//

#ifndef AVL_H
#define AVL_H

#include <vector>
#include <string>
using namespace std;

class AVL {
public:
  // PROJECT FUNCTIONS
  void insert(const string& name, const string& ID);        
  void remove(const string& ID);                            
  void searchID(const string& ID);                        
  void searchName(const string& name);                      
  void printInorder();                                        
  void printPreorder();                                       
  void printPostorder();                                      
  void printLevelCount();                                     
  void removeInorder(int n);
  vector<int> inorder();
  ~AVL();

private:
  // NODE
  struct Node {
    string name;
    string ID_str;
    int ID_num;
    int height;
    Node* left;
    Node* right;
    Node (const string& n, const string& s, int i)
      : name(n), ID_str(s), ID_num(i), height(1), left(nullptr), right(nullptr) {}
  };

  Node* root = nullptr; 

  // HELPER FUNCTIONS
  int height(Node* n);
  void update(Node* n);
  int balance(Node* n);
  Node* rotateRight(Node* y);
  Node* rotateLeft(Node* x);
  bool validName(const string& name);
  bool validID(const string& ID);
  Node* insertRecursiveHelper(Node* node, const string& name, const string& ID, int id_num, bool& inserted);
  Node* minNode(Node* n);
  Node* removeRecursiveHelper(Node* node, int id_num, bool& removed);
  void printInorderHelper(Node* node, bool& first);
  void printPreorderHelper(Node* node, bool& first);
  void printPostorderHelper(Node* node, bool& first);
  Node* removeInorderHelper(Node* node, int& n);
  void inorderHelper(Node* node, vector<int>& result);
};



#endif //AVL_H