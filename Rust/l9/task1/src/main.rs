fn main() {
    println!("{}", part_list(vec!["I", "wish", "I", "hadn't", "come"]));
}

fn part_list(arr: Vec<&str>) -> String {
    let mut s: String = String::new();
    let size = arr.len();
    for i in 0..size-1 {
        let mut vec:Vec<String> = arr.clone().into_iter().map(|x| x.to_string()).collect();
        vec[i].push(',');
        s = format!("{}({})", s, vec.join(" "));
    }
    s
}

#[cfg(test)]
mod tests {
    use super::*;

    fn dotest(arr: Vec<&str>, exp: &str) -> () {
        println!("arr: {:?}", arr);
        let ans = part_list(arr);
        println!("actual:\n{}", ans);
        println!("expect:\n{}", exp);
        println!("{}", ans == exp);
        assert_eq!(ans, exp);
        println!("{}", "-");
    }

    #[test]
    fn part_list_test_1() {
        dotest(vec!["I", "wish", "I", "hadn't", "come"],
               "(I, wish I hadn't come)(I wish, I hadn't come)(I wish I, hadn't come)(I wish I hadn't, come)");
    }
    #[test]
    fn part_list_test_2() {
        dotest(vec!["cdIw", "tzIy", "xDu", "rThG"],
               "(cdIw, tzIy xDu rThG)(cdIw tzIy, xDu rThG)(cdIw tzIy xDu, rThG)");
    }
    #[test]
    fn part_list_test_3() {
        dotest(vec!["I", "want", "to", "break", "free"],
               "(I, want to break free)(I want, to break free)(I want to, break free)(I want to break, free)");
    }
    #[test]
    fn part_list_test_4() {
        dotest(vec!["test1", "test2", "test3", "test4"],
               "(test1, test2 test3 test4)(test1 test2, test3 test4)(test1 test2 test3, test4)");
    }
    #[test]
    fn part_list_test_5() {
        dotest(vec!["one", "two"],
               "(one, two)");
    }
    #[test]
    fn part_list_test_6() {
        dotest(vec!["test1", "test2", "test3"],
               "(test1, test2 test3)(test1 test2, test3)");
    }
    #[test]
    fn part_list_test_7() {
        dotest(vec!["echo", "echo", "echo", "echo"],
               "(echo, echo echo echo)(echo echo, echo echo)(echo echo echo, echo)");
    }
    #[test]
    fn part_list_test_8() {
        dotest(vec!["a", "b", "c", "d", "e", "f"],
               "(a, b c d e f)(a b, c d e f)(a b c, d e f)(a b c d, e f)(a b c d e, f)");
    }
    #[test]
    fn part_list_test_9() {
        dotest(vec!["po", "op"],
               "(po, op)");
    }
    #[test]
    fn part_list_test_10() {
        dotest(vec!["makao", "makao", "o"],
               "(makao, makao o)(makao makao, o)");
    }
}
