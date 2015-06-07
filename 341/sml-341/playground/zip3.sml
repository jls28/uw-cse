fun zip3(xs, ys, zs) =
	case (xs, ys, zs) of
		([], [], []) => []
		| (x::xs', y::ys', z::zs') 
			=> (x, y, z)::zip3(xs', ys', zs')
		| _ => []

fun unzip3(xs) =
	case xs of 
		[] => ([], [], [])
		| (x, y, z)::xs' => let
					val (l1, l2, l3) = unzip3(xs')
				in
					(x::l1, y::l2, z::l3)
				end 

exception Ohno;

fun di(a, b) =
  if b = 0 then raise Ohno else a div b


fun fact(n) =
  let
    fun aux(n, a) =
      if n < 2
      then a
      else aux(n-1, n*a)
  in
    aux(n, 1)
  end

  (* a is the accumulator, pass in a each time keeps track of
  sum, by the time n <2 then we can return a*)

fun rev1(xs) =
  case xs of
    [] => []
    | x::xs' => rev1(xs') @ [x]

fun rev2(x2) =
  let
    fun aux(xs, a) =
      case xs of
        [] => a
        | x::xs' => aux(xs', x::a)
  in
    aux(xs, [])
  end
