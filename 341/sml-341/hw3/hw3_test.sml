use "hw3.sml";

(* Stefan Dierauf sdierauf@cs 1232328 *)
(* HW3 testssss*)

fun assert(eval: bool, test_name: string) =
  if eval
  then ()
  else (print ("TEST FAILED: " ^ test_name ^ "\n"));


val mixed = ["Hej", "hello", "Stul", "olleh", "Javl"];

assert(only_capitals(mixed) = ["Hej", "Stul", "Javl"],
 "only_capitals multiple things");

assert(longest_string1(mixed) = "hello",
  "longest_string1 get first longest");

assert(longest_string2(mixed) = "olleh",
  "longest_string2 get last longest");

assert(longest_string3(mixed) = "hello",
  "longest_string3 get first longest");

assert(longest_string4(mixed) = "olleh",
  "longest_string4 get last longest");

assert(longest_capitalized(mixed) = "Javl",
  "longest_capitalized fuck yeah currying");

assert(rev_string("stefan") = "nafets",
  "rev_string muh name");

assert((first_answer (fn x => SOME x) []) handle NoAnswer => NONE = NONE, 
  "first_answer empty list");

assert((first_answer (fn x => SOME x) [1, 2]) = 1, 
  "first_answer two elements first element");

assert((first_answer (fn x => if x = 2 then SOME x else NONE) [1, 2]) = 2, 
  "first_answer two elements second element");

assert(all_answers (fn x => SOME x) [] = SOME [],
  "all_answers pls work :c");

assert(all_answers (fn x => SOME [x]) [1, 2] = SOME [2, 1],
  "all_answers simple test");

assert(all_answers (fn x => NONE) [1, 2] = NONE,
  "all_answers NONE FOREVER");

assert(count_wildcards UnitP = 0,
    "no wildcards");

assert(count_wildcards Wildcard = 1,
    "one wildcards");

assert(count_wildcards (ConstructorP("nested", Wildcard)) = 1,
  "count_wildcards nested wildcard");

assert(count_wildcards(TupleP [ConstP 1, ConstructorP ("S", TupleP [Wildcard, Wildcard]), Wildcard, Wildcard]) = 4,
  "count_wildcards hella");

assert(count_wild_and_variable_lengths UnitP = 0,
    "count_wild_and_variable_lengths no wildcards");

assert(count_wild_and_variable_lengths Wildcard = 1,
    "count_wild_and_variable_lengths one wildcards");

assert(count_wild_and_variable_lengths (ConstructorP("nested", Wildcard)) = 1,
  "count_wild_and_variable_lengths nested wildcard");

assert(count_wild_and_variable_lengths(TupleP [ConstP 1, Wildcard, ConstructorP ("S", TupleP [Variable "kitten"])]) = 7,
  "some strings too");

assert(check_pat(TupleP[Variable "b", Variable "c"]) = true,
  "check_pat diff stuff");

assert(check_pat(TupleP[Variable "a", Variable "a"]) = false,
  "check_pat has repeat");

assert(match(Const 4, Variable "c") = SOME [("c",Const 4)],
  "simple match");

assert(match(Unit, UnitP) = SOME [],
  "match unit");

assert(match(Tuple[Const 4, Const 5], TupleP[Variable "c", Variable "d"]) 
    = SOME [("d",Const 5),("c",Const 4)],
  "match oh sheet tuples");
 
assert(match(Const 4, UnitP) = NONE,
  "match none matches D:");

assert(match(Const 4, ConstP 4) = SOME [],
  "match on consts");

assert(match(Const 4, ConstP 17) = NONE,
  "match different consts");

assert(first_match (Const 4) [UnitP] = NONE,
  "first_match none matches D:");
