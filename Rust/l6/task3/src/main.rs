fn main() {
    println!("{}", print(5).unwrap());
}

fn diamond_line(whitespaces: usize, asterisks: usize) -> String{
    format!("{}{}\n", " ".repeat(whitespaces), "*".repeat(asterisks))
}

fn print(n: i32) -> Option<String> {
    if n.is_negative() || n % 2 == 0 {return None;}
    Some((n/2+1..n).rev().fold(diamond_line(0, n as usize), |acc, x| {
        format!("{1}{0}{1}", acc, diamond_line((n - x) as usize,  (2 * x - n)as usize)) // x - (n - x)
    }))
}


#[test]
fn print_test_1() {
    assert_eq!(print(3), Some(" *\n***\n *\n".to_string()) );
}
#[test]
fn print_test_2() {
    assert_eq!(print(5), Some("  *\n ***\n*****\n ***\n  *\n".to_string()) );
}
#[test]
fn print_test_3() {
    assert_eq!(print(-3),None);
}
#[test]
fn print_test_4() {
    assert_eq!(print(2),None);
}
#[test]
fn print_test_5() {
    assert_eq!(print(0),None);
}
#[test]
fn print_test_6() {
    assert_eq!(print(1), Some("*\n".to_string()) );
}
#[test]
fn print_test_7() {
    assert_eq!(print(7), Some("   *\n  ***\n *****\n*******\n *****\n  ***\n   *\n".to_string()) );
}
#[test]
fn print_test_8() {
    assert_eq!(print(9), Some("    *\n   ***\n  *****\n *******\n*********\n *******\n  *****\n   ***\n    *\n".to_string()) );
}
#[test]
fn print_test_9() {
    assert_eq!(print(11), Some("     *\n    ***\n   *****\n  *******\n *********\n***********\n *********\n  *******\n   *****\n    ***\n     *\n".to_string()) );
}
#[test]
fn print_test_10() {
    assert_eq!(print(13), Some("      *\n     ***\n    *****\n   *******\n  *********\n ***********\n*************\n ***********\n  *********\n   *******\n    *****\n     ***\n      *\n".to_string()) );
}