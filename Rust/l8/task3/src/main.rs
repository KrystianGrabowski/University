
fn main() {
    let a = dec2_fact_string(463);
    println!("{}", a);
    println!("{}", fact_string_2dec(a));
}

fn fact(n:u64) -> u64 {
    (2u64..=n as u64).fold(1, |x, acc| acc * x)
}

fn sign_to_num(sign: char) -> u64 {
    match sign {
        '0'..='9' => sign.to_digit(10).unwrap() as u64,
        'A'..='Z' => (sign as u8 - 'A' as u8 + 10) as u64,
        _ => panic!()
    }
}

fn num_to_sign(number: u64) -> char {
    match number {
        0..=9 => number.to_string().parse().unwrap(),
        10..=36 => (number as u8 - 10 + 'A' as u8) as char,
        _ => panic!()
    }
}

fn dec2_fact_string(nb: u64) -> String {
    let mut nr = nb.clone();
    let mut it = 1;
    let mut s: String = "".to_string();
    while nr != 0 {
        let mod_res = nr % it;
        nr = nr / it;
        it += 1;
        s.push(num_to_sign(mod_res));
    }
    s.chars().rev().collect()
}

fn fact_string_2dec(s: String) -> u64 {
    let mut iterator = (0..s.len()).rev();
    s.chars().fold(0, |acc, v| {
        acc + (sign_to_num(v) * fact(iterator.next().unwrap() as u64))
    })
}

fn testing1(nb: u64, exp: &str) -> () {
    assert_eq!(&dec2_fact_string(nb), exp)
}

fn testing2(s: &str, exp: u64) -> () {
    assert_eq!(fact_string_2dec(s.to_string()), exp)
}

#[test]
fn dec2_fact_string_1() {
    testing1(2982, "4041000");
}
#[test]
fn fact_string_2dec_1() {
    testing2("4041000", 2982);
}
#[test]
fn dec2_fact_string_2() {
    testing1(463, "341010");
}
#[test]
fn fact_string_2dec_2() {
    testing2("341010", 463);
}
#[test]
fn dec2_fact_string_3() {
    testing1(1234, "1411200");
}
#[test]
fn fact_string_2dec_3() {
    testing2("1411200", 1234);
}
#[test]
fn dec2_fact_string_4() {
    testing1(746, "1010100");
}
#[test]
fn fact_string_2dec_4() {
    testing2("1010100", 746);
}
#[test]
fn dec2_fact_string_5() {
    testing1(666, "523000");
}
#[test]
fn fact_string_2dec_5() {
    testing2("523000", 666);
}
