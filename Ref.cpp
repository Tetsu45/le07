#include <cstdio>

class Node {
public:
    int id;
    int degree;
    int parent;
    int left;
    int right_sibling;
    int depth;
    Node() {
        id = 0;
        degree = 0;
        parent = -1;
        left = -1;
        right_sibling = -1;
        depth = 0;
    }
    ~Node() {}
};

class Root_tree {
public:
    Node* tree;
    int nodes;
public:
    Root_tree(int n) {
        tree = new Node[n];
        nodes = n;
    }
    ~Root_tree() {
        delete[] tree;
    }
    void read_inputs();
    int  read_int();
    void add_child(int parent, int child);
    void calculate_depth(int id, int depth);
    void printTreeNodes(int id);
};

int read_int() {
    char ch = getchar_unlocked();
    int res = 0;
    while ('0' <= ch && ch <= '9') {
        res = res * 10 + ch - '0';
        ch = getchar_unlocked();
    }
    return res;
}

void print_str(const char* str) {
    while (*str != '\0') {
        putchar_unlocked(*str);
        ++str;
    }
}

char buf[1024];
void print_int(int x) {
    if (x < 0) {
        putchar_unlocked('-');
        x *= -1;
    }
    int ptr = 0, g;
    do {
        g = x / 10;
        buf[ptr++] = x - g * 10;
        x = g;
    } while (x > 0);
    while (ptr--) {
        putchar_unlocked(buf[ptr] + '0');
    }
}

void Root_tree::printTreeNodes(int id) {
    const char* nodeType;
    if (tree[id].parent == -1) {
        nodeType = "root";
    } else if (tree[id].degree == 0) {
        nodeType = "leaf";
    } else {
        nodeType = "internal node";
    }

    print_str("node ");
    print_int(id);
    print_str(": parent = ");
    print_int(tree[id].parent);
    print_str(", depth = ");
    print_int(tree[id].depth);
    print_str(", ");
    print_str(nodeType);
    print_str(", [");

    int child = tree[id].left;
    while (child != -1) {
        print_int(child);
        child = tree[child].right_sibling;
        if (child != -1) {
            print_str(", ");
        }
    }
    print_str("]\n");
}

void Root_tree::calculate_depth(int id, int depth) {
    tree[id].depth = depth;
    int child = tree[id].left;
    while (child != -1) {
        calculate_depth(child, depth + 1);
        child = tree[child].right_sibling;
    }
}

void Root_tree::add_child(int parent, int child) {
    if (tree[parent].left == -1) {
        tree[parent].left = child;
    } else {
        int sibling = tree[parent].left;
        while (tree[sibling].right_sibling != -1) {
            sibling = tree[sibling].right_sibling;
        }
        tree[sibling].right_sibling = child;
    }
    tree[parent].degree++;
    tree[child].parent = parent;
}

void Root_tree::read_inputs() {
    for (int i = 0; i < nodes; i++) {
        int id = read_int();
        int degree = read_int();
        for (int j = 0; j < degree; j++) {
            int child = read_int();
            add_child(id, child);
        }
    }
}

int main() {
    int n = read_int();
    Root_tree nodesTree(n);
    nodesTree.read_inputs();

    int root = 0;
    while (nodesTree.tree[root].parent != -1) {
        root++;
    }
    nodesTree.calculate_depth(root, 0);

    for (int i = 0; i < n; i++) {
        nodesTree.printTreeNodes(i);
    }

    return 0;
}
