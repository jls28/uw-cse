fun absurd(x: int) = let
  val foo = 42
  val bar = foo * foo
  val z = if x < foo then 1 else bar
  fun some(y: int) = ~y
in
  if z > foo then bar else foo * x
end

(*fun silly2() =
  let
    val name = value
  in
    body
  end*)

fun silly2() =
  let
    val x = 1
  in
    (let val x = 2 in x + 1 end) + 
    (let val y = x + 2 in y + 1 end)
  end

fun count1(n: int) =
  let
    fun loop(i: int) = 
      if i = n
      then i::[]
      else i::loop(i+1)
  in
    loop(0)
  end

fun get_nth(nums: num list, n: int) =
  if n <= 1
  then (hd nums)
  else get_nth((tl nums), n - 1)

fun fibb(n: int) =
  let
    val memo = [1]
  in
    if n < (size memo)
    then (get_nth(memo, n))
    else ()
  end