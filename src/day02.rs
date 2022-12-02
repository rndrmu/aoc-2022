
fn main() {
    let f = include_str!("../input/day02.txt");
    println!("Part 1: {:?}", part_one(f));
    println!("Part 2: {:?}", part_two(f));
}


fn part_one(input: &str) -> i32 {
    let mut total_score = 0;

/*
 * A => Rock
 * B => Paper
 * C => Scissors
 * --------------
 * X => Rock + 1 P
 * Y => Paper + 2 P
 * Z => Scissors + 3 P
 * --------------
 * Win + 6P
 * Lose 0P
 * Draw + 3P
 */


    for lines in input.lines() {
        for (them, us) in lines.split_ascii_whitespace().into_iter().zip(lines.split_ascii_whitespace().into_iter().skip(1)) {
            match (them, us) {
                ("A", "X") => /* Stone + Stone => Draw => 3P + 1P For Rock */ total_score += 4,
                ("A", "Y") => /* Stone + Paper => Win => 6P + 2P For Paper */ total_score += 8,
                ("A", "Z") => /* Stone + Scissors => Lose => 0P + 3P for Scissors */ total_score += 3,
                ("B", "X") => /* Paper + Stone => Lose => 0P + 1P For Rock */ total_score += 1,
                ("B", "Y") => /* Paper + Paper => Draw => 3P + 2P For Paper */ total_score += 5,
                ("B", "Z") => /* Paper + Scissors => Win => 6P + 3P for Scissors */ total_score += 9,
                ("C", "X") => /* Scissors + Stone => Win => 6P + 1P For Rock */ total_score += 7,
                ("C", "Y") => /* Scissors + Paper => Lose => 0P + 2P For Paper */ total_score += 2,
                ("C", "Z") => /* Scissors + Scissors => Draw => 3P + 3P for Scissors */ total_score += 6,
                _ => panic!("ayo"),
            }
        }
    }

    total_score
}


fn part_two(input: &str) -> i32 {


/*
 * A => Rock
 * B => Paper
 * C => Scissors
 * --------------
 * Rock + 1 P
 * Paper + 2 P
 * Scissors + 3 P
 * --------------
 * Win + 6P
 * Lose 0P
 * Draw + 3P
 * --------------
 * X means you need to lose, Y means you need to end the round in a draw, and Z means you need to win.
 */

    let mut total_score = 0;
    for lines in input.lines() {
        for (them, us) in lines.split_ascii_whitespace().into_iter().zip(lines.split_ascii_whitespace().into_iter().skip(1)) {
            match (them, us) {
                ("A", "X") => /* X => We need to loose => We choose Scissors (+3P) */ total_score += 3,
                ("A", "Y") => /* Y => We need to draw (+3P) => We choose Rock (+1P) */ total_score += 4,
                ("A", "Z") => /* Z => We need to win (+6P) => We choose Paper (+2P) */ total_score += 8,
                ("B", "X") => /* X => We need to loose => We choose Rock (+1P) */ total_score += 1,
                ("B", "Y") => /* Y => We need to draw (+3P) => We choose Paper (+2P) */ total_score += 5,
                ("B", "Z") => /* Z => We need to win (+6P) => We choose Scissors (+3P) */ total_score += 9,
                ("C", "X") => /* X => We need to loose => We choose Paper (+2P) */ total_score += 2,
                ("C", "Y") => /* Y => We need to draw (+3P) => We choose Scissors (+3P) */ total_score += 6,
                ("C", "Z") => /* Z => We need to win (+6P) => We choose Rock (+1P) */ total_score += 7,
                _ => panic!("ayo"),
            }
        }
    }
    total_score 
}