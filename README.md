# CS 124 P1
A programming assignment for CS 124 (Data Structures and Algorithms)

By Ashlan Ahmed and Christy Jestin

## Background
We studied minimum spanning trees formed by randomly generating points within the unit square, unit cube, and unit hypercube. WTF does that mean? A graph is a series of vertices (blue circles) connected by edges (black lines), and these edges may have weights (the example has weights). Edges may be directed i.e. they go from a to b but not b to a (the arrows indicate direction) or undirected i.e. they go in both directions. We're studying undirected graphs, but the example below is simple.

![image](https://user-images.githubusercontent.com/52580002/155817786-1452f06b-57ce-4b2a-929b-ddd947e31110.png)

A spanning tree is a subset of edges of a graph such that all vertices are the endpoint of at least one edge (the technical definition of a tree isn't necessary in this context). A minimum spanning tree is the spanning tree for which the sum of the edge weights are smaller than the sum of the edge weights for any other spanning tree.

In particular, we studied complete graphs i.e. graphs in which every possible edge between distinct vertices exists. For the cases where we considered the unit square, unit cube, or unit hypercube, the weight of an edge was simply the Euclidean distance between the two endpoints. In addition to these cases, we also studied a "zero-dimensional case" where the weight of an edge was randomly generated from the uniform distribution (between 0 and 1).

## Our Code
Our code was written in C++ with some scripting and graph plotting in Python. You can run our code by running:
```
make randmst
./randmst 0 numpoints numtrials numdimensions
```
An example is:
```
./randmst 0 128 10 2
```
This will run the MST code 10 times each in 2 dimensions and with 128 vertices in the unit square. It will return the average size of the MST over the 10 trials.

## Results
You can see a graph of the average MST size for 3 dimensions below (please use light mode to see the axes and title):
![three](https://user-images.githubusercontent.com/52580002/155817013-f43f2a60-b3c4-4a1b-a34e-2c002fbf4a8f.png)

Our hypothesis is that the average size grows according to n over the dth root of n where n is the number of points and d is the dimension. You can read our complete reasoning and other results in the PDF called REPORT - Christy and Ash.pdf. The rough idea is that you expect the n points to distributed uniformly within the unit square/cube/hypercube. Thus their positions will resemble a grid pattern with about dth root of n points along each dimension. Since the side length of our shape (unit square/cube/hypercube) is always 1, the distance between grid points will be 1 over dth root of n. There are n-1 edges in the minimum spanning tree, so the average size should come out to around n over the dth root of n. While this lines up with the data, there is an additional constant factor for all 3 dimensions, and while the factors were similar for d=2 and d=3, it was much larger for d=4. This may be explained by some property of the expected value of edge length that depends on the dimension, but we're not sure.
