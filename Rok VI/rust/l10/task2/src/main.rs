fn main() {
    let b = vec![];
    let c = vec!["B", "R", "D", "X"];
    println!("{:?}", stock_list(b, c));
}

fn stock_list(list_art: Vec<&str>, list_cat: Vec<&str>) -> String {
    if list_art.len() == 0 {return String::new()}
    let a: Vec<i32> = list_cat.clone()
        .into_iter()
        .map(|x| list_art.clone()
            .into_iter()
            .filter(|e| e.starts_with(x))
            .map(|c| c.split_whitespace().last().unwrap().parse::<i32>().unwrap())
            .sum())
        .collect();
    list_cat.clone().into_iter().zip(a).map(|x| format!("({} : {})", x.0, x.1)).collect::<Vec<String>>().join(" - ")
}

#[cfg(test)]
mod tests {
    use super::*;

    fn dotest(list_art: Vec<&str>, list_cat: Vec<&str>, exp: &str) -> () {
        println!("list_art: {:?};", list_art);
        println!("list_cat: {:?};", list_cat);
        let ans = stock_list(list_art, list_cat);
        println!("actual:\n{:?};", ans);
        println!("expect:\n{:?};", exp);
        println!("{};", ans == exp);
        assert_eq!(ans, exp);
        println!("{};", "-");
    }

    #[test]
    fn stock_test_1() {
        let b = vec!["BBAR 150", "CDXE 515", "BKWR 250", "BTSQ 890", "DRTY 600"];
        let c = vec!["A", "B", "C", "D"];
        dotest(b, c, "(A : 0) - (B : 1290) - (C : 515) - (D : 600)");
    }
    #[test]
    fn stock_test_2() {
        let b = vec!["ABAR 200", "CDXE 500", "BKWR 250", "BTSQ 890", "DRTY 600"];
        let c = vec!["A", "B"];
        dotest(b, c, "(A : 200) - (B : 1140)");
    }
    #[test]
    fn stock_test_3() {
        let b = vec![];
        let c = vec!["B", "R", "D", "X"];
        dotest(b, c, "");
    }
    #[test]
    fn stock_test_4() {
        let b = vec!["ABAR 200", "CDXE 500", "BKWR 250", "BTSQ 890", "DRTY 600"];
        let c = vec![];
        dotest(b, c, "");
    }
    #[test]
    fn stock_test_5() {
        let b = vec!["AAAA 100", "BBBB 200", "CCCC 300", "DDDD 400"];
        let c = vec!["A", "B", "C", "D"];
        dotest(b, c, "(A : 100) - (B : 200) - (C : 300) - (D : 400)");
    }
    #[test]
    fn stock_test_6() {
        let b = vec!["ABCD 100", "ABCD 100", "ABCD 100", "ABCD 100", "ABCD 100"];
        let c = vec!["A", "B"];
        dotest(b, c, "(A : 500) - (B : 0)");
    }
    #[test]
    fn stock_test_7() {
        let b = vec!["ABBB 150", "BAAA 200", "ABBB 250", "BAAA 300"];
        let c = vec!["A", "B"];
        dotest(b, c, "(A : 400) - (B : 500)");
    }
    #[test]
    fn stock_test_8() {
        let b = vec!["XUUU 200", "YCCCC 200", "ZZZT 1", "XUXYU 23", "YYYK 666"];
        let c = vec!["X", "Y", "Z"];
        dotest(b, c, "(X : 223) - (Y : 866) - (Z : 1)");
    }
    #[test]
    fn stock_test_9() {
        let b = vec!["AAAA 55", "AAAAA 22", "AAAA 90"];
        let c = vec!["A"];
        dotest(b, c, "(A : 167)");
    }
    #[test]
    fn stock_test_10() {
        let b = vec!["AAAA 0", "AAAA 0", "AAAA 0"];
        let c = vec!["A"];
        dotest(b, c, "(A : 0)");
    }
}

