#include <iostream> //std::cout
#include <fstream>  // std::ifstream
#include <string>
#include <sstream>
#include <vector>

#include <string_parser.h>

typedef std::vector<int> ints_t;

std::vector<ints_t> parse_day5()
{
    std::ifstream input ("../inputs/day_5.txt");

    std::vector<ints_t> sets_of_4_ints;
    std::string line;
    while (std::getline(input, line))
    {
        strings_t two_pairs = substrings_to_strings(line, " -> ");
        ints_t x1y1x2y2 = substrings_to_ints(two_pairs.at(0) + "," + two_pairs.at(1), ",");
        sets_of_4_ints.push_back(x1y1x2y2);
    }


    for (auto set : sets_of_4_ints)
        std::cout << set[0] << "," << set[1] << " -> " << set[2] << "," << set[3] << "\n";

    return sets_of_4_ints;
}

int main ()
{
    std::vector<ints_t> sets_of_4_ints = parse_day5();


    int a = 1;


    return 0;
}
