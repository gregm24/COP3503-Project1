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
  void insert(const string& name, const string& ufid);        // prints successful/unsuccessful
  void remove(const string& ufid);                            // prints successful/unsuccessful
  void searchID(const string& ufid);                        // prints NAME or unsuccessful
  void searchName(const string& name);                      // prints IDs or unsuccessful
  void printInorder();                                        // prints comma-separated names
  void printPreorder();                                       // prints comma-separated names
  void printPostorder();                                      // prints comma-separated names
  void printLevelCount();                                     // prints integer
  void removeInorder(int n);    

  vector<int> inorder() {
    return {};
  }
  bool runCommand(string cmd) {
    return false;
  }
};



#endif //AVL_H
