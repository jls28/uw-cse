datatype 'a tree = Empty
        | Node of 'a * 'a tree * 'a tree

val tree1 = Node(1, 
  Node(3, Empty, Empty), Node(2, Empty, Empty));

fun tree_map(f, Empty) = Empty
  | tree_map(f, Node (x, l, r)) = Node (f x,
                                  tree_map(f, l), 
                                  tree_map(f, r))


val res = tree_map(fn x => x + 1, tree1)