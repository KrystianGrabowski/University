fn main() {
    println!("{}", number(&[]));
}

fn number(bus_stops:&[(i32,i32)]) -> i32 {
    bus_stops.into_iter().map(|x| x.0 - x.1).sum()
}

#[test]
fn bus_stops_test1() {
    assert_eq!(number(&[(10,0),(3,5),(5,8)]), 5);
}
#[test]
fn bus_stops_test2() {
    assert_eq!(number(&[(3,0),(9,1),(4,10),(12,2),(6,1),(7,10)]), 17);
}
#[test]
fn bus_stops_test3() {
    assert_eq!(number(&[(6,0),(6,0),(6,0)]), 18);
}
#[test]
fn bus_stops_test4() {
    assert_eq!(number(&[(554,0)]), 554);
}
#[test]
fn bus_stops_test5() {
    assert_eq!(number(&[(1,1),(1,1),(1,1),(1,1),(1,1),(1,1)]), 0);
}
#[test]
fn bus_stops_test6() {
    assert_eq!(number(&[(6,0),(6,1),(6,2),(6,3),(6,4),(6,5)]), 21);
}
#[test]
fn bus_stops_test7() {
    assert_eq!(number(&[(15,0),(0,5),(0,5)]), 5);
}
#[test]
fn bus_stops_test8() {
    assert_eq!(number(&[(1,0),(0,1),(1,0),(0,1)]), 0);
}
#[test]
fn bus_stops_test9() {
    assert_eq!(number(&[(4,0),(9,1),(12,11),(1,1),(68,1),(0,65)]), 15);
}
#[test]
fn bus_stops_test10() {
    assert_eq!(number(&[]), 0);
}

