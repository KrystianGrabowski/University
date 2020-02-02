fn main() {
    print!("{}", zoom(3));
}

fn generate_line(total_size: i32, inner_size: i32, char_type: usize) -> String {
    let v: Vec<char> = vec!['□', '■'];
    let mut c: Vec<char> = (0..inner_size).map(|_x| v[char_type]).collect();
    let mut it = (0..2).cycle().skip((char_type + 1) % 2);
    for _i in 0..(total_size-inner_size)/2 {
        let col = it.next().unwrap();
        c.insert(0, v[col]);
        c.push(v[col]);
    }
    c.into_iter().collect()
}
fn zoom(n: i32) -> String {
    let mut pattern: String = generate_line(n , 1, 1);
    let mut it = (0..2).cycle();
    (3..=n)
        .step_by(2)
        .for_each(|x| pattern = format!("{1}\n{0}\n{1}",
                                        pattern,
                                        generate_line(n, x, it.next().unwrap())
            )
        );
    pattern
}

#[test]
fn basic_test_1() {
    assert_eq!(zoom(1), "■");
}

#[test]
fn basic_test_2() {
    assert_eq!(zoom(3), "\
□□□
□■□
□□□"
    );
}

#[test]
fn basic_test_3() {
    assert_eq!(zoom(5), "\
■■■■■
■□□□■
■□■□■
■□□□■
■■■■■"
    );
}

#[test]
fn basic_test_4() {
    assert_eq!(zoom(7), "\
□□□□□□□
□■■■■■□
□■□□□■□
□■□■□■□
□■□□□■□
□■■■■■□
□□□□□□□"
    );
}

#[test]
fn basic_test_5() {
    assert_eq!(zoom(9), "\
■■■■■■■■■
■□□□□□□□■
■□■■■■■□■
■□■□□□■□■
■□■□■□■□■
■□■□□□■□■
■□■■■■■□■
■□□□□□□□■
■■■■■■■■■"
    );
}

#[test]
fn basic_test_6() {
    assert_eq!(zoom(11), "\
□□□□□□□□□□□
□■■■■■■■■■□
□■□□□□□□□■□
□■□■■■■■□■□
□■□■□□□■□■□
□■□■□■□■□■□
□■□■□□□■□■□
□■□■■■■■□■□
□■□□□□□□□■□
□■■■■■■■■■□
□□□□□□□□□□□"
    );
}
#[test]
fn basic_test_7() {
    assert_eq!(zoom(13), "\
■■■■■■■■■■■■■
■□□□□□□□□□□□■
■□■■■■■■■■■□■
■□■□□□□□□□■□■
■□■□■■■■■□■□■
■□■□■□□□■□■□■
■□■□■□■□■□■□■
■□■□■□□□■□■□■
■□■□■■■■■□■□■
■□■□□□□□□□■□■
■□■■■■■■■■■□■
■□□□□□□□□□□□■
■■■■■■■■■■■■■"
    );
}
#[test]
fn basic_test_8() {
    assert_eq!(zoom(15), "\
□□□□□□□□□□□□□□□
□■■■■■■■■■■■■■□
□■□□□□□□□□□□□■□
□■□■■■■■■■■■□■□
□■□■□□□□□□□■□■□
□■□■□■■■■■□■□■□
□■□■□■□□□■□■□■□
□■□■□■□■□■□■□■□
□■□■□■□□□■□■□■□
□■□■□■■■■■□■□■□
□■□■□□□□□□□■□■□
□■□■■■■■■■■■□■□
□■□□□□□□□□□□□■□
□■■■■■■■■■■■■■□
□□□□□□□□□□□□□□□"
    );
}
#[test]
fn basic_test_9() {
    assert_eq!(zoom(17), "\
■■■■■■■■■■■■■■■■■
■□□□□□□□□□□□□□□□■
■□■■■■■■■■■■■■■□■
■□■□□□□□□□□□□□■□■
■□■□■■■■■■■■■□■□■
■□■□■□□□□□□□■□■□■
■□■□■□■■■■■□■□■□■
■□■□■□■□□□■□■□■□■
■□■□■□■□■□■□■□■□■
■□■□■□■□□□■□■□■□■
■□■□■□■■■■■□■□■□■
■□■□■□□□□□□□■□■□■
■□■□■■■■■■■■■□■□■
■□■□□□□□□□□□□□■□■
■□■■■■■■■■■■■■■□■
■□□□□□□□□□□□□□□□■
■■■■■■■■■■■■■■■■■"
    );
}


#[test]
fn basic_test_10() {
    assert_eq!(zoom(25), "\
■■■■■■■■■■■■■■■■■■■■■■■■■
■□□□□□□□□□□□□□□□□□□□□□□□■
■□■■■■■■■■■■■■■■■■■■■■■□■
■□■□□□□□□□□□□□□□□□□□□□■□■
■□■□■■■■■■■■■■■■■■■■■□■□■
■□■□■□□□□□□□□□□□□□□□■□■□■
■□■□■□■■■■■■■■■■■■■□■□■□■
■□■□■□■□□□□□□□□□□□■□■□■□■
■□■□■□■□■■■■■■■■■□■□■□■□■
■□■□■□■□■□□□□□□□■□■□■□■□■
■□■□■□■□■□■■■■■□■□■□■□■□■
■□■□■□■□■□■□□□■□■□■□■□■□■
■□■□■□■□■□■□■□■□■□■□■□■□■
■□■□■□■□■□■□□□■□■□■□■□■□■
■□■□■□■□■□■■■■■□■□■□■□■□■
■□■□■□■□■□□□□□□□■□■□■□■□■
■□■□■□■□■■■■■■■■■□■□■□■□■
■□■□■□■□□□□□□□□□□□■□■□■□■
■□■□■□■■■■■■■■■■■■■□■□■□■
■□■□■□□□□□□□□□□□□□□□■□■□■
■□■□■■■■■■■■■■■■■■■■■□■□■
■□■□□□□□□□□□□□□□□□□□□□■□■
■□■■■■■■■■■■■■■■■■■■■■■□■
■□□□□□□□□□□□□□□□□□□□□□□□■
■■■■■■■■■■■■■■■■■■■■■■■■■"
    );
}