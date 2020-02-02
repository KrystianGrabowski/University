use std::mem::swap;

fn main() {}

fn next_bigger_number(n: i64) -> i64 {
    if n < 10 { return -1 };
    let mut digits: Vec<char> = n.to_string().chars().collect();
    let mut first_smaller: usize = 0;
    for i in (1..digits.len()).rev() {
        if digits[i] > digits[i - 1] {
            first_smaller = i;
            break;
        }
        if i == 1 { return -1; }
    }
    let mut tail: Vec<char> = digits.split_off(first_smaller); tail.sort();
    let mut last = digits.pop().unwrap();
    for i in 0..tail.len() {
        if last < tail[i] {
            swap(&mut tail[i], &mut last);
            break;
        }
    }
    digits.push(last); digits.append(&mut tail);
    digits.into_iter().collect::<String>().parse().unwrap()
}

#[test]
fn zero_test() {
    assert_eq!(next_bigger_number(0), -1);
}
#[test]
fn invalid_number_of_digits_1() {
    assert_eq!(next_bigger_number(0), -1);
}
#[test]
fn invalid_number_of_digits_2() {
    assert_eq!(next_bigger_number(0), -1);
}
#[test]
fn valid_number_1() {
    assert_eq!(21, next_bigger_number(12));
}
#[test]
fn valid_number_2() {
    assert_eq!(531, next_bigger_number(513));
}
#[test]
fn valid_number_3() {
    assert_eq!(2071, next_bigger_number(2017));
}
#[test]
fn valid_number_4() {
    assert_eq!(441, next_bigger_number(414));
}
#[test]
fn valid_number_5() {
    assert_eq!(414, next_bigger_number(144));
}
#[test]
fn invalid_number_1() {
    assert_eq!(-1, next_bigger_number(111));
}
#[test]
fn invalid_number_2() {
    assert_eq!(-1, next_bigger_number(531));
}
#[test]
fn invalid_number_3() {
    assert_eq!(-1, next_bigger_number(987654321));
}
#[test]
fn invalid_number_4() {
    assert_eq!(-1, next_bigger_number(5432));
}
#[test]
fn invalid_number_5() {
    assert_eq!(-1, next_bigger_number(8221));
}



