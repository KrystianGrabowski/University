fn main() {
    print!("{}", last_digit(&vec![ 2, 2, 100, 2]) )
}

fn last_digit(lst: &[u64]) -> u64 {
    let mut vec = lst.to_vec();
    if lst.len() == 0 {return 1}
    if lst.len() == 1 { return lst[0] % 10; }
    for i in (1..vec.len()).rev() {
        let last = vec[i];
        let prev_last = vec[i - 1];
        let new_val = std::cmp::min(prev_last % 20 + 20, prev_last).pow(std::cmp::min((last % 4 + 4) as u32, last as u32 ));
        vec.pop();
        vec.pop();
        vec.push(new_val);
    }
    vec[0] % 10
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn last_digit_test_1() {
        assert_eq!(last_digit(&vec![]), 1);
    }
    #[test]
    fn last_digit_test_2() {
        assert_eq!(last_digit(&vec![0, 0]), 1);
    }
    #[test]
    fn last_digit_test_3() {
        assert_eq!(last_digit(&vec![0, 0, 0]), 0);
    }
    #[test]
    fn last_digit_test_4() {
        assert_eq!(last_digit(&vec![1, 2]), 1);
    }
    #[test]
    fn last_digit_test_5() {
        assert_eq!(last_digit (&vec![3, 4, 5]), 1);
    }
    #[test]
    fn last_digit_test_6() {
        assert_eq!(last_digit(&vec![4, 3, 6]), 4);
    }
    #[test]
    fn last_digit_test_7() {
        assert_eq!(last_digit(&vec![7, 6, 21]), 1);
    }
    #[test]
    fn last_digit_test_8() {
        assert_eq!(last_digit(&vec![12, 30, 21]), 6);
    }
    #[test]
    fn last_digit_test_9() {
        assert_eq!(last_digit(&vec![2, 2, 2, 0]), 4);
    }
    #[test]
    fn last_digit_test_10() {
        assert_eq!(last_digit(&vec![937640, 767456, 981242]), 0);
    }
    #[test]
    fn last_digit_test_11() {
        assert_eq!(last_digit(&vec![123232, 694022, 140249]), 6);
    }
    #[test]
    fn last_digit_test_12() {
        assert_eq!(last_digit(&vec![499942, 898102, 846073]), 6);
    }
}