import { readFileSync } from 'fs';

const cratesTest = {
    1: ["Z", "N"],
    2: ["M", "C", "D"],
    3: ["P"]
};

const cratesInput = {
    1: ["R", "N", "F", "V", "L", "J", "S", "M"],
    2: ["P", "N", "D", "Z", "F", "J", "W", "H"],
    3: ["W", "R", "C", "D", "G"],
    4: ["N", "B", "S"],
    5: ["M", "Z", "W", "P", "C", "B", "F", "N"],
    6: ["P", "R", "M", "W"],
    7: ["R", "T", "N", "G", "L", "S", "W"],
    8: ["Q", "T", "H", "F", "N", "B", "V"],
    9: ["L", "M", "H", "Z", "N", "F"]
}

/*
    [D]    
[N] [C]    
[Z] [M] [P]
 1   2   3 

*/

const instructions = readFileSync('input/day05.txt', 'utf8').split('\n\n')[1].split('\n');

const partOne = (crates, instructions) => {
    instructions.map(instruction => instruction.match(/(?<amount>\d{1,2})|(?<source>\d)|(?<dest>\d)/gm))
    .forEach(([ amount, source, dest ]) => {
        // move crates
        crates[dest].push(...crates[source].splice(-amount).reverse());
    });


    // get top crates
    return Object.values(crates).map(crate => crate[crate.length - 1]).join('');
};

const partTwo = (crates, instructions) => {
    instructions.map(instruction => instruction.match(/(?<amount>\d{1,2})|(?<source>\d)|(?<dest>\d)/gm))
        .forEach(([ amount, source, dest ]) => {
            crates[dest].push(...crates[source].splice(-amount));
        });
    // get top crates
    return Object.values(crates).map(crate => crate[crate.length - 1]).join('');

};



console.log(partOne(cratesInput, instructions));
//console.log(partTwo(cratesInput, instructions));
