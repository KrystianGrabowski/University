fn main() {
    println!("{}", last_digit("1606938044258990275541962092341162602522202993782792835301376","2037035976334486086268445688409378161051468393665936250636140449354381299763336706183397376"));
}

fn build_table(digit: i32) -> Vec<i32>{
    let mut v: Vec<i32> = (2..)
        .map(|x| digit.pow(x) % 10)
        .take_while(|&x| x != digit)
        .collect();
    v.insert(0, digit as i32);
    v
}

fn modulo(str1: &str, a: u32) -> u32 {
    str1
        .chars()
        .fold(0, |acc, x| ( acc * 10 + x.to_digit(10).unwrap() ) % a)
}

fn last_digit(str1: &str, str2: &str) -> i32 {
    if str2 == "0" { return 1; }
    let v: Vec<i32> = build_table(str1.chars().last().unwrap().to_digit(10).unwrap() as i32);
    let mut h: usize = modulo(str2, v.len() as u32) as usize;
    if h == 0 {h = v.len();}
    v[h - 1]
}


#[test]
fn zero_test_1() {
    assert_eq!(last_digit("4", "0"), 1);
}
#[test]
fn basic_test_1() {
    assert_eq!(last_digit("4", "1"), 4);
}
#[test]
fn basic_test_2() {
    assert_eq!(last_digit("4", "2"), 6);
}
#[test]
fn basic_test_3() {
    assert_eq!(last_digit("9", "7"), 9);
}
#[test]
fn basic_test_4() {
    assert_eq!(last_digit("10","10000000000"), 0);
}
#[test]
fn basic_test_5() {
    assert_eq!(last_digit("19", "19"), 9);
}
#[test]
fn basic_test_6() {
    assert_eq!(last_digit("4", "30"), 6);
}
#[test]
fn basic_test_7() {
    assert_eq!(last_digit("7","66"), 9);
}
#[test]
fn basic_test_8() {
    assert_eq!(last_digit("3","167"), 7);
}
#[test]
fn basic_test_9() {
    assert_eq!(last_digit("1606938044258990275541962092341162602522202993782792835301376","2037035976334486086268445688409378161051468393665936250636140449354381299763336706183397376"), 6);
}
#[test]
fn basic_test_10() {
    assert_eq!(last_digit("3715290469715693021198967285016729344580685479654510946723", "68819615221552997273737174557165657483427362207517952651"), 7);
}

