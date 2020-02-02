fn main() {
    println!("{}", order("is2 Thi1s T4est 3a"));
}

fn order(sentence: &str) -> String {
    let vec: Vec<String> = sentence.split_whitespace().map(|x| x.to_string()).collect();
    let mut res_vec: Vec<String> = vec.clone();
    for i in vec {
        let num: String = i.chars().filter(|x|x.is_ascii_digit()).collect();
        res_vec[num.parse::<usize>().unwrap() - 1] = i.clone();
    }
    res_vec.join(" ")
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn test_string_1() {
        assert_eq!(order("is2 Thi1s T4est 3a"), "Thi1s is2 3a T4est");
    }
    #[test]
    fn test_string_2() {
        assert_eq!(order(""), "");
    }
    #[test]
    fn test_string_3() {
        assert_eq!(order("tes1t te2st tes3t tes4t"), "tes1t te2st tes3t tes4t");
    }
    #[test]
    fn test_string_4() {
        assert_eq!(order("a1"), "a1");
    }
    #[test]
    fn test_string_5() {
        assert_eq!(order("a2 b1"), "b1 a2");
    }
    #[test]
    fn test_string_6() {
        assert_eq!(order("tes2t te1st tes4t tes3t"), "te1st tes2t tes3t tes4t");
    }
    #[test]
    fn test_string_7() {
        assert_eq!(order("test1 test2 test3 test4"), "test1 test2 test3 test4");
    }
    #[test]
    fn test_string_8() {
        assert_eq!(order("1test 2test 3test 4test"), "1test 2test 3test 4test");
    }
    #[test]
    fn test_string_9() {
        assert_eq!(order("te3st t2est 1test 4test"), "1test t2est te3st 4test");
    }
    #[test]
    fn test_string_10() {
        assert_eq!(order("ta2 ta3 ta4 ta1"), "ta1 ta2 ta3 ta4");
    }




}
