#include <advent_of_code.h>

int step_octo_grid(ints_t_2d* octo_grid)
{

    static constexpr size_t max_n = 10;
    if(octo_grid->size() != max_n || octo_grid->at(0).size() != max_n)
        return 0;

    bools_t_2d already_flashed (max_n, bools_t(max_n, false));

    //increment everything
    for (size_t ii = 0; ii < max_n; ++ii)
        for (size_t jj = 0; jj < max_n; ++jj)
            ++octo_grid->at(ii)[jj];

    //Flash everything
    static constexpr int flash_cutoff = 9;
    for (size_t ii = 0; ii < max_n; )
    {
        for (size_t jj = 0; jj < max_n; )
        {
            if (!already_flashed[ii][jj] && octo_grid->at(ii)[jj] > flash_cutoff)
            {
                already_flashed[ii][jj] = true;
                bool on_top_row =    ii == 0;
                bool on_bottom_row = ii == max_n - 1;
                bool on_left_col =   jj == 0;
                bool on_right_col =  jj == max_n - 1;

                if (on_top_row)
                {
                    if (on_left_col)
                    {
                        ++octo_grid->at(ii + 1)[jj    ];
                        ++octo_grid->at(ii + 1)[jj + 1];
                        ++octo_grid->at(ii    )[jj + 1];
                    }
                    else if (on_right_col)
                    {
                        ++octo_grid->at(ii    )[jj - 1];
                        ++octo_grid->at(ii + 1)[jj - 1];
                        ++octo_grid->at(ii + 1)[jj    ];
                    }
                    else
                    {
                        ++octo_grid->at(ii    )[jj - 1];
                        ++octo_grid->at(ii + 1)[jj - 1];
                        ++octo_grid->at(ii + 1)[jj    ];
                        ++octo_grid->at(ii + 1)[jj + 1];
                        ++octo_grid->at(ii    )[jj + 1];
                    }
                }
                else if (on_bottom_row)
                {
                    if (on_left_col)
                    {
                        ++octo_grid->at(ii - 1)[jj    ];
                        ++octo_grid->at(ii - 1)[jj + 1];
                        ++octo_grid->at(ii    )[jj + 1];
                    }
                    else if (on_right_col)
                    {
                        ++octo_grid->at(ii    )[jj - 1];
                        ++octo_grid->at(ii - 1)[jj - 1];
                        ++octo_grid->at(ii - 1)[jj    ];
                    }
                    else
                    {
                        ++octo_grid->at(ii    )[jj - 1];
                        ++octo_grid->at(ii - 1)[jj - 1];
                        ++octo_grid->at(ii - 1)[jj    ];
                        ++octo_grid->at(ii - 1)[jj + 1];
                        ++octo_grid->at(ii    )[jj + 1];
                    }
                }
                else
                {
                    if (on_left_col)
                    {
                        ++octo_grid->at(ii + 1)[jj    ];
                        ++octo_grid->at(ii + 1)[jj + 1];
                        ++octo_grid->at(ii    )[jj + 1];
                        ++octo_grid->at(ii - 1)[jj + 1];
                        ++octo_grid->at(ii - 1)[jj    ];
                    }
                    else if (on_right_col)
                    {
                        ++octo_grid->at(ii - 1)[jj    ];
                        ++octo_grid->at(ii - 1)[jj - 1];
                        ++octo_grid->at(ii    )[jj - 1];
                        ++octo_grid->at(ii + 1)[jj - 1];
                        ++octo_grid->at(ii + 1)[jj    ];
                    }
                    else
                    {
                        ++octo_grid->at(ii - 1)[jj - 1];
                        ++octo_grid->at(ii    )[jj - 1];
                        ++octo_grid->at(ii + 1)[jj - 1];
                        ++octo_grid->at(ii + 1)[jj    ];
                        ++octo_grid->at(ii + 1)[jj + 1];
                        ++octo_grid->at(ii    )[jj + 1];
                        ++octo_grid->at(ii - 1)[jj + 1];
                        ++octo_grid->at(ii - 1)[jj    ];
                    }
                }

                //Move back to the first square affected by the flash
                ii = (ii > 0) ? ii - 1 : ii;
                jj = (jj > 0) ? jj - 1 : jj;
            }
            else
            {
                ++jj;
                if (jj == max_n)
                    ++ii;
            }
        }
    }

    // Wrap around
    int count1 = 0;
    for (size_t ii = 0; ii < max_n; ++ii)
        for (size_t jj = 0; jj < max_n; ++jj)
        {
            if (octo_grid->at(ii)[jj] > flash_cutoff)
            {
                if (!already_flashed[ii][jj])
                    std::cout << "Whoops! A\n";
                octo_grid->at(ii)[jj] = 0;
                ++count1;
            }
            else if (already_flashed[ii][jj])
                std::cout << "Whoops! B\n";
        }

    // Count flashed
    int count_flashed = 0;//already_flashed
    return count1;
}

int part2(ints_t_2d grid)
{
    int woah_too_many = 10000;
    int step_where_100_flash = 0;
    for ( ; step_where_100_flash < woah_too_many; ++step_where_100_flash)
    {
        if (step_octo_grid(&grid) == 100)
            break;
    }
    return step_where_100_flash + 1;
}
int main ()
{
    std::string day_string = "11";
    strings_t test_data = get_strings_from_file("../inputs/day" + day_string + "_test.txt");
    strings_t real_data = get_strings_from_file("../inputs/day" + day_string + ".txt");
    std::cout << "Day " << day_string << std::endl;

    ints_t_2d test_grid = strings_of_digits_to_ints(test_data);
    ints_t_2d real_grid = strings_of_digits_to_ints(real_data);

    int iterations = 100;
    int results_test_1 = 0;;
    int results_real_1 = 0;
    for (int ii = 0; ii < iterations; ++ii)
    {
        results_test_1 += step_octo_grid(&test_grid);
        results_real_1 += step_octo_grid(&real_grid);
    }
    // print_T_2d(test_grid);

    //reset
    test_grid = strings_of_digits_to_ints(test_data);
    real_grid = strings_of_digits_to_ints(real_data);

    int results_test_2 = part2(test_grid);
    int results_real_2 = part2(real_grid);



    results(results_test_1, 1656, results_real_1);
    results(results_test_2, 195, results_real_2);

    return 0;
}
