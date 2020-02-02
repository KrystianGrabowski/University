use std::collections::HashSet;

fn main() {
    let l1 = [1, 4, 8, 7, 3, 15];
    print!("{:?}", sum_pairs(&l1, 8));
}

fn sum_pairs(ints: &[i8], s: i8) -> Option<(i8, i8)> {
    let mut required_values: HashSet<i8> = HashSet::new();
    for &el in ints {
        if required_values.contains(&(s-el)) {
            return Some((s-el, el))
        }
        required_values.insert(el);
    }
    None
}


#[test]
fn test_sum_pairs_1() {
    let l1 = [1, 4, 8, 7, 3, 15];
    assert_eq!(sum_pairs(&l1, 8), Some((1, 7)));
}
#[test]
fn test_sum_pairs_2() {
    let l2 = [1, -2, 3, 0, -6, 1];
    assert_eq!(sum_pairs(&l2, -6), Some((0, -6)));
}
#[test]
fn test_sum_pairs_3() {
    let l3 = [20, -13, 40];
    assert_eq!(sum_pairs(&l3, -7), None);
}
#[test]
fn test_sum_pairs_4() {
    let l4 = [1, 2, 3, 4, 1, 0];
    assert_eq!(sum_pairs(&l4, 2), Some((1, 1)));
}
#[test]
fn test_sum_pairs_5() {
    let l5 = [10, 5, 2, 3, 7, 5];
    assert_eq!(sum_pairs(&l5, 10), Some((3, 7)));
}
#[test]
fn test_sum_pairs_6() {
    let l6 = [4, -2, 3, 3, 4];
    assert_eq!(sum_pairs(&l6, 8), Some((4, 4)));
}
#[test]
fn test_sum_pairs_7() {
    let l7 = [0, 2, 0];
    assert_eq!(sum_pairs(&l7, 0), Some((0, 0)));
}
#[test]
fn test_sum_pairs_8() {
    let l8 = [5, 9, 13, -3];
    assert_eq!(sum_pairs(&l8, 10), Some((13, -3)));
}
#[test]
fn test_sum_pairs_9() {
    let l1 = [1, 2, 3, 4, 5];
    assert_eq!(sum_pairs(&l1, 9), Some((4, 5)));
}
#[test]
fn test_sum_pairs_10() {
    let l1 = [];
    assert_eq!(sum_pairs(&l1, 8), None);
}
#[test]
fn test_sum_pairs_11() {
    let l1 = [66, 22, 14, 9, 3];
    assert_eq!(sum_pairs(&l1, 36), Some((22, 14)));
}
#[test]
fn test_sum_pairs_12() {
    let l1 = [1, 1, 1, 1, 1, 1];
    assert_eq!(sum_pairs(&l1, 3), None);
}
