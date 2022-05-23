use std::io::{stdin, stdout, Write};

fn main() {
  print!("Enter a string to search in: ");
  stdout().flush().unwrap();
  let mut t = String::new();
  stdin().read_line(&mut t).expect("Can't read from stdin");
  t = t.trim().to_string();

  print!("Enter what to search for: ");
  stdout().flush().unwrap();
  let mut s = String::new();
  stdin().read_line(&mut s).expect("Can't read from stdin");
  s = s.trim().to_string();

  let indices = kmp(&s, &t);
  println!("Found indices: {:?}", indices);
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

fn kmp(pattern: &str, text: &str) -> Vec<usize> {
    let n = text.len();
    let m = pattern.len();

    let pi = prefix_function(pattern);

    let mut indices = Vec::new();
    let mut i = 0;
    let mut j = 0;
    while i < n {
        if pattern.chars().nth(j) == text.chars().nth(i) {
          i += 1;
          j += 1;
        }

        if j == m {
          indices.push(i - m);
          j = pi[j - 1];
        } else if i < n && pattern.chars().nth(j) != text.chars().nth(i) {
            if j == 0 {
              i += 1;
            } else {
              j = pi[j - 1];
            }
        }
    }

    return indices;
}
