use std::io::{stdin, stdout, Write};
use std::collections::HashMap;
use std::cmp;

fn z_function(s: &Vec<char>) -> Vec<usize> {
  let n = s.len();
  let mut z = vec![0; n];
  let mut l = 0;
  let mut r = 0;
  for i in 1..n {
    if i <= r {
      z[i] = cmp::min(r - i + 1, z[i - l]);
    }
    while i + z[i] < n && s[z[i]] == s[i + z[i]] {
      z[i] += 1;
    }
    if i + z[i] - 1 > r {
      l = i;
      r = i + z[i] - 1;
    }
  }
  return z;
}

fn suffix_table(pattern: &Vec<char>) -> Vec<usize> {
  let pat_len = pattern.len();
  let zf = z_function(pattern);
  let mut suffix_table = vec![pat_len; pat_len + 1];
  for j in (0..(pat_len - 1)).rev() {
    suffix_table[pat_len - zf[j]] = j;
  }
  for j in 1..pat_len {
    if j + zf[j] == pat_len {
      for r in 1..(j + 1) {
        if suffix_table[r] == pat_len {
          suffix_table[r] = j;
        }
      }
    }
  }
  return suffix_table;
}

fn stop_table(pattern: &Vec<char>) -> HashMap<char, usize> {
  let mut stop_table = HashMap::new();
  for (i, letter) in pattern.iter().enumerate() {
    stop_table.entry(*letter).or_insert(i);
  }
  return stop_table;
}

fn boyer_moore(text: &str, pattern: &str) -> Vec<usize> {
  let text: Vec<char> = text.chars().collect();
  let pattern: Vec<char> = pattern.chars().collect();
  let pat_len = pattern.len();
  let text_len = text.len();

  let suffix_table = suffix_table(&pattern);
  let stop_table = stop_table(&pattern);

  let mut indices = Vec::new();
  let mut bound = 0;
  let mut i = 0;
  while i <= text_len - pat_len {
    let mut j = (pat_len - 1) as i32;
    while j >= bound && pattern[j as usize] == text[i + j as usize] {
      j -= 1;
    }
    if j < bound {
      indices.push(i);
      bound = (pat_len - suffix_table[0]) as i32;
      j = -1;
    } else {
      bound = 0;
    }
    if j < bound { 
      i += suffix_table[(j + 1) as usize];
    } else {
      let letter = &text[i + j as usize];
      let idx = if stop_table.contains_key(letter) { stop_table[letter] }
                       else { 0 };
      i += cmp::max(suffix_table[(j + 1) as usize], j as usize - idx);
    }
  }
  return indices;
}

fn main() {
  print!("Enter a string to search in: ");
  stdout().flush().unwrap();
  let mut text = String::new();
  stdin().read_line(&mut text).expect("Can't read from stdin");
  text = text.trim().to_string();

  print!("Enter a s to search for: ");
  stdout().flush().unwrap();
  let mut pattern = String::new();
  stdin().read_line(&mut pattern).expect("Can't read from stdin");
  pattern = pattern.trim().to_string();

  println!("Found index: {:?}", boyer_moore(&text, &pattern));
}