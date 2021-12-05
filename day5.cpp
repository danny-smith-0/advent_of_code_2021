#include <iostream> //std::cout
#include <fstream>  // std::ifstream
#include <string>
#include <sstream>
#include <vector>
#include <array>

#include <string_parser.h>

typedef std::vector<int> ints_t;

std::vector<ints_t> parse_day5()
{
    std::ifstream input ("../inputs/day_5_test.txt");

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

    static constexpr int max_dimension = 10;//00;
    std::array<std::array<int, max_dimension>, max_dimension> cells = {0};
    // cells[]
    for (auto set : sets_of_4_ints)
    {
        if (set[0] == set[2])
        {
            //add to cells
            int min = std::min(set[1], set[3]);
            int max = std::max(set[1], set[3]);
            for ( int ii = min; ii <= max; ++ii)
                cells.at(ii).at(set[0])++;
        }
        else if (set[1] == set[3])
        {
            //add to cells
            int min = std::min(set[0], set[2]);
            int max = std::max(set[0], set[2]);
            for ( int ii = min; ii <= max; ++ii)
                cells.at(set[1]).at(ii)++;
        }
    }

    for (auto rows : cells)
    {
        for (auto cell : rows)
        {
            if (cell == 0)
                std::cout << ".";
            else
                std::cout << cell;
        }
        std::cout << "\n";
    }



    return 0;
}
