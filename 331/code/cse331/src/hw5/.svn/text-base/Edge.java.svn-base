package hw5;

/**
 * Created by Stefan Dierauf on 10/21/14.
 * Edge represents an edge between two Nodes,
 * but an Edge only stores the destination Node, not the parent.
 * Therefore, Edges only go in a single direction
 * An edge may have data, but that is up to the user to manage
 * If a user does not set this.data on instantiation, it will be set to empty string
 *
 * Representation Invariant:
 * this.label != null
 * this.destination != null
 *
 * Abstraction function
 * An Edge represents a labeled edge between whichever node 'owns' the edge and
 * a destination that the edge points to. Edges are not reflexive.
 *
 * Generic Types:
 * Node, the type the Edge points to
 * Label, the label for the edge
 * both types *must* implement comparable in order to ensure Edge is comparable
 */
public class Edge<Node extends Comparable<Node>, Label extends Comparable<Label>> implements Comparable<Edge<Node, Label>> {

  private final Label label;
  private final Node destination;

//  /**
//   * Constructs an Edge with Node destination
//   * @param destination The Node the edge points to
//   * @requires destination to not be null;
//   * @effects Constructs a new Edge pointing at destination
//   * Note: this does not set the data field, which means it can never be set again!
//   */
//  public Edge(Node destination) {
//    this.destination = destination;
//    this.label = "";
//  }

  /**
   * Constructs an Edge with a destination and a label
   * @param destination the Node the edge points to
   * @param label the String of data the Node holds
   * @requires destination to not be null
   * @effects Constructs a new Edge pointing at destination with the label
   */
  public Edge(Node destination, Label label) {
    this.destination = destination;
    this.label = label;
  }

  /**
   * Getter for the destination of this Edge
   * @return this Edge's destination
   */
  public Node getDestination() {
    return this.destination;
  }

  /**
   * Getter for this Edge's data String
   * @return The data String of this edge
   */
  public Label getData()  {
    return this.label;
  }

  /**
   * Standard equality function
   * @param o The object to be compared for equality.
   * @return true iff o is an instance of Edge and
   * this.destination equals o.destination and this.label
   * equals o.label
   */
  @Override
  public boolean equals(Object o) {
    if (o instanceof Edge) {
      Edge<?, ?> e = (Edge<?, ?>) o;
      return this.destination.equals(e.destination)
          && this.label.equals(e.label);
    } else {
      return false;
    }
  }

  /**
   * Standard hashCode function.
   * @return an int that all objects equal to this will also
   * return.
   */
  @Override
  public int hashCode() {
    return (this.label.hashCode()
            * 17 * this.destination.hashCode());
  }

  /**
   * Standard compareTo
   * Compares by destination then by label
   * @param other
   * @return @see compareTo()
   */
  @Override
  public int compareTo(Edge<Node, Label> other) {
    if (this.getDestination().equals(other.getDestination())) {
      //characters are the same, so need to compare books
      return this.getData().compareTo(other.getData());
    } else {
      return this.getDestination().compareTo(other.getDestination());
    }
  }
}
