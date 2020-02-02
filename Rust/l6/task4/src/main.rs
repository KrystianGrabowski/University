fn main() {
    let a1 = vec![121, 144, 19, 161, 19, 144, 19, 11];
    let a2 = vec![11*11, 121*121, 144*144, 19*19, 161*161, 19*19, 144*144, 19*19];
    println!("{}", comp(a1, a2));
}

fn comp(a: Vec<i64>, b: Vec<i64>) -> bool {
    let mut x: Vec<i64> = a.into_iter().map(|x| x * x).collect();
    let mut c: Vec<i64> = b.clone();
    x.sort();
    c.sort();
    x == c
}

fn testing(a: Vec<i64>, b: Vec<i64>, exp: bool) -> () {
    assert_eq!(comp(a, b), exp)
}

#[test]
fn tests_comp_1() {
    let a1 = vec![121, 144, 19, 161, 19, 144, 19, 11];
    let a2 = vec![11*11, 121*121, 144*144, 19*19, 161*161, 19*19, 144*144, 19*19];
    testing(a1, a2, true);
}
#[test]
fn tests_comp_2() {
    let a1 = vec![121, 144, 19, 161, 19, 144, 19, 11];
    let a2 = vec![11*21, 121*121, 144*144, 19*19, 161*161, 19*19, 144*144, 19*19];
    testing(a1, a2, false);
}
#[test]
fn tests_comp_3() {
    let a1 = vec![1, 2, 3, 4];
    let a2 = vec![1, 4, 9, 16];
    testing(a1, a2, true);

}
#[test]
fn tests_comp_4() {
    let a1 = vec![5, 10];
    let a2 = vec![5*5, 10*10];
    testing(a1, a2, true);

}
#[test]
fn tests_comp_5() {
    let a1 = vec![1000];
    let a2 = vec![1000000];
    testing(a1, a2, true);

}
#[test]
fn tests_comp_6() {
    let a1 = vec![];
    let a2 = vec![];
    testing(a1, a2, true);

}
#[test]
fn tests_comp_7() {
    let a1 = vec![10, 20, 30, 161, 19, 144, 19, 11];
    let a2 = vec![10*10, 20*20, 30*31];
    testing(a1, a2, false);

}
#[test]
fn tests_comp_8() {
    let a1 = vec![11, 12, 13, 14];
    let a2 = vec![11*11, 12*10];
    testing(a1, a2, false);

}
#[test]
fn tests_comp_9() {
    let a1 = vec![121, 144, 19, 161, 19, 144, 11];
    let a2 = vec![11*21, 132*121, 144*144, 161*161, 19*19, 144*144, 19*19];
    testing(a1, a2, false);

}
#[test]
fn tests_comp_10() {
    let a1 = vec![6, 7, 8];
    let a2 = vec![6*7, 7*6, 8*8];
    testing(a1, a2, false);

}
