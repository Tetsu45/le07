#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
class Node{
  public:
  int id;
  int degree;
  int parent;
  int left;
  int right_sibling;
  int depth;
  Node(){
    id = 0;
    degree = 0;
    parent = -1;
    left =-1;
    right_sibling = -1;
    depth = 0;
  }
  ~Node(){}
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
  int  read_int();
  void add_child(int parent,int child);
  void calculate_depth(int depth);
  void printTreeNodes(int id);
};
void Root_tree::printTreeNodes(int id){
  char* nodeType;
  if(tree[id].parent == -1){
    nodeType = "root";
  }
  else if(tree[id].degree == 0){
    nodeType = "leaf";
  }
  else nodeType = "internal node";
  printf("node %d: parent = %d, depth = %d, %s, [",id,tree[id].parent,tree[id].depth,nodeType);
  int child = tree[id].left;
  while(child!= -1){
  printf("%d",child);
  child = tree[child].right_sibling;
  if(child != -1){
  printf(", ") 
  }
  }
   printf("]\n");
}
void Root_tree::calculate_depth(int depth){
  int root = 0;
  while(tree[root].parent != -1){
    root++;
  }
  tree[root].depth =  depth;
  int child = tree[root].left;
  while(child != -1){
    calculate_depth(child,depth+1);
    child = tree[child].right_sibling;
  }
}

void Root_tree::add_child(int parent,int child){
  if(tree[parent].left == -1){
    tree[parent].left = child;
  }
  else {
    int sibling = tree[parent].left;
    while(tree[sibling].right_sibling != -1){
      sibling = tree[sibling].right_sibling;
    }
    tree[sibling].right_sibling = child;
  }
  tree[parent].degree++;
  tree[child].parent =  parent;
}
int Root_tree::read_int(){
  int num = 0;
  char c;
  while (cin.get(c) && c >= '0' && c <= '9') {
    num = num * 10 + (c - '0');
}
return num;
} 
void Root_tree:: read_inputs(){
  //int num = 0;
  //char c;
  for(int i = 0;i < nodes;i++){
    int id = read_int();
    int degree = read_int();
    for(int j =0;j<degree;j++){
      int child = read_int();
      add_child(id,child);
    }
  }
}

int main(){
  int n;
  cin >> n;
  Root_tree nodesTree(n);
  nodesTree.read_inputs();
  nodesTree.calculate_depth(0);
  for(int i = 0;i < n; i++){
    nodesTree.printTreeNodes(i);
  }
  return 0;
}
