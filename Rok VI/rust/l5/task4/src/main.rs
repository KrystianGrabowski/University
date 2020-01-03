extern crate regex;
use regex::Regex;
use std::cmp::{max, min};

fn main() {
    println!("{}\n", execute("F3RF5LFLFRFLFRFLFRFLFRFLFRFLFLFRFLFRFLFRFLFRFLFRFLFLF5RFFF"));
}

#[derive(Clone)]
struct Point {
    col: i32,
    row: i32,
}

struct Dimensions {
    max_row: i32,
    min_row: i32,
    max_col: i32,
    min_col: i32
}

fn create_table(columns: usize, rows: usize) -> Vec<String> {
    (0..rows).map(|x| create_row(columns, if x == rows-1 {""} else {"\r\n"})).collect()
}

fn create_row(size: usize, ends_with: &str) -> String {
    format!("{}{}", " ".repeat(size), ends_with)
}

fn position_update(pos_vec: &mut Vec<Point>, dir :&str, pos: &mut Point) {
    match dir {
        "right" => pos.col += 1,
        "left" =>  pos.col -= 1,
        "up" => pos.row -= 1,
        "down" => pos.row += 1,
        _ => {}
    };
    pos_vec.push(pos.to_owned());
}
fn translate(text: &str) -> String {
    let (command, number) = text.split_at(1);
    let num = number.parse::<usize>().unwrap_or(1);
    match command {
        "F" => "F".repeat(num),
        "L" => "L".repeat(num),
        "R" => "R".repeat(num),
        _ =>  String::new()
    }
}

fn disassemble(code: &str) -> String {
    let re = Regex::new(r"R\d+|L\d+|F\d+|\(|\)|F|R|L").unwrap();
    re.captures_iter(code)
        .map(|x| translate(x.get(0).map_or("", |m| m.as_str())))
        .collect()
}

fn dimensions_update(dim: &mut Dimensions, pos: Point) {
    dim.max_col = max(dim.max_col, pos.col);
    dim.max_row = max(dim.max_row, pos.row);
    dim.min_col = min(dim.min_col, pos.col);
    dim.min_row = min(dim.min_row, pos.row);
}

pub fn execute(code: &str) -> String {
    let path: String = disassemble(code);
    let dir_vec: Vec<&str> = vec!["right", "down", "left", "up"];
    let mut dir : usize  = 0;
    let mut position: Point = Point { col:0, row: 0 };
    let mut pos_vec: Vec<Point> = vec![Point{col:0, row:0}];
    let mut dim = Dimensions{max_row: 0, max_col:0, min_row: 0, min_col:0};

    for i in path.chars() {
        match i {
            'F' => {
                position_update(&mut pos_vec , dir_vec[dir], &mut position);
                dimensions_update(&mut dim, position.clone());
            },
            'R' => {dir = (dir + 1) % dir_vec.len()},
            'L' => {dir = dir.checked_sub(1).unwrap_or(3);}
            _ => {}
        }
    }
    let mut res_vec: Vec<String> =
        create_table(
            (dim.max_col - dim.min_col) as usize + 1,
            (dim.max_row - dim.min_row) as usize + 1
        );
    pos_vec = pos_vec.into_iter().map(|p| Point {col: p.col - dim.min_col, row: p.row - dim.min_row}).collect();
    for p in pos_vec {
        res_vec[p.row as usize].replace_range(p.col as usize..p.col as usize + 1 , "*");
    }
    res_vec.join("")
}

#[cfg(test)]
macro_rules! expect_equal {
  ($actual:expr, $expected:expr $(,)*) => {{
    let actual = $actual;
    let expected = $expected;
    assert_eq!(actual, expected, "\ngot:\n{}\n\nexpected:\n{}\n", actual, expected);
  }};
}

#[cfg(test)]
mod tests {
    use super::execute;
    #[test]
    fn robotest_1() {
        expect_equal!(execute(""), "*");
    }
    #[test]
    fn robotest_2() {
        expect_equal!(execute("FFFFF"), "******");
    }
    #[test]
    fn robotest_3() {
        expect_equal!(
    execute("FFFFFLFFFFFLFFFFFLFFFFFL"),
    "******\r\n*    *\r\n*    *\r\n*    *\r\n*    *\r\n******",
  );
    }
    #[test]
    fn robotest_4() {
        expect_equal!(
    execute("LFFFFFRFFFRFFFRFFFFFFF"),
    "    ****\r\n    *  *\r\n    *  *\r\n********\r\n    *   \r\n    *   ",
  );
    }
    #[test]
    fn robotest_5() {
        expect_equal!(
    execute("LF5RF3RF3RF7"),
    "    ****\r\n    *  *\r\n    *  *\r\n********\r\n    *   \r\n    *   ",
  );
    }
    #[test]
    fn robotest_6() {
        expect_equal!(
    execute("FFLFFRRFFFFLLFFRFF"),
    "  *  \r\n  *  \r\n*****\r\n  *  \r\n  *  ",
  );
    }
    #[test]
    fn robotest_7() {
        expect_equal!(
    execute("FLFRFLFRFLFRFLFRFLFRFL"),
    "     **\r\n    ** \r\n   **  \r\n  **   \r\n **    \r\n**     ",
  );
    }
    #[test]
    fn robotest_8() {
        expect_equal!(
    execute("LLFFRFLFFLFFRF2RF2LFFLFFRF2RF2LFFLFFRF2RF2LFFLFFRF2RF2"),
    "* *** *** *** ***  \r\n* * * * * * * * ***\r\n*** *** *** ***    ",
  );
    }
    #[test]
    fn robotest_9() {
        expect_equal!(
    execute("F3RF5LFLFRFLFRFLFRFLFRFLFRFLFLFRFLFRFLFRFLFRFLFRFLFLF5RFFF"),
    "   **     \r\n   ***    \r\n   * **   \r\n   *  **  \r\n   *   ** \r\n****    **\r\n\
    ****    **\r\n   *   ** \r\n   *  **  \r\n   * **   \r\n   ***    \r\n   **     ",
  );
    }
    #[test]
    fn robotest_10() {
        expect_equal!(
    execute("F20LLF40"),
    "*****************************************",
  );
    }

}