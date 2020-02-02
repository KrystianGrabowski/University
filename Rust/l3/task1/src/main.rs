fn main() {
    println!("{}", row_sum_odd_numbers(1));
}

fn row_sum_odd_numbers(n:i64) -> i64 {
    n * n * n
}

#[test]
fn odd_triangle_test_1() {
    assert_eq!(row_sum_odd_numbers(1), 1);
}
#[test]
fn odd_triangle_test_2() {
    assert_eq!(row_sum_odd_numbers(42), 74088);
}
#[test]
fn odd_triangle_test_3() {
    assert_eq!(row_sum_odd_numbers(2), 8);
}
#[test]
fn odd_triangle_test_4() {
    assert_eq!(row_sum_odd_numbers(3), 27);
}
#[test]
fn odd_triangle_test_5() {
    assert_eq!(row_sum_odd_numbers(4), 64);
}
#[test]
fn odd_triangle_test_6() {
    assert_eq!(row_sum_odd_numbers(5), 125);
}
#[test]
fn odd_triangle_test_7() {
    assert_eq!(row_sum_odd_numbers(6), 216);
}
#[test]
fn odd_triangle_test_8() {
    assert_eq!(row_sum_odd_numbers(10), 1000);
}
#[test]
fn odd_triangle_test_9() {
    assert_eq!(row_sum_odd_numbers(50), 125000);
}
#[test]
fn odd_triangle_test_10() {
    assert_eq!(row_sum_odd_numbers(100), 1000000);
}