#include <advent_of_code.h>

static constexpr size_t size1 = 2;
static constexpr size_t size4 = 4;
static constexpr size_t size7 = 3;
static constexpr size_t size8 = 7;
// static constexpr size_t size = ;

struct InputLine
{
    strings_t before_delim;
    strings_t after_delim;
};

std::vector<InputLine> parse8(strings_t data)
{
    std::vector<InputLine> out_data;
    InputLine out_line;
    for (auto line : data)
    {
        strings_t before_and_after = substrings_to_strings(line, "|");
        out_line.before_delim = substrings_to_strings(before_and_after[0], " ");
        out_line.after_delim  = substrings_to_strings(before_and_after[1], " ");

        out_data.push_back(out_line);
    }
    return out_data;
}

int count_part_1(std::vector<InputLine> lines)
{
    int count = 0;
    for (auto line : lines)
    {
        for (auto entry : line.after_delim)
        {
            size_t sz = entry.size();
            if (sz == size1 || sz == size4 || sz == size7 || sz == size8)
            {
                ++count;
            }
        }
    }
    return count;
}
int main ()
{
    strings_t test_data = get_strings_from_file("../inputs/day8_test.txt");
    strings_t real_data = get_strings_from_file("../inputs/day8.txt");

    int results_test_1 = count_part_1(parse8(test_data));
    int results_real_1 = count_part_1(parse8(real_data));

    int results_test_2 = 0;
    int results_real_2 = 0;

    results(results_test_1, 26, results_real_1);
    results(results_test_2, 0, results_real_2);

    return 0;
}
