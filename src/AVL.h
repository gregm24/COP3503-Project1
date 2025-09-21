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
  void insert(const string& name, const string& ID);        
  void remove(const string& ID);                            
  void searchID(const string& ID);                        
  void searchName(const string& name);                      
  void printInorder();                                        
  void printPreorder();                                       
  void printPostorder();                                      
  void printLevelCount();                                     
  void removeInorder(int n);    

  vector<int> inorder() {
    return {};
  }
  bool runCommand(string cmd) {
    return false;
  }

private:
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

  int height(Node* n);
  void update(Node* n);
  int balance(Node* n);
  Node* rotateRight(Node* y);
  Node* rotateLeft(Node* x);
  bool validName(const string& name);
  bool validID(const string& ID);
};



#endif //AVL_H