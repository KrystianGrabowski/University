fn main() {
    println!("{}", dig_pow(111111, 3));
}

fn dig_pow(n: i64, p: i32) -> i64 {
    let s: String = n.to_string();
    let digits: Vec<i64> = s.chars().map(|c| c.to_digit(10).unwrap() as i64).collect();
    let c: i64 = (p..).map(|x| digits[(x - p) as usize].pow(x as u32)).take(digits.len()).sum();
    if c % n == 0 {c / n} else {-1}
}

#[cfg(test)]
mod tests {
    use super::*;

    fn dotest(n: i64, p: i32, exp: i64) -> () {
        println!(" n: {:?};", n);
        println!("p: {:?};", p);
        let ans = dig_pow(n, p);
        println!(" actual:\n{:?};", ans);
        println!("expect:\n{:?};", exp);
        println!(" {};", ans == exp);
        assert_eq!(ans, exp);
        println!("{};", "-");
    }

    #[test]
    fn dig_pow_test_1() {
        dotest(89, 1, 1);
    }
    #[test]
    fn dig_pow_test_2() {
        dotest(92, 1, -1);
    }
    #[test]
    fn dig_pow_test_3() {
        dotest(46288, 3, 51);
    }
    #[test]
    fn dig_pow_test_4() {
        dotest(123, 1, -1);
    }
    #[test]
    fn dig_pow_test_5() {
        dotest(695, 2, 2);
    }
    #[test]
    fn dig_pow_test_6() {
        dotest(1, 54, 1);
    }
    #[test]
    fn dig_pow_test_7() {
        dotest(5, 5, 625);
    }
    #[test]
    fn dig_pow_test_8() {
        dotest(987, 4, -1);
    }
    #[test]
    fn dig_pow_test_9() {
        dotest(7, 7, 117649);
    }
    #[test]
    fn dig_pow_test_10() {
        dotest(10, 50, -1);
    }
}
