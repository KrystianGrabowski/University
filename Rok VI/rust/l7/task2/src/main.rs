fn main() {
    println!("{:?}", letter_frequency("actu   al"));
}

use std::collections::BTreeMap;

fn letter_frequency(input: &str) -> BTreeMap<char, i32> {
    input.to_lowercase()
        .chars()
        .filter(|c| c.is_alphabetic())
        .fold(BTreeMap::new(), |mut acc, x| {
            *acc.entry(x).or_insert(0) += 1;
            acc
        })
}

#[cfg(test)]
mod tests {
    use std::collections::BTreeMap;
    use super::letter_frequency;

    #[test]
    fn freq_1() {
        let answer: BTreeMap<char, i32> =
            [('a', 2),
                ('c', 1),
                ('l', 1),
                ('t', 1),
                ('u', 1)]
                .iter().cloned().collect();

        assert_eq!(letter_frequency("actual"), answer);
    }

    #[test]
    fn freq_2() {
        let answer: BTreeMap<char, i32> =
            [('a', 3),
                ('b', 2),
                ('f', 1),
                ('p', 1),
                ('s', 1),
                ('t', 2),
                ('u', 1),
                ('x', 5)]
                .iter().cloned().collect();

        assert_eq!(letter_frequency("AaabBF UttsP xxxxx"), answer);
    }
    #[test]
    fn freq_3() {
        let answer: BTreeMap<char, i32> =
            [('a', 2)]
                .iter().cloned().collect();

        assert_eq!(letter_frequency("a                 a"), answer);
    }
    #[test]
    fn freq_4() {
        let answer: BTreeMap<char, i32> =
            [('a', 2),
                ('b', 2)]
                .iter().cloned().collect();

        assert_eq!(letter_frequency("abba"), answer);
    }
    #[test]
    fn freq_5() {
        let answer: BTreeMap<char, i32> =
            [('a', 2),
                ('p', 2),
                ('r', 2),
                ('s', 1),
                ('e', 1),
                ('n', 1),
                ('u', 1),
                ('w', 1)]
                .iter().cloned().collect();

        assert_eq!(letter_frequency("parse unwraP"), answer);
    }
    #[test]
    fn freq_6() {
        let answer: BTreeMap<char, i32> =
            [('m', 50)]
                .iter().cloned().collect();

        assert_eq!(letter_frequency("MMMMMMMMMMMMMMMMMMM///>??21312MMMM32 MMMMMMMMMMMMMMMMMMMMMMMMMMM"), answer);
    }

    #[test]
    fn freq_7() {
        let answer: BTreeMap<char, i32> =
            [('e', 1),
                ('s', 1),
                ('t', 8)]
                .iter().cloned().collect();

        assert_eq!(letter_frequency("t t t t t t test"), answer);
    }
    #[test]
    fn freq_8() {
        let answer: BTreeMap<char, i32> =
            [('z', 6)]
                .iter().cloned().collect();

        assert_eq!(letter_frequency("ZZZzzz"), answer);
    }
    #[test]
    fn freq_9() {
        let answer: BTreeMap<char, i32> =
            [('a', 4),
                ('b', 4)]
                .iter().cloned().collect();

        assert_eq!(letter_frequency("AbAbAbAb"), answer);
    }
    #[test]
    fn freq_10() {
        let answer: BTreeMap<char, i32> =
            [('a', 26)]
                .iter().cloned().collect();

        assert_eq!(letter_frequency("AAAAAAAAAAAAAAAaAAAAAAAAAA"), answer);
    }
}