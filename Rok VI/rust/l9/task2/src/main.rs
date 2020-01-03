fn main() {
    println!("{}", dont_give_me_five(1, 9));
}

fn dont_give_me_five(start: isize, end: isize) -> isize {
    (start..=end).filter(|x| !(x.to_string().contains('5'))).count() as isize
}

#[cfg(test)]
mod tests {
    use super::dont_give_me_five;

    #[test]
    fn five_test_1() {
        assert_eq!(dont_give_me_five(1, 9), 8);
    }
    #[test]
    fn five_test_2() {
        assert_eq!(dont_give_me_five(4, 17), 12);
    }
    #[test]
    fn five_test_3() {
        assert_eq!(dont_give_me_five(4, 6), 2);
    }
    #[test]
    fn five_test_4() {
        assert_eq!(dont_give_me_five(4, 5), 1);
    }
    #[test]
    fn five_test_5() {
        assert_eq!(dont_give_me_five(0, 4), 5);
    }
    #[test]
    fn five_test_6() {
        assert_eq!(dont_give_me_five(10, 20), 10);
    }
    #[test]
    fn five_test_7() {
        assert_eq!(dont_give_me_five(0, 20), 19);
    }
    #[test]
    fn five_test_8() {
        assert_eq!(dont_give_me_five(14, 15), 1);
    }
    #[test]
    fn five_test_9() {
        assert_eq!(dont_give_me_five(-10, -1), 9);
    }
    #[test]
    fn five_test_10() {
        assert_eq!(dont_give_me_five(-1, 1), 3);
    }
}