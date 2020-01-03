extern crate regex;
use regex::Regex;
use std::ops::Index;

fn main() {
    println!("{}", highlight("FFFR345F2LL"));
}

fn map_string(s: String) -> String {
    let c: char = s.chars().last().unwrap();
    match c {
        'F' => format!("<span style=\"color: pink\">{}</span>", s),
        'L' => format!("<span style=\"color: red\">{}</span>", s),
        'R' => format!("<span style=\"color: green\">{}</span>", s),
        '(' | ')' => format!("{}", s),
        _ => format!("<span style=\"color: orange\">{}</span>", s)
    }
}

pub fn highlight(code: &str) -> String {
    let re = Regex::new(r"\d+|R+|L+|F+|\(|\)").unwrap();
    re.captures_iter(code)
        .map(|x| map_string(x.index(0).to_string())).collect()
}


#[cfg(test)]
mod tests {
    use super::*;

    #[cfg(test)]
    macro_rules! assert_highlight {
        ($code:expr , $expected:expr $(,)*) => {{
            let actual = highlight($code);
            let expected = $expected;
            println!("Code without syntax highlighting:\n {}", $code);
            println!("Your code with syntax highlighting:\n {}", actual);
            println!("Expected syntax highlighting:\n {}", expected);
            assert_eq!(actual, expected);
        }};
    }

    #[test]
    fn test_1() {
        assert_highlight!(
            "F3RF5LF7",
            r#"<span style="color: pink">F</span><span style="color: orange">3</span><span style="color: green">R</span><span style="color: pink">F</span><span style="color: orange">5</span><span style="color: red">L</span><span style="color: pink">F</span><span style="color: orange">7</span>"#,
        );
    }
    #[test]
    fn test_2() {
        assert_highlight!(
            "FFFR345F2LL",
            r#"<span style="color: pink">FFF</span><span style="color: green">R</span><span style="color: orange">345</span><span style="color: pink">F</span><span style="color: orange">2</span><span style="color: red">LL</span>"#,
        );
    }
    #[test]
    fn test_3() {
        assert_highlight!(
            "FRFRFR",
            r#"<span style="color: pink">F</span><span style="color: green">R</span><span style="color: pink">F</span><span style="color: green">R</span><span style="color: pink">F</span><span style="color: green">R</span>"#,
        );
    }
    #[test]
    fn test_4() {
        assert_highlight!(
            "FFFR345(()F2LL)",
            r#"<span style="color: pink">FFF</span><span style="color: green">R</span><span style="color: orange">345</span>(()<span style="color: pink">F</span><span style="color: orange">2</span><span style="color: red">LL</span>)"#,
        );
    }
    #[test]
    fn test_5() {
        assert_highlight!(
            "(123F456)",
            r#"(<span style="color: orange">123</span><span style="color: pink">F</span><span style="color: orange">456</span>)"#,
        );
    }
    #[test]
    fn test_6() {
        assert_highlight!(
            "1F2R3F",
            r#"<span style="color: orange">1</span><span style="color: pink">F</span><span style="color: orange">2</span><span style="color: green">R</span><span style="color: orange">3</span><span style="color: pink">F</span>"#,
        );
    }
    #[test]
    fn test_7() {
        assert_highlight!(
            "",
            r#""#,
        );
    }
    #[test]
    fn test_8() {
        assert_highlight!(
            "F",
            r#"<span style="color: pink">F</span>"#,
        );
    }
    #[test]
    fn test_9() {
        assert_highlight!(
            "FRF(F)LLF",
            r#"<span style="color: pink">F</span><span style="color: green">R</span><span style="color: pink">F</span>(<span style="color: pink">F</span>)<span style="color: red">LL</span><span style="color: pink">F</span>"#,
        );
    }
    #[test]
    fn test_10() {
        assert_highlight!(
            "L(123)L",
            r#"<span style="color: red">L</span>(<span style="color: orange">123</span>)<span style="color: red">L</span>"#,
        );
    }
}
