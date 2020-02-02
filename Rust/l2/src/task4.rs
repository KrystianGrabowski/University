fn main() {}

fn count_bits(n: i64) -> u32 {
    n.count_ones()
}

#[test]
fn number_of_bits_1() {
    assert_eq!(count_bits(0), 0);
}
#[test]
fn number_of_bits_2() {
    assert_eq!(count_bits(4), 1);
}
#[test]
fn number_of_bits_3() {
    assert_eq!(count_bits(7), 3);
}
#[test]
fn number_of_bits_4() {
    assert_eq!(count_bits(9), 2);
}
#[test]
fn number_of_bits_5() {
    assert_eq!(count_bits(240), 4);
}
#[test]
fn number_of_bits_6() {
    assert_eq!(count_bits(208), 3);
}
#[test]
fn number_of_bits_7() {
    assert_eq!(count_bits(407552), 5);
}
#[test]
fn number_of_bits_8() {
    assert_eq!(count_bits(67516416), 6);
}
#[test]
fn number_of_bits_9() {
    assert_eq!(count_bits(67516532), 10);
}
#[test]
fn number_of_bits_10() {
    assert_eq!(count_bits(255), 8);
}
#[test]
fn number_of_bits_11() {
    assert_eq!(count_bits(1048575), 20);
}
#[test]
fn number_of_bits_12() {
    assert_eq!(count_bits(1044495), 12);
}