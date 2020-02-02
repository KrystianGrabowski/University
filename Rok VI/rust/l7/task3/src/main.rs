fn main() {
    println!("{}" , fcn(17));
}

fn fcn(n: i32) -> i64 {
    2i64.pow(n as u32)
}

/*fn fcn(n: i32) -> i64 {
    let mut a: i128 = 1;
    let mut b: i128 = 2;
    let mut c: i128 = 0;
    for i in 0..n-1 {
        c = 6*a*b / ((5*a) - b);
        a=b;
        b=c;
    }
    c as i64
}*/

#[test]
fn fcn_test_1() {
    assert_eq!(fcn(17), 131072);
}
#[test]
fn fcn_test_2() {
    assert_eq!(fcn(21), 2097152);
}
#[test]
fn fcn_test_3() {
    assert_eq!(fcn(32), 4294967296);
}
#[test]
fn fcn_test_4() {
    assert_eq!(fcn(31), 2147483648);
}
#[test]
fn fcn_test_5() {
    assert_eq!(fcn(20), 1048576);
}
#[test]
fn fcn_test_6() {
    assert_eq!(fcn(10), 1024);
}
#[test]
fn fcn_test_7() {
    assert_eq!(fcn(6), 64);
}
#[test]
fn fcn_test_8() {
    assert_eq!(fcn(2), 4);
}
#[test]
fn fcn_test_9() {
    assert_eq!(fcn(3), 8);
}
#[test]
fn fcn_test_10() {
    assert_eq!(fcn(43), 8796093022208i64);
}
