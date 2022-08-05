#[cfg(test)]
use crate::utils::{
    bin_to_dec, //
    bin_to_hex,
    dec_to_bin,
    dec_to_hex,
    hex_to_bin,
    hex_to_dec,
};

mod utils;

#[test]
fn test_dec_to_hex() {
    let number_decimal = vec!['6', '5', '5', '3', '5'];

    let result = dec_to_hex(number_decimal);

    assert_eq!(result, vec!['f', 'f', 'f', 'f']);
}

#[test]
fn test_dec_to_bin() {
    let number_decimal = vec!['6', '5', '5', '3', '5'];

    let result = dec_to_bin(number_decimal);

    assert_eq!(
        result,
        vec![
            '1', '1', '1', '1', //
            '1', '1', '1', '1', //
            '1', '1', '1', '1', //
            '1', '1', '1', '1'
        ]
    );
}

#[test]
fn test_hex_to_dec() {
    let number_hex = vec!['b', 'e', 'e', 'f'];

    let result = hex_to_dec(number_hex);

    assert_eq!(result, vec!['4', '8', '8', '7', '9']);
}

#[test]
fn test_hex_to_bin() {
    let number_hex = vec!['b', 'e', 'e', 'f'];

    let result = hex_to_bin(number_hex);

    assert_eq!(
        result,
        vec![
            '1', '0', '1', '1', //
            '1', '1', '1', '0', //
            '1', '1', '1', '0', //
            '1', '1', '1', '1',
        ]
    );
}

#[test]
fn test_bin_to_hex() {
    let number_bin = vec!['1', '0', '0', '1'];

    let result = bin_to_hex(number_bin);

    assert_eq!(result, vec!['9']);
}

#[test]
fn test_bin_to_dec() {
    let number_bin = vec!['1', '0', '0', '1'];

    let result = bin_to_dec(number_bin);

    assert_eq!(result, vec!['9']);
}
