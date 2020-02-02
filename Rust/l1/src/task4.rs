fn square_area_to_circle(size:f64) -> f64 {
    (size / 4.0) * 3.14159265359
}

fn assert_close(a:f64, b:f64, epsilon:f64) {
    assert!( (a-b).abs() < epsilon, format!("Expected: {}, got: {}",b,a) );
}


#[test]
fn returns_expected() {
    assert_close(square_area_to_circle(9.0), 7.0685834705770345, 1e-8);
}
#[test]
fn test_66() {
    assert_close(square_area_to_circle(66.0), 51.836278784, 1e-8);
}
#[test]
fn test_10() {
    assert_close(square_area_to_circle(10.0), 7.853981634, 1e-8);
}
#[test]
fn test_200() {
    assert_close(square_area_to_circle(200.0), 157.07963268, 1e-8);
}
#[test]
fn test_1() {
    assert_close(square_area_to_circle(1.0), 0.785398163, 1e-8);
}
#[test]
fn test_50() {
    assert_close(square_area_to_circle(50.0), 39.26990817, 1e-8);
}