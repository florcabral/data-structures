# Graphs

For this assignment I implemented an object oriented graphs data
structure (in graphs.cpp), including the following functions:

* **Node::setColor** - sets the 'color' of a node, which refers to its discovery (visited) state
* **Node::getDiscoveryInformation** - returns a node's discovery state and time
* **Node::clear** - resets node to undiscovered state
* **Node::isAncestor** - returns true if the given node is reachable by traversing another node's predecessor list
* **Node::setPredecessor** - sets a node's predecessor node in the spanning tree (node from which another was discovered)
* **Edge::setType** - sets the edge type to the given value (undiscovered, tree, back, forward, or cross edge)
* **Graph::clear** - resets all of graph's nodes and edges to undiscovered state
* **Graph::dfs** - runs a depth-first search from the indicated start node, and explores all reachable nodes
* **Graph::bfs** - 2 implementations: one simple BFS from starting node, another that stops when given target node is reached

## To run the tests:

Run `make`, then one of the following:

* `python grade.py graphs_test` - this runs the python grading
  script, using `points.json` and produces a tab separated report on the number of points 
  earned for each function based on the number of tests passed (ie, 5/5)
* `./graphs_test` - this runs all the unit tests in a row.
* `./graphs_test "[sometest]"` - runs a particular unit
  test:

   1. `Node.clear`
   2. `Edge.setType`
   3. `Graph.clear`
   4. `Node.setColor`
   5. `Node.getDisco`
   6. `Node.setPredecessor`
   7. `Node.isAncestor`
   8. `Graph.dfs`
   9. `Graph.dfs edges`
   10. `Graph.bfs 1`
   11. `Graph.bfs 2`