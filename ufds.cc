#include <unordered_map>

struct ufds {
    int* parent;
    int* rank;

    ufds (int n) {
        parent = new int[n];
        rank = new int[n];
    }

    ~ufds () {
        delete parent;
        delete rank;
    }

    int find(int n) {
        if (parent[n] == n) {
            return n;
        }
        parent[n] = find(parent[n]);
        return parent[n];
    }

    void makeset(int n) {
        parent[n] = n;
        rank[n] = 0;
    }

    void link(int n, int m) {
        if (rank[n] > rank[m]) {
            parent[m] = n;
        } else if (rank[n] == rank[m]) {
            rank[n]++;
            parent[m] = n;
        } else {
            parent[n] = m;
        }
    }

    void unite(int n, int m) {
        link(find(n), ufds::find(m));
    }
};