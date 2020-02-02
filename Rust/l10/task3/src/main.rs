use std::cmp::Ordering;

fn main() {
    println!("{}", good_vs_evil("0 0 0 0 0 10", "0 0 0 0 0 0 0"));
}

fn get_worth(s: &str, vec: Vec<i32>) -> i32{
    let mut iter = vec.into_iter();
    s.split_whitespace()
        .map(|x| x.parse::<i32>().unwrap() * iter.next().unwrap())
        .sum()
}

fn good_vs_evil(good: &str, evil: &str) -> String {
    let good_values: Vec<i32> = vec![1, 2, 3, 3, 4, 10];
    let evil_values: Vec<i32> = vec![1, 2, 2, 2, 3, 5, 10];
    match get_worth(good, good_values).cmp(&get_worth(evil, evil_values)) {
        Ordering::Greater => "Battle Result: Good triumphs over Evil".to_string(),
        Ordering::Less => "Battle Result: Evil eradicates all trace of Good".to_string(),
        Ordering::Equal => "Battle Result: No victor on this battle field".to_string(),
    }
}

#[test]
fn good_vs_evil_test_1() {
    assert_eq!(good_vs_evil("0 0 0 0 0 10", "0 0 0 0 0 0 0"), "Battle Result: Good triumphs over Evil");
}
#[test]
fn good_vs_evil_test_2() {
    assert_eq!(good_vs_evil("0 0 0 0 0 0", "0 0 0 0 0 0 10"), "Battle Result: Evil eradicates all trace of Good");
}
#[test]
fn good_vs_evil_test_3() {
    assert_eq!(good_vs_evil("0 0 0 0 0 10", "0 0 0 0 0 0 10"), "Battle Result: No victor on this battle field");
}
#[test]
fn good_vs_evil_test_4() {
    assert_eq!(good_vs_evil("0 1 0 0 2 0", "0 0 1 2 0 0 0"), "Battle Result: Good triumphs over Evil");
}
#[test]
fn good_vs_evil_test_5() {
    assert_eq!(good_vs_evil("0 0 0 1 0 1", "1 0 0 0 1 0 1"), "Battle Result: Evil eradicates all trace of Good");
}
#[test]
fn good_vs_evil_test_6() {
    assert_eq!(good_vs_evil("0 1 0 0 0 0", "0 1 0 0 0 0 0"), "Battle Result: No victor on this battle field");
}
#[test]
fn good_vs_evil_test_7() {
    assert_eq!(good_vs_evil("0 0 0 0 0 0", "1 1 1 1 1 1 1"), "Battle Result: Evil eradicates all trace of Good");
}
#[test]
fn good_vs_evil_test_8() {
    assert_eq!(good_vs_evil("1 1 1 1 1 1", "0 0 0 0 0 0 0"), "Battle Result: Good triumphs over Evil");
}
#[test]
fn good_vs_evil_test_9() {
    assert_eq!(good_vs_evil("1 1 1 1 1 1", "1 1 1 1 1 1 1"), "Battle Result: Evil eradicates all trace of Good");
}
#[test]
fn good_vs_evil_test_10() {
    assert_eq!(good_vs_evil("0 0 0 0 0 0", "0 0 0 0 0 0 0"), "Battle Result: No victor on this battle field");
}