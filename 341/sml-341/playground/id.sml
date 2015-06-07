

fun ntimes(f, x, 0) = x
  | ntimes(f, x, n) = f (ntimes (f, x, n-1))

fun inc x = x + 1

fun mult(x, y) =
  let
    fun addX z = ntimes(inc, x, z)
  in
    ntimes(addX, 0, y)
  end