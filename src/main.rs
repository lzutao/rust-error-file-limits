use std::io::Write;
use std::net::TcpStream;
use std::net::ToSocketAddrs;

fn main() {
    let mut a = Vec::new();
    let saddrs = ("example.com", 80)
        .to_socket_addrs()
        .unwrap()
        .next()
        .unwrap();
    for i in 0..300 {
        println!("{}", i);

        let mut stream = match TcpStream::connect(saddrs) {
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
