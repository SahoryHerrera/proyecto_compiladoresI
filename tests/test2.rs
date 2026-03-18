// test2_control.rs
// Prueba: while, for, mut, operadores compuestos, tipos primitivos
// Compiladores I - UNITEC

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
    }
}
