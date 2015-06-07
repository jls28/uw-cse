use "hw1.sml";

(* ===TESTS=== *)

fun assert(eval: bool, expected: bool, test_name: string) =
  if eval <> expected
  then
    (print ("TEST FAILED: " ^ test_name ^ "\n");
    false)
  else true

(* is_older tests *)

val old_date = (1900, 1, 8);
val bday = (1993, 10, 28);
val same_year = (1900, 2, 9);
val same_month = (1900, 1, 9);

assert(
  is_older(old_date, bday),
  true,
  "is_older different year");

assert(
  is_older(old_date, same_year),
  true,
  "is_older same year");

assert(
  is_older(old_date, same_month),
  true,
  "is_older same month");

assert(
  is_older(old_date, old_date),
  false,
  "is_older same date");

(* number_in_month tests *)

val four_dates = [old_date, bday, same_year, same_month];

assert(
  number_in_month(four_dates, 1) = 2,
  true,
  "number_in_month two dates");

assert(
  number_in_month(four_dates, 10) = 1,
  true,
  "number_in_month one date");

assert(
  number_in_month(four_dates, 5) = 0,
  true,
  "number_in_month no dates");

(* number_in_months tests *)

assert(
  number_in_months(four_dates, [1,2]) = 3,
  true,
  "number_in_months 3 dates");

assert(
  number_in_months(four_dates, [3, 5, 11]) = 0,
  true,
  "number_in_months 2 dates");

assert(
  number_in_months(four_dates, []) = 0,
  true,
  "number_in_months empty list");

assert(
  number_in_months(four_dates, [1, 2, 10]) = 4,
  true,
  "number_in_months ALL THE DATES");

(* dates_in_month tests *)

assert(
  length(dates_in_month(four_dates, 1)) = 2,
  true,
  "dates_in_month some months");

assert(
  length(dates_in_month(four_dates, 5)) = 0,
  true,
  "dates_in_month no months");

(* dates_in_months tests *)

assert(
  length(dates_in_months(four_dates, [1, 2, 10])) = 4,
  true,
  "dates_in_months ALL THE DATES");

assert(
  length(dates_in_months(four_dates, [3, 4, 5, 6, 7])) = 0,
  true,
  "dates_in_months lots of params, none found");

assert(
  length(dates_in_months(four_dates, [])) = 0,
  true,
  "dates_in_months empty months list");

(* get_nth tests *)

val letters = ["a", "b", "c", "d", "e"];

assert(
  get_nth(letters, 1) = "a",
  true,
  "get_nth first el");

assert(
  get_nth(letters, length(letters)) = "e",
  true,
  "get_nth last el");

assert(
  get_nth(letters, 3) = "c",
  true,
  "get_nth middle el");

(* date_to_string tests *)

assert(
  date_to_string(bday) = "October 28, 1993",
  true,
  "date_to_string of bday");

(* number_before_reaching_sum tests *)

val nums = [1, 2, 3, 4, 5];

assert(
  number_before_reaching_sum(1, nums) = 0,
  true,
  "number_before_reaching_sum first el");

assert(
  number_before_reaching_sum(10, nums) = 3,
  true,
  "number_before_reaching_sum middle el");

assert(
  number_before_reaching_sum(11, nums) = 4,
  true,
  "number_before_reaching_sum just past middle el");

(* what_month tests *)

assert(
  what_month(1) = 1,
  true,
  "what_month first day");

assert(
  what_month(364) = 12,
  true,
  "what_month last day"); (* list sums to 365,
  so last valid day is 364. via spec "Assume the entire 
  list sums to more than the passed in value' *)

assert(
  what_month(301) = 10,
  true,
  "what_month my bday");

(* month_range tests *)

assert(
  month_range(200, 190) = [],
  true,
  "month_range day1 greater than day2");

assert(month_range(1, 1) = [1],
  true,
  "month_range day1 = day 2");

assert(month_range(1, 5) = [1, 1, 1, 1, 1],
  true,
  "month_range a few days");

assert(month_range(31, 32) = [1, 2],
  true,
  "month_range boundary check");

(* oldest tests *)

assert(
  valOf (oldest([bday])) = bday,
  true,
  "oldest single date");

assert(
  valOf (oldest(four_dates)) = old_date,
  true,
  "oldest four_dates");

assert(
  isSome (oldest([])) = false,
  true,
  "oldest empty list");
