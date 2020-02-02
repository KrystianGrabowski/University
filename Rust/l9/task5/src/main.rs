fn main() {
    println!("{}", solution::range_extraction(&[-6,-3,-2,-1,0,1,3,4,5,7,8,9,10,11,14,15,17,18,19,20]));
}

mod solution {
    pub fn range_extraction(a: &[i32]) -> String {
        let mut s: Vec<String> = vec![];
        let mut iterator: usize = 0;
        while iterator < a.len() {
            let start = iterator;
            while iterator < a.len() - 1 && a[iterator] == a[iterator+1] - 1 {
                iterator+=1;
            }
            if iterator - start > 1 {
                s.push(format!("{}-{}", a[start], a[iterator]))
            }
            else {
                (start..=iterator).for_each(|x| s.push(format!("{}", a[x])));
            }
            iterator += 1;
        }
        s.join(",")
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn range_test_1() {
        assert_eq!("-6,-3-1,3-5,7-11,14,15,17-20", solution::range_extraction(&[-6,-3,-2,-1,0,1,3,4,5,7,8,9,10,11,14,15,17,18,19,20]));
    }
    #[test]
    fn range_test_2() {
        assert_eq!("-3--1,2,10,15,16,18-20", solution::range_extraction(&[-3,-2,-1,2,10,15,16,18,19,20]));
    }
    #[test]
    fn range_test_3() {
        assert_eq!("-3--1,1-3", solution::range_extraction(&[-3,-2,-1,1,2,3]));
    }
    #[test]
    fn range_test_4() {
        assert_eq!("", solution::range_extraction(&[]));
    }
    #[test]
    fn range_test_5() {
        assert_eq!("1-6", solution::range_extraction(&[1,2,3,4,5,6]));
    }
    #[test]
    fn range_test_6() {
        assert_eq!("1,3,5,7", solution::range_extraction(&[1,3,5,7]));
    }
    #[test]
    fn range_test_7() {
        assert_eq!("1,2,4-6,8,9", solution::range_extraction(&[1,2,4,5,6,8,9]));
    }
    #[test]
    fn range_test_8() {
        assert_eq!("1-6,100", solution::range_extraction(&[1,2,3,4,5,6,100]));
    }
    #[test]
    fn range_test_9() {
        assert_eq!("1,2,4,5,7,8", solution::range_extraction(&[1,2,4,5,7,8]));
    }
    #[test]
    fn range_test_10() {
        assert_eq!("-5--2,0", solution::range_extraction(&[-5,-4,-3,-2,0]));
    }
}
