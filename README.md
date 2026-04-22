# Smart Navigation System

<<<<<<< HEAD
## Team

* Jenish Pancholi (IU2441230510)
* Jainesh Patel (IU2441230479)
* Nandan Khagram (IU2441230558)

---

## Problem Statement

In real-world navigation, the shortest path is not always the fastest.
Traffic conditions affect travel time, but basic algorithms often ignore this.

This project improves pathfinding by combining graph algorithms with a simple machine learning model.

---

## Project Overview

* The road network is modeled as a directed graph
* Nodes = locations
* Edges = roads

Each edge stores:

* Distance
* Traffic
* Predicted travel time

A Linear Regression model predicts travel time using distance and traffic.

Finally, Dijkstra’s Algorithm is used to find the fastest path based on predicted time.

---

## Graph Used

```
![Graph](images/graph.png)
```

Format: (distance, traffic)

## Data Structures

### Graph (Adjacency List)

* `vector<vector<Edge>>`
* Efficient for sparse graphs

### Edge

Stores:

* Destination
* Distance
* Traffic
* Predicted time

### Priority Queue (Min-Heap)

* Used in Dijkstra’s Algorithm
* Selects node with minimum cost

### Stack

* Reconstructs final path

## Linear Regression

Model:

```
time = w1 * distance + w2 * traffic + b
```

Training:

* Uses sample data (distance, traffic → time)
* Optimized with gradient descent

Loss:

```
MSE = (1/n) * Σ(predicted - actual)^2
```

Updates:

```
w1, w2, b adjusted to minimize error
```

## Why Dijkstra’s Algorithm

* Works on weighted graphs
* Uses predicted travel time as cost
* Guarantees shortest (fastest) path

Why not BFS:

* Ignores weights

Why not DFS:

* Not optimal

## Advantages

* Combines ML + algorithms
* More realistic than fixed formulas
* Adapts to traffic conditions

## Limitations

* Small dataset
* Simple model (2 features)
* Assumes static traffic values

## Conclusion

This system predicts travel time using distance and traffic, then applies Dijkstra’s Algorithm to find the fastest route.

It demonstrates how machine learning can enhance traditional graph algorithms.
=======
## Contributors

- Jenish Pancholi - IU2441230510  
- Jainesh Patel - IU2441230479  
- Nandan Khagram - IU2441230559 


## Problem Statement

In real-world navigation, the shortest path is not always the fastest due to traffic conditions. Traditional graph algorithms mainly focus on distance or number of edges and ignore dynamic factors like traffic.

This project addresses that limitation by combining graph algorithms with a simple machine learning model to estimate realistic travel time.


## Project Overview

The system represents a road network using a directed weighted graph where:
- Nodes represent locations
- Edges represent roads with distance and traffic values

A Linear Regression model is trained to predict travel time using distance and traffic. These predicted values are used as edge weights.

Breadth First Search (BFS) is then used to find a path from source to destination.


## Graph Representation

Graph used in code:

0 -> 1 (5, 0.2)
0 -> 2 (8, 0.7)
1 -> 3 (4, 0.3)
1 -> 4 (6, 0.8)
1 -> 2 (2, 0.1)
2 -> 3 (3, 0.5)
2 -> 5 (7, 0.4)
3 -> 6 (5, 0.6)
4 -> 6 (4, 0.2)
5 -> 6 (6, 0.9)

Format: (distance, traffic)


## Data Structures Used

- Vector: adjacency list representation of graph  
- Queue: BFS traversal  
- Stack: path reconstruction  


## Algorithms Used

- Breadth First Search (BFS): path finding  
- Linear Regression: travel time prediction  


## Linear Regression Model

time = w1 * distance + w2 * traffic + b

error = predicted - actual

MSE = (1/n) * Σ(predicted - actual)^2


## Why Linear Regression?

- Learns weights from data instead of manual guessing  
- Adjusts based on real patterns  
- More flexible than static formulas  


## Why BFS?

- Simple traversal algorithm  
- Finds path with minimum edges  

Limitation:
- Does not use weights, so predicted time is not used in routing  


## Conclusion

This project combines graph theory and machine learning to simulate smarter navigation by predicting travel time using real factors like distance and traffic.
>>>>>>> 2b953d55a192d0224f6e29801679e2ff7ee490f6
