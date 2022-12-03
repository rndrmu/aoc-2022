import { readFileSync } from 'node:fs';

const input = readFileSync('input/day03.txt', 'utf-8');
const alphabet = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'; // priority is letter position in this string
const letterToNumber = (letter: string): number => {
    return alphabet.indexOf(letter) + 1;
};

const part1 = (ogInput: string) => {
    let score = 0;
    const input = ogInput.split('\n').map(line => line.trim());

    const letterArray = new Array<string>();

    input.forEach((line) => {
        const compartmentOne = line.slice(0, line.length / 2).split('');
        const compartmentTwo = line.slice(line.length / 2).split('');

        // check if compartmentTwo has any overlap with compartmentOne, if there is a duplicate letter, add it only once 
        compartmentTwo
        .filter((letter) => compartmentOne.includes(letter))
        .filter((letter, index, array) => array.indexOf(letter) === index)
        .forEach((letter) => letterArray.push(letter));


    });

    // compute score
    letterArray.forEach((letter) => {
        score += alphabet.indexOf(letter) + 1;
    });

    console.log(score);
}


const part2 = (ogInput: string): number => {
    // 3 lines == 1 group
    const groups = new Array<Array<string>>();
    const input = ogInput.split('\n').map(line => line.trim());
    let score = 0;
    input.forEach((line, index) => {
        if (index % 3 === 0) {
            groups.push([line]);
        } else {
            console
            groups[groups.length - 1].push(line);
        }
    });

    // find common letter among(us)st group members
    const letterArray = new Array<string>();
    groups.forEach((group) => {
        const compartmentOne = group[0].split('');
        const compartmentTwo = group[1].split('');
        const compartmentThree = group[2].split('');

        compartmentOne
        .filter((letter) => compartmentTwo.includes(letter) && compartmentThree.includes(letter))
        .filter((letter, index, array) => array.indexOf(letter) === index)
        .forEach((letter) => letterArray.push(letter));
    });

    // compute score
    letterArray.forEach((letter) => {
        score += alphabet.indexOf(letter) + 1;
    });

    return score;
    
}


//part1(input);
console.log(part2(input));