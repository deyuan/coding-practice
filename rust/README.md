# Rust Programming Language

## Links
* Rust official site: https://www.rust-lang.org
* Install Rust: https://www.rust-lang.org/tools/install
* Rust by example: https://doc.rust-lang.org/stable/rust-by-example

## After Installation
* RUSTUP_HOME: `~/.rustup`
  * Rustup metadata
  * Programming language toolchains
* CARGO_HOME: `~/.cargo`
  * Cargo package manager
  * Commands such as `cargo`, `rustc`, and `rustup` in `bin` subdirectory
* Shell PATH configuration
  * For example, `. "$HOME/.cargo/env"` in `~/.zshenv`
* To uninstall
  * `rustup self uninstall`

## Rust Hello World
Create source code file `hello.rs`:
```
// Rust Hello World
fn main() {
    println!("Hello World!");
}
```
Compile with `rustc`:
```
rustc hello.rs
```
Run the executable `hello`:
```
./hello
Hello World!
```