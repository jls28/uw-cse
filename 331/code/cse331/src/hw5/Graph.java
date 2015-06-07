package hw5;

import java.util.*;

/**
 * Created by Stefan Dierauf on 10/21/14.
 *
 *
 * Graph represents a set of Nodes each connected to each other
 * by 0 or more edges
 * A graph internally is a HashMap of Strings to HashSets of Edges.
 * From here on, any reference to a 'node' is referring to it's string key
 * Each Edge in a Node's set represents the edge between the node and it's child.
 * Each Node in a graph must be unique and each Edge must be unique
 * A Node can still have multiple Edges to another Node but each of those Edges must have a unique data field
 *
 * A Graph is a directed labeled multigraph, so it will support being used as
 * an undirected graph or as a directed graph.
 *
 * Representation invariant:
 * for all nodes in graph,
 *  no node is null
 *  every node maps to a hashset of edges
 *  every edge in the hashset has a label that is not null
 *  every edge has a child that is in the graph
 *
 * Abstraction Function:
 * A Graph is a representation of a labeled multi graph, where the nodes are strings
 * a node/string maps to a set of edges in the Graph.graph hashmap. Each edge has a label and refers
 * to another node in the hashmap
 *
 * Generic Types:
 * Node, the type for each Node in the graph
 * Label, the type for the label for each Edge connecting two Nodes
 * Nodes and Labels must implement comparable
 */
public class Graph<Node extends Comparable<Node>, Label extends Comparable<Label>> {

  private final boolean DEBUG = false;
  private HashMap<Node, HashSet<Edge<Node, Label>>> graph;

  /**
   * Constructs an empty graph
   * @effects Constructs an empty graph
   */
  public Graph() {
    this.graph = new HashMap<Node, HashSet<Edge<Node, Label>>>();
    checkRep();
  }

  /**
   * Adds a new Node to the Graph with it's data set to data
   * returns true if the Node was successfully added, false if an identical node
   * already exists in this.graph
   * @param data String key for the node
   * @requires data != null
   * @modifies this.graph by adding a node
   * @return true iff this.graph does not already contain the node, false otherwise
   */
  public boolean addNode(Node data) {
    if (data == null) {
      throw new IllegalArgumentException();
    }
    if (graph.containsKey(data)) {
      return false;
    } else {
      this.graph.put(data, new HashSet<Edge<Node, Label>>());
      checkRep();
      return true;
    }
  }

  /**
   * Removes a node and all edges pointing to that node from the graph
   * @param key the node to remove
   */
  public void removeNode(Node key) {
    if (key == null) {
      throw new IllegalArgumentException();
    }
    if (this.graph.containsKey(key)) {
      this.graph.remove(key);
    }
    //now clean up references
    for (Set<Edge<Node, Label>> edges: this.graph.values()) {
        List<Edge<Node, Label>> toRemove = new ArrayList<Edge<Node, Label>>();
        for (Edge<Node, Label> e : edges) {
            if (e.getDestination().equals(key)) {
                toRemove.add(e);
            }
        }
        edges.removeAll(toRemove);
    }
  }

  /**
   * Adds a new Edge to the parentNode. childNode will be created if it does
   * not exist. Returns true iff the Edge was added to the Node, false if the Edge already exists
   * @requires parentNode must exist in Node form in the graph.
   * @param parentNode  the parent node
   * @param edgeLabel new label of Edge to be made
   * @param childNode the child node the Edge should point at
   * @modifies this.graph by adding a new Edge and childNode if it doesn't exist
   * @return true iff a new unique Edge was created.
   */
  public boolean addEdge(Node parentNode, Label edgeLabel, Node childNode) {
    if (parentNode == null || childNode == null
        || !this.graph.containsKey(parentNode)) {
      throw new IllegalArgumentException();
    } else {
      if (!graph.containsKey(childNode)) {
        this.graph.put(childNode, new HashSet<Edge<Node, Label>>());
      }
      HashSet<Edge<Node, Label>> edges = graph.get(parentNode);
      Edge<Node, Label> newEdge = new Edge<Node, Label>(childNode, edgeLabel);
      boolean success = edges.add(newEdge);
      checkRep();
      return success;
    }
  }

  /**
   * Removes an edge from a node in the graph. Returns true if the Edge was removed
   * and false if the parent Node did not have that edge
   * @param parentNode the parent node
   * @param edge the Edge of parentNode to remove
   * @modifies graph by removing the edge if it exists
   * @requires graph contains parentNode && edge != null
   * @return returns true iff the parentNode had the Edge and that edge was removed.
   */
  public boolean removeEdge(Node parentNode, Edge<Node, Label> edge) {
    if (!this.graph.containsKey(parentNode) || edge == null) {
      throw new IllegalArgumentException();
    }
    checkRep();
    return this.graph.get(parentNode).remove(edge);
  }

  /**
   * returns true if the graph contains a Node equivalent to data
   * @param data
   * @return true iff graph has a Node equivalent to data
   */
  public boolean contains(Node data) {
    return this.graph.containsKey(data);
  }

  /**
   * Returns true if parent has an edge to child
   * @param parent the parent Node
   * @param child the child Node
   * @return true iff parent has an edge to child
   */
  public boolean isChild(Node parent, Node child) {
    if (!this.graph.containsKey(parent) || !this.graph.containsKey(child)) {
      return false;
    }
    for (Edge<Node, Label> pChild : this.graph.get(parent)) {
      if (pChild.getDestination() == child) {
        return true;
      }
    }
    return false;
  }

  /**
   * Returns a set of Nodes equal to the children of the given node
   * @param parent
   * @requires parent to be a key present in the graph.
   * @return Set of strings of the keys of the children
   */
  public Set<Node> listChildren(Node parent) {
    if (!this.graph.containsKey(parent)) {
      throw new IllegalArgumentException();
    }
    Set<Node> children = new HashSet<Node>();
    for (Edge<Node, Label> child : this.graph.get(parent)) {
      children.add(child.getDestination());
    }
    return children;
  }


  /**
   * Returns a Set of strings of of all the nodes in the graph
   * @return a Set of strings of all Nodes in the graph
   */
  public Set<Node> listNodes() {
    return this.graph.keySet();
  }

  /**
   * Returns a set of all Edges from the given parent node
   * @param parent
   * @return a set of all Edges from the given parent node
   */
  public Set<Edge<Node, Label>> getEdges(Node parent) {
    return new HashSet<Edge<Node, Label>>(this.graph.get(parent));
  }

  /**
   * Returns a sorted list of Edges from the given parent node
   * @param parent
   * @return a sorted list of Edges from the given parent node
   */
  public List<Edge<Node, Label>> getSortedEdges(Node parent) {
    List<Edge<Node, Label>> edges = new LinkedList<Edge<Node, Label>>();
    edges.addAll(this.getEdges(parent));
    Collections.sort(edges);
    return edges;
  }

  /**
   * Returns a Set of edges of all edges between the parent and the child node
   * if child is not a child of parent, will return no edges.
   * @requires for all edges from parent to child, the edge must have a data field that is not null
   * @param parent the parent Node
   * @param child the child Node
   * @return a Set of all the edges data between the parent and the child
   */
  public Set<Edge<Node, Label>> getEdgesToChild(Node parent, Node child) {
    if (!this.graph.containsKey(parent)) {
      throw new IllegalArgumentException();
    }
    Set<Edge<Node, Label>> specialEdges = new HashSet<Edge<Node, Label>>();
    for (Edge<Node, Label> edge : this.graph.get(parent)) {
      if (edge.getDestination().equals(child)) {
        specialEdges.add(edge);
      }
    }
    return specialEdges;
  }

  /**
   * @return a deep copy of this
   */
  public Graph<Node, Label> deepCopy() {
    Graph<Node, Label> copy = new Graph<Node, Label>();
    for (Node node : this.listNodes()) {
      copy.addNode(node);
    }
    for (Node node : this.listNodes()) {
      for (Edge<Node, Label> e : this.getEdges(node)) {
        copy.addEdge(node, e.getData(), e.getDestination());
      }
    }
    return copy;
  }

  /**
   * Checks to make sure the representation invariant holds
   */
  public void checkRep() {
    //no null nodes
    if (DEBUG) {
      for (Node key: this.graph.keySet()) {
        assert(key != null);
        for (Edge<Node, Label> e : this.graph.get(key)) {
          //no null edges
          assert(e != null);
          //edge labels are not null (Can be "")
          assert(e.getData() != null);
          assert(e.getDestination() != null);
          //all edges point to valid nodes
          assert(this.graph.get(e.getDestination()) instanceof HashSet); //should be a hashset
        }
      }
    }
  }








}
