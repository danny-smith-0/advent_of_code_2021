#include <advent_of_code.h>

bool steps(strings_t& sea_floor)
{
    size_t num_rows = sea_floor.size();
    size_t num_cols = sea_floor[0].size();
    bool moved = false;

    // east
    for (size_t ii = 0; ii < num_rows; ++ii)
    {
        char orig_first_char = sea_floor[ii][0];
        for (size_t jj = 0; jj < num_cols; )
        {
            char& this_one = sea_floor[ii][jj];
            char& next_one  = jj != num_cols - 1 ? sea_floor[ii][jj + 1] : sea_floor[ii][0];
            char check_next = jj != num_cols - 1 ? sea_floor[ii][jj + 1] : orig_first_char;
            if ( this_one == '>' && check_next == '.')
            {
                this_one = '.';
                next_one = '>';
                moved = true;
                jj += 2;
            }
            else
                ++jj;
        }
    }

    // south
    for (size_t jj = 0; jj < num_cols; ++jj)
    {
        char orig_first_char = sea_floor[0][jj];
        for (size_t ii = 0; ii < num_rows; )
        {
            char& this_one = sea_floor[ii][jj];
            char& next_one  = ii != num_rows - 1 ? sea_floor[ii + 1][jj] : sea_floor[0][jj];
            char check_next = ii != num_rows - 1 ? sea_floor[ii + 1][jj] : orig_first_char;
            if ( this_one == 'v' && check_next == '.')
            {
                this_one = '.';
                next_one = 'v';
                moved = true;
                ii += 2;
            }
            else
                ++ii;
        }
    }

    return moved;
}

sll part1(strings_t sea_floor)
{
    sll count_steps = 0;
    bool moving_cucumbers = true;
    sll safety = 1000000; // Change based on empirical results
    while (moving_cucumbers && count_steps < safety)
    {
        moving_cucumbers = steps(sea_floor);
        ++count_steps;
    }
    return count_steps;
}

int main ()
{
    std::string day_string = "25";
    std::cout << "Day " << day_string << std::endl;
    strings_t test_data = get_strings_from_file("../inputs/day" + day_string + "_test.txt");
    strings_t real_data = get_strings_from_file("../inputs/day" + day_string + ".txt");

    std::cout << "\nPart 1\n\n";
    sll results_test_1 = part1(test_data);
    sll expected_test_result_1 = 58;
    if (results(results_test_1, expected_test_result_1))
    {
        sll results_real_1 = part1(real_data);
        std::cout << "Real result is " << results_real_1 << std::endl;
    }


    return 0;
}
