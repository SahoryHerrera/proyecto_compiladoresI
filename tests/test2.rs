fn print_num(n: i32) {
    return;
}

fn main() {
    let i: i32 = 0;
    let limite: i32 = 5;
    let activo: bool = true;
    let letra: char = 'a';
    let nombre: str = "jesus";
    let pi: f64 = 3.14;

    while i < limite && activo {
        print_num(i);
        return;
    }

    for j in 0 .. 3 {
        print_num(j);
    }
}