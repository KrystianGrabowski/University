fn main() {
    println!("{}", find_digit(-456, 4));
}

fn find_digit(num: i32, nth: i32) -> i32 {
    let s: String = num.to_string();
    let length: i32 = s.len() as i32;
    if nth <= 0 {return -1;}
    if nth > length || (num < 0 && nth >= length) {return 0;}
    return s.chars().rev().nth((nth - 1) as usize).unwrap().to_digit(10).unwrap() as i32;
}

#[test]
fn test_1() {
    assert_eq!(find_digit(5673, 4), 5);
}
#[test]
fn test_2() {
    assert_eq!(find_digit(129, 2), 2);
}
#[test]
fn test_3() {
    assert_eq!(find_digit(-2825, 3), 8);
}
#[test]
fn test_4() {
    assert_eq!(find_digit(-456, 4), 0);
}
#[test]
fn test_5() {
    assert_eq!(find_digit(0, 20), 0);
}
#[test]
fn test_6() {
    assert_eq!(find_digit(65, 0), -1);
}
#[test]
fn test_7() {
    assert_eq!(find_digit(24, -8), -1);
}
#[test]
fn test_8() {
    assert_eq!(find_digit(666, 2), 6);
}
#[test]
fn test_9() {
    assert_eq!(find_digit(123456789, 4), 6);
}
#[test]
fn test_10() {
    assert_eq!(find_digit(9000, 1), 0);
}