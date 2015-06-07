fun greaterThan x =
  fn y => x < y

fun filter (f,xs) =
    case xs of
  [] => []
      | x::xs' => if f x then x::(filter(f,xs')) else filter(f,xs')

fun fold (f,acc,xs) =
    case xs of 
  [] => acc
      | x::xs' => fold (f,f(acc,x),xs')

fun compose (f, g) = 
  fn x => f (g x)

fun compose' f g x = f (g x)

fun shorterThan x =
  fn y => String.size x > String.size y

(*fun map f [] = []
  | map f (x::xs) = f x :: map f xs*)

(*fun fold f acc [] = acc
  | fold f acc x::xs = fold f (f acc x) xs*)

exception OutsideRange;

fun nth [] i = raise OutsideRange
  | nth (x::xs) 0 = x
  | nth (x::xs) i = nth xs (i-1)

infix |>
fun x |> f = f x

fun strMap f s =
  s |> String.explode
    |> map f
    |> String.implode

(*fun strFilter f s =
  s |> String.explode
    |> filter f
    |> String.implode*)

fun strLift (f: char list -> char list) s =
  s |> String.explode
    |> f
    |> String.implode

fun split s =
  let
    fun aux (w::ws) c = 
      if Char.isSpace c then ([]::w::ws)
      else ((c::w)::ws)
  in
    s |> String.explode
      |> fold aux [[]]
      |> map rev
      |> rev
      |> map String.implode
  end