use std::cmp::Ordering;

fn main() {
    println!("{}", dbl_linear(220));
}

fn dbl_linear(n: u32) -> u32{
    let mut vec: Vec<u32> = vec![1];
    let mut two = 0;
    let mut three = 0;
    for _i in 1..=n {
        let two_result = vec[two] * 2 + 1;
        let three_result = vec[three] * 3 + 1;
        match two_result.cmp(&three_result) {
            Ordering::Less => {vec.push(two_result); two+=1;}
            Ordering::Greater => {vec.push(three_result); three+=1;}
            Ordering::Equal => {vec.push(two_result); three+=1; two+=1;}
        }
    }
    vec[n as usize]
}

#[cfg(test)]
mod tests {
    use super::dbl_linear;
    fn testing(n: u32, exp: u32) -> () {
        assert_eq!(dbl_linear(n), exp)
    }

    #[test]
    fn basic_test_1() {
        testing(3, 7);
    }
    #[test]
    fn basic_test_2() {
        testing(6, 13);
    }
    #[test]
    fn basic_test_3() {
        testing(8, 19);
    }
    #[test]
    fn basics_dbl_linear_1() {
        testing(10, 22);
    }
    #[test]
    fn basics_dbl_linear_2() {
        testing(20, 57);
    }
    #[test]
    fn basics_dbl_linear_3() {
        testing(30, 91);
    }
    #[test]
    fn basics_dbl_linear_4() {
        testing(50, 175);
    }
    #[test]
    fn basics_dbl_linear_5() {
        testing(100, 447);
    }
    #[test]
    fn basics_dbl_linear_6() {
        testing(150, 733);
    }
    #[test]
    fn basics_dbl_linear_7() {
        testing(200, 1051);
    }
    #[test]
    fn basics_dbl_linear_8() {
        testing(220, 1147);
    }
}