use std::io::{stdin, stdout, Write};
use std::cmp;

fn main() {
  print!("Enter any string: ");
  stdout().flush().unwrap();

  let mut input = String::new();
  stdin().read_line(&mut input).expect("Can't read from stdin");
  input = input.trim().to_string();

  let pf = prefix_function(&input);
  let zf = z_function(&input);

  println!("Prefix function: {:?}", pf);
  println!("Z function:      {:?}", zf);
}

fn prefix_function(s: &str) -> Vec<usize> {
  let n = s.len();
  let mut pi = vec![0; n];
  for i in 1..n {
    let mut j = pi[i - 1];
    while j > 0 && s.chars().nth(i) != s.chars().nth(j) {
      j = pi[j - 1];
    }
    if s.chars().nth(i) == s.chars().nth(j) {
      j += 1;
    }
    pi[i] = j;
  }
  return pi;
}

fn z_function(s: &str) -> Vec<usize> {
  let n = s.len();
  let mut z = vec![0; n];
  let mut l = 0;
  let mut r = 0;
  for i in 1..n {
    if i <= r {
      z[i] = cmp::min(r - i + 1, z[i - l]);
    }
    while i + z[i] < n && s.chars().nth(z[i]) == s.chars().nth(i + z[i]) {
      z[i] += 1;
    }
    if i + z[i] - 1 > r {
      l = i;
      r = i + z[i] - 1;
    }
  }
  return z;
}