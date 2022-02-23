#include <vector>
#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <cassert>
#include <math.h>
#include <unordered_map>
#include <string>
#include "ufds.cc"
#include "max_weights.cc" // used for pruning

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

// finds distance between 2 points `a` and `b` in n-dimensional space
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
            float weight = unif();
            // no need to prune for sufficiently small n
            if (n <= 8192 || weight < max_weights["0 " + std::to_string(n / 2)]) {
                edges.push_back(edge {i, j, weight});
            }
        }
    }
    return edges;
}

std::vector<edge> higher_dim_graph(int n, int dim) {
    assert(dim != 1 && dim < 5);
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
            float weight = dist(nodes[i].coords, nodes[j].coords);
            // no need to prune for sufficiently small n
            if (n <= 8192 || weight < max_weights[std::to_string(dim) + " " + std::to_string(n / 2)]) {
                edges.push_back(edge {i, j, weight});
            }
        }
    }
    return edges;
}

std::vector<edge> kruskal(int n, std::vector<edge> edges) {
    ufds sets (n);
    for (int i = 0; i < n; i++) {
        sets.makeset(i);
    }
    sort(edges.begin(), edges.end(), [](const auto &x, const auto &y){return x.dist < y.dist;});

    std::vector<edge> mst;

    for (edge e : edges) {
        if (sets.find(e.u) != sets.find(e.v)) {
            sets.unite(e.u, e.v);
            mst.push_back(e);
            if ((int) mst.size() == n-1) break;
        }
    }
    assert((int) mst.size() == n-1);
    return mst;
}

// helper function for sum_weights
inline float add_weight(float sum, edge e) {
    return sum + e.dist;
}

// sum the weights of all edges in a minimum spanning tree
float sum_weights(std::vector<edge> mst) {
    return std::accumulate(mst.begin(), mst.end(), 0.0f, add_weight);
}

// find largest weight of any edge in a minimum spanning tree
float largest_weight(std::vector<edge> mst) {
    sort(mst.begin(), mst.end(), [](const auto &x, const auto &y){return x.dist < y.dist;});
    return mst.back().dist;
}

// find the average weight of edges in a minimum spanning tree
float avg(std::vector<float> sums) {
    return std::accumulate(sums.begin(), sums.end(), 0.0f) / sums.size();
}

// print our updated map of weights
void print_map(std::unordered_map<std::string, float> map, std::string map_name) {
    std::string output = "#include <unordered_map>\n\nstd::unordered_map<std::string, float> " + map_name + " ({";
    for (auto keyval : map) {
        output += "\n\t{\"" + keyval.first + "\", " + std::to_string(keyval.second) + "},";
    }
    output +="\n});";
    printf("%s", output.c_str());
}

int main(int argc, char** argv) {
    assert(argc == 5);
    // flag 0 outputs only avg, flag 1 outputs info for each mst, flag 2 automates pruning
    int flag = atoi(argv[1]);
    assert(flag >= 0 && flag < 3);
    int n = atoi(argv[2]);
    int numtrials = atoi(argv[3]);
    int dim = atoi(argv[4]);
    srand(time(0));

    float max_weight = 0;
    std::vector<float> tree_sizes;
    for (int i = 0; i < numtrials; i++) {
        std::vector<edge> graph = dim == 0 ? zero_dim_graph(n) : higher_dim_graph(n, dim);
        std::vector<edge> mst = kruskal(n, graph);

        float size = sum_weights(mst);
        tree_sizes.push_back(size);

        float lw = largest_weight(mst);
        if (flag == 1) printf("largest weight: %f\n", lw);
        if (lw > max_weight) max_weight = lw;
    }
    if (flag == 1) printf("max largest weight: %f\n", max_weight);
    if (flag == 2) {
        max_weights[std::to_string(dim) + " " + std::to_string(n)] = max_weight;
        print_map(max_weights, (std::string) "max_weights");
    }
    if (flag != 2) printf("average tree size is %f for %d points with %d trials and %d dimensions\n", avg(tree_sizes), n, numtrials, dim);
}