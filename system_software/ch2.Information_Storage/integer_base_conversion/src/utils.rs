#[cfg(test)]
pub fn dec_to_hex(data: Vec<char>) -> Vec<char> {
    let num_str: String = data.into_iter().collect();

    let num: u64 = num_str.parse::<u64>().unwrap();

    let result = format!("{:x}", num);

    result.chars().collect()
}

#[cfg(test)]
pub fn dec_to_bin(data: Vec<char>) -> Vec<char> {
    let num_str: String = data.into_iter().collect();

    let num: u64 = num_str.parse::<u64>().unwrap();

    let result = format!("{:b}", num);

    result.chars().collect()
}

#[cfg(test)]
pub fn hex_to_dec(data: Vec<char>) -> Vec<char> {
    let num_str: String = data.into_iter().collect();

    let num = u64::from_str_radix(&num_str, 16).unwrap();

    let result = num.to_string();

    result.chars().collect()
}

#[cfg(test)]
pub fn hex_to_bin(data: Vec<char>) -> Vec<char> {
    let num_str: String = data.into_iter().collect();

    let num = u64::from_str_radix(&num_str, 16).unwrap();

    let result = format!("{:b}", num);

    result.chars().collect()
}

#[cfg(test)]
pub fn bin_to_hex(data: Vec<char>) -> Vec<char> {
    let num_str: String = data.into_iter().collect();

    let num = u64::from_str_radix(&num_str, 2).unwrap();

    let result = format!("{:x}", num);

    result.chars().collect()
}

#[cfg(test)]
pub fn bin_to_dec(data: Vec<char>) -> Vec<char> {
    let num_str: String = data.into_iter().collect();

    let num = u64::from_str_radix(&num_str, 2).unwrap();

    let result = format!("{}", num);

    result.chars().collect()
}
