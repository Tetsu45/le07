#include <iostream>
#include <cstdio>

class Node {
public:
    int parent;
    int depth;
    int* children;
    int sibling;
    int child_count;
    int height;
    Node(){
        parent = -1;
        depth = 0;
        children = NULL;
        child_count = 0;
        sibling = -1;
        height = 0;
    }
    void reserveChildren(int degree) {
        children = new int[degree];
        child_count = degree;
    }
    ~Node() {
        delete[] children;
    }
};

class BinaryTree {
private:
    Node* tree;
    int root;
    int node_count;

    int readInt() {
        int v = 0;
        char c;
        while ((c = getchar()) && (c < '0' || c > '9')){
            if(c == '-') return -1;
        }
        v = c & 15;
        while ((c = getchar()) >= '0' && c <= '9') {
            v = (v << 3) + (v << 1) + (c & 15);
        }
        return v;
    }

public:
    BinaryTree(int n)  {
        tree = new Node[n];
        root = -1;
        node_count = n;
    }

    ~BinaryTree() {
        delete[] tree;
    }

    void readInputs() {
        for (int i = 0; i < node_count; i++) {
            int* temp =  new int[2];
            int id =  readInt();
            int left = readInt();
            int right =  readInt();
            if(left != -1 && right == -1){
                temp[0] = left;
                tree[id].reserveChildren(1);
            }
            else if(left == -1 && right == -1) break;
            else {
                temp[0] = left;
                temp[0] = right;
                tree[id].reserveChildren(2);
            }

            for(int j = 0; j <tree[id].child_count;j++){
                tree[id].children[j] = temp[j];
                tree[temp[j]].parent =  id;
            }
            
        }
        findRoot();
    }

    void findRoot() {
        for (int i = 0; i < node_count; i++) {
            if (tree[i].parent == -1) {
                root = i;
                break;
            }
        }
    }

    void calculateDepth() {
        int* stack = new int[node_count];
        int stack_size = 0;
        stack[stack_size++] = root;
        while (stack_size > 0) {
            int id = stack[--stack_size];
            for (int j = 0; j < tree[id].child_count; j++) {
                int child = tree[id].children[j];
                tree[child].depth = tree[id].depth + 1;
                stack[stack_size++] = child;
            }
        }
        delete[] stack;
    }

    void printTreeNodes() {
        for (int i = 0; i < node_count; i++) {
            const char* nodeType = (tree[i].parent == -1) ? "root" :
                (tree[i].child_count == 0) ? "leaf" : "internal node";
            printf("node %d: parent = %d, degree = %d, depth = %d, %s, [", i, tree[i].parent,tree[i].child_count, tree[i].depth, nodeType);
            
        }
    }
     int findTreeHeight() {
        return findNodeHeight(root);
    }

    int findNodeHeight(int nodeId) {
        if (nodeId == -1) {
            return -1;
        }

        // Base case: leaf node
        if (tree[nodeId].child_count == 0) {
            return 0;
        }

        // Recursive case: internal node
        int maxChildHeight = -1;
        for (int i = 0; i < tree[nodeId].child_count; i++) {
            int childHeight = findNodeHeight(tree[nodeId].children[i]);
            maxChildHeight = std::max(maxChildHeight, childHeight);
        }

        return maxChildHeight + 1;
    }

    void calculateHeightForAllNodes() {
        for (int i = 0; i < node_count; i++) {
            tree[i].height = findNodeHeight(i);
        }
    }
    


};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    scanf("%d", &n);
    BinaryTree nodesTree(n);
    nodesTree.readInputs();
    nodesTree.calculateDepth();
    nodesTree.printTreeNodes();

    return 0;
}
