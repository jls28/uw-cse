type point = { x: int, y: int}

val pointx = 
{
  x = 15,
  y = 3
}

val tuplePoint = (15, 3);

fun collatz(n: int) = 
  if n <= 1
  then [n]
  else if n mod 2 = 0
    then n :: collatz(n div 2)
    else n :: collatz(3 * n + 1)

fun zip(l1: int list, l2: int list) =
  case (l1, l2)
    of (x::xs, y::ys) => (x, y)