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

    for (size_t ii = 0; ii < nn; ++ii)
    {
        std::map<size_t, strings_t> to_insert;
        for (auto rule : rules)
        {
            std::string pair = rule[0];
            size_t pos = 0;
            bool found_a_match = false;
            while (1)
            {
                size_t start_pos = found_a_match ? pos + 1 : pos;
                pos = polymer.find(pair, start_pos);
                if (pos != std::string::npos)
                {
                    to_insert[pos] = rule;
                    found_a_match = true;
                }
                else
                    break;
            }
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
        std::cout << "step " << ii + 1 << ". length: " << polymer.size();
        if (polymer.size() < 100) { std::cout << " " << polymer; }
        std::cout << std::endl;
    }

    std::vector<sll> counts;


    std::string unique_chars = polymer;
    std::sort(unique_chars.begin(), unique_chars.end());
    auto last = std::unique(unique_chars.begin(), unique_chars.end());
    unique_chars.erase(last, unique_chars.end());

    for (auto my_char : unique_chars)
        counts.push_back(std::count(polymer.begin(), polymer.end(), my_char));
    std::sort(counts.begin(), counts.end());

    sll min = counts[0];
    sll max = counts.at(counts.size() - 1);
    sll diff = max - min;
    std::cout << max << " - " << min << " = " << diff << "\n";
    return diff;
}

sll part2(std::string polymer, strings_t_2d rules, size_t nn)
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

    sll results_test_1 = part1(polymer_test, test_rules, 10);
    sll results_real_1 = part1(polymer_real, real_rules, 10);
    sll expected_test_result_1 = 1588;

    sll results_test_2 = part2(polymer_test, test_rules, 21);
    sll results_real_2 = part2(polymer_test, test_rules, 21);
    sll expected_test_result_2 = 2188189693529;

    results(results_test_1, expected_test_result_1, results_real_1); //1207 is too low. Its 2590. I'd tailored the method too close to the test.
    results(results_test_2, expected_test_result_2, results_real_2);

    return 0;
}
