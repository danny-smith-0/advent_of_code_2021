#include <advent_of_code.h>

std::map<std::string, strings_t_2d> parse()
{
    std::map<std::string, strings_t_2d> all_options;
    return all_options;
}

sll part1(strings_t data)
{
    sll out = 0;
    return out;
}

sll part2(strings_t data)
{
    sll out = 0;
    return out;
}

int main ()
{
    std::string day_string = "12";
    strings_t test_dat1 = get_strings_from_file("../inputs/day" + day_string + "_test_1.txt");
    strings_t test_dat2 = get_strings_from_file("../inputs/day" + day_string + "_test_2.txt");
    strings_t test_dat3 = get_strings_from_file("../inputs/day" + day_string + "_test_3.txt");
    strings_t real_data = get_strings_from_file("../inputs/day" + day_string + ".txt");
    std::cout << "Day " << day_string << std::endl;


    sll results_test_1 = part1(test_dat1); sll expected_test_result_1 = 10;
    // sll results_test_1 = part1(test_dat2); sll expected_test_result_1 = 19;
    // sll results_test_1 = part1(test_dat3); sll expected_test_result_1 = 226;
    sll results_real_1 = part1(real_data);


    sll results_test_2 = part2(test_dat1); sll expected_test_result_2 = 0;
    sll results_real_2 = part2(real_data);


    results(results_test_1, expected_test_result_1, results_real_1);
    results(results_test_2, expected_test_result_2, results_real_2);

    return 0;
}
