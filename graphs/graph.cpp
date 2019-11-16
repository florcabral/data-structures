//
// graph.cpp
//

#include <iostream>
#include <sstream>
#include <queue> 

#include "graph.hpp"

using namespace std;

// fwd declarations
string make_dot(Graph* g);
string what(int& v);

Graph::Graph() {
  directed = false; // graphs are undirected by default
}

Graph::~Graph() {
// no implementation needed
}

vector<Node*> Graph::getNodes() {
  return nodes;
}

vector<Edge*> Graph::getEdges() {
  return edges;
}

int Graph::getClock() {
  return clock;
}

void Graph::addNode(Node& n) {
  nodes.push_back(&n);
}

void Graph::addEdge(Edge& e) {
  edges.push_back(&e);
}
 
void Graph::removeNode(Node& n) {
  for (vector<Node*>::iterator it = nodes.begin();
       it != nodes.end(); 
       it++) {
    if (&n == *it) {
      nodes.erase(it);
      break;
    }
  }
}
 
void Graph::removeEdge(Edge& e) {
  for (vector<Edge*>::iterator it = edges.begin();
       it != edges.end(); 
       it++) {
    if (&e == *it) {
      edges.erase(it);
      break;
    }
  }
}

void Graph::setDirected(bool val) {
  directed = val;
}

bool Graph::isDirected() {
  return directed;
}

set<Edge*> Graph::getAdjacentEdges(Node& n) {
  set<Edge*> ret;
  for (vector<Edge*>::iterator it = edges.begin(); it != edges.end(); it++) {
    Edge* edge = *it;
    if (edge->getStart() == &n) {
      ret.insert(edge);
    }
    if (!directed && edge->getEnd() == &n) {
      ret.insert(edge);
    }
  }
  return ret;
}


void Graph::clear() {
    
    // run through all the graph's nodes and clear them
    for (vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
        Node* node = *it;
        node->clear();
    }
    // run through all the graph's edges and set them to type 9 = UNDISCOVERED_EDGE
    for (vector<Edge*>::iterator it = edges.begin(); it != edges.end(); it++) {
        Edge* edge = *it;
        edge->setType(9);
    }
    // finally, reset the graph clock to 0
    clock = 0;
}

void Graph::tick(string message) {
  // optional debugging function, disabled with if(false) to prevent
  // unused var warning.
  //
  // recommended use: call it just after incrementing the clock.
  if (false) {
    cout << "// " << message << endl << make_dot(this) << endl;
  }
}


void Node::setColor(int search_color, int time) {

    // if we're setting the node White, clear the node
    if (search_color == 1){
        this->clear();
        
    }
    // if we're setting the node Gray, update the discovery time to the time given
    if (search_color == 2) {
        this->color = 2;
        this->discovery_time = time;
        
    }
    // if we're setting the node Black, update the completion time to the time given
    if (search_color == 3) {
        this->color = 3;
        this->completion_time = time;
    }
}


void Node::getDiscoveryInformation(int& color, int& disco_time, 
				   int& finish_time, int& bfs_rank) {
  
    // we'll call 'this' to set the current parameter values to the argument variables
    color = this->color;
    disco_time = this->discovery_time;
    finish_time = this->completion_time;
    bfs_rank = this->rank;
}


void Graph::dfs(Node& start) {

    // visit node - set its discovery time to clock time
    // & mark node gray
    start.setColor(2, clock);
    this->clock++;
    
    // get all the outgoing edges for our start node
    set<Edge*> nodes_edges = getAdjacentEdges(start);
    
    for (auto it = begin(nodes_edges); it != end(nodes_edges); ++it) {
        
        Edge* edge = *it;
        Node* new_node = edge->getEnd();  // for each of these edges, visit the nodes they lead to
        new_node->setPredecessor(start);  // set each of these nodes' predecessor to start
        
        // now we want this node's color, so call getDiscoveryInformation
        int color;
        int disco_time;
		int finish_time;
        int bfs_rank;
        
        new_node->getDiscoveryInformation(color, disco_time, finish_time, bfs_rank);

        // we want all edges by default to be tree edges
        edge->setType(10);
        
        // if the node's black, it's a forward edge
        if (color == 3) {
            edge->setType(12);
        }
        
        // if the node's gray, it's a back edge
        if (color == 2) {
            edge->setType(11);
        }
        
        // if the node is White (undiscovered)
        // call dfs on it recursively, to keep moving down the graph
        if (color == 1) {
            dfs(*new_node);
            this->clock++;
        }
    }
    
    // finally, mark starting node black
    start.setColor(3, clock);
    
}

void Graph::bfs(Node& start) {
    
    // first, clear the graph
    this->clear();
    
    // mark initial node gray
    start.setColor(2, clock);
    
    // set up a queue
    // add start node to queue
    queue<Node*> myqueue;
    myqueue.push(&start);
   
    // set the starting node's rank to 0
    start.setRank(0);
      
    // while there are items in the queue:
    while (!myqueue.empty()) {
        
    // pop first item from queue and store it for use
        Node* first_node = myqueue.front();
        myqueue.pop();
        
    // visit the node (mark gray)
        first_node->setColor(2, clock);
        
    // get all the outgoing edges for our node
    set<Edge*> adj_edges = getAdjacentEdges(*first_node);
    
    for (auto it = begin(adj_edges); it != end(adj_edges); ++it) {
        
    // for each of these edges, visit the nodes they lead to
        Edge* edge = *it;
        Node* next_node = edge->getEnd();
        
    // we want to know if the other node is white
    // if so, its rank should be set to the predecessor's + 1
    // so we get both their colors with getDiscoveryInformation
        
        int next_color;
        int next_disco_time;
		int next_finish_time;
        int next_bfs_rank;
        
        next_node->getDiscoveryInformation(next_color, next_disco_time, next_finish_time, next_bfs_rank);
        
        int pred_color;
        int pred_disco_time;
		int pred_finish_time;
        int pred_bfs_rank;
        
        first_node->getDiscoveryInformation(pred_color, pred_disco_time, pred_finish_time, pred_bfs_rank);
        
        if (next_color == 1) {
            next_node->setRank(pred_bfs_rank+1);
            // also mark the node gray
            next_node->setColor(2, clock);  
            // and add it to the queue
            myqueue.push(next_node);
        }

    }
}
}

  // bfs(start, target) has the same requirements as the other version
  // of `bfs`, except this one stops after the target node is
  // reached. If found, the target node should be marked BLACK, and
  // its rank should be correctly set on exit. If it is not found, the
  // target node should remain WHITE with a rank of -1.
void Graph::bfs(Node& start, Node& finish) {
    
    finish.setColor(1, clock);
    finish.setRank(-1);
    
    // first, clear the graph
    this->clear();
    
    // mark initial node gray
    start.setColor(2, clock);
    
    // set up a queue
    // add start node to queue
    queue<Node*> myqueue;
    myqueue.push(&start);
   
    // set the starting node's rank to 0
    start.setRank(0);
      
    // while there are items in the queue:
    while (!myqueue.empty()) {
        
    // pop first item from queue and store it for use
        Node* first_node = myqueue.front();
        myqueue.pop();
        
    // visit the node (mark gray)
        first_node->setColor(2, clock);
        
    // get all the outgoing edges for our node
    set<Edge*> adj_edges = getAdjacentEdges(*first_node);
    
    for (auto it = begin(adj_edges); it != end(adj_edges); ++it) {
        
    // for each of these edges, visit the nodes they lead to
        Edge* edge = *it;
        Node* next_node = edge->getEnd();
        
    // we want to know if the other node is white
    // if so, its rank should be set to the predecessor's + 1
    // so we get both their colors with getDiscoveryInformation
        
        int next_color;
        int next_disco_time;
		int next_finish_time;
        int next_bfs_rank;
        
        next_node->getDiscoveryInformation(next_color, next_disco_time, next_finish_time, next_bfs_rank);
        
        int pred_color;
        int pred_disco_time;
		int pred_finish_time;
        int pred_bfs_rank;
        
        first_node->getDiscoveryInformation(pred_color, pred_disco_time, pred_finish_time, pred_bfs_rank);
        
        if (next_color == 1) {
            next_node->setRank(pred_bfs_rank+1);
            // also mark the node gray
            next_node->setColor(2, clock);  
            // and add it to the queue
            myqueue.push(next_node);
        }
        
        // we reached our target node
        // so we want to set it to black, and stop right there
        // also if the graph is directed, the node's rank should be 1
        if (next_node == &finish) {
            finish.setColor(3, clock);
            if (!isDirected()) {
                finish.setRank(1);
            }
            break;
        }

    }
}
}

Node::Node(string s) {
  data = s;
}

Node::~Node() {
  // This is equivalent to the default destructor the compiler will
  // generate for you. As a rule of thumb, you only need to `delete`
  // member variables that were created with `new` inside this
  // class. So, you don't need to do anything here. It could have been
  // left out of the header/impl file entirely.
}

string Node::getData() {
  return data;
}

void Node::setRank(int r) {
  rank = r;
}

void Node::clear() {
    this->color = 1;
    this->discovery_time = -1;
    this->completion_time = -1;
    this->rank = -1;
    this->predecessor = NULL;
}


bool Node::isAncestor(Node& other) {
    
    Node* cursor = this;
    
    // move up the lineage by looking at nodes' predecessors
    while (cursor->predecessor != NULL) {
        
        cursor = cursor->predecessor;
        
        // if we reached our node of interest, we return true
        if (&other == cursor)
        {
            return true;
        }
    }
    
    // otherwise, admit you haven't reached it, so it's not an ancestor
  return false;
}

void Node::setPredecessor(Node& other) {
    
    this->predecessor = &other;   // set the predecessor to the given node
}


Edge::Edge(Node& n1, Node& n2) {
  a = &n1;
  b = &n2;
}

Edge::~Edge() {
}


Node* Edge::getStart() {
  return a;
}

Node* Edge::getEnd() {
  return b;
}

int Edge::getType() {
  return type;
}

void Edge::setType(int edge_type) {
    this->type = edge_type;   // set the edge type to the type given
}

// overloading operator << lets you put a Graph object into an output
// stream.
ostream &operator << (ostream& out, Graph graph) {
  out << graph.nodes.size() << " Nodes:" << endl;
  out << "[";
  for (vector<Node*>::iterator it = graph.nodes.begin(); it != graph.nodes.end(); it++) {
    Node* n = *it;
    out << *n << ", ";
  }
  out << "]" << endl;
  out << graph.edges.size() << " Edges:" << endl;
  out << "[";
  for (vector<Edge*>::iterator it = graph.edges.begin(); it != graph.edges.end(); it++) {
    Edge* e = *it;
    out << *e << ", ";
  }
  out << "]";
  return out;
}

// overloading operator << lets you put a Node object into an output
// stream.
ostream &operator << (std::ostream& out, Node node) {
  out << node.data;
  return out;
}

// overloading operator << lets you put an Edge object into an output
// stream.
ostream &operator << (std::ostream& out, Edge edge) {
  out << *edge.a << " -- " << *edge.b;
  return out;
}

// what is a helper function that turns a constant (e.g. WHITE or
// FORWARD_EDGE) into a string for debugging goodness. 
string what(int& v) {
  string ret = "Unknown";
  if (v == WHITE) {
    ret = "white";
  } else if (v == GRAY) {
    ret = "gray";
  } else if (v == BLACK) {
    ret = "black";
  } else if (v == UNDISCOVERED_EDGE) {
    ret = "undiscovered";
  } else if (v == TREE_EDGE) {
    ret = "tree";
  } else if (v == BACK_EDGE) {
    ret = "back";
  } else if (v == FORWARD_EDGE) {
    ret = "forward";
  } else if (v == CROSS_EDGE) {
    ret = "cross";
  }
  return ret;
}


// make_dot generates a dotfile string for viewing your graph. Have
// tick() print out the results of this function, and then use
// http://www.webgraphviz.com/ (or get a copy of GraphViz) to view the
// result. If you're stuck, this can help you get un-stuck.
string make_dot(Graph* g) {
  stringstream ss;
  vector<Node*> nodes = g->getNodes();
  vector<Edge*> edges = g->getEdges();
  string gt = "graph";
  string con = "--";
  if (g->isDirected()) {
    con = "->";
    gt = "digraph";
  }
  ss << gt << " homework {" << endl;
  int c, dt, ft, r;
  string textColor = "black";
  for (auto it=nodes.begin(); it != nodes.end(); ++it) {
    Node* n = *it;
    n->getDiscoveryInformation(c, dt, ft, r);
    if (c == BLACK) {
      textColor = "white";
    } else {
      textColor = "black";
    }
    ss << "  " << n->getData() << " [ style=\"filled\" fontcolor=\"" << textColor << "\" fillcolor=\"" << what(c) << "\"" << " ]" << endl;
  }
  
  string edgeColor = "black";
  for (auto it=edges.begin(); it != edges.end(); ++it) {
    Edge* e = *it;
    if (e->getType() == TREE_EDGE) {
      edgeColor = "black";
    } else if (e->getType() == FORWARD_EDGE) {
      edgeColor = "purple";
    } else if (e->getType() == BACK_EDGE) {
      edgeColor = "blue";
    } else if (e->getType() == CROSS_EDGE) {
      edgeColor = "green";
    } else {
      edgeColor = "gray";
    }
    ss << "  " << e->getStart()->getData() << con << e->getEnd()->getData() << " [color=\"" << edgeColor << "\"]" << endl;
  }
  ss << "}" << endl;
  return ss.str();
}
