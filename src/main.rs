use std::io::Write;
use std::net::TcpStream;

fn main() {
    let mut a = Vec::new();
    for i in 0..300 {
        println!("{}", i);

        let mut stream = match TcpStream::connect(("example.com", 80)) {
            Ok(s) => s,
            Err(e) => {
                panic!("raw: {:?}, kind: {:?}", e.raw_os_error(), e.kind());
            }
        };
        stream.flush().unwrap();
        a.push(stream);
    }

    println!("finish")
}
