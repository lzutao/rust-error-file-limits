use std::fs::File;
use std::io::Write;

fn main() {
    let mut a = Vec::new();
    for i in 0..300 {

        println!("{}",i);

        let mut fd = File::create(i.to_string()).unwrap(); 
        fd.write_all(b"asdfasdfasdfa").unwrap();
        a.push(fd);        
    }

    println!("finish")
}
