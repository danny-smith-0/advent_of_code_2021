#include <advent_of_code.h>

bools_t_2d parse(strings_t strs, bools_t &algorithm)
{
    //First two lines are the algorithm and a blank line before the image
    bools_t_2d algorithm_2d = parse_pounds_and_decimals(strings_t(strs.begin(), strs.begin() + 1));
    algorithm = algorithm_2d[0];
    //Trim front and parse image
    strs = strings_t(strs.begin() + 2, strs.end());
    bools_t_2d out = parse_pounds_and_decimals(strs);
    return out;
}

sll part1(strings_t input)
{
    sll out = 0;
    return out;
}

sll part2(strings_t input)
{
    sll out = 0;
    return out;
}

int main ()
{
    std::string day_string = "20";
    std::cout << "Day " << day_string << std::endl;
    strings_t test_data = get_strings_from_file("../inputs/day" + day_string + "_test.txt");
    strings_t real_data = get_strings_from_file("../inputs/day" + day_string + ".txt");

    bools_t test_algo, real_algo;
    bools_t_2d test_image = parse(test_data, test_algo);
    bools_t_2d real_image = parse(real_data, real_algo);

    print_T_2d(bools_t_2d(1, test_algo)); std::cout << "\n";
    print_T_2d(test_image);
    std::cout << "\n";std::cout << "\n";

    print_T_2d(bools_t_2d(1, real_algo)); std::cout << "\n";
    print_T_2d(real_image);

    std::cout << "\nPart 1\n\n";
    sll results_test_1 = part1(test_data);
    sll expected_test_result_1 = 0;
    if (results(results_test_1, expected_test_result_1))
    {
        sll results_real_1 = part1(real_data);
        std::cout << "Real result is " << results_real_1 << std::endl;
    }

    std::cout << "\nPart 2\n\n";
    sll results_test_2 = part2(test_data);
    sll expected_test_result_2 = 0;
    if (results(results_test_2, expected_test_result_2))
    {
        sll results_real_2 = part2(real_data);
        std::cout << "Real result is " << results_real_2 << "\n\nFinished" << std::endl;
    }

    return 0;
}
