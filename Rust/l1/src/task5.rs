fn printer_error(s: &str) -> String {
    let v: Vec<_>  = s.matches( |c| c > 'm').collect();
    format!("{}/{}", v.len() , s.len())
}

#[test]
fn empty_string() {
    assert_eq!(&printer_error(""), "0/0");
}
#[test]
fn valid_string_1() {
    assert_eq!(&printer_error("abc"), "0/3");
}
#[test]
fn valid_string_2() {
    assert_eq!(&printer_error("aaaaccbbbbbaaahhhh"), "0/18");
}
#[test]
fn valid_string_3() {
    assert_eq!(&printer_error("hhhhhmmmmm"), "0/10");
}
#[test]
fn invalid_str_1() {
    assert_eq!(&printer_error("yyyyyyyyyyyyyyyyyyyyyy"), "22/22");
}
#[test]
fn invalid_str_2() {
    assert_eq!(&printer_error("sssssssssttttta"), "14/15");
}
#[test]
fn invalid_str_3() {
    assert_eq!(&printer_error("cccwwwaaaaaaaaaaabbbbbbbbbbbbmmmmmmmmmmmmmuuuuuzzzzzcccccca"), "13/59");
}
#[test]
fn invalid_str_4() {
    assert_eq!(&printer_error("aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"), "3/56");
}
#[test]
fn invalid_str_5() {
    assert_eq!(&printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"), "6/60");
}
#[test]
fn invalid_str_6() {
    assert_eq!(&printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyzuuuuu"), "11/65");
}

