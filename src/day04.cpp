#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <tuple>

int part01(std::vector<std::string>);
int part02(std::vector<std::string>);
std::vector<std::string> split(std::string str, char delimiter);
template <typename T>
bool vector_contains_another(std::vector<T> A, std::vector<T> B);
bool vec_intersect(std::vector<int> A, std::vector<int> B);

int main(int argc, char** argv) {
    // read input file input/day04.txt
    std::ifstream input("input/day04.txt");
    std::string line;
    std::vector<std::string> lines;
    while (std::getline(input, line)) {
        lines.push_back(line);
    }
    std::cout << "Day 04: Camp Cleanup" << std::endl;
    std::cout << "===================" << std::endl;
    //std::cout << "Part 1: " << part01(lines) << std::endl;
    std::cout << "Part 2: " << part02(lines) << std::endl;


}

int part01(std::vector<std::string> input) {
    std::vector<int> overlapping_areas;
                           /* Elf 1's area */  /* Elf 2's area */
    std::vector<std::tuple<std::vector<int>, std::vector<int>>> areas;
    int current_index = 0;
    for (auto line : input) {
        std::string elf1 = split(line, ',')[0];
        std::string elf2 = split(line, ',')[1];
        std::vector<int> elf1_areas;
        std::vector<int> elf2_areas;
        int elf1_area_start = std::stoi(split(elf1, '-')[0]);
        int elf1_area_end   = std::stoi(split(elf1, '-')[1]);

        if (elf1_area_start != elf1_area_end) {
            for (int i = elf1_area_start; i <= elf1_area_end; i++) {
                elf1_areas.push_back(i);
            }
        } else {
            elf1_areas.push_back(elf1_area_start);
        }

        // same for elf2
        int elf2_area_start = std::stoi(split(elf2, '-')[0]);
        int elf2_area_end   = std::stoi(split(elf2, '-')[1]);

        if (elf2_area_start != elf2_area_end) {
            for (int i = elf2_area_start; i <= elf2_area_end; i++) {
                elf2_areas.push_back(i);
            }
        } else {
            elf2_areas.push_back(elf2_area_start);
        }
        areas.push_back(std::make_tuple(elf1_areas, elf2_areas));
    };

    for (auto area : areas) {
        std::vector<int> elf1_areas = std::get<0>(area);
        std::vector<int> elf2_areas = std::get<1>(area);
        
        if (vector_contains_another(elf1_areas, elf2_areas)) {
            overlapping_areas.push_back(elf1_areas[0]);
        } else if (vector_contains_another(elf2_areas, elf1_areas)) {
            overlapping_areas.push_back(elf2_areas[0]);
        }

    }

    return overlapping_areas.size();
};

int part02(std::vector<std::string> input) {
    std::vector<int> overlapping_areas;
                           /* Elf 1's area */  /* Elf 2's area */
    std::vector<std::tuple<std::vector<int>, std::vector<int>>> areas;
    int current_index = 0;
    for (auto line : input) {
        std::string elf1 = split(line, ',')[0];
        std::string elf2 = split(line, ',')[1];
        std::vector<int> elf1_areas;
        std::vector<int> elf2_areas;
        int elf1_area_start = std::stoi(split(elf1, '-')[0]);
        int elf1_area_end   = std::stoi(split(elf1, '-')[1]);

        if (elf1_area_start != elf1_area_end) {
            for (int i = elf1_area_start; i <= elf1_area_end; i++) {
                elf1_areas.push_back(i);
            }
        } else {
            elf1_areas.push_back(elf1_area_start);
        }

        // same for elf2
        int elf2_area_start = std::stoi(split(elf2, '-')[0]);
        int elf2_area_end   = std::stoi(split(elf2, '-')[1]);

        if (elf2_area_start != elf2_area_end) {
            for (int i = elf2_area_start; i <= elf2_area_end; i++) {
                elf2_areas.push_back(i);
            }
        } else {
            elf2_areas.push_back(elf2_area_start);
        }
        areas.push_back(std::make_tuple(elf1_areas, elf2_areas));
    };

    for (auto area : areas) {
        std::vector<int> elf1_areas = std::get<0>(area);
        std::vector<int> elf2_areas = std::get<1>(area);

        
        int index = 0;

        if (vec_intersect(elf1_areas, elf2_areas)) {
            if (!vector_contains_another(overlapping_areas, elf1_areas)) {
                overlapping_areas.push_back(index);
            }
        }
        index++;

    }

    return overlapping_areas.size();
};

/*

-------------------- Helper Functions --------------------

*/




std::vector<std::string> split(std::string str, char delimiter) {
    std::vector<std::string> internal;


    while(str.find(delimiter) != std::string::npos) {
        internal.push_back(str.substr(0, str.find(delimiter)));
        str = str.substr(str.find(delimiter) + 1, str.length());
    }

    internal.push_back(str);

    return internal;
}

template <typename T>
bool vector_contains_another(std::vector<T> A, std::vector<T> B) {
    std::sort (A.begin(), A.end());
    std::sort (B.begin(), B.end());
    return std::includes(A.begin(), A.end(), B.begin(), B.end());
}


/*
 Thank you StackOverflow for this snippet <3
*/
bool vec_intersect(std::vector<int> A, std::vector<int> B) {
    std::sort(A.begin(), A.end());
    std::sort(B.begin(), B.end());

    if (A.size() == 1) {
        return std::binary_search(B.begin(), B.end(), A[0]);
    } else if (B.size() == 1) {
        return std::binary_search(A.begin(), A.end(), B[0]);
    }


    std::vector<int> v_intersection;
    std::set_intersection(A.begin(), A.end(), B.begin(), B.end(), std::back_inserter(v_intersection));
    


    return v_intersection.size() > 0;
}