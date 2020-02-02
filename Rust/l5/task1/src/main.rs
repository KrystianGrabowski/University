fn main() {
    println!("{}", xo("xxOo"));
}

fn xo(string: &'static str) -> bool {
    let s: String = string.to_lowercase();
    let filtered_string: usize = s.chars().filter(|&x| (x == 'x') | (x == 'o')).count();
    let string_wo_x: usize = s.chars().filter(|&x| x == 'o').count();
    filtered_string - string_wo_x == string_wo_x
}

#[test]
fn test_1() {
    assert_eq!(xo("xo"), true);
}
#[test]
fn test_2() {
    assert_eq!(xo("Xo"), true);
}
#[test]
fn test_3() {
    assert_eq!(xo("xxOo"), true);
}
#[test]
fn test_4() {
    assert_eq!(xo("xxxm"), false);
}
#[test]
fn test_5() {
    assert_eq!(xo("Oo"), false);
}
#[test]
fn test_6() {
    assert_eq!(xo("ooom"), false);
}
#[test]
fn test_7() {
    assert_eq!(xo("xxxooo"), true);
}
#[test]
fn test_8() {
    assert_eq!(xo("XOXOXO"), true);
}
#[test]
fn test_9() {
    assert_eq!(xo("XXxOooo"), false);
}
#[test]
fn test_10() {
    assert_eq!(xo("LLPWDXO"), true);
}



