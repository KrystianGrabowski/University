fn main() {}

fn get_count(string: &str) -> usize {
    return string.chars().filter(|c| ['a', 'e', 'i', 'o', 'u'].contains(c)).count();
}

#[test]
fn test_does_not_contain_1() {
    assert_eq!(get_count("bbbcccbbb"), 0);
}
#[test]
fn test_does_not_contain_2() {
    assert_eq!(get_count("bcdfghjklmmnprstwxyz"), 0);
}
#[test]
fn test_empty() {
    assert_eq!(get_count(""), 0);
}
#[test]
fn test_contains_1() {
    assert_eq!(get_count("alibaba"), 4);
}
#[test]
fn test_contains_2() {
    assert_eq!(get_count("alamakota"), 5);
}
#[test]
fn test_contains_3() {
    assert_eq!(get_count("xxxxxxxxxxyyyyyyyyyyzzzzzzzzzza"), 1);
}
#[test]
fn test_contains_4() {
    assert_eq!(get_count("aaaaaaaaaeeeeeeeeiiiiiiiiiiioooooooooouuuuuuuuu"), 47);
}
#[test]
fn test_contains_5() {
    assert_eq!(get_count("pppppeeeeenutbutter"), 8);
}
#[test]
fn test_contains_6() {
    assert_eq!(get_count("jaaaaaaaaaaaaaaaam"), 16);
}
#[test]
fn test_contains_7() {
    assert_eq!(get_count("stonoga"), 3);
}
#[test]
fn test_contains_with_spaces_1() {
    assert_eq!(get_count("a bbb aa uuuuccci"), 8);
}
#[test]
fn test_contains_with_spaces_2() {
    assert_eq!(get_count("k a b o p i u y x y z"), 4);
}
#[test]
fn test_does_not_contain_with_spaces_2() {
    assert_eq!(get_count("ccccccc pppp ll lll "), 0);
}



