#include <advent_of_code.h>

struct InputData
{
    bools_t_2d dots;
    strings_t_2d folds;

    InputData(strings_t data) { parse(data); }

    void parse(strings_t data)
    {
        bool collect_dots_not_folds = true;
        ints_t_2d coords;
        int max_x = 0;
        int max_y = 0;
        //Get coords (to become dots) & folds
        for (auto str : data)
        {
            if (str.empty()) // At the empty line, switch input collection
            {
                collect_dots_not_folds = false;
                continue;
            }
            if (collect_dots_not_folds)
            {
                ints_t coord = substrings_to_ints(str, ",");
                max_x = coord[0] > max_x ? coord[0] : max_x;
                max_y = coord[1] > max_y ? coord[1] : max_y;
                coords.push_back(coord);
            }
            else
            {
                std::string scrubbed = str.substr(11);
                folds.push_back( substrings_to_strings( scrubbed, "="));
            }
        }

        dots = bools_t_2d(max_y + 1, bools_t(max_x + 1, false));
        for (auto coord : coords)
        {
            dots[coord[1]][coord[0]] = true;
        }

    }

    void fold()
    {
        strings_t fold = folds.front();
        folds.erase(folds.begin());

        if (fold[0] == "x")
        {
            int fold_line = std::stoi(fold[1]);

            for (auto& row : dots)
            {
                for (int diff = 1; diff <= fold_line; ++diff)
                {
                    if (fold_line + diff > static_cast<int>(row.size()) - 1)
                        break;
                    row[fold_line - diff] = row[fold_line - diff] || row[fold_line + diff];
                }
                // Remove columns to the right of the fold
                row = bools_t(row.begin(), row.begin() + fold_line);
            }
        }
        if (fold[0] == "y")
        {
            int fold_line = std::stoi(fold[1]);

            for (size_t ii = 0; ii < dots[0].size(); ++ii)
            {
                for (int diff = 1; diff <= fold_line; ++diff)
                {
                    if (fold_line + diff > static_cast<int>(dots.size()) - 1)
                        break;
                    dots[fold_line - diff][ii] = dots[fold_line - diff][ii] || dots[fold_line + diff][ii];
                }
            }
            //Remove row below the fold
            dots = bools_t_2d(dots.begin(), dots.begin() + fold_line);
        }
    }

    void do_all_folds()
    {
        while (!folds.empty())
            this->fold();
    }
};

int main ()
{
    std::string day_string = "13";
    strings_t test_data = get_strings_from_file("../inputs/day" + day_string + "_test.txt");
    strings_t real_data = get_strings_from_file("../inputs/day" + day_string + ".txt");
    std::cout << "Day " << day_string << std::endl;

    InputData test(test_data);
    InputData real(real_data);

    //Part 1
    test.fold();
    real.fold();

    int results_test_1 = count_bools_t_2d(test.dots);
    int results_real_1 = count_bools_t_2d(real.dots); //866 is too high;
    results(results_test_1, 17, results_real_1);

    //Part 2
    test.do_all_folds();
    bool with_comma = false;
    bool null_is_space = true;
    std::cout << std::endl;
    print_T_2d(test.dots, with_comma, null_is_space);

    real.do_all_folds();
    print_T_2d(real.dots, with_comma, null_is_space);

    // 1111 1  1  11  1  1  11  1111 1  1  11
    //    1 1 1  1  1 1  1 1  1 1    1  1 1  1
    //   1  11   1  1 1  1 1    111  1  1 1
    //  1   1 1  1111 1  1 1    1    1  1 1
    // 1    1 1  1  1 1  1 1  1 1    1  1 1  1
    // 1111 1  1 1  1  11   11  1     11   11

    return 0;
}
