#include <iostream>
#include <cstdio>

class Node {
public:
    int parent;
    int depth;
    int* children;
    int child_count;
    Node(){
        parent = -1;
        depth = 0;
        children = NULL;
        child_count = 0;
    }

    void reserveChildren(int degree) {
        children = new int[degree];
        child_count = degree;
    }

    ~Node() {
        delete[] children;
    }
};

class RootTree {
private:
    Node* tree;
    int root;
    int node_count;

    int readInt() {
        int v = 0;
        char c;
        while ((c = getchar()) && (c < '0' || c > '9'));
        v = c & 15;
        while ((c = getchar()) >= '0' && c <= '9') {
            v = (v << 3) + (v << 1) + (c & 15);
        }
        return v;
    }

public:
    RootTree(int n)  {
        tree = new Node[n];
        root = -1;
        node_count = n;
    }

    ~RootTree() {
        delete[] tree;
    }

    void readInputs() {
        for (int i = 0; i < node_count; i++) {
            int id = readInt();
            int degree = readInt();
            tree[id].reserveChildren(degree);
            for (int j = 0; j < degree; j++) {
                int child = readInt();
                tree[id].children[j] = child;
                tree[child].parent = id;
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
            printf("node %d: parent = %d, depth = %d, %s, [", i, tree[i].parent, tree[i].depth, nodeType);
            for (int j = 0; j < tree[i].child_count; j++) {
                printf("%d%s", tree[i].children[j], (j == tree[i].child_count - 1) ? "" : ", ");
            }
            puts("]");
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    scanf("%d", &n);
    RootTree nodesTree(n);
    nodesTree.readInputs();
    nodesTree.calculateDepth();
    nodesTree.printTreeNodes();

    return 0;
}

