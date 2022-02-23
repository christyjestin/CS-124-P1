#include <vector>
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <cassert>
#include <math.h>
#include "ufds.cc"

struct edge {
    int u;
    int v;
    float dist;
};

struct euclid_node {
    int v;
    std::vector<float> coords;

    euclid_node(int i, int dim) {
        v = i;
        coords = std::vector<float> (dim, 0);
    }
};

// random number between 0 to 1
float unif() {
    return ((float) rand() / RAND_MAX);
}

float dist(std::vector<float> a, std::vector<float> b) {
    assert(a.size() == b.size());
    std::vector<float> diff;
    for (int i = 0; i < (int) a.size(); i++) {
        float d = a[i] - b[i];
        diff.push_back(d * d);
    }
    return sqrt(std::accumulate(diff.begin(), diff.end(), 0.0f));
}

std::vector<edge> zero_dim_graph(int n) {
    std::vector<edge> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            edges.push_back(edge {i, j, unif()});
        }
    }
    return edges;
}

std::vector<edge> higher_dim_graph(int n, int dim) {
    std::vector<euclid_node> nodes;
    std::vector<edge> edges;
    for (int i = 0; i < n; i++) {
        euclid_node new_node (i, dim);
        for (auto it = new_node.coords.begin(); it != new_node.coords.end(); it++) {
            *it = unif();
        }
        nodes.push_back(new_node);
    }
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            edges.push_back(edge {i, j, dist(nodes[i].coords, nodes[j].coords)});
        }
    }
    return edges;
}

std::vector<edge> kruskal(int n, std::vector<edge> edges) {
    ufds sets;
    for (int i = 0; i < n; i++) {
        sets.makeset(i);
    }
    sort(edges.begin(), edges.end(), [](const auto &x, const auto &y){return x.dist < y.dist;});

    std::vector<edge> mst;

    for (auto edge : edges) {
        if (sets.find(edge.u) != sets.find(edge.v)) {
            sets.unite(edge.u, edge.v);
            mst.push_back(edge);
            if ((int) mst.size() == n-1) break;
        }
    }
    return mst;
}

inline float add_weight(float sum, edge e) {
    return sum + e.dist;
}

float sum_weights(std::vector<edge> mst) {
    return std::accumulate(mst.begin(), mst.end(), 0.0f, add_weight);
}

int main(int argc, char** argv) {
    assert(argc == 5);
    int n = atoi(argv[2]);
    int numtrials = atoi(argv[3]);
    int dim = atoi(argv[4]);
    srand(time(0));
    for (int i = 0; i < numtrials; i++) {
        std::vector<edge> graph = dim == 0 ? zero_dim_graph(n) : higher_dim_graph(n, dim);
        std::vector<edge> mst = kruskal(n, graph);
        printf("%f\n", sum_weights(mst));
    }
}