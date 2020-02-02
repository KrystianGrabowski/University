fn main() {
    println!("{:?}", even_numbers(&vec!(1, 2, 3, 4, 5, 6, 7, 8, 9), 3));
}

fn even_numbers(array: &Vec<i32>, number: usize) -> Vec<i32> {
    let v: Vec<i32> = array.clone()
        .into_iter()
        .filter(|x| x % 2 == 0)
        .collect();
    let c: usize = v.len();
    v.into_iter().skip(c - number).take(number).collect()
}

#[test]
fn test_1() {
    assert_eq!(even_numbers(&vec!(1, 2, 3, 4, 5, 6, 7, 8, 9), 3), vec!(4, 6, 8));
}
#[test]
fn test_2() {
    assert_eq!(even_numbers(&vec!(-22, 5, 3, 11, 26, -6, -7, -8, -9, -8, 26), 2), vec!(-8, 26));
}
#[test]
fn test_3() {
    assert_eq!(even_numbers(&vec!(6, -25, 3, 7, 5, 5, 7, -3, 23), 1), vec!(6));
}
#[test]
fn test_4() {
    assert_eq!(even_numbers(&vec!(2, 4, 6, 8, 10, 12), 1), vec!(12));
}
#[test]
fn test_5() {
    assert_eq!(even_numbers(&vec!(2, 4, 6, 8, 10, 12), 2), vec!(10, 12));
}
#[test]
fn test_6() {
    assert_eq!(even_numbers(&vec!(2, 4, 6, 8, 10, 12), 6), vec!(2, 4, 6, 8, 10, 12));}
#[test]
fn test_7() {
    assert_eq!(even_numbers(&vec!(2), 1), vec!(2));
}
#[test]
fn test_8() {
    assert_eq!(even_numbers(&vec!(-2, -3, -4, -5, -6, -7 ,-8), 2), vec!(-6, -8));
}
#[test]
fn test_9() {
    assert_eq!(even_numbers(&vec!(2, -2, 4, -4), 2), vec!(4, -4));
}
#[test]
fn test_10() {
    assert_eq!(even_numbers(&vec!(111, 112, 221, 222), 2), vec!(112, 222));
}