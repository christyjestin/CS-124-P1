#include <vector>
#include <algorithm>
#include <cstdlib> 
#include <ctime>
#include <numeric>
#include <cassert>
#include <math.h>
#include "ufds.cc"

struct edge {
    int u;
    int v;
    float dist;
};

// node struct, has name and coords
struct euclid_node {
    int v;
    std::vector<float> coords;
};

// random number between 0 to 1
float unif() {
    // reseed each time
    srand(std::time(0));
    return ((float) std::rand() / RAND_MAX);
}

float dist(std::vector<float> a, std::vector<float> b) {
    assert(a.size() == b.size());
    std::vector<float> diff;
    for (int i = 0; i < a.size(); i++) {
        int d = a[i] - b[i];
        diff.push_back(d * d);
    }
    return sqrt(std::accumulate(diff.begin(), diff.end(), 0));
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
        euclid_node new_node;
        new_node.v = i;
        std::fill(new_node.coords.begin(), new_node.coords.begin(), unif());
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
        }
    }
    return mst;
}

int main() {
    int n = 4;
    std::vector<edge> graph = zero_dim_graph(n);
    std::vector<edge> mst = kruskal(n, graph);
    printf("graph");
    for (auto edge : graph) {
        printf("i: %d, j: %d, dist: %f", edge.u, edge.v, edge.dist);
    }
    printf("mst");
    for (auto edge : mst) {
        printf("i: %d, j: %d, dist: %f", edge.u, edge.v, edge.dist);
    }
}