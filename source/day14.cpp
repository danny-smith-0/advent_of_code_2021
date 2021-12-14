#include <advent_of_code.h>

strings_t_2d parse(strings_t input, std::string& polymer)
{
    polymer = input.at(0);
    input.erase(input.begin()); //clear polymer
    input.erase(input.begin()); //and the blank line

    strings_t_2d rules;
    for (auto str : input)
    {
        strings_t rule = substrings_to_strings(str, " -> ");
        rule.erase(rule.begin() + 1); //remove arrow
        rules.push_back(rule);
    }
    return rules;
}

sll part1(std::string polymer, strings_t_2d rules, size_t nn)
{
    sll out = 0;

    std::map<size_t, strings_t> to_insert;
    // std::vector<size_t> str_itrs;
    for (auto rule : rules)
    {
        std::string pair = rule[0];
        // std::string to_insert = rule[1];
        size_t pos = polymer.find(pair);
        to_insert[pos] = rule;
    }


    for (std::map<size_t, strings_t>::reverse_iterator riter = to_insert.rbegin(); riter != to_insert.rend(); ++riter)
    {
        size_t pos = riter->first;
        if (pos != std::string::npos)
        {
            strings_t rule = riter->second;
            polymer.insert(pos + 1, rule[1]);
        }
    }
    return out;
}

sll part2(strings_t_2d input)
{
    sll out = 0;
    return out;
}

int main ()
{
    std::string day_string = "14";
    std::cout << "Day " << day_string << std::endl;
    strings_t test_data = get_strings_from_file("../inputs/day" + day_string + "_test.txt");
    strings_t real_data = get_strings_from_file("../inputs/day" + day_string + ".txt");

    std::string polymer_test;
    std::string polymer_real;

    strings_t_2d test_rules = parse(test_data, polymer_test);
    strings_t_2d real_rules = parse(real_data, polymer_real);

    sll results_test_1 = part1(polymer_test, test_rules);
    sll results_real_1 = part1(polymer_real, real_rules);
    sll expected_test_result_1 = 0;

    sll results_test_2 = part2(test_rules);
    sll results_real_2 = part2(real_rules);
    sll expected_test_result_2 = 0;

    results(results_test_1, expected_test_result_1, results_real_1);
    results(results_test_2, expected_test_result_2, results_real_2);

    return 0;
}
