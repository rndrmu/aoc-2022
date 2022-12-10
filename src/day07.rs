//! This solution is taken from <https://maebli.github.io/rust/2022/12/06/100rust-69.html>
//! because i'm too retarded to understand the problem :^)

use std::collections::HashMap;

const TOTAL_DISK_SPACE: u64 = 70000000;
const MINIMUM_FREE_SPACE: u64 = 30000000;

fn main() {

    let directories = include_str!("../../../input/day07.txt").split_terminator("$")
                                .filter(|x|x.len()>0)
                                .map(Command::parse)
                                .fold((vec![],HashMap::<String,Vec<Node>>::new()),|mut acc,curr| {
                                        match curr{
                                            Command::CdUp() => {acc.0.pop();},
                                            Command::Cd(_) => {acc.0.push(curr.name().unwrap().trim().to_string());},
                                            Command::Ls(children) => {
                                                children.into_iter()
                                                        .for_each(|mut node| {
                                                            let child_path= [acc.0.join("/"),node.name].join("/");
                                                            let parent_path= acc.0.join("/");
                                                            node.name = child_path;
                                                            acc.1.entry(parent_path).or_insert(vec![]).push(node);
                                                });
                                            }
                                        };
                                        acc
                                }).1;
    let sum = directories.iter()
                .map(|(k,_v)| {
                    size_of_node_in_tree(String::from(k), &directories)
                }).filter(|x| *x<100000).sum::<u64>();

    println!("Sum of all files below size 10000: {}", sum);


    let used_disk_space = size_of_node_in_tree("/".to_string(), &directories);
    println!("Used disk space: {}", used_disk_space);

    let unused_disk_space = TOTAL_DISK_SPACE - used_disk_space;
    let required_additonal_space = MINIMUM_FREE_SPACE-unused_disk_space;
                                         

    println!("Unused disk space: {}", unused_disk_space);
    println!("Additional required space: {}",required_additonal_space);

    let mut sum:Vec<u64> = directories.iter()
                .map(|(k,_v)| {
                    size_of_node_in_tree(String::from(k), &directories)
                })
                .filter(|x| *x>required_additonal_space).collect();
    sum.sort();
    
    println!("File to delete: {}", sum.first().unwrap());



}

#[derive(PartialEq,Debug)]
struct Node {
    name: String,
    size: u64,
}

#[derive(PartialEq,Debug)]
struct Response {
    value: String,
}

#[derive(PartialEq,Debug)]
enum Command{
    CdUp(),
    Cd(Node),
    Ls(Vec<Node>)
}


fn size_of_node_in_tree(file_name: String, directory_tree: &HashMap<String,Vec<Node>>) -> u64 {
    let mut size = 0;
    if let Some(nodes) = directory_tree.get(&file_name) {
        for node in nodes {
            if node.size == 0 {
                size += size_of_node_in_tree(node.name.to_string(), directory_tree);
            } else {
                size += node.size;
            }
        }
    }
    size
}


impl Command {
    fn parse(input: &str) -> Command {

        match input[0..3].to_owned().as_str() {
            " cd" => {
                if input.len()>5 && input[4..6].eq("..") {
                    Command::CdUp()
                }else {
                    Command::Cd(Node{name: input[4..].trim().to_string(), size: 0})
                }
            },
            " ls" => Command::Ls({
                input.lines().skip(1).fold(vec![], |mut acc, line| {
                    let mut line = line.split_whitespace();
                    let mut n = 0;
                    if let Ok(number)=line.next().unwrap().parse::<u64>(){
                        n = number;
                    }
                    acc.push(Node{
                        name: line.next().unwrap().to_string(), 
                        size: n
                    });
                    acc
                })
            }),
            _ => panic!("Unknown command '{}'", input[0..3].to_owned().as_str()),
        }
    }

    fn name(&self) -> Option<String> {
        match self {
            Command::CdUp() => None,
            Command::Cd(node) => Some(node.name.to_string()),
            Command::Ls(_) => None,
        }
        
    }
}
