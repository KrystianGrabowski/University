fn main() {
    println!("{:?}", game(204));
}

fn game(n: u64) -> Vec<u64> {
    let x: u64 =  n.pow(2);
    if x % 2 == 0 { return vec![x/2] } else { vec![x, 2] }
}

fn testing(n: u64, exp: Vec<u64>) -> () {
    assert_eq!(game(n), exp)
}

#[test]
fn basics_game_1() {
    testing(204, vec![20808]);
}
#[test]
fn basics_game_2() {
    testing(807, vec![651249, 2]);
}
#[test]
fn basics_game_3() {
    testing(5014, vec![12570098]);
}
#[test]
fn basics_game_4() {
    testing(750001, vec![562501500001, 2]);
}
#[test]
fn basics_game_5() {
    testing(161, vec![25921, 2]);
}
#[test]
fn basics_game_6() {
    testing(721, vec![519841, 2]);
}
#[test]
fn basics_game_7() {
    testing(10000, vec![50000000]);
}
#[test]
fn basics_game_8() {
    testing(666, vec![221778]);
}
#[test]
fn basics_game_9() {
    testing(8, vec![32]);
}
#[test]
fn basics_game_10() {
    testing(900, vec![405000]);
}

