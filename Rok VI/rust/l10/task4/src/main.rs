extern crate regex;
use std::collections::HashMap;
use regex::Regex;

fn main() {
    let s1="Program title: Bumper\nAuthor: Tolkien\nCorporation: Apple\nPhone: +1-503-555-0098\nDate: Friday March 9, 2008\nVersion: 500\nLevel: Beta";
    println!("{}",  change(s1, "Hoist", "1.5"));
}

fn extract_item(s: &str) -> (String, String) {
    let mut a = s.splitn(2, ':');
    let key: String = a.next().unwrap().trim_end().trim_start().to_string();
    let value: String = a.next().unwrap().trim_end().trim_start().to_string();
    (key, value)
}

fn extract(s: &str) -> HashMap<String, String> {
    let v: Vec<&str> = s.split('\n').collect();
    v.into_iter().fold(HashMap::new(), |mut acc, x| {
        let tuple = extract_item(x);
        acc.insert(tuple.0, tuple.1);
        acc
    })
}

fn change(s: &str, prog: &str, version: &str) -> String {
    let mut v: HashMap<String, String> = extract(s);

    let re_phone = Regex::new(r"^\+1-\d{3}-\d{3}-\d{4}$").unwrap();
    let re_version = Regex::new(r"^\d+\.\d+$").unwrap();

    if !re_phone.is_match(v.get("Phone").unwrap()) { return "ERROR: VERSION or PHONE".to_string() };
    if !re_version.is_match(v.get("Version").unwrap()) { return "ERROR: VERSION or PHONE".to_string() };

    if v.get("Version").unwrap() != "2.0" {v.insert("Version".to_string(), version.to_string());}

    format!("Program: {} Author: g964 Phone: +1-503-555-0090 Date: 2019-01-01 Version: {}",
            prog,
            v.get("Version").unwrap(),
    )
}

#[cfg(test)]
mod tests {
    use super::*;

    fn dotest(s: &str, prog: &str, version: &str, exp: &str) -> () {
        println!("s:{:?}", s);
        println!("prog:{:?}", prog);
        println!("version:{:?}", version);
        let ans = change(s, prog, version);
        println!("actual: {:?}", ans);
        println!("expect: {:?}", exp);
        println!("{}", ans == exp);
        assert_eq!(ans, exp);
        println!("{}", "-");
    }

    #[test]
    fn change_test_1() {
        let s1="Program title: Primes\nAuthor: Kern\nCorporation: Gold\nPhone: +1-503-555-0091\nDate: Tues April 9, 2005\nVersion: 6.7\nLevel: Alpha";
        dotest(s1, "Ladder", "1.1", "Program: Ladder Author: g964 Phone: +1-503-555-0090 Date: 2019-01-01 Version: 1.1");
    }
    #[test]
    fn change_test_2() {
        let s2="Program title: Balance\nAuthor: Dorries\nCorporation: Funny\nPhone: +1-503-555-0095\nDate: Tues July 19, 2014\nVersion: 6.7\nLevel: Release";
        dotest(s2, "Circular", "1.5", "Program: Circular Author: g964 Phone: +1-503-555-0090 Date: 2019-01-01 Version: 1.5");
    }
    #[test]
    fn change_test_3() {
        let s13="Program title: Primes\nAuthor: Kern\nCorporation: Gold\nPhone: +1-503-555-0090\nDate: Tues April 9, 2005\nVersion: 67\nLevel: Alpha";
        dotest(s13, "Ladder", "1.1", "ERROR: VERSION or PHONE");
    }
    #[test]
    fn change_test_4() {
        let s1="Program title: Primes\nAuthor: Kern\nCorporation: Gold\nPhone: +1-503-555-0091\nDate: Tues April 9, 2005\nVersion: 2.0\nLevel: Alpha";
        dotest(s1, "Ladder", "1.1", "Program: Ladder Author: g964 Phone: +1-503-555-0090 Date: 2019-01-01 Version: 2.0");
    }
    #[test]
    fn change_test_5() {
        let s2="Program title: Balance\nAuthor: Dorries\nCorporation: Funny\nPhone: 1-503-555-0095\nDate: Tues July 19, 2014\nVersion: 6.7\nLevel: Release";
        dotest(s2, "Circular", "1.5", "ERROR: VERSION or PHONE");
    }
    #[test]
    fn change_test_6() {
        let s13="Program title: Primes\nAuthor: Kern\nCorporation: Gold\nPhone: +1-503-555-000\nDate: Tues April 9, 2005\nVersion: 67\nLevel: Alpha";
        dotest(s13, "Ladder", "1.1", "ERROR: VERSION or PHONE");
    }
    #[test]
    fn change_test_7() {
        let s1="Program title: Primes\nAuthor: Kern\nCorporation: Gold\nPhone: +1-503-555-0091\nDate: Tues April 9, 2005\nVersion: 6.7\nLevel: Alpha";
        dotest(s1, "Primes", "1.1", "Program: Primes Author: g964 Phone: +1-503-555-0090 Date: 2019-01-01 Version: 1.1");
    }
    #[test]
    fn change_test_8() {
        let s2="Program title: Balance\nAuthor: Dorries\nCorporation: Corporation\nPhone: +1-503-555-0095\nDate: Tues July 19, 2014\nVersion: 6.7\nLevel: Level";
        dotest(s2, "Circular", "14.176", "Program: Circular Author: g964 Phone: +1-503-555-0090 Date: 2019-01-01 Version: 14.176");
    }
    #[test]
    fn change_test_9() {
        let s13="Program title: Primes\nAuthor: Kern\nCorporation: Gold\nPhone: +1-503-555-0090\nDate: Tues April 9, 2005\nVersion: .7\nLevel: Alpha";
        dotest(s13, "Ladder", "1.1", "ERROR: VERSION or PHONE");
    }
    #[test]
    fn change_test_10() {
        let s1="Program title: Primes\nAuthor: Kern\nCorporation: Gold\nPhone: +1-503-555-0091\nDate: Tues April 9, 2005\nVersion: 6.7\nLevel: Alpha";
        dotest(s1, "Steven", "112.1", "Program: Steven Author: g964 Phone: +1-503-555-0090 Date: 2019-01-01 Version: 112.1");
    }
}
