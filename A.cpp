#include <stdio.h>
#include <cstring>
using namespace std;
class Node{
  public:
  int id;
  int degree;
  int left;
  int right_sibling;
  int depth;
  Node(){
    id = 0;
    degree = 0;
    left =-1;
    right_sibling = -1;
    depth = 0;
  }
  ~Node(){

  }
};
class Root_tree{
  private:
  Node * tree;
  int nodes;
  public:
  Root_tree(int n){
    tree = new Node[n];
    nodes = n;
  }
  ~Root_tree(){
    delete[] tree;
  }
  void read_inputs();

};
void Root_tree:: read_inputs(){
  int x
}

int main(){
  return 0;
}
