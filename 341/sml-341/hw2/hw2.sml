(* Stefan Dierauf sdierauf@cs 1232328*)
(* Homework 2 solution: card games and string lists*)
(* Actually pattern mathcing and tail recursion*)

(* if you use this function to compare two strings (returns true if the same
   string), then you avoid several of the functions in problem 1 having
   polymorphic types that may be confusing *)
fun same_string(s1 : string, s2 : string) =
    s1 = s2

(* put your solutions for problem 1 here *)

(* Given a list env and a lookup string lookup,
  returns SOME of env without lookup if lookup was found,
  else returns NONE if lookup was not found *)
fun all_except_option(lookup: string, env: string list) = 
  case env
    of [] => NONE
    |  x::xs => if same_string(lookup, x) then SOME xs else 
                case all_except_option(lookup, xs)
                  of NONE => NONE
                  | SOME s => SOME (x::s)


(* Given a list of list of strings representing substitutions,
and a target string to substitue on, returns a list of all found
  alternatives to the target except the target*)
fun get_substitutions1(subs: string list list, s: string) =
  case subs
    of [] => []
    | xs::xss => (case all_except_option(s, xs)
                  of NONE => []
                  | SOME ys => ys) @ get_substitutions1(xss, s)


(* @see get_substitutions1*)
fun get_substitutions2(subs: string list list, s: string) =
  let
    fun aux(subs, s, a) = 
      case subs of
        [] => a
        | xs::xss => aux(xss, s, (case all_except_option(s, xs) of
                      SOME ys => ys
                      | NONE => []) @ a)
  in
    aux(subs, s, [])
  end



(* Takes a list of substitutions and a fullname, returns all possible
  mutations of fullname mutating only the first name *)
fun similar_names(subs: string list list, full: {first:string,middle:string,last:string}) =
  let
    fun aux(firstnames, full: {first:string,middle:string,last:string}, a) =
      case firstnames of
        [] => a
        | x::xs => aux(xs, full, {first = x, middle = #middle full, last = #last full} :: a)
  in
    full::aux(get_substitutions1(subs, #first full), full, [])
  end



(* you may assume that Num is always used with values 2, 3, ..., 10
   though it will not really come up *)
datatype suit = Clubs | Diamonds | Hearts | Spades
datatype rank = Jack | Queen | King | Ace | Num of int 
type card = suit * rank

datatype color = Red | Black
datatype move = Discard of card | Draw 

exception IllegalMove

(* put your solutions for problem 2 here *)

(* Given a card, returns the color of the suite of the card *)
fun card_color(c: card) =
  case (#1 c) of
    Clubs => Black
    | Diamonds => Red
    | Hearts => Red
    | Spades => Black

(* Given a card, returns the value of the rank of the card 
  as determined by the arbitrary game's rules*)
fun card_value(c: card) =
  case (#2 c)
    of Ace => 11
    | Num x => x
    | _ => 10

(*Given a list of cards, the card to remove, and an exception,
  returns a list of cards with the specified card removed if
  it was found, otherwise raises the exception*)
fun remove_card(cs: card list, c: card, e) =
  case cs
    of [] => raise e
    | x::xs => if (x = c) then xs else x::remove_card(xs, c, e)

(* returns true iff all the cards in the passed list are the same color*)
fun all_same_color(cs: card list) =
  case cs
    of [] => true
    | x::[] => true
    | x::y::xs => if card_color(x) = card_color(y)
                  then all_same_color(y::xs)
                  else false

(* returns the sum of the values of the passed cards *)
fun sum_cards(cs: card list) =
  let
    fun aux(cs: card list, a) =
      case cs
        of [] => a
        | x::xs => aux(xs, a + card_value(x))
  in
    aux(cs, 0)
  end

(* Returns the score of the game given a card list
  and a goal value.*)
fun score(cs: card list, goal: int) =
  let
    val sum = sum_cards(cs);
    val prelim = if sum > goal then 3 * (sum - goal)
                  else goal - sum;
  in
    if all_same_color(cs) then prelim div 2 else prelim
  end

(* Takes a list of cards, a list of moves, and a goal value,
and returns final score following the game's rules*)
fun officiate(cs: card list, ms: move list, goal: int) =
  let
    fun round(cs, ms, goal, h) =
      case (cs, ms) of
        (c::cs', Draw::ms') => if sum_cards(c::h) > goal then score(c::h, goal)
                              else round(cs', ms', goal, c::h)
        | (_, Discard x::ms') => round(cs, ms', goal, remove_card(h, x, IllegalMove))
        | ([], _) => score(h, goal)
        | (_, []) => score(h, goal)
  in
    round(cs, ms, goal, [])
  end
