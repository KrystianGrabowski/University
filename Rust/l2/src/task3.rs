fn main() {}

fn summy(strng: &str) -> i32 {
    let v: Vec<i32> = strng.rsplit(" ").map(|x| x.parse().unwrap()).collect();
    v.iter().sum()
}




#[test]
fn sample_test_1() {
    assert_eq!(summy("1 2 3"), 6);
}
#[test]
fn sample_test_2() {
    assert_eq!(summy("1 2 3 4"), 10);
}
#[test]
fn sample_test_3() {
    assert_eq!(summy("1 2 3 4 5"), 15);
}
#[test]
fn sample_test_4() {
    assert_eq!(summy("10 10"), 20);
}
#[test]
fn sample_test_5() {
    assert_eq!(summy("0 0"), 0);
}
#[test]
fn sample_test_6() {
    assert_eq!(summy("222 111"), 333);
}
#[test]
fn sample_test_7() {
    assert_eq!(summy("6 66"), 72);
}
#[test]
fn sample_test_8() {
    assert_eq!(summy("1 1 1 1 1"), 5);
}
#[test]
fn sample_test_9() {
    assert_eq!(summy("32 23"), 55);
}
#[test]
fn sample_test_10() {
    assert_eq!(summy("1 6 7 8"), 22);
}
