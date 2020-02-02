fn string_to_number(s: &str) -> i32 {
    s.parse::<i32>().unwrap()
}


#[test]
fn stn_1() {
    assert_eq!(string_to_number("1234"), 1234);
}
#[test]
fn stn_2() {
    assert_eq!(string_to_number("222"), 222);
}
#[test]
fn stn_3() {
    assert_eq!(string_to_number("1405"), 1405);
}
#[test]
fn stn_4() {
    assert_eq!(string_to_number("-777"), -777);
}
#[test]
fn stn_5() {
    assert_eq!(string_to_number("643"), 643);
}
#[test]
fn stn_6() {
    assert_eq!(string_to_number("9999991"), 9999991);
}