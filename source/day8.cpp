#include <advent_of_code.h>

/*
  0:      1:      2:      3:      4:
 aaaa    ....    aaaa    aaaa    ....
b    c  .    c  .    c  .    c  b    c
b    c  .    c  .    c  .    c  b    c
 ....    ....    dddd    dddd    dddd
e    f  .    f  e    .  .    f  .    f
e    f  .    f  e    .  .    f  .    f
 gggg    ....    gggg    gggg    ....

  5:      6:      7:      8:      9:
 aaaa    aaaa    aaaa    aaaa    aaaa
b    .  b    .  .    c  b    c  b    c
b    .  b    .  .    c  b    c  b    c
 dddd    dddd    ....    dddd    dddd
.    f  e    f  .    f  e    f  .    f
.    f  e    f  .    f  e    f  .    f
 gggg    gggg    ....    gggg    gggg

 top, top-left, bottom-left, bottom, bottom-right, top-right, center
 000000. - 6
 2.22.22 - 5
 3..3333 - 5
 55.55.5 - 5
 66666.6 - 6
 99.9999 - 6

 ....11. - 2
 .4..444 - 4
 7...77. - 3
 8888888 - 7
*/

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
        for(auto& entry : out_line.after_delim)
            std::sort(entry.begin(), entry.end());
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
                ++count;
        }
    }
    return count;
}

bool does_string_have_char(std::string str, char c)
{
    return str.find(c) != std::string::npos;
}

strings_t strings_without_this_char(strings_t inputs, char c)
{
    strings_t out;
    for (auto str : inputs)
        if (!does_string_have_char(str, c))
            out.push_back(str);
    return out;
}

strings_t map_input_strings(InputLine line)
{
    strings_t map (10, "");

    //first pass
    strings_t remaining_strings;
    for (auto& entry : line.before_delim)
    {
        std::sort(entry.begin(), entry.end());
        size_t sz = entry.size();
        if (sz == size1)
            map[1] = entry;
        else if (sz == size4)
            map[4] = entry;
        else if (sz == size7)
            map[7] = entry;
        else if (sz == size8)
            map[8] = entry;
        else
            remaining_strings.push_back(entry);
    }

    //find zero - Find the only string that doesn't have the center line. This is the only line only 1 of the remaining dont have.
    char center_char = '.';
    for (auto c : map[8])
    {
        //Whoops. The bottom right in 2 is also uniquely gone in the remaining values. Patch with ignoring chars found in 1.
        if (c == map[1][0] || c == map[1][1])
            continue;
        strings_t strs_w_o = strings_without_this_char(remaining_strings, c);
        if (strs_w_o.size() == 1)
        {
            map[0] = strs_w_o[0];
            remaining_strings.erase(std::find(remaining_strings.begin(), remaining_strings.end(), strs_w_o[0]));
            center_char = c;
            break;
        }
    }

    //find six - the only remaining string (2,3,5,6,9) size 6 AND missing only one of the chars is 1
    char top_right_char = '.';
    for (auto c : map[1])
    {
        bool found_it = false;
        strings_t strs_w_o = strings_without_this_char(remaining_strings, c);
        for (auto str : strs_w_o)
        {
            if( str.size() == 6)
            {
                map[6] = str;
                remaining_strings.erase(std::find(remaining_strings.begin(), remaining_strings.end(), str));
                top_right_char = c;
                found_it = true;
                break;
            }
        }
        if (found_it)
            break;
    }

    //find nine - only remaining input (2,3,5,9) size 6
    for (strings_t::iterator str_itr = remaining_strings.begin(); str_itr != remaining_strings.end(); ++str_itr)
    {
        if(str_itr->size() == 6)
        {
            map[9] = *str_itr;
            str_itr = remaining_strings.erase(str_itr);
            break;
        }
    }

    //find five - of remaining (2,3,5), only 5 doesn't have the top right char
    strings_t strs_w_o_char6 = strings_without_this_char(remaining_strings, top_right_char);
    map[5] = strs_w_o_char6[0];
    remaining_strings.erase(std::find(remaining_strings.begin(), remaining_strings.end(), strs_w_o_char6[0]));

    // only 2 and 3 remain. 2 is the one that's missing one of the chars from 1.
    for (auto c : map[1])
    {
        strings_t strs_w_o = strings_without_this_char(remaining_strings, c);
        if (strs_w_o.size() == 1)
        {
            map[2] = strs_w_o[0];
            remaining_strings.erase(std::find(remaining_strings.begin(), remaining_strings.end(), strs_w_o[0]));
            break;
        }
    }
    map[3] = remaining_strings[0];
    return map;
}

int get_four_digit_Code(strings_t line, strings_t map)
{
    if(line.size() != 4)
        return 0;

    int code = 0;
    for (size_t digit = 0; digit < map.size(); ++digit)
    {
        if(line[0] == map[digit])
            code += 1000 * digit;
        if(line[1] == map[digit])
            code +=  100 * digit;
        if(line[2] == map[digit])
            code +=   10 * digit;
        if(line[3] == map[digit])
            code +=    1 * digit;
    }
    return code;
}

int sum_part2(std::vector<InputLine> lines)
{
    int sum = 0;
    for (auto line : lines)
    {
        strings_t map = map_input_strings(line);
        sum += get_four_digit_Code(line.after_delim, map);
    }
    return sum;
}

int main ()
{
    strings_t test_data = get_strings_from_file("../inputs/day8_test.txt");
    strings_t real_data = get_strings_from_file("../inputs/day8.txt");

    int results_test_1 = count_part_1(parse8(test_data));
    int results_real_1 = count_part_1(parse8(real_data));

    int results_test_2 = sum_part2(parse8(test_data));
    int results_real_2 = sum_part2(parse8(real_data));

    results(results_test_1, 26, results_real_1);
    results(results_test_2, 61229, results_real_2);

    return 0;
}
