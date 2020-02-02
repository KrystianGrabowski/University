use std::collections::HashMap;
use std::borrow::Borrow;

struct MorseDecoder {
    morse_code: HashMap<String, String>,
}

fn main() {
    let decoder = MorseDecoder::new();
    print!("{}", decoder.decode_morse(".... . .-.. .-.. ---   .-- --- .-. .-.. -.. -.-.--"));
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

    fn decode_word(&self, encoded: &str) -> String {
        encoded
            .split(" ")
            .fold(String::new(), |word, letter| {
                format!("{}{}", word, self.morse_code.get(letter).unwrap_or(String::new().borrow()))
            })
    }

    fn decode_morse(&self, encoded: &str) -> String {
        encoded
            .trim()
            .split("   ")
            .into_iter()
            .map(|word| self.decode_word(word))
            .collect::<Vec<String>>()
            .join(" ")
    }
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_hey_jude() {
        let decoder = MorseDecoder::new();
        assert_eq!(decoder.decode_morse(".... . -.--   .--- ..- -.. ."), "HEY JUDE");
    }
    #[test]
    fn test_empty() {
        let decoder = MorseDecoder::new();
        assert_eq!(decoder.decode_morse(""), "");
    }
    #[test]
    fn test_add_whitespaces() {
        let decoder = MorseDecoder::new();
        assert_eq!(decoder.decode_morse("      ...---... -.-.--   - .... .   --.- ..- .. -.-. -.-   -... .-. --- .-- -.   ..-. --- -..-   .--- ..- -- .--. ...   --- ...- . .-.   - .... .   .-.. .- --.. -.--   -.. --- --. .-.-.-       "), "SOS! THE QUICK BROWN FOX JUMPS OVER THE LAZY DOG.");
    }
    #[test]
    fn test_hello_world() {
        let decoder = MorseDecoder::new();
        assert_eq!(decoder.decode_morse(" .... . .-.. .-.. --- --..--   .-- --- .-. .-.. -.. -.-.--  "), "HELLO, WORLD!");
    }
    #[test]
    fn test_test() {
        let decoder = MorseDecoder::new();
        assert_eq!(decoder.decode_morse("- . ... -"), "TEST");
    }
    #[test]
    fn test_morse() {
        let decoder = MorseDecoder::new();
        assert_eq!(decoder.decode_morse("-- --- .-. ... .   -.-. --- -.. .   - . ... -"), "MORSE CODE TEST");
    }
    #[test]
    fn test_german() {
        let decoder = MorseDecoder::new();
        assert_eq!(decoder.decode_morse(". .. -. --..   --.. .-- . ..   -.. .-. . .."), "EINZ ZWEI DREI");
    }
    #[test]
    fn test_whitespaces() {
        let decoder = MorseDecoder::new();
        assert_eq!(decoder.decode_morse("                             "), "");
    }
    #[test]
    fn test_morse_sos() {
        let decoder = MorseDecoder::new();
        assert_eq!(decoder.decode_morse("-- --- .-. ... .   ... --- ...   -.-. --- -.. ."), "MORSE SOS CODE");
    }
    #[test]
    fn test_final() {
        let decoder = MorseDecoder::new();
        assert_eq!(decoder.decode_morse("...---... .--.-. ...---... ...---...   ...---..."), "SOS@SOSSOS SOS");
    }
}
