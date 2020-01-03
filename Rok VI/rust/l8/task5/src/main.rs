use std::collections::HashMap;
use std::borrow::Borrow;
use regex::Regex;

struct MorseDecoder {
    morse_code: HashMap<String, String>,
}

fn main() {
    let decoder = MorseDecoder::new();
    print!("{}", decoder.decode_bits("1100110011001100000011000000111111001100111111001111110000000000000011001111110011111100111111000000110011001111110000001111110011001100000011"));
}

impl MorseDecoder {
    fn new() -> MorseDecoder {
        MorseDecoder{ morse_code :
        [("....-", "4"),("--..--", ","),(".--", "W"),(".-.-.-", "."),("..---", "2"),(".", "E"),("--..", "Z"),(".----", "1"),(".-..", "L"),
            (".--.", "P"),(".-.", "R"),("...", "S"),("-.--", "Y"),("...--", "3"),(".....", "5"),("--.", "G"),("-.--.", "("),("-....", "6"),
            (".-.-.", "+"),("...-..-", "$"),(".--.-.", "@"),("...---...", "SOS"),("..--.-", "_"),("-.", "N"),("-..-", "X"),("-----", "0"),
            ("....", "H"),("-...", "B"),(".---", "J"),("---...", ","),("-", "T"),("---..", "8"),("-..-.", "/"),("--.-", "Q"),("...-", "V"),
            ("----.", "9"),("--", "M"),("-.-.-.", ";"),("-.-.--", "!"),("..-.", "F"),("..--..", "?"),("-...-", "="),("..-", "U"),(".----.", "'"),
            ("---", "O"),("-.--.-", ")"),("..", "I"),("-....-", "-"),(".-..-.", "\""),(".-", "A"),("-.-.", "C"),("-..", "D"),(".-...", "&"),
            ("--...", "7"),("-.-", "K")].iter().map(|(k, v)| (k.to_string(), v.to_string())).collect()}

    }

    fn match_zeros(&self, s: &str, scale: usize) -> String {
        match s.len() / scale{
            1 =>  "".to_string(),
            3 => " ".to_string(),
            _ => "   ".to_string()
        }
    }

    fn match_ones(&self, s: &str, scale: usize) -> String {
        match s.len() / scale {
            1 => ".".to_string(),
            3 => "-".to_string(),
            _ => panic!()
        }

    }

    fn decode_seq(&self, s: &str, scale: usize) -> String {
        match s.chars().next().unwrap() {
            '1' => self.match_ones(s, scale),
            '0' => self.match_zeros(s, scale),
            _ => panic!()
        }
    }

    fn extract_scale(&self, vec: Vec<&str>) -> usize {
        vec.into_iter()
            .map(|x| x.len())
            .min().unwrap_or(0)
    }

    pub fn decode_bits(&self, encoded: &str) -> String {
        let encoded_zeros_removed = encoded
            .trim_start_matches('0')
            .trim_end_matches('0');
        let signals: Vec<&str> = Regex::new(r"1+|0+").unwrap()
            .find_iter(encoded_zeros_removed)
            .map(|x| x.as_str())
            .collect();
        let scale: usize = self.extract_scale(signals.clone());

        signals
            .into_iter()
            .map(|x| self.decode_seq(x, scale))
            .collect()
    }

    fn decode_word(&self, encoded: &str) -> String {
        encoded
            .split(" ")
            .fold(String::new(), |word, letter| {
                format!("{}{}", word, self.morse_code.get(letter).unwrap_or(String::new().borrow()))
            })
    }

    pub fn decode_morse(&self, encoded: &str) -> String {
        encoded
            .trim()
            .split("   ")
            .into_iter()
            .map(|word| self.decode_word(word))
            .collect::<Vec<String>>()
            .join(" ")
    }
}


#[test]
fn example_1() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("1100110011001100000011000000111111001100111111001111110000000000000011001111110011111100111111000000110011001111110000001111110011001100000011")), "HEY JUDE".to_string());
}
#[test]
fn example_2() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("111000111000111000111000000000111000000000111111111000111000111111111000111111111000000000000000000000111000111111111000111111111000111111111000000000111000111000111111111000000000111111111000111000111000000000111")), "HEY JUDE".to_string());
}
#[test]
fn example_extra_zeros_1() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("1100110011001100000011000000111111001100111111001111110000000000000011001111110011111100111111000000110011001111110000001111110011001100000011000000000000")), "HEY JUDE".to_string());
}
#[test]
fn example_extra_zeros_2() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("000000000000000111000111000111000111000000000111000000000111111111000111000111111111000111111111000000000000000000000111000111111111000111111111000111111111000000000111000111000111111111000000000111111111000111000111000000000111")), "HEY JUDE".to_string());
}
#[test]
fn empty() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("")), "".to_string());
}
#[test]
fn empty_zeros() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("0000000000000000")), "".to_string());
}
#[test]
fn example_4() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("11001100110011000000110000001100111111001100110000001100111111001100110000001111110011111100111111")), "HELLO".to_string());
}
#[test]
fn example_5() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("1111000011110000111100000000000001111111111110000111111111111000011111111111100000000000011110000111100001111")), "SOS".to_string());
}
#[test]
fn example_6() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("111010111010001110101110101110111")), "C!".to_string());
}
#[test]
fn example_7() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("111000000000111111111000111000000000111111111000111000111")), "END".to_string());
}


