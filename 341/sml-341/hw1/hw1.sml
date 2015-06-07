(*Stefan Dierauf April 2015
Homework 1
A number of functions for calendar dates *)

(* a date is represented as year/month/day *)
type date = int * int * int

(* returns true iff first is a date older than second,
  otherwise false *)
fun is_older(first: date, second: date) =
  if #1 first < #1 second
  then true
  else if #2 first < #2 second
  then true
  else if #3 first < #3 second
  then true
  else false

(* returns the number of dates with the passed month
  in the passed list of dates *)
fun number_in_month(dates: date list, month: int) =
  if null dates
  then 0
  else if #2 (hd dates) = month
  then 1 + number_in_month(tl dates, month)
  else 0 + number_in_month(tl dates, month)

(* returns the number of dates with the passed list of months
  in the passed list of dates
  pre: all elements of months are unique *)
fun number_in_months(dates: date list, months: int list) =
  if null months
  then 0
  else (number_in_month(dates, (hd months))
    + number_in_months(dates, (tl months)))

(* returns a list of dates with the passed month *)
fun dates_in_month(dates: date list, month: int) =
  if null dates
  then []
  else if #2 (hd dates) <> month
  then dates_in_month((tl dates), month)
  else (hd dates)::dates_in_month((tl dates), month)

(* returns a list of dates with months of the passed list of months 
  pre: all elements of months are unique *)
fun dates_in_months(dates: date list, months: int list) =
  if null months
  then []
  else dates_in_month(dates, (hd months))
    @ dates_in_months(dates, (tl months))

(* returns the nth string in strings 
  pre: n < length strings *)
fun get_nth(strings: string list, n: int) =
  if n <= 1
  then (hd strings)
  else get_nth((tl strings), n - 1)

(* converts a date to a string in the format 'Month day, year'
  where day and year are integers 
  pre: 1 <= #2 n <= 12*)
fun date_to_string(n: date) =
  let
    val month_names = ["January", "February", "March", 
    "April", "May", "June", "July", "August", "September",
    "October", "November", "December"];
  in
    (get_nth(month_names, #2 n) ^ " " ^ Int.toString(#3 n) 
      ^ ", " ^ Int.toString(#1 n))
  end;

(* returns a number representing how many of the first n 
  elements of pos_nums are needed before reaching or exceeding sum 
  pre: all elements of pos_nums are > 0*)
fun number_before_reaching_sum(sum: int, pos_nums: int list) =
  if (sum - (hd pos_nums)) <= 0
  then 0
  else 1 + number_before_reaching_sum(sum - (hd pos_nums), (tl pos_nums));

(* takes a day of the year and returns an integer representing
  what month it is 
  pre: 0 < day < 365 *)
fun what_month(day: int) =
  let
    val month_cutoffs = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31];
  in
    1 + number_before_reaching_sum(day, month_cutoffs)
  end;

(* returns a list of integers for each day from day1 to day2
  representing the month they map to *)
fun month_range(day1: int, day2: int) =
  if day1 > day2
  then []
  else what_month(day1)::month_range(day1 + 1, day2)

(* returns SOME oldest date in dates iff dates is not null,
  otherwise NONE *)
fun oldest(dates: date list) =
  if null dates
  then NONE
  else
    let
      val old = oldest(tl dates)
    in
      if isSome old andalso is_older(valOf old, (hd dates))
      then old
      else SOME (hd dates)
    end
