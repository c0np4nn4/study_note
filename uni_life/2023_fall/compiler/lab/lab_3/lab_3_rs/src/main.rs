use std::io::{self, Write};

#[derive(Debug)]
enum Data {
    TINT(i32),
    TSTR(String),
    TSYM(String),
}

fn main() {
    let mut input_string = String::new();
    io::stdin()
        .read_line(&mut input_string)
        .expect("Failed to read line");
    let input_string = input_string.trim_end();

    let parsed_data = parse_string(&input_string);
    for data in parsed_data.iter() {
        match data {
            Data::TINT(val) => println!("(INT, {})", val),
            Data::TSTR(val) => println!("(STR, '{}')", val),
            Data::TSYM(val) => println!("(SYM, {})", val),
        }
    }
}

fn parse_string(input: &str) -> Vec<Data> {
    let mut data_vec = Vec::new();
    let mut chars = input.chars().peekable();

    while let Some(&ch) = chars.peek() {
        if ch.is_whitespace() {
            chars.next();
            continue;
        }

        if ch.is_digit(10) {
            let mut num = 0;
            while let Some(&ch) = chars.peek() {
                if ch.is_digit(10) {
                    num = num * 10 + ch.to_digit(10).unwrap() as i32;
                    chars.next();
                } else {
                    break;
                }
            }
            data_vec.push(Data::TINT(num));
        } else if ch == '"' {
            chars.next(); // skip the opening quote
            let mut s = String::new();
            while let Some(ch) = chars.next() {
                if ch == '\\' && chars.peek() == Some(&'"') {
                    chars.next(); // skip the backslash
                    s.push('"');
                } else if ch == '"' {
                    break;
                } else {
                    s.push(ch);
                }
            }
            data_vec.push(Data::TSTR(s));
        } else {
            let mut s = String::new();
            while let Some(&ch) = chars.peek() {
                if ch.is_whitespace() || ch == '"' {
                    break;
                } else {
                    s.push(ch);
                    chars.next();
                }
            }
            data_vec.push(Data::TSYM(s));
        }
    }
    data_vec
}
