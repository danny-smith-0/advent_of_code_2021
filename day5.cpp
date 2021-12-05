#include <iostream> //std::cout
#include <fstream>  // std::ifstream
#include <string>
#include <sstream>
#include <vector>
#include <array>

#include <string_parser.h>

typedef std::vector<int> ints_t;

int max_value = 0;
int count_max = 0;

std::vector<ints_t> parse_day5()
{
    // std::ifstream input ("../inputs/day_5_test.txt");
    std::ifstream input ("../inputs/day_5.txt");

    std::vector<ints_t> sets_of_4_ints;
    std::string line;
    while (std::getline(input, line))
    {
        strings_t two_pairs = substrings_to_strings(line, " -> ");
        ints_t x1y1x2y2 = substrings_to_ints(two_pairs.at(0) + "," + two_pairs.at(1), ",");
        sets_of_4_ints.push_back(x1y1x2y2);
    }

    //Succesfully recreates the input strings. No bug here.
    // for (auto set : sets_of_4_ints)
        // std::cout << set[0] << "," << set[1] << " -> " << set[2] << "," << set[3] << "\n";

    return sets_of_4_ints;
}

void check_and_count_max(int cell_value)
{
    if ( cell_value > max_value)
    {
        max_value = cell_value;
        count_max = 1;
    }
    else if (cell_value == max_value)
    {
        count_max++;
    }
}

int main ()
{
    std::vector<ints_t> sets_of_4_ints = parse_day5();

    static constexpr int max_dimension = 1000;
    std::array<std::array<uint8_t, max_dimension>, max_dimension> cells = {0};
    // std::array<std::array<uint8_t, max_dimension>, max_dimension> cells2 = {0};
    // cells[]
    for (auto set : sets_of_4_ints)
    {
        if (set[0] == set[2])
        {
            //add to cells
            int min = std::min(set[1], set[3]);
            int max = std::max(set[1], set[3]);
            for ( int ii = min; ii <= max; ++ii)
            {
                cells[ii][set[0]]++;
                int cell_value = cells[ii][set[0]];
                check_and_count_max(cell_value);

            }
        }
        else if (set[1] == set[3])
        {
            //add to cells
            int min = std::min(set[0], set[2]);
            int max = std::max(set[0], set[2]);
            for ( int ii = min; ii <= max; ++ii)
            {
                cells[set[1]][ii]++;
                int cell_value = cells[set[1]][ii];
                check_and_count_max(cell_value);
            }
        }
    }

    std::cout << "\n\n" << "max_value: " << max_value << ", " << count_max << " times" << "\n\n";

    //Plot
    // std::ofstream out("out.txt");
    // for (auto rows : cells)
    // {
    //     for (auto cell : rows)
    //     {
    //         if (cell == 0)
    //         {
    //             // std::cout << ".";
    //             out << "0,";
    //         }
    //         else
    //         {
    //             // std::cout << static_cast<int>(cell);// << " ";
    //             out << static_cast<int>(cell) << ",";
    //         }
    //     }
    //     // std::cout << "\n";
    //     out << "\n";
    // }

    return 0;
}
