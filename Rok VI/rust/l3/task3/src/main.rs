use std::collections::HashMap;

fn main() {
    let map1 = "abcdefghijklmnopqrstuvwxyz";
    let map2 = "etaoinshrdlucmfwypvbgkjqxz";
    let cipher = Cipher::new(map1, map2);
    print!("{}\n", cipher.encode("abc"));
    print!("{}\n", cipher.decode("eta"));
}

struct Cipher {
    map_encode: HashMap<char, char>,
    map_decode: HashMap<char, char>
}

impl Cipher {
    fn new(map1: &str, map2: &str) -> Cipher {
        Cipher{
            map_encode: map1.chars().zip(map2.chars()).collect(),
            map_decode: map2.chars().zip(map1.chars()).collect()
        }
    }

    fn get_mapping_encode(&self, character: &char) -> char {
        *self.map_encode.get(character).unwrap_or(character)
    }

    fn get_mapping_decode(&self, character: &char) -> char {
        *self.map_decode.get(character).unwrap_or(character)
    }

    fn encode(&self, string: &str) -> String {
        string.chars().map(|character| self.get_mapping_encode(&character)).collect()
    }

    fn decode(&self, string: &str) -> String {
        string.chars().map(|character| self.get_mapping_decode(&character)).collect()
    }
}


#[test]
fn examples0() {
    let map1 = "abcdefghijklmnopqrstuvwxyz";
    let map2 = "etaoinshrdlucmfwypvbgkjqxz";

    let cipher = Cipher::new(map1, map2);

    assert_eq!(cipher.encode("abc"), "eta");
}
#[test]
fn examples1() {
    let map1 = "abcdefghijklmnopqrstuvwxyz";
    let map2 = "etaoinshrdlucmfwypvbgkjqxz";

    let cipher = Cipher::new(map1, map2);

    assert_eq!(cipher.encode("klmnrst"), "lucmpvb");
}
#[test]
fn examples2() {
    let map1 = "abcdefghijklmnopqrstuvw";
    let map2 = "etaoinshrdlucmfwypvbgkj";

    let cipher = Cipher::new(map1, map2);

    assert_eq!(cipher.decode("xxx"), "xxx");
}
#[test]
fn examples3() {
    let map1 = "abcdefghijklmnopqrstuvwxyz";
    let map2 = "etaoinshrdlucmfwypvbgkjqxz";

    let cipher = Cipher::new(map1, map2);

    assert_eq!(cipher.decode("erlang"), "aikcfu");
}
#[test]
fn examples4() {
    let map1 = "abcdefghijklmnopqrstuvwxyz";
    let map2 = "etaoinshrdlucmfwypvbgkjqxz";

    let cipher = Cipher::new(map1, map2);

    assert_eq!(cipher.encode("xyz"), "qxz");
}
#[test]
fn examples5() {
    let map1 = "abcdefghijklmnopqrstuvwxyz";
    let map2 = "zyxwvuysrqponmlkjihgfedcba";

    let cipher = Cipher::new(map1, map2);

    assert_eq!(cipher.encode("zaz"), "aza");
}
#[test]
fn examples6() {
    let map1 = "abcdefghijklmnopqrstuvwxyz";
    let map2 = "etaoinshrdlucmfwypvbgkjqxz";

    let cipher = Cipher::new(map1, map2);

    assert_eq!(cipher.decode("kmzar"), "vnzci");
}
#[test]
fn examples7() {
    let map1 = "abcdefghijklmnopqrstuvwxyz";
    let map2 = "abcdefghijklmnopqrstuvwxyz";

    let cipher = Cipher::new(map1, map2);

    assert_eq!(cipher.encode("abcdefghijklmnopqrstuvwxyz"), "abcdefghijklmnopqrstuvwxyz");
}
#[test]
fn examples8() {
    let map1 = "abcdefghijklmnopqrstuvwxyz";
    let map2 = "abcdefghijklmnopqrstuvwxyz";

    let cipher = Cipher::new(map1, map2);

    assert_eq!(cipher.encode("abc"), "abc");
}
#[test]
fn examples9() {
    let map1 = "";
    let map2 = "";

    let cipher = Cipher::new(map1, map2);

    assert_eq!(cipher.encode("abc"), "abc");
}
#[test]
fn examples10() {
    let map1 = "abcdefghijklmnopqrstuvwxyz";
    let map2 = "etaoinshrdlucmfwypvbgkjqxz";

    let cipher = Cipher::new(map1, map2);

    assert_eq!(cipher.decode("drcccb"), "jimmmt");
}
