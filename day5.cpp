#include <iostream> //std::cout
#include <fstream>  // std::ifstream
#include <string>
#include <sstream>
#include <vector>
#include <array>

#include <string_parser.h>

typedef std::vector<int> ints_t;

// int max_value = 0;
int count_2s = 0;

ints_t matlab_colon(int first, int last)
{
    int incr = first < last ? 1 : -1;
    ints_t vector;
    for (int ii = first; ; ii += incr)
    {
        vector.push_back(ii);
        if ( ii == last)
            break;
    }
    return vector;
}

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

int main ()
{
    {
        // std::vector<ints_t> sets_of_4_ints = parse_day5();

        // static constexpr int max_dimension = 1000;
        // std::array<std::array<uint8_t, max_dimension>, max_dimension> cells = {0};
        // // std::array<std::array<uint8_t, max_dimension>, max_dimension> cells2 = {0};

        // for (auto set : sets_of_4_ints)
        // {
        //     // //Only horizontal & vertical
        //     // if (set[0] == set[2])
        //     // {
        //     //     //add to cells
        //     //     int min = std::min(set[1], set[3]);
        //     //     int max = std::max(set[1], set[3]);
        //     //     for ( int ii = min; ii <= max; ++ii)
        //     //     {
        //     //         cells[ii][set[0]]++;
        //     //         int cell_value = cells[ii][set[0]];
        //     //         // check_and_count_max(cell_value);
        //     //         if (cell_value == 2)
        //     //             count_2s++;
        //     //     }
        //     // }
        //     // else if (set[1] == set[3])
        //     // {
        //     //     //add to cells
        //     //     int min = std::min(set[0], set[2]);
        //     //     int max = std::max(set[0], set[2]);
        //     //     for ( int ii = min; ii <= max; ++ii)
        //     //     {
        //     //         cells[set[1]][ii]++;
        //     //         int cell_value = cells[set[1]][ii];
        //     //         // check_and_count_max(cell_value);
        //     //         if (cell_value == 2)
        //     //             count_2s++;
        //     //     }
        //     // }

        //     ints_t xs = matlab_colon(set[0], set[2]);
        //     ints_t ys = matlab_colon(set[1], set[3]);
        //     if (xs.size() == 1 && ys.size() > 1)
        //         xs = ints_t(ys.size(), xs[0]);
        //     if (ys.size() == 1 && xs.size() > 1)
        //         ys = ints_t(xs.size(), ys[0]);
        //     if (ys.size() != xs.size())
        //         std::cout << "Size error!\n";
        //     int kk = set[0];
        //     for (int ii = 0; ii < xs.size() ; ++ii)
        //     {
        //         int cell_value = ++cells[ys[ii]][xs[ii]];
        //         if (cell_value == 2)
        //                 count_2s++;
        //     }
        // }

        // std::cout << "\n\n" << /*"max_value: " << max_value << ", " <<*/ count_2s << " times" << "\n\n";

        // // Plot
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
    }

    // ints_t fishys = {3,4,3,1,2};
    ints_t fishys = {5,1,2,1,5,3,1,1,1,1,1,2,5,4,1,1,1,1,2,1,2,1,1,1,1,1,2,1,5,1,1,1,3,1,1,1,3,1,1,3,1,1,4,3,1,1,4,1,1,1,1,2,1,1,1,5,1,1,5,1,1,1,4,4,2,5,1,1,5,1,1,2,2,1,2,1,1,5,3,1,2,1,1,3,1,4,3,3,1,1,3,1,5,1,1,3,1,1,4,4,1,1,1,5,1,1,1,4,4,1,3,1,4,1,1,4,5,1,1,1,4,3,1,4,1,1,4,4,3,5,1,2,2,1,2,2,1,1,1,2,1,1,1,4,1,1,3,1,1,2,1,4,1,1,1,1,1,1,1,1,2,2,1,1,5,5,1,1,1,5,1,1,1,1,5,1,3,2,1,1,5,2,3,1,2,2,2,5,1,1,3,1,1,1,5,1,4,1,1,1,3,2,1,3,3,1,3,1,1,1,1,1,1,1,2,3,1,5,1,4,1,3,5,1,1,1,2,2,1,1,1,1,5,4,1,1,3,1,2,4,2,1,1,3,5,1,1,1,3,1,1,1,5,1,1,1,1,1,3,1,1,1,4,1,1,1,1,2,2,1,1,1,1,5,3,1,2,3,4,1,1,5,1,2,4,2,1,1,1,2,1,1,1,1,1,1,1,4,1,5};

    static constexpr int days = 256;

    for ( int ii = 0; ii < days; ++ii)
    {
        int count_add = 0;
        static constexpr int max = 6;
        for ( auto& fish : fishys)
        {
            --fish;
            if (fish < 0)
            {
                ++count_add;
                fish = max;
            }
        }
        ints_t baby_fish (count_add, 8);
        fishys.insert(fishys.end(), baby_fish.begin(), baby_fish.end());

        // for ( auto fish : fishys)
        //     std::cout << fish << ",";
        // std::cout << std::endl;
        std::cout << "\nafter " << ii << " days, num fish: " << fishys.size();
    }

    // for ( auto fish : fishys)
        // std::cout << fish << ",";
    std::cout << "\nnum fish: " << fishys.size();

    return 0;
}
