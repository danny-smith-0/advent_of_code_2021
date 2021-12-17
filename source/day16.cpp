#include <advent_of_code.h>


strings_t parse(strings_t input)
{
    strings_t out;
    std::stringstream bin_ss;
    for (auto line : input)
    {
        for (auto hexchar : line)
            bin_ss << hexchar_to_binstring(hexchar);
        out.push_back(bin_ss.str());
    }
    return out;
}

ull parse_type4(std::string binstr)
{
    return 0;
}

void parse_binstring(std::string binstr)
{

    ull pkt_ver     = binstring_to_value(binstr.substr(0,3)); // 0,1,2
    ull pkt_type_id = binstring_to_value(binstr.substr(3,3)); // 3,4,5
    binstring_to_value("011111100101");
}

sll part1(strings_t input)
{
    for (auto binstr : input)
    {
        parse_binstring(binstr);
    }
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
    std::string day_string = "16";
    std::cout << "Day " << day_string << std::endl;
    strings_t test_data = parse(get_strings_from_file("../inputs/day" + day_string + "_test.txt"));
    strings_t real_data = parse(get_strings_from_file("../inputs/day" + day_string + ".txt"));


    sll results_test_1 = part1(test_data);
    sll results_real_1 = part1(real_data);
    sll expected_test_result_1 = 0;

    results(results_test_1, expected_test_result_1, results_real_1);

    sll results_test_2 = part2(test_data);
    sll results_real_2 = part2(real_data);
    sll expected_test_result_2 = 0;

    results(results_test_2, expected_test_result_2, results_real_2);

    return 0;
}
