#include <iostream>
#include <string>
#include <queue>
#include <regex>
#include <fstream>
#include <optional>


std::vector<std::string> split_string(const std::string& str,
                                      const std::string& delimiter);
void part1(std::vector<std::string> lines, std::vector<std::pair<int, int>> bitch_ass_monkes);
void part2(std::vector<std::string> lines, std::vector<std::pair<int, int>> bitch_ass_monkes);
enum Meth {
    ADD = '+',
    MULTIPLY = '*',
    POTENZ = '^'
};


class Monke {
    public: 
        Monke(int multiplier, int divisible, std::queue<int> items, Meth meth, std::tuple<int, int> target_monkes);
        ~Monke();
        std::queue<int> items_in_hand;
        int worry_level_multiplier;
        Meth worry_level_multiplier_method;
        int divisible_test;
        std::tuple<int, int> target_monkes;
        int get_monke_inspection_count() { return monke_inspection_count; }
        void yeet(int item, Monke* monke);
        void yoink(int item, Monke* monke);
        void inspect(std::vector<Monke> &monke_vector);
        int monke_inspection_count;
};

Monke::Monke(int multiplier, int divisible, std::queue<int> items, Meth meth, std::tuple<int, int> target_monkes) {
    this->worry_level_multiplier = multiplier;
    this->divisible_test = divisible;
    this->items_in_hand = items;
    this->worry_level_multiplier_method = meth;
    this->monke_inspection_count = 0;
}

Monke::~Monke() 
{
}



void Monke::yeet(int item, Monke* monke) 
{
    // remove item from this monke
    std::queue<int> items = this->items_in_hand;
    std::queue<int> new_items;
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
    std::queue<int> items = monke->items_in_hand;
    std::queue<int> new_items;
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

void Monke::inspect(std::vector<Monke> &monke_vector) 
{
    // inspect item
    while (!this->items_in_hand.empty()) {
        int item = this->items_in_hand.front();
        this->items_in_hand.pop();
        this->monke_inspection_count++;
        
        std::cout << "monke inspect item w/ worry lvl " << item << std::endl;

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
        item = item / 3;
        // test and yeet to correct monke
        if (item % this->divisible_test == 0) {
            std::cout << "monke yeet item to " << std::get<0>(this->target_monkes) << std::endl;
            this->yeet(item, &monke_vector[std::get<0>(this->target_monkes)]);
        }
        else {
            std::cout << "monke yeet item to " << std::get<1>(this->target_monkes) << std::endl;
            this->yeet(item, &monke_vector[std::get<1>(this->target_monkes)]);
        }
    }
}


int main(int argc, char** argv) 
{
    std::vector<std::pair<int, int>> bitch_ass_monkes;
    // read input file
    std::ifstream input("input/day11.txt");
    std::stringstream buffer;
    buffer << input.rdbuf();
    // split input at empty lines
    std::vector<std::string> lines = split_string(buffer.str(), "\n\n");
    // ^Monkey\s(\d):\n\s+Starting items: (\d+(, \d+)*)?\n\s+Operation: new = old\s(\*|\+)\s+(\d+)\n\s+Test: divisible by (\d+)\n\s+If true: throw to monkey\s(\d)\n\s+If false: throw to monkey (\d)$
    std::regex monke_regex ("^Monkey\\s(\\d):\\n\\s+Starting items: (\\d+(, \\d+)*)?\\n\\s+Operation: new = old\\s(\\*|\\+)\\s+(\\w+)\\n\\s+Test: divisible by (\\d+)\\n\\s+If true: throw to monkey\\s(\\d)\\n\\s+If false: throw to monkey (\\d)$");

    part1(lines, bitch_ass_monkes);

   /*  std::cout << "Day 11: Monkey in the middle" << std::endl;
    std::cout << "======================" << std::endl;
    // print input
    std::cout << "monke: " << buffer.str() << std::endl; */
}


void part1(std::vector<std::string> lines, std::vector<std::pair<int, int>> bitch_ass_monkes) 
{
    std::regex monke_regex ("^Monkey\\s(\\d):\\n\\s+Starting items: (\\d+(, \\d+)*)?\\n\\s+Operation: new = old\\s(\\*|\\+)\\s+(\\w+)\\n\\s+Test: divisible by (\\d+)\\n\\s+If true: throw to monkey\\s(\\d)\\n\\s+If false: throw to monkey (\\d)$");
    std::vector<Monke> monke_vector;

    for (auto line : lines) {
        std::smatch monke_match;
        std::regex_search(line, monke_match, monke_regex);

        std::cout << "match 7: " << monke_match[7] << std::endl;
        std::cout << "match 8: " << monke_match[8] << std::endl;
        std::cout << "match 7 as int: " << std::stoi(monke_match[7]) << std::endl;
        std::cout << "match 8 as int: " << std::stoi(monke_match[8]) << std::endl;
        int target_monke_1 = std::stoi(monke_match[7]);
        int target_monke_2 = std::stoi(monke_match[8]);
        std::cout << "target_monke_1: " << target_monke_1 << std::endl;
        std::cout << "target_monke_2: " << target_monke_2 << std::endl;
        bitch_ass_monkes.push_back(std::make_pair(
            target_monke_1, target_monke_2
        ));

        // parse into Monke class
        std::queue<int> items;
        if (monke_match[2] != "") {
            std::vector<std::string> items_str = split_string(monke_match[2], ", ");
            for (auto item : items_str) {
                items.push(std::stoi(item));
            }
        }
        if (monke_match[4] == "*" || monke_match[5] == "old")
        {
            Monke monke = Monke(0, std::stoi(monke_match[6]), items, Meth::POTENZ, std::make_tuple(target_monke_1, target_monke_2));
            monke_vector.push_back(monke);
        }
        else if (monke_match[4] == "+")
        {
            Monke monke = Monke(std::stoi(monke_match[5]), std::stoi(monke_match[6]), items, Meth::ADD, std::make_tuple(target_monke_1, target_monke_2));
            monke_vector.push_back(monke);
        }
        else if (monke_match[4] == "*")
        {
            Monke monke = Monke(std::stoi(monke_match[5]), std::stoi(monke_match[6]), items, Meth::MULTIPLY, std::make_tuple(target_monke_1, target_monke_2));
            monke_vector.push_back(monke);
        }
        else
        {
            std::cout << "Error: unknown method" << std::endl;
        } 
    
    }


    // show bitch ass monkes
    for (int i; i < bitch_ass_monkes.size(); i++) {
        std::cout << "Monke " << i << " throws to " << std::get<0>(bitch_ass_monkes[i]) << " and " << std::get<1>(bitch_ass_monkes[i]) << std::endl;

    }

/*     for (auto monke : monke_vector) {

        monke.inspect(monke_vector);
    } */

    // print monke state
    for (int i = 0; i < monke_vector.size(); i++) {
        std::cout << "Monke " << i << " has " 
            << monke_vector[i].items_in_hand.size() << " items in hand " 
            "and inspected " << monke_vector[i].get_monke_inspection_count() << " items" << std::endl; 
    }
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