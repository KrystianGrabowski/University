
fn main() {
    println!("{}", interpreter("n*[ne*]", 38, 10, 10));
}

fn flip_field(field: String) -> String {
    match field.as_ref() {
        "0" => "1".to_string(),
        "1" => "0".to_string(),
        _ => panic!()
    }
}

fn find_bracket(code: Vec<char>, mut i: usize, step: i32) -> usize {
    let mut ratio = 0;
    loop {
        match code[i] {
            ']' => ratio -= 1,
            '[' => ratio += 1,
            _ => {},
        }
        if ratio == 0 { break; }
        i = (i as i32 + step) as usize;
    }
    i
}

fn interpreter(code: &str, iterations: usize, width: usize, height: usize) -> String {
    let mut board: Vec<Vec<String>> = vec![vec!["0".to_string(); width]; height];
    let mut row: usize = 0;
    let mut col: usize = 0;
    let filtered_code: Vec<char> = code.chars().filter(|&x| "nesw*[]".contains(x)).collect();
    let mut i = 0;
    let mut j = 0;

    while j < iterations && i < filtered_code.len(){
        match filtered_code[i]{
            'n' => row = row.checked_sub(1).unwrap_or(height-1),
            'e' => col = (col + 1) % width,
            's' => row = (row + 1) % height,
            'w' => col = col.checked_sub(1).unwrap_or(width-1),
            '*' => board[row][col] = flip_field( board[row][col].clone() ) ,
            '[' => if  board[row][col] == "0".to_string() { i = find_bracket(filtered_code.clone(), i, 1) }
            ']' => if board[row][col] == "1".to_string() { i = find_bracket(filtered_code.clone(), i, -1) }
            _ => {}
        };
        i += 1;
        j += 1;
    }
    board.into_iter().map(|x| x.join("")).collect::<Vec<String>>().join("\r\n")
}


#[test]
fn simple_case_1() {
    assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 0, 6, 9)), display_expected("000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000"), "Your interpreter should initialize all cells in the datagrid to 0");
}
#[test]
fn simple_case_2() {
    assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 7, 6, 9)), display_expected("111100\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000"), "Your interpreter should adhere to the number of iterations specified");
}
#[test]
fn simple_case_3() {
    assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 19, 6, 9)), display_expected("111100\r\n000010\r\n000001\r\n000010\r\n000100\r\n000000\r\n000000\r\n000000\r\n000000"), "Your interpreter should traverse the 2D datagrid correctly");
}
#[test]
fn simple_case_4() {
    assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 42, 6, 9)), display_expected("111100\r\n100010\r\n100001\r\n100010\r\n111100\r\n100000\r\n100000\r\n100000\r\n100000"), "Your interpreter should traverse the 2D datagrid correctly for all of the \"n\", \"e\", \"s\" and \"w\" commands");
}
#[test]
fn simple_case_5() {
    assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 100, 6, 9)), display_expected("111100\r\n100010\r\n100001\r\n100010\r\n111100\r\n100000\r\n100000\r\n100000\r\n100000"), "Your interpreter should terminate normally and return a representation of the final state of the 2D datagrid when all commands have been considered from left to right even if the number of iterations specified have not been fully performed");
}
#[test]
fn simple_case_6() {
    assert_eq!(display_actual(&interpreter("*", 100, 1, 1)), display_expected("1"), "Your interpreter should work with size 1");
}
#[test]
fn simple_case_7() {
    assert_eq!(display_actual(&interpreter("*n*", 100, 1, 1)), display_expected("0"), "Your interpreter should flip bit two times");
}
#[test]
fn simple_case_8() {
    assert_eq!(display_actual(&interpreter("*s*s*s*s*e*e*e*e*n*n*n*n*w*w*w*", 33, 5, 5)), display_expected("11111\r\n10001\r\n10001\r\n10001\r\n11111"), "Your interpreter should print frame");
}
#[test]
fn simple_case_9() {
    assert_eq!(display_actual(&interpreter("n*[ne*]", 38, 10, 10)), display_expected("0000000001\r\n0000000010\r\n0000000100\r\n0000001000\r\n0000010000\r\n0000100000\r\n0001000000\r\n0010000000\r\n0100000000\r\n1000000000"), "Your interpreter should handle loop");
}
#[test]
fn simple_case_10() {
    assert_eq!(display_actual(&interpreter("*e*e*e*e*e*e*e*e*e*sw*sw*sw*sw*sw*sw*sw*sw*sw*e*e*e*e*e*e*e*e*e*", 3000, 10, 10)), display_expected("1111111111\r\n0000000010\r\n0000000100\r\n0000001000\r\n0000010000\r\n0000100000\r\n0001000000\r\n0010000000\r\n0100000000\r\n1111111111"), "Your interpreter should print Z");
}