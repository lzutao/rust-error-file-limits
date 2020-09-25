use std::io::Write;
use std::net::TcpStream;

fn main() {
    let mut a = Vec::new();
    for i in 0..300 {
        println!("{}", i);

        let mut stream = TcpStream::connect(("example.com", 80)).unwrap();
        stream.flush().unwrap();
        a.push(stream);
    }

    println!("finish")
}
