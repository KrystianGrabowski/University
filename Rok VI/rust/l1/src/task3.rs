fn count_red_beads(n: u32) -> u32 {
    if n < 2 { 0 } else { (n - 1 ) * 2 }
}


#[test]
fn less_than_zero_0() {
    assert_eq!(count_red_beads(0), 0);
}
#[test]
fn less_than_zero_1() {
    assert_eq!(count_red_beads(1), 0);
}
#[test]
fn three_beads() {
    assert_eq!(count_red_beads(3), 4);
}
#[test]
fn five_beads() {
    assert_eq!(count_red_beads(5), 8);
}
#[test]
fn six_beads() {
    assert_eq!(count_red_beads(6), 10);
}
#[test]
fn ten_beads() {
    assert_eq!(count_red_beads(10), 18);
}