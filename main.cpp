#include <iostream> //std::cout
#include <fstream>  // std::ifstream
#include <string>
#include <sstream>
#include <vector>

#include <string_parser.h>

typedef std::vector<int> ints_t;

struct BingoSquare
{
    std::vector<ints_t> rows;
    std::vector<ints_t> cols;

    void create_cols_from_rows()
    {
        if (rows.size() != 5)
        {
            std::cout << "Failed row to col conversion";
            return;
        }
        for (int ii = 0; ii < 5; ++ii)
        {
            ints_t col;
            col.push_back(rows[0][ii]);
            col.push_back(rows[1][ii]);
            col.push_back(rows[2][ii]);
            col.push_back(rows[3][ii]);
            col.push_back(rows[4][ii]);
            cols.push_back(col);
        }
    }

    bool bingo(ints_t rands)
    {
        std::vector<ints_t> both;
        both.insert(both.end(), rows.begin(), rows.end());
        both.insert(both.end(), cols.begin(), cols.end());

        for (auto thing : both)
        {
            int remaining_to_match = thing.size();
            for (auto roll : rands)
            {
                if (std::find(thing.begin(), thing.end(), roll) != thing.end())
                {
                    --remaining_to_match;
                    if(remaining_to_match  < 1)
                        return true;
                }
            }
        }
        return false;
    }
    
    ints_t all_values()
    {
        ints_t values;
        for (auto row : rows)
            values.insert(values.end(), row.begin(), row.end());
        return values;
    }

    int sum_values_not_found(ints_t to_find)
    {
        int sum = 0;
        ints_t values = this->all_values();
        for (auto value : values)
        {
            if(std::find(to_find.begin(), to_find.end(), value) == to_find.end())
                sum += value;
        }
        return sum;
    }
};

int main ()
{
    std::ifstream input ("C:/Users/danny/OneDrive/Coding/advent_of_coding/cpp/inputs/day_4.txt");

    std::string line;
    std::getline( input, line); //Get the random draws
    // std::cout << "size: " << line.size() << ", " << line << std::endl;
    ints_t rands = substrings_to_ints(line, ",");

    std::vector<BingoSquare> squares;
    BingoSquare square;
    int num_rows = 5;
    int count = 0;
    while (std::getline( input, line))
    {
        // std::cout << "size: " << line.size() << ", " << line << std::endl;
        if(count++ == 0)
            continue;
        
        square.rows.push_back(substrings_to_ints(line, " "));

        if(count > num_rows)
        {
            square.create_cols_from_rows();
            squares.push_back(square);
            square = BingoSquare();
            count = 0;
        }        
    }


    for (size_t ii = 1; ii < rands.size(); ++ii)
    {
        ints_t current_rands(rands.begin(), rands.begin() + ii);
        int counter = 0;
        // for (auto square : squares)
        // for (auto square_iter = squares.begin() ; square_iter != squares.end(); ++square_iter)
        for (auto square_iter = squares.begin() ; square_iter != squares.end(); )
        {   
            if(square_iter->bingo(current_rands))
            {
                int unmarked_score = square_iter->sum_values_not_found(current_rands); 
                int last_draw = current_rands.at(current_rands.size() - 1);
                std::cout << unmarked_score << " * " << last_draw << " = " << unmarked_score * last_draw << std::endl;
                //911 * 96 = 87456
                // return 0;
                square_iter = squares.erase(square_iter);
            }
            else
                ++square_iter;
        }
    }

    return 0;
}
