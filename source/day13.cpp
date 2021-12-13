#include <advent_of_code.h>

struct InputData
{
    bools_t_2d dots;
    strings_t_2d folds;

    InputData(strings_t data) { parse13(data); }
    void parse13(strings_t data)
    {
        bool collect_dots_not_folds = true;
        ints_t_2d coords;
        int max_x = 0;
        int max_y = 0;
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
                for (int diff = 1; diff < fold_line; ++diff)
                {
                    row[fold_line - diff] = row[fold_line - diff] || row[fold_line + diff];
                    row[fold_line + diff] = false;
                }
            }
        }
        if (fold[0] == "y")
        {
            int fold_line = std::stoi(fold[1]);

            for (size_t ii = 0; ii < dots[0].size(); ++ii)
            {
                for (int diff = 1; diff < fold_line; ++diff)
                {
                    dots[fold_line - diff][ii] = dots[fold_line - diff][ii] || dots[fold_line + diff][ii];
                    dots[fold_line + diff][ii] = false;
                }
            }
        }
    }

    void do_all_folds()
    {
        while (!folds.empty())
        {
            this->fold();
        }
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
    // print_T_2d(test.dots);
    std::cout << count_bools_t_2d(real.dots) << "\n";

    test.fold();
    real.fold();

    int results_test_1 = count_bools_t_2d(test.dots);
    int results_real_1 = count_bools_t_2d(real.dots); //866 is too high;

    test.do_all_folds();
    print_T_2d(test.dots);

    int results_test_2 = 0;
    int results_real_2 = 0;

    results(results_test_1, 17, results_real_1);
    results(results_test_2, 0, results_real_2);

    return 0;
}
