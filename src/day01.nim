import system/io
import std/strutils
import std/sequtils
import std/algorithm

let input = open("input/day01.txt");

let eachElf = input.readAll().split("\n\n")

var i = 1;

proc taskOne() =
    var elfWithMostCalories = 0;
    for elf in eachElf:
        let calories = elf.splitLines().map(parseInt)
        # sum of all the calories
        var total = 0;
        for c in calories:
            total += c
        echo "elf #" & $i & " has " & $total & " calories"
        i += 1
        if total > elfWithMostCalories:
            elfWithMostCalories = total

    echo "elf with most calories: " & $elfWithMostCalories

proc taskTwo() =
    var topThreeElves: seq[int] = @[];
    var topThreeElvesSum = 0;
    for elf in eachElf:
        let calories = elf.splitLines().map(parseInt)
        # sum of all the calories
        var total = 0;
        for c in calories:
            total += c
        echo "elf #" & $i & " has " & $total & " calories"
        i += 1
        topThreeElves.insert(total)
        topThreeElves.sort()
        

    echo "top three elves: " & $topThreeElves[^3..^1]
    # sum 
    for i in topThreeElves[^3..^1]:
        topThreeElvesSum += i
    echo "top three elves sum: " & $topThreeElvesSum



# taskOne()
taskTwo()