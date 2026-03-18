// test3_operadores.rs
// Prueba: todos los operadores aritmeticos y logicos del alcance
// Compiladores I - UNITEC

fn operaciones(x: i32, y: i32) -> bool {
    let suma        = x + y;
    let resta       = x - y;
    let producto    = x * y;
    let cociente    = x / y;
    let modulo      = x % y;

    let mayor       = x > y;
    let menor       = x < y;
    let igual       = x == y;
    let diferente   = x != y;
    let mayor_igual = x >= y;
    let menor_igual = x <= y;

    let cond1  = mayor || menor;
    let cond2  = igual && diferente;
    let negado = !cond1;

    return negado;
}

fn main() {
    let r = operaciones(10, 3);
    println!(r);
}
