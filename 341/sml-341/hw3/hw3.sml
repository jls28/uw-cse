(* Stefan Dierauf sdierauf@cs 1232328 *)
(* higher order functions yee *)

(* takes a string list and returns a string list that has only
the strings in the argument that start with an uppercase letter*)

(* yee infix *)
infix |> 
fun x |> f  =  f x

fun only_capitals l = List.filter (fn x => Char.isUpper (String.sub(x, 0))) l

(* takes a string list and returns the longest string closest
  to the beginning of the list *)

fun longest_string1 l = foldl (fn (a, b) => if String.size a > String.size b then a else b) "" l;

(* same as longest_string1 but returns the longest at the end of the list*)
fun longest_string2 l = foldl (fn (a, b) => if String.size a >= String.size b then a else b) "" l;

(* Helper for longest_string3 and 4*)
fun longest_string_helper f l = 
  foldl (fn (a, b) => if f(String.size a, String.size b) then a else b) "" l;

(* Same behavior as longest_string1*)
val longest_string3 = longest_string_helper (fn (a, b) => a > b) ;

(* Same behavior as longest_string1*)
val longest_string4 = longest_string_helper (fn (a, b) => a >= b) ;

(* returns longest word that is capitalized at the end of the list*)
val longest_capitalized = longest_string4 o only_capitals;

(*returns reversed string*)
val rev_string = String.implode o List.rev o String.explode

exception NoAnswer

(* takes a list and returns the first result of f on each el
  if no f(el) returns SOME, raises NoAnswer *)
fun first_answer f [] = raise NoAnswer
  | first_answer f (x::xs) = case f(x) 
                              of NONE => first_answer f xs
                              |  SOME y => y

(* takes a list and returns SOME list of results if all els
  had SOME result, else returns NONE *)
fun all_answers f l = let
  fun aux [] acc = SOME acc
    | aux (x::xs) acc = case f x
                        of NONE => NONE
                        | SOME v => aux xs (v @ acc)
in
  aux l []
end 

datatype pattern = Wildcard
     | Variable of string
     | UnitP
     | ConstP of int
     | TupleP of pattern list
     | ConstructorP of string * pattern

datatype valu = Const of int
        | Unit
        | Tuple of valu list
        | Constructor of string * valu

fun g f1 f2 p =
    let 
  val r = g f1 f2 
    in
  case p of
      Wildcard          => f1 ()
    | Variable x        => f2 x
    | TupleP ps         => List.foldl (fn (p,i) => (r p) + i) 0 ps
    | ConstructorP(_,p) => r p
    | _                 => 0
    end

(**** for the challenge problem only ****)

datatype typ = Anything
       | UnitT
       | IntT
       | TupleT of typ list
       | Datatype of string

(**** you can put all your code here ****)


(* g() takes a function that maps units to ints, and a function
that maps strings to ints, and a pattern and produces and int *)

(* counts the number of wildcards in the pattern *)
fun count_wildcards (p: pattern) = g (fn wild => 1) (fn var => 0) p

(* counts the number of wildcards and the lengths of the variable names *)
fun count_wild_and_variable_lengths (p: pattern) = g (fn wild => 1) (fn var => String.size var) p

(* counts the number of times var appears in the pattern *)
fun count_some_var s (p:pattern) = g (fn w => 0) (fn var => if var = s then 1 else 0) p

(* checks the pattern to make sure there are no repeat variables *)
fun check_pat (p: pattern) = let
  fun all_strings (Variable(x)) = [x]
    | all_strings (TupleP(xs)) = List.foldl (fn (y, ys) => ys @ all_strings(y)) [] xs
    | all_strings (ConstructorP(_, p)) = all_strings(p)
    | all_strings (_) = []

  fun no_repeats [] = true
    | no_repeats (x::xs) = if List.exists (fn y => x = y) xs then false
                           else no_repeats(xs)
in 
  no_repeats (all_strings p)
end

(* Takes a value and a pattern and returns SOME list of the bindings
otherwise returns NONE *)
fun match (v, Variable x) = SOME [(x, v)]
  | match (v, UnitP) = (case v of Unit => SOME []
                        |  _ => NONE)
  | match (v, Wildcard) = SOME []
  | match (v, ConstP x) = 
          (case v of Const(v) => if v = x then SOME [] else NONE
                                 |  _ => NONE)
  | match (v, TupleP ps) = 
          (case v of Tuple(xs) => if List.length xs = List.length ps
                                  then all_answers match (ListPair.zip(xs, ps))
                                  else NONE
                  | _ => NONE)
  | match (v, ConstructorP(s, p)) = 
          (case v of Constructor(s', v') => if s = s' then match (v', p) else NONE
            | _ => NONE)

(* returns the first found answer of match*)
fun first_match v pl = SOME(first_answer (fn p => match(v, p)) pl) handle NoAnswer => NONE




