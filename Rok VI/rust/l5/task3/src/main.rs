fn main() {
    println!("{}", solution(-4.25));
}

fn solution(n: f64) -> f64 {
    let t = n.trunc().abs();
    let f = n.fract().abs();
    let res = match (f * 100f64) as i64 {
        0..=24 => t,
        25..=74 => t + 0.5,
        75..=99 => t + 1.0,
        _ => 0.0
    };
    if n < 0.0 {res * -1f64} else {res}
}

#[cfg(test)]
mod tests {
    use super::solution;

    #[test]
    fn test_1() {
        assert_eq!(solution(4.2), 4.0);
    }
    #[test]
    fn test_2() {
        assert_eq!(solution(4.4), 4.5);
    }
    #[test]
    fn test_3() {
        assert_eq!(solution(4.6), 4.5);
    }
    #[test]
    fn test_4() {
        assert_eq!(solution(4.8), 5.0);
    }
    #[test]
    fn test_5() {
        assert_eq!(solution(-4.2), -4.0);
    }
    #[test]
    fn test_6() {
        assert_eq!(solution(-4.4), -4.5);
    }
    #[test]
    fn test_7() {
        assert_eq!(solution(-4.6), -4.5);
    }
    #[test]
    fn test_8() {
        assert_eq!(solution(-4.8), -5.0);
    }
    #[test]
    fn test_9() {
        assert_eq!(solution(4.75), 5.0);
    }
    #[test]
    fn test_10() {
        assert_eq!(solution(4.74), 4.5);
    }
}