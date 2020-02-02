fn main() {
    println!("{:?}", ann(30));
}

fn get_sequences(n: i32) -> (Vec<i32>, Vec<i32>) {
    let mut ann = vec![1];
    ann.reserve(n as usize);
    let mut john = vec![0];
    john.reserve(n as usize);
    for i in 1..n {
        john.push(i - ann[*john.last().unwrap() as usize]);
        ann.push(i - john[*ann.last().unwrap() as usize]);
    }
    (ann, john)
}

fn john(n: i32) -> Vec<i32> {
    get_sequences(n).1
}
fn ann(n: i32) -> Vec<i32> {
    get_sequences(n).0
}
fn sum_john(n: i32) -> i32 {
    get_sequences(n).1.into_iter().sum()
}
fn sum_ann(n: i32) -> i32 {
    get_sequences(n).0.into_iter().sum()
}


fn test_john(n: i32, exp: Vec<i32>) -> () {
    assert_eq!(john(n), exp)
}
fn test_ann(n: i32, exp: Vec<i32>) -> () {
    assert_eq!(ann(n), exp)
}
fn test_sum_john(n: i32, exp: i32) -> () {
    assert_eq!(sum_john(n), exp)
}
fn test_sum_ann(n: i32, exp: i32) -> () {
    assert_eq!(sum_ann(n), exp)
}

#[test]
fn test_test_john() {
    test_john(11, vec![0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6]);
}
#[test]
fn test_test_john2() {
    test_john(14, vec![0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6, 7, 7, 8]);
}
#[test]
fn test_test_john3() {
    test_john(30, vec![0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6, 7, 7, 8, 9, 9, 10, 11, 11, 12, 12, 13, 14, 14, 15, 16, 16, 17, 17, 18]);
}
#[test]
fn test_test_ann() {
    test_ann(6, vec![1, 1, 2, 2, 3, 3]);
}
#[test]
fn test_test_ann2() {
    test_ann(15, vec![1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6, 7, 8, 8, 9]);
}
#[test]
fn test_test_ann3() {
    test_ann(30, vec![1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6, 7, 8, 8, 9, 9, 10, 11, 11, 12, 13, 13, 14, 14, 15, 16, 16, 17, 17, 18]);
}
#[test]
fn test_test_sum_john() {
    test_sum_john(75, 1720);
}
#[test]
fn test_test_sum_john2() {
    test_sum_john(78, 1861);
}
#[test]
fn test_test_sum_ann() {
    test_sum_ann(115, 4070);
}
#[test]
fn test_test_sum_ann2() {
    test_sum_ann(150, 6930);
}
