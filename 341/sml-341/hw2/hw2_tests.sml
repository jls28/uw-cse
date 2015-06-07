(* Stefan Dierauf sdierauf@cs 1232328 *)
(* Unit tests for hw2 *)
use "hw2.sml";

(* These are just two tests for problem 2; you will want more.

   Naturally these tests and your tests will use bindings defined 
   in your solution, in particular the officiate function, 
   so they will not type-check if officiate is not defined.
 *)

fun assert(eval: bool, test_name: string) =
  if eval
  then ()
  else (print ("TEST FAILED: " ^ test_name ^ "\n"));

val names = ["stefan", "bob", "joe", "sara"];

(* all_except_options tests *)

assert(all_except_option("stefan", names) = SOME ["bob", "joe", "sara"],
  "all_except_option first element");

assert(all_except_option("sara", names) = SOME ["stefan", "bob", "joe"],
  "all_except_option last element");

assert(all_except_option("zzz", names) = NONE,
  "all_except_option element not found");


(* get_substitutions1 tests *)

assert((get_substitutions1([["Fred","Fredrick"],["Elizabeth","Betty"],["Freddie","Fred","F"]], "Fred") 
  = ["Fredrick","Freddie","F"]),
  "get_substitutions1 some substitutions");

assert(get_substitutions1([["Fred","Fredrick"],["Elizabeth","Betty"],["Freddie","Fred","F"]],
"Joe") = [],
  "get_substitutions1 no substitutions");

(* get_substitutions2 tests *)

assert(get_substitutions2([["Fred","Fredrick"],["Elizabeth","Betty"],["Freddie","Fred","F"]],
"Fred") = ["Freddie","F", "Fredrick"],
  "get_substitutions2 some substitutions");

assert(get_substitutions2([["Fred","Fredrick"],["Elizabeth","Betty"],["Freddie","Fred","F"]],
"Joe") = [],
  "get_substitutions2 no substitutions");

(* similar_names tests *)

assert(similar_names([["Fred","Fredrick"],["Elizabeth","Betty"],["Freddie","Fred","F"]],
{first="Fred", middle="W", last="Smith"}) = [{first="Fred",last="Smith",middle="W"},{first="F",last="Smith",middle="W"},
   {first="Freddie",last="Smith",middle="W"},
   {first="Fredrick",last="Smith",middle="W"}], 
"similar_names simple test");

assert(similar_names([["Fred","Fredrick"],["Elizabeth","Betty"],["Freddie","Fred","F"]],
{first="GEORGE", middle="W", last="Smith"}) = [{first="GEORGE",last="Smith",middle="W"}], 
"similar_names only original");

(* card color tests*)

assert(card_color(Clubs, Num 10) = Black, "card_color clubs = black");
assert(card_color(Diamonds, Num 10) = Red, "card_color diamonds = red");
assert(card_color(Hearts, Num 10) = Red, "card_color hearts = red");
assert(card_color(Spades, Num 10) = Black, "card_color spades = black");

(* card_value tests *)

assert(card_value(Clubs, Num 9) = 9, "card_value integer");
assert(card_value(Clubs, Ace) = 11, "card_value ace");
assert(card_value(Clubs, King) = 10, "card_value facecard");

(* remove_card tests *)

val cardlist = [(Clubs, Num(5)), (Clubs, Num(6))];
val longcardlist = [(Clubs, Num(5)), (Clubs, Num(6)), (Clubs, Num(7))];
val diffcards = (Hearts, Num(7))::cardlist;

assert(remove_card(cardlist, (Clubs, Num(5)), IllegalMove) = [(Clubs, Num(6))],
  "remove_card found");

assert((remove_card(cardlist, (Clubs, King), IllegalMove) handle IllegalMove => []) = [],
  "remove_card not found throw exception");


(* all_same_color tests *)

assert(all_same_color(cardlist), "all_same_color true");
assert(all_same_color(diffcards) = false, "all_same_color not the same");
assert(all_same_color([(Spades,Ace),(Clubs,Ace),(Diamonds,Ace)]) = false,
  "all_same_color not the same diff order");

(* sum_cards tests *)

assert(sum_cards(cardlist) = 11, "sum_cards two cards");
assert(sum_cards([]) = 0, "sum_cards empty card list");
assert(sum_cards(diffcards) = 18, "sum_cards diff suits");
assert(sum_cards((Clubs, Ace)::diffcards) = 29, "sum_cards diffcards WITH AN ACE");

(* score tests *)

assert(score(diffcards, 0) = 3*sum_cards(diffcards),
  "score with goal 0 and not same color");
assert(score(cardlist, 11) = 0, "score same color and goal equal to sum");
assert(score(cardlist, 5) = 9, "score same color and goal < sum");

(* officiate tests *)

val cards = [(Clubs,Jack),(Spades,Num(8))];
val moves = [Draw,Discard(Hearts,Jack)];

assert((officiate(cards,moves,42) handle IllegalMove => ~1) = ~1,
  "officiate raise IllegalMove");

val cards = [(Clubs,Ace),(Spades,Ace),(Clubs,Ace),(Spades,Ace)];
val moves = [Draw,Draw,Draw,Draw,Draw];

assert(officiate(cards, moves, 42) = 3, "officiate simple game exhaust stock");

val moves = [Draw,Draw,Draw];

assert(officiate(cards, moves, 42) = 4, "officiate simple game dont exhaust stock same colors");

val cards = [(Hearts,Ace),(Spades,Ace),(Clubs,Ace),(Diamonds,Ace)];
val moves = [Draw,Draw,Draw,Draw,Draw];

assert(officiate(cards, moves, 42) = 6, "officiate simple game exhaust stock diff colors");

val moves = [Draw,Draw,Draw];

assert(officiate(cards, moves, 42) = 9, "officiate simple game dont exhaust stock diff colors");
