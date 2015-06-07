datatype 'a mylist = Empty
          | Cons of 'a * 'a mylist


datatype 'a tree
  = Leaf
  | Node of 'a * 'a tree * 'a tree

fun tinsert lt x Leaf = Node(x, Leaf, Leaf)
  | tinsert lt x (Node(a, l, r)) =
      if lt x a
      then Node (a, tinsert lt x l, r)
      else Node (a, l, tinsert lt x r)

fun intLT a b = a < b

val tinsertInt = tinsert intLT;

fun tmap f Leaf = Leaf
  | tmap f (Node(a, l, r)) = 
    Node (f a, tmap f l, tmap f r)

fun tfold f acc Leaf = acc
  | tfold f acc (Node (a, l, r)) = 
    tfold f (f a (tfold f acc l)) r

(*fun sort lt l =
  l |> fold (tinsert lt) Leaf
    |> tfold cons  *)

fun curry f a b = f (a, b)

fun curry' f =
  fn a => fn b => f (a, b)

fun uncurry f (a, b) = f a b

fun flip f a b = f b a

