fn main() {
    println!("{}", chessboard_cell_color("A1", "C3"));
}
fn convert_cell(cell: &str) -> (usize, usize) {
    let mut str: String = cell.to_string();
    let col = str.pop().unwrap().to_digit(10).unwrap();
    let row = str.pop().unwrap() as i8 - ('A' as i8 - 1);
    (col as usize, row as usize)
}

fn chessboard_cell_color(cell1: &str, cell2: &str) -> bool {
    let v: Vec<Vec<char>> = vec![vec!['a', 'b', 'a', 'b', 'a', 'b', 'a', 'b'], vec!['b', 'a', 'b', 'a', 'b', 'a', 'b','a']];
    let a = convert_cell(cell1);
    let b = convert_cell(cell2);
    v[a.0%2][a.1 - 1] == v[b.0%2][b.1 - 1]
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn chessboard_test_1() {
        assert_eq!(chessboard_cell_color("A1", "C3"), true);
    }
    #[test]
    fn chessboard_test_2() {
        assert_eq!(chessboard_cell_color("A1", "H3"), false);
    }
    #[test]
    fn chessboard_test_3() {
        assert_eq!(chessboard_cell_color("A1", "A2"), false);
    }
    #[test]
    fn chessboard_test_4() {
        assert_eq!(chessboard_cell_color("A1", "C1"), true);
    }
    #[test]
    fn chessboard_test_5() {
        assert_eq!(chessboard_cell_color("A1", "A1"), true);
    }

    #[test]
    fn chessboard_test_6() {
        assert_eq!(chessboard_cell_color("A8", "H8"), false);
    }
    #[test]
    fn chessboard_test_7() {
        assert_eq!(chessboard_cell_color("D6", "H2"), true);
    }
    #[test]
    fn chessboard_test_8() {
        assert_eq!(chessboard_cell_color("E5", "E8"), false);
    }
    #[test]
    fn chessboard_test_9() {
        assert_eq!(chessboard_cell_color("G2", "G1"), false);
    }
    #[test]
    fn chessboard_test_10() {
        assert_eq!(chessboard_cell_color("A5", "H5"), false);
    }
}
