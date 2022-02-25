# CS 124 P1
A programming assignment for CS 124 (Data Structures and Algorithms)

By Ashlan Ahmed and Christy Jestin


We studied minimum spanning trees formed by randomly generating points within the unit square, unit cube, and unit hypercube. A spanning tree is a subset of edges of a graph such that all vertices are the endpoint of at least one edge. A minimum spanning tree is the spanning tree for which the sum of the edge weights are smaller than the sum of the edge weights for any other spanning tree. In particular, we studied complete undirected graphs i.e. graphs in which every possible edge exists. For the cases where we considered the unit square, unit cube, and unit hypercube, the weight of an edge was simply the Euclidean distance between the two endpoints. In addition to these cases, we also studied a "zero-dimensional case" where the weight of an edge was randomly generated from the uniform distribution (between 0 and 1).

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

You can see a graph of the average MST size for 3 dimensions below:
![three](https://user-images.githubusercontent.com/52580002/155817013-f43f2a60-b3c4-4a1b-a34e-2c002fbf4a8f.png)
Our hypothesis is that the average size grows according to $n^{1-1/d}$ where n is the number of points and d is the dimension. You can read our reasoning in the PDF called in our repo.

