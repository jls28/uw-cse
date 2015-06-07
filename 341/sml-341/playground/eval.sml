datatype exp = 
  Constant of int 
  | Negate of exp
  | Add of exp * exp
  | Multiply of exp * exp

fun eval(Constant(c)) = c
  | eval(Negate(c)) = ~(eval(c))
  | eval(Add(a, b)) = eval(a) + eval(b)
  | eval(Multiply(a, b)) = eval(a) * eval(b)

