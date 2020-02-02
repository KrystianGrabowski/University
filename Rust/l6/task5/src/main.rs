fn main() {
    let good_sudoku_1 = Sudoku{
        data: vec![
            vec![7,8,4, 1,5,9, 3,2,6],
            vec![5,3,9, 6,7,2, 8,4,1],
            vec![6,1,2, 4,3,8, 7,5,9],

            vec![9,2,8, 7,1,5, 4,6,3],
            vec![3,5,7, 8,4,6, 1,9,2],
            vec![4,6,1, 9,2,3, 5,8,7],

            vec![8,7,6, 3,9,4, 2,1,5],
            vec![2,4,3, 5,6,1, 9,7,8],
            vec![1,9,5, 2,8,7, 6,3,4]
        ]
    };
    print!("{}", good_sudoku_1.is_valid());
}

struct Sudoku{
    data: Vec<Vec<u32>>,
}

impl Sudoku{
    fn validate(&self, n: usize, v: Vec<u32>) -> bool{
        let mut array = v.clone();
        array.sort();
        (1..=n as u32).collect::<Vec<u32>>() == array
    }

    fn check_dimension(&self, col: usize, sqrt: usize) -> bool {
        sqrt.pow(2) == col && col > 0 && self.data.clone().into_iter().all(|row| row.len() == col)
    }

    fn is_valid(&self) -> bool {
        let n: usize = self.data.len();
        let sqrt_n: usize = (n as f32).sqrt() as usize;
        if !self.check_dimension(n, sqrt_n) { return false; }
        let vector = self.data.clone();

        // rows
        if vector.clone().into_iter().any(|row| !self.validate(n, row)) { return false; }

        // columns
        let flattened_iter= self.data.clone().into_iter().flatten();
        let val_res: bool = (0..n).any(|col|
            !self.validate(n, flattened_iter.clone().skip(col).step_by(n).take(n).collect())
        );
        if val_res {return false;}


        // square sqrt size
        let flattened: Vec<u32>= vector.into_iter().flatten().collect();
        let chunks = flattened.chunks(sqrt_n).collect::<Vec<&[u32]>>();

        for i in 0..sqrt_n {
            for j in 0..sqrt_n {
                let mut arr = Vec::new();
                for k in 0..sqrt_n {
                    arr.extend_from_slice(chunks[i*n + j + k*sqrt_n]);
                }
                if !self.validate(n, arr) {return false;}
            }
        }
        true
    }
}

#[test]
fn good_sudoku_1() {
    let good_sudoku = Sudoku{
        data: vec![
            vec![7,8,4, 1,5,9, 3,2,6],
            vec![5,3,9, 6,7,2, 8,4,1],
            vec![6,1,2, 4,3,8, 7,5,9],

            vec![9,2,8, 7,1,5, 4,6,3],
            vec![3,5,7, 8,4,6, 1,9,2],
            vec![4,6,1, 9,2,3, 5,8,7],

            vec![8,7,6, 3,9,4, 2,1,5],
            vec![2,4,3, 5,6,1, 9,7,8],
            vec![1,9,5, 2,8,7, 6,3,4]
        ]
    };
    assert!(good_sudoku.is_valid());
}
#[test]
fn good_sudoku_2() {
    let good_sudoku = Sudoku{
        data: vec![
            vec![1, 4,  2, 3],
            vec![3, 2,  4, 1],

            vec![4, 1,  3, 2],
            vec![2, 3,  1, 4],
        ]
    };
    assert!(good_sudoku.is_valid());
}
#[test]
fn good_sudoku_3() {
    let good_sudoku = Sudoku{
        data: vec![
            vec![1],
        ]
    };
    assert!(good_sudoku.is_valid());
}
#[test]
fn good_sudoku_4() {
    let good_sudoku = Sudoku{
        data: vec![
            vec![4,3,5, 2,6,9, 7,8,1],
            vec![6,8,2, 5,7,1, 4,9,3],
            vec![1,9,7, 8,3,4, 5,6,2],

            vec![8,2,6, 1,9,5, 3,4,7],
            vec![3,7,4, 6,8,2, 9,1,5],
            vec![9,5,1, 7,4,3, 6,2,8],

            vec![5,1,9, 3,2,6, 8,7,4],
            vec![2,4,8, 9,5,7, 1,3,6],
            vec![7,6,3, 4,1,8, 2,5,9]
        ]
    };
    assert!(good_sudoku.is_valid());
}
#[test]
fn good_sudoku_5() {
    let good_sudoku = Sudoku{
        data: vec![
            vec![3,4, 2,1],
            vec![2,1, 4,3],

            vec![4,3, 1,2],
            vec![1,2, 3,4]
        ]
    };
    assert!(good_sudoku.is_valid());
}
#[test]
fn bad_sudoku_1() {
    let bad_sudoku = Sudoku{
        data: vec![
            vec![1,2,3, 4,5,6, 7,8,9],
            vec![1,2,3, 4,5,6, 7,8,9],
            vec![1,2,3, 4,5,6, 7,8,9],

            vec![1,2,3, 4,5,6, 7,8,9],
            vec![1,2,3, 4,5,6, 7,8,9],
            vec![1,2,3, 4,5,6, 7,8,9],

            vec![1,2,3, 4,5,6, 7,8,9],
            vec![1,2,3, 4,5,6, 7,8,9],
            vec![1,2,3, 4,5,6, 7,8,9],
        ]
    };
    assert!(!bad_sudoku.is_valid());
}
#[test]
fn bad_sudoku_2() {
    let bad_sudoku = Sudoku{
        data: vec![
            vec![1,2,3,4,5],
            vec![1,2,3,4],
            vec![1,2,3,4],
            vec![1],
        ]
    };
    assert!(!bad_sudoku.is_valid());
}
#[test]
fn bad_sudoku_3() {
    let bad_sudoku = Sudoku{
        data: vec![
            vec![],
        ]
    };
    assert!(!bad_sudoku.is_valid());
}
#[test]
fn bad_sudoku_4() {
    let bad_sudoku = Sudoku{
        data: vec![
            vec![4,3,5, 2,6,9, 7,8,1],
            vec![6,8,2, 5,7,1, 4,9,3],
            vec![1,9,7, 8,3,4, 5,6,2],

            vec![8,2,6, 3,9,5, 3,4,7],
            vec![3,7,4, 6,8,2, 9,1,5],
            vec![9,5,1, 7,4,3, 6,2,8],

            vec![5,1,9, 3,2,6, 8,7,4],
            vec![2,4,8, 9,5,7, 1,3,6],
            vec![7,6,3, 4,1,8, 2,5,9]
        ]
    };
    assert!(!bad_sudoku.is_valid());
}
#[test]
fn bad_sudoku_5() {
    let bad_sudoku = Sudoku{
        data: vec![
            vec![3,4, 2,1],
            vec![1,2, 4,3],

            vec![4,3, 1,2],
            vec![1,2, 3,4]
        ]
    };
    assert!(!bad_sudoku.is_valid());
}
#[test]
fn bad_sudoku_6() {
    let bad_sudoku = Sudoku{
        data: vec![
            vec![4,3,5, 2,6,9, 7,1,8],
            vec![6,8,2, 5,7,1, 4,9,3],
            vec![1,9,7, 8,3,4, 5,6,2],

            vec![8,2,6, 1,9,5, 3,4,7],
            vec![3,7,4, 6,8,2, 9,1,5],
            vec![9,5,1, 7,4,3, 6,2,8],

            vec![5,1,9, 3,2,6, 8,7,4],
            vec![2,4,8, 9,5,7, 1,3,6],
            vec![7,6,3, 4,1,8, 2,5,9]
        ]
    };
    assert!(!bad_sudoku.is_valid());
}
#[test]
fn bad_sudoku_7() {
    let bad_sudoku = Sudoku{
        data: vec![
            vec![4,3,5, 2,6,9, 7,8,1],
            vec![6,8,2, 5,7,1, 4,9,3],
            vec![1,9,7, 8,3,4, 5,6,2],

            vec![8,2,6, 1,9,5, 3,4,7],
            vec![3,7,4, 6,8,2, 9,1,5],
            vec![9,5,1, 7,4,3, 6,2,8],

            vec![5,1,9, 3,2,6, 8,7,4],
            vec![2,4,8, 9,5,7, 1,3,6],
            vec![7,6,3, 4,1,8, 2,7,9]
        ]
    };
    assert!(!bad_sudoku.is_valid());
}
#[test]
fn bad_sudoku_8() {
    let bad_sudoku = Sudoku{
        data: vec![
            vec![4,3,5, 2,6,9, 7,8,1],
            vec![6,8,2, 5,7,1, 4,9,3],
            vec![5,9,7, 8,3,4, 1,6,2],

            vec![8,2,6, 1,9,5, 3,4,7],
            vec![3,7,4, 6,8,2, 9,1,5],
            vec![9,5,1, 7,4,3, 6,2,8],

            vec![5,1,9, 3,2,6, 8,7,4],
            vec![2,4,8, 9,5,7, 1,3,6],
            vec![7,6,3, 4,1,8, 2,7,9]
        ]
    };
    assert!(!bad_sudoku.is_valid());
}