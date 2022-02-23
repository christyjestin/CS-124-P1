#include <unordered_map>

struct ufds {
    std::unordered_map<int, int> parent;
    std::unordered_map<int, int> rank;

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