#include <vector>
#include <cassert>
#include "randmst.cc"

int binsearch(std::vector<edge> edges, float dist) {
    int min_index = 0;
    int max_index = edges.size() - 1;
    while (min_index < max_index) {
        printf("min: %i\n", min_index);
        printf("max: %i\n", max_index);
        int mid = (max_index + min_index) / 2;
        if (edges[mid].dist < dist) {
            min_index = mid + 1;
        }
        else {
            max_index = mid;
        } 
    }
    return min_index;
}

std::vector<edge> prune(std::vector<edge> edges, int keep) {
    assert((int) edges.size() >= keep);
    std::vector<edge> output (keep);
    copy(edges.begin(), edges.begin() + keep, output.begin());
    sort(output.begin(), output.end(), [](const auto &x, const auto &y){return x.dist < y.dist;});
    for (int i = keep; i < edges.size(); i++) {
        if (edges[i].dist > output[keep-1].dist) continue;
        int index = binsearch(output, edges[i].dist);
        output.insert(output.begin() + index, edges[i]);
        output.pop_back();
    }
}