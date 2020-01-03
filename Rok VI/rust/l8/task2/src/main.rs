fn main() {
    println!("{}", alphabet_position("The sunset sets at twelve o' clock."));
}

fn alphabet_position(text: &str) -> String {
    text.to_lowercase().chars()
        .filter(|x| x.is_ascii_alphabetic())
        .map(|x| (x as u8 - ('a' as u8 - 1)).to_string())
        .collect::<Vec<String>>().join(" ")
}

#[test]
fn alp_pos_test_1() {
    assert_eq!(
        alphabet_position("The sunset sets at twelve o' clock."),
        "20 8 5 19 21 14 19 5 20 19 5 20 19 1 20 20 23 5 12 22 5 15 3 12 15 3 11".to_string()
    );
}
#[test]
fn alp_pos_test_2() {
    assert_eq!(
        alphabet_position("The narwhal bacons at midnight."),
        "20 8 5 14 1 18 23 8 1 12 2 1 3 15 14 19 1 20 13 9 4 14 9 7 8 20".to_string()
    );
}
#[test]
fn alp_pos_test_3() {
    assert_eq!(
        alphabet_position("new test"),
        "14 5 23 20 5 19 20".to_string()
    );
}
#[test]
fn alp_pos_test_4() {
    assert_eq!(
        alphabet_position("do it"),
        "4 15 9 20".to_string()
    );
}
#[test]
fn alp_pos_test_5() {
    assert_eq!(
        alphabet_position(""),
        "".to_string()
    );
}
#[test]
fn alp_pos_test_6() {
    assert_eq!(
        alphabet_position("..()(()(&&^$$$$k"),
        "11".to_string()
    );
}
#[test]
fn alp_pos_test_7() {
    assert_eq!(
        alphabet_position("hhhaaahhh"),
        "8 8 8 1 1 1 8 8 8".to_string()
    );
}
#[test]
fn alp_pos_test_8() {
    assert_eq!(
        alphabet_position("aaaAAA.."),
        "1 1 1 1 1 1".to_string()
    );
}
#[test]
fn alp_pos_test_9() {
    assert_eq!(
        alphabet_position("zzz"),
        "26 26 26".to_string()
    );
}
#[test]
fn alp_pos_test_10() {
    assert_eq!(
        alphabet_position("abc"),
        "1 2 3".to_string()
    );
}
