// test_final_confirmacion.rs
// Validación completa del compilador - Compiladores I UNITEC

fn operaciones(x: i32, y: i32) -> bool {
    let suma = x + y;
    let resta = x - y;
    let producto = x * y;
    let cociente = x / y;
    let modulo = x % y;

    let mayor = x > y;
    let menor = x < y;
    let igual = x == y;
    let diferente = x != y;
    let mayor_igual = x >= y;
    let menor_igual = x <= y;

    let cond1 = mayor || menor;
    let cond2 = igual && diferente;
    let negado = !cond1;

    return negado;
}

fn contar(limite: i32) -> i32 {
    let mut suma: i32 = 0;
    let mut i: i32 = 0;

    while i < limite {
        suma += i;
        i += 1;
    }

    return suma;
}

fn tabla(n: i32) {
    for k in 1..11 {
        let resultado = n * k;
        println!(resultado);
    }
}

fn main() {
    let resultado_bool = operaciones(10, 5);
    let total: i32 = contar(10);
    tabla(5);

    let a: f64 = 3.14;
    let b: bool = true;
    let c: bool = false;
    let msg: str = "Hola Rust";
    let letra: char = 'R';

    if b && !c {
        let x = total * 2;
        let y = x - 5;
        let z = y % 3;
    } else {
        return;
    }
}