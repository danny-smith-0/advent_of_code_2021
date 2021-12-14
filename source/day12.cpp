#include <advent_of_code.h>

typedef std::map<std::string, strings_t> option_map_t;

option_map_t parse(strings_t data)
{
    option_map_t all_options;
    for (auto str : data)
    {
        strings_t pair = substrings_to_strings(str, "-");
        all_options[pair[0]].push_back(pair[1]);
        all_options[pair[1]].push_back(pair[0]);
    }

    //Don't go anywhere from "end:"
    all_options.erase(all_options.find("end"));
    for (auto& options : all_options)
    {
        std::sort(options.second.begin(), options.second.end());
    }

    return all_options;
}

void remove_lower_case_option(std::string option_to_remove, option_map_t& all_options)
{
    for (auto& options_pair : all_options)
    {
        strings_t& options = options_pair.second;
        auto iter_to_remove = std::find(options.begin(), options.end(), option_to_remove);
        if (iter_to_remove != options.end())
        {
            options.erase(iter_to_remove);
        }
    }
}

sll part1(option_map_t all_options)
{
    // No place needs to return to start
    remove_lower_case_option("start", all_options); //edited by reference

    sll out = 0;
    return out;
}

sll part2(option_map_t all_options)
{
    sll out = 0;
    return out;
}

int main ()
{
    std::string day_string = "12";
    std::cout << "Day " << day_string << std::endl;
    strings_t test_dat1 = get_strings_from_file("../inputs/day" + day_string + "_test_1.txt");
    strings_t test_dat2 = get_strings_from_file("../inputs/day" + day_string + "_test_2.txt");
    strings_t test_dat3 = get_strings_from_file("../inputs/day" + day_string + "_test_3.txt");
    strings_t real_data = get_strings_from_file("../inputs/day" + day_string + ".txt");

    option_map_t tst1_options = parse(test_dat1);
    option_map_t tst2_options = parse(test_dat2);
    option_map_t tst3_options = parse(test_dat3);
    option_map_t real_options = parse(real_data);

    sll results_test_1 = part1(tst1_options); sll expected_test_result_1 = 10;
    // sll results_test_1 = part1(tst2_options); sll expected_test_result_1 = 19;
    // sll results_test_1 = part1(tst3_options); sll expected_test_result_1 = 226;
    sll results_real_1 = part1(real_options);


    sll results_test_2 = part2(tst1_options); sll expected_test_result_2 = 0;
    sll results_real_2 = part2(real_options);


    results(results_test_1, expected_test_result_1, results_real_1);
    results(results_test_2, expected_test_result_2, results_real_2);

    return 0;
}
