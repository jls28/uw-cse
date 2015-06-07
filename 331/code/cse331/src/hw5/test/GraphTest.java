package hw5.test;

import hw5.Edge;
import hw5.Graph;
import org.junit.Test;
import org.junit.Before;
import org.junit.rules.ExpectedException;

import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;

import static org.junit.Assert.*;

/**
 * Created by Stefan Dierauf on 10/22/14.
 */
public class GraphTest {

  public ExpectedException exception = ExpectedException.none();

  Graph<String, String> g1, g1_also, g1_trans, test, gParentAndChild, gParentAndChildWithEdge, empty;
  String parent, child, dumb;
  @Before
  public void setup() {
    parent = "parent";
    child = "child";
    dumb = "dumb";
    g1 = new Graph<String, String>();
    g1.addNode("node1");

    test = new Graph<String, String>();
    empty = new Graph<String, String>();

    gParentAndChild = new Graph<String, String>();
    gParentAndChild.addNode("parent");
    gParentAndChild.addNode("child");

    gParentAndChildWithEdge = new Graph<String, String>();
    gParentAndChildWithEdge.addNode("parent");
    gParentAndChildWithEdge.addNode("child");
    gParentAndChildWithEdge.addEdge(parent, "data", child);
  }

  //Instantiation
  @Test
  public void testConstructor() {
    Graph<String, String> g = new Graph<String, String>();
  }

  //addNode(string)
  @Test
  public void testAddNode() {
    test.addNode("node1");
  }

  @Test
  public void testAddNodeRetTrue() {
    assertTrue(test.addNode("node1"));
  }

  @Test
  public void testRemoveNodeReturnsFalseIfExists() {
    test.addNode("node1");
    assertFalse(test.addNode("node1"));
  }

  //addEdge(parent, label, child)
  @Test
  public void testAddEdge() {
    gParentAndChild.addEdge(parent, "edgeLabel",child);
  }

  @Test
  public void testAddEdgeReturnsTrueOnSuccess() {
    assertTrue(gParentAndChild.addEdge(parent, "edgeLabel", child));
  }

  @Test
  public void testAddEdgeReturnsFalseOnFailure() {
    gParentAndChild.addEdge(parent, "edgeLabel", child);
    assertFalse(gParentAndChild.addEdge(parent, "edgeLabel", child));
  }

  @Test (expected = IllegalArgumentException.class)
  public void testAddEdgeExpectThrowIfParentDoesntExist() {
    Graph<String, String> nothing = new Graph<String, String>();
    nothing.addEdge("I should throw", "throwwwin", "throwy throw");
  }

  //removeEdge
  @Test
  public void testRemoveEdge() {
    gParentAndChildWithEdge.removeEdge(parent, new Edge<String, String>(child, "data"));
  }

  @Test
  public void testRemoveEdgeReturnsTrueOnSuccess() {
    assertTrue(gParentAndChildWithEdge.removeEdge(parent, new Edge<String, String>(child, "data")));
  }

  @Test
  public void testRemoveEdgeReturnsFalseOnFailure() {
    gParentAndChildWithEdge.removeEdge(parent, new Edge<String, String>(child, "data"));
    assertFalse(gParentAndChildWithEdge.removeEdge(parent, new Edge<String, String>(child, "data")));
  }

  //contains
  @Test
  public void testContains() {
    assertTrue(gParentAndChild.contains(parent));
    assertFalse(gParentAndChild.contains(dumb));
  }

  //isChild
  @Test
  public void testIsChild() {
    assertTrue(gParentAndChildWithEdge.isChild(parent, child));
    assertFalse(gParentAndChildWithEdge.isChild(parent, dumb));
  }

  //listChildren
  @Test
  public void testListChildrenSingleChild() {
    Set<String> temp = new HashSet<String>();
    temp.add(child);
    assertTrue(gParentAndChildWithEdge.listChildren(parent).containsAll(temp));
    assertTrue(temp.containsAll(gParentAndChildWithEdge.listChildren(parent)));
  }

  @Test
  public void testListChildrenTwoChildren() {
    Set<String> temp = new HashSet<String>();
    temp.add(child);
    temp.add(dumb);
    gParentAndChildWithEdge.addEdge(parent, "dumb edge", dumb);
    assertTrue(gParentAndChildWithEdge.listChildren(parent).containsAll(temp));
    assertTrue(temp.containsAll(gParentAndChildWithEdge.listChildren(parent)));
  }

  @Test
  public void testListChildrenNoChildren() {
    Set<String> temp = new HashSet<String>();
    assertTrue(g1.listChildren("node1").containsAll(temp));
    assertTrue(temp.containsAll(g1.listChildren("node1")));
  }
    //one, two, 0
  //listNodes

  @Test
  public void testListNodesEmpty() {
    assertTrue(empty.listNodes().isEmpty());
  }

  @Test
  public void testListNodesSingle() {
    Set<String> temp = new HashSet<String>();
    temp.add("node1");
    assertTrue(g1.listNodes().containsAll(temp));
    assertTrue(temp.containsAll(g1.listNodes()));
  }

  @Test
  public void testListNodesMultiple() {
    gParentAndChild.addNode(dumb);
    Set<String> temp = new HashSet<String>();
    temp.add(parent);
    temp.add(child);
    temp.add(dumb);
    assertTrue(gParentAndChild.listNodes().containsAll(temp));
    assertTrue(temp.containsAll(gParentAndChild.listNodes()));
  }

  @Test
  public void testGetEdgesToChildNone() {
    assertTrue(gParentAndChild.getEdgesToChild(parent, child).isEmpty());
  }

  @Test
  public void testGetEdgesToChildSingle() {
    Set<Edge<String, String>> temp = new HashSet<Edge<String, String>>();
    temp.add(new Edge<String, String>(child, "data"));
    assertTrue(gParentAndChildWithEdge.getEdgesToChild(parent, child).containsAll(temp));
    assertTrue(temp.containsAll(gParentAndChildWithEdge.getEdgesToChild(parent, child)));
  }

  @Test
  public void testGetEdgesToChildMultiple() {
    Set<Edge<String, String>> temp = new HashSet<Edge<String, String>>();
    temp.add(new Edge<String, String>(child, "data"));
    temp.add(new Edge<String, String>(child, "data2"));
    gParentAndChildWithEdge.addEdge(parent, "data2", child);
    assertTrue(gParentAndChildWithEdge.getEdgesToChild(parent, child).containsAll(temp));
    assertTrue(temp.containsAll(gParentAndChildWithEdge.getEdgesToChild(parent, child)));
  }

  @Test
  public void testGraphEdgeSetSafeness() {
    Set<Edge<String, String>> ref = gParentAndChildWithEdge.getEdges(parent);
    ref.clear();
    assertTrue(!gParentAndChildWithEdge.getEdges(parent).isEmpty());
    assertTrue(ref.isEmpty());
  }

  @Test
  public void testGraphKeySetSafeness() {
    Set<String> ref = gParentAndChild.listNodes();
    ref.clear();
    assertTrue(!gParentAndChildWithEdge.listNodes().isEmpty());
    assertTrue(ref.isEmpty());
  }

  @Test
  public void testRemoveNodeShouldDeleteEdgeFromParent() {
    gParentAndChildWithEdge.removeNode(child);
    assertFalse(gParentAndChild.listChildren(parent).contains(new Edge<String, String>(child, "data")));
  }

  @Test
  public void testGetSortedEdges() {
    gParentAndChildWithEdge.addEdge(parent, "asfnjksdaf", child);
    List<Edge<String, String>> temp = gParentAndChildWithEdge.getSortedEdges(parent);
    List<Edge<String, String>> temp2 = new LinkedList<Edge<String, String>>();
    temp2.addAll(gParentAndChildWithEdge.getEdges(parent));
    assertTrue(temp.equals(temp2));
  }
}
