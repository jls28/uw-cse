val r = ref 0;
val x = !r;
val _ = r := 1;
val y = !r;


val bump = fn x => x + 1;
val ding = fn x => x - 1;

val s = ref bump;
val x = (!s) 20;
val _ = s := ding;
val y = (!s) 20;

val a = Array.array (4, "tatlock");
