fn main() {
    println!("{}", descending_order(15));
}

fn descending_order(x: u64) -> u64 {
    let mut digits: Vec<char> = x.to_string().chars().collect();
    digits.sort();
    digits.reverse();
    digits.into_iter().collect::<String>().parse().unwrap()
}

#[test]
fn test_1() {
    assert_eq!(descending_order(0), 0);
}
#[test]
fn test_2() {
    assert_eq!(descending_order(1), 1);
}
#[test]
fn test_3() {
    assert_eq!(descending_order(15), 51);
}
#[test]
fn test_4() {
    assert_eq!(descending_order(1021), 2110);
}
#[test]
fn test_5() {
    assert_eq!(descending_order(123456789), 987654321);
}
#[test]
fn test_6() {
    assert_eq!(descending_order(145263), 654321);
}
#[test]
fn test_7() {
    assert_eq!(descending_order(1254859723), 9875543221);
}
#[test]
fn test_8() {
    assert_eq!(descending_order(5555543), 5555543);
}
#[test]
fn test_9() {
    assert_eq!(descending_order(123), 321);
}
#[test]
fn test_10() {
    assert_eq!(descending_order(666), 666);
}