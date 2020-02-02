fn main() {}

fn longest(a1: &str, a2: &str) -> String {
    let mut v1: Vec<char> = a1.chars().collect();
    let v2: Vec<char> = a2.chars().collect();
    v1.extend(v2);
    v1.sort();
    v1.dedup();
    return v1.into_iter().collect();
}

#[test]
fn basic_test_1() {
    assert_eq!(longest("aretheyhere", "yestheyarehere"), "aehrsty");
}
#[test]
fn basic_test_2() {
    assert_eq!(longest("loopingisfunbutdangerous", "lessdangerousthancoding"), "abcdefghilnoprstu");
}
#[test]
fn basic_test_3() {
    assert_eq!(longest("abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz"), "abcdefghijklmnopqrstuvwxyz");
}
#[test]
fn basic_test_4() {
    assert_eq!(longest("aaaaaaaaaaaaaaa", "bbbbbbbbbbbbbbb"), "ab");
}
#[test]
fn basic_test_5() {
    assert_eq!(longest("", ""), "");
}
#[test]
fn basic_test_6() {
    assert_eq!(longest("ttteeeesssster", "jjjjaaam"), "aejmrst");
}
#[test]
fn basic_test_7() {
    assert_eq!(longest("aaaaaaaaaa", "aaaaaaaaaa"), "a");
}
#[test]
fn basic_test_8() {
    assert_eq!(longest("abecadlo", ""), "abcdelo");
}
#[test]
fn basic_test_9() {
    assert_eq!(longest("hesoyam", "awsssety"), "aehmostwy");
}
#[test]
fn basic_test_10() {
    assert_eq!(longest("a", "c"), "ac");
}