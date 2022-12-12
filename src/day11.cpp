#include <iostream>
#include <string>
#include <queue>
#include <regex>
#include <fstream>
#include <optional>
#include <tuple>

std::vector<std::string> split_string(const std::string& str,
                                      const std::string& delimiter);
long long part1(std::vector<std::string> lines);
void part2(std::vector<std::string> lines);
enum Meth {
    ADD = '+',
    MULTIPLY = '*',
    POTENZ = '^'
};


const int GAME_ROUNDS = 20;


class Monke {
    public: 
        Monke(int multiplier, int divisible, std::queue<long long> items, Meth meth, std::pair<int, int> target_monkes);
        ~Monke();
        int id;
        std::queue<long long> items_in_hand;
        int worry_level_multiplier;
        Meth worry_level_multiplier_method;
        int divisible_test;
        std::pair<int, int> target_monkes;
        int get_monke_inspection_count() { return monke_inspection_count; }
        void yeet(int item, Monke* monke);
        void yoink(int item, Monke* monke);
        void inspect(std::vector<Monke> &monke_vector, bool manage_worry_level);
        int monke_inspection_count;
};

Monke::Monke(int multiplier, int divisible, std::queue<long long> items, Meth meth, std::pair<int, int> target_monkes) {
    this->worry_level_multiplier = multiplier;
    this->divisible_test = divisible;
    this->items_in_hand = items;
    this->worry_level_multiplier_method = meth;
    this->monke_inspection_count = 0;
    this->target_monkes = target_monkes;
}

Monke::~Monke() 
{
}



void Monke::yeet(int item, Monke* monke) 
{
    // remove item from this monke
    std::queue<long long> items = this->items_in_hand;
    std::queue<long long> new_items;
    while (!items.empty()) {
        if (items.front() != item) {
            new_items.push(items.front());
        }
        items.pop();
    }
    this->items_in_hand = new_items;
    // add item to other monke
    monke->items_in_hand.push(item);
}

void Monke::yoink(int item, Monke* monke) 
{
    // remove item from other monke
    std::queue<long long> items = monke->items_in_hand;
    std::queue<long long> new_items;
    while (!items.empty()) {
        if (items.front() != item) {
            new_items.push(items.front());
        }
        items.pop();
    }
    monke->items_in_hand = new_items;
    // add item to this monke
    this->items_in_hand.push(item);
}

void Monke::inspect(std::vector<Monke> &monke_vector, bool manage_worry_level = true) 
{
    // inspect item
    while (!this->items_in_hand.empty()) {
        int item = this->items_in_hand.front();
        this->items_in_hand.pop();
        this->monke_inspection_count++;
        

        if (this->worry_level_multiplier_method == Meth::POTENZ) {
            item = item * item;
        }
        else if (this->worry_level_multiplier_method == Meth::MULTIPLY) {
            item = item * this->worry_level_multiplier;
        }
        else if (this->worry_level_multiplier_method == Meth::ADD) {
            item = item + this->worry_level_multiplier;
        }

        // monkey is done with inspection => worry level / 3
        manage_worry_level ? item = item / 3 : item = item;
        // test and yeet to correct monke
        if (item % this->divisible_test == 0) {
            this->yeet(item, &monke_vector[this->target_monkes.first]);
        }
        else {
            this->yeet(item, &monke_vector[this->target_monkes.second]);
        }
    }
}


int main(int argc, char** argv) 
{
    // read input file
    std::ifstream input("input/day11.txt");
    std::stringstream buffer;
    buffer << input.rdbuf();
    // split input at empty lines
    std::vector<std::string> lines = split_string(buffer.str(), "\n\n");
    // ^Monkey\s(\d):\n\s+Starting items: (\d+(, \d+)*)?\n\s+Operation: new = old\s(\*|\+)\s+(\d+)\n\s+Test: divisible by (\d+)\n\s+If true: throw to monkey\s(\d)\n\s+If false: throw to monkey (\d)$
    std::regex monke_regex ("^Monkey\\s(\\d):\\n\\s+Starting items: (\\d+(, \\d+)*)?\\n\\s+Operation: new = old\\s(\\*|\\+)\\s+(\\w+)\\n\\s+Test: divisible by (\\d+)\\n\\s+If true: throw to monkey\\s(\\d)\\n\\s+If false: throw to monkey (\\d)$");

    std::cout << part1(lines) << std::endl;

   /*  std::cout << "Day 11: Monkey in the middle" << std::endl;
    std::cout << "======================" << std::endl;
    // print input
    std::cout << "monke: " << buffer.str() << std::endl; */
}


long long part1(std::vector<std::string> lines) 
{
    std::regex monke_regex ("^Monkey\\s(\\d):\\n\\s+Starting items: (\\d+(, \\d+)*)?\\n\\s+Operation: new = old\\s(\\*|\\+)\\s+(\\w+)\\n\\s+Test: divisible by (\\d+)\\n\\s+If true: throw to monkey\\s(\\d)\\n\\s+If false: throw to monkey (\\d)$");
    std::vector<Monke> monke_vector;

    for (auto line : lines) {
        std::smatch monke_match;
        std::regex_search(line, monke_match, monke_regex);

        int target_monke_1 = std::stoi(monke_match[7]);
        int target_monke_2 = std::stoi(monke_match[8]);

        // show monkey info
        std::cout << "Monkey #" << monke_match[1] << std::endl;
        if (monke_match[2] != "") {
            std::cout << " with items: " << monke_match[2];
        }
        std::cout << " with operation: " << monke_match[4] << " " << monke_match[5] << std::endl;
        std::cout << " with test: " << monke_match[6] << std::endl;
        std::cout << " with target monke 1: " << monke_match[7] << std::endl;
        std::cout << " with target monke 2: " << monke_match[8] << std::endl;

        // parse into Monke class
        std::queue<long long> items;
        if (monke_match[2] != "") {
            std::vector<std::string> items_str = split_string(monke_match[2], ", ");
            for (auto item : items_str) {
                items.push(std::stoi(item));
            }
        }
        if (monke_match[5] == "old")
        {
            Monke monke = Monke(0, std::stoi(monke_match[6]), items, Meth::POTENZ, std::make_pair(target_monke_1, target_monke_2));
            monke_vector.push_back(monke);
        }
        else if (monke_match[4] == "+")
        {
            Monke monke = Monke(std::stoi(monke_match[5]), std::stoi(monke_match[6]), items, Meth::ADD, std::make_pair(target_monke_1, target_monke_2));
            monke_vector.push_back(monke);
        }
        else if (monke_match[4] == "*")
        {
            Monke monke = Monke(std::stoi(monke_match[5]), std::stoi(monke_match[6]), items, Meth::MULTIPLY, std::make_pair(target_monke_1, target_monke_2));
            monke_vector.push_back(monke);
        }
        else
        {
            std::cout << "Error: unknown method" << std::endl;
        } 
    
    }




    int i = 0;
    do  
    {
        for (int j = 0; j < monke_vector.size(); j++) 
        {
            monke_vector[j].inspect(monke_vector, true);

        }
        i++;
    } while ( i < 20);

    // last = 61200 | 67077 => wrong :( 

    // print monke state
    for (int i = 0; i < monke_vector.size(); i++) {
        std::cout << "Monke " << i << " has " 
        << monke_vector[i].items_in_hand.size() << " items" 
        << "and inspected " << monke_vector[i].get_monke_inspection_count() << " items" << std::endl;
        std::cout << "Monke #" << i << " has the following items: ";
        while (!monke_vector[i].items_in_hand.empty()) {
            std::cout << monke_vector[i].items_in_hand.front() << " ";
            monke_vector[i].items_in_hand.pop();
        }
        std::cout << std::endl;
    }

    // 2 largest counters
    std::sort(monke_vector.begin(), monke_vector.end(), [](Monke a, Monke b) { return a.get_monke_inspection_count() > b.get_monke_inspection_count(); });
    long long largest = monke_vector[0].get_monke_inspection_count();
    long long second_largest = monke_vector[1].get_monke_inspection_count();

    return largest * second_largest;
}





/**
 * ================================
 * Helper function section
 * ================================
*/


std::vector<std::string> split_string(const std::string& str,
                                      const std::string& delimiter)
{
    std::vector<std::string> strings;

    std::string::size_type pos = 0;
    std::string::size_type prev = 0;
    while ((pos = str.find(delimiter, prev)) != std::string::npos)
    {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + delimiter.size();
    }

    // To get the last substring (or only, if delimiter is not found)
    strings.push_back(str.substr(prev));

    return strings;
}