fn main() {
    println!("{}", camel_case("test case"));
}

fn camel_case(str: &str) -> String {
    str.split_whitespace()
        .map(|x| x.to_uppercase()
            .chars()
            .take(1).chain(x.chars().skip(1)).collect())
        .collect::<Vec<String>>()
        .join("")
}

#[test]
fn camel_case_test_1() {
    assert_eq!(camel_case("test case"), "TestCase");
}
#[test]
fn camel_case_test_2() {
    assert_eq!(camel_case("camel case method"), "CamelCaseMethod");
}
#[test]
fn camel_case_test_3() {
    assert_eq!(camel_case("say hello "), "SayHello");
}
#[test]
fn camel_case_test_4() {
    assert_eq!(camel_case(" camel case word"), "CamelCaseWord");
}
#[test]
fn camel_case_test_5() {
    assert_eq!(camel_case(""), "");
}
#[test]
fn camel_case_test_6() {
    assert_eq!(camel_case("test test      test"), "TestTestTest");
}
#[test]
fn camel_case_test_7() {
    assert_eq!(camel_case(" c c c"), "CCC");
}
#[test]
fn camel_case_test_8() {
    assert_eq!(camel_case("SAY HELLO "), "SAYHELLO");
}
#[test]
fn camel_case_test_9() {
    assert_eq!(camel_case(" C C c "), "CCC");
}
#[test]
fn camel_case_test_10() {
    assert_eq!(camel_case("Camel Case Word"), "CamelCaseWord");
}

