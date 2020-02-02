fn main() {
    print!("{:?}", encode("scout".to_string(), 1939));
}

fn encode(msg: String, n: i32) -> Vec<i32> {
    let s: String = n.to_string();
    let mut key = s.chars().map(|c| c.to_digit(10).unwrap() as u8).cycle();
    msg.chars().map(|c| (c as u8 - ('a' as u8 - 1) + key.next().unwrap()) as i32).collect()
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn encode_test_1() {
        assert_eq!(encode("scout".to_string(), 1939), vec![20, 12, 18, 30, 21]);
    }
    #[test]
    fn encode_test_2() {
        assert_eq!(encode("masterpiece".to_string(), 1939), vec![14, 10, 22, 29, 6, 27, 19, 18, 6, 12, 8]);
    }
    #[test]
    fn encode_test_3() {
        assert_eq!(encode("abcd".to_string(), 0), vec![1, 2, 3, 4]);
    }
    #[test]
    fn encode_test_4() {
        assert_eq!(encode("".to_string(), 1939), vec![]);
    }
    #[test]
    fn encode_test_5() {
        assert_eq!(encode("wolfram".to_string(), 696969), vec![29, 24, 18, 15, 24, 10, 19]);
    }
    #[test]
    fn encode_test_6() {
        assert_eq!(encode("string".to_string(), 123), vec![20, 22, 21, 10, 16, 10]);
    }
    #[test]
    fn encode_test_7() {
        assert_eq!(encode("scout".to_string(), 9999), vec![28, 12, 24, 30, 29]);
    }
    #[test]
    fn encode_test_8() {
        assert_eq!(encode("man".to_string(), 4926), vec![17, 10, 16]);
    }
    #[test]
    fn encode_test_9() {
        assert_eq!(encode("a".to_string(), 7533688), vec![8]);
    }
    #[test]
    fn encode_test_10() {
        assert_eq!(encode("z".to_string(), 19), vec![27]);
    }
}