#include <advent_of_code.h>

bool enhance_flipper = false;

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

std::string row_string(bools_t_2d const& padded_input, size_t row, size_t col, std::string infinte /* 0 or 1*/)
{
    bool first_col = col == 0;
    bool last_col = col == padded_input.size() - 1; //assumes square

    std::string binstr;
    if (first_col)
        binstr += infinte;
    else
        binstr += padded_input[row][col - 1] ? "1" : "0";

    binstr += padded_input[row][col] ? "1" : "0";

    if (last_col)
        binstr += infinte;
    else
        binstr += padded_input[row][col + 1] ? "1" : "0";

    return binstr;
}

bool get_pixel(bools_t_2d const& padded_input, size_t row, size_t col, bools_t const& algorithm, std::string infinte)
{
    std::string binstr;
    bool top_row = row == 0;
    bool bot_row = row == padded_input.size() - 1;

    // Top row
    if (top_row)
        binstr += infinte + infinte + infinte;
    else
        binstr += row_string(padded_input, row - 1, col, infinte);

    // Middle row
    binstr += row_string(padded_input, row, col, infinte);

    // Bottom row
    if (bot_row)
        binstr += infinte + infinte + infinte;
    else
        binstr += row_string(padded_input, row + 1, col, infinte);

    size_t value = static_cast<size_t>(binstring_to_value(binstr));
    return algorithm[value];
}


bools_t_2d enhance_image(bools_t_2d const& input_image, bools_t const& algorithm, std::string infinite)
{
    //Pad the input. The output will have two more rows and columns than the input
    bool pad_bool = infinite == "1";
    bools_t empty_row (input_image.size() + 2, pad_bool);
    bools_t_2d padded_input;
    padded_input.push_back(empty_row);
    for (auto line : input_image)
    {
        bools_t new_line (2, pad_bool);
        new_line.insert(new_line.begin() + 1, line.begin(), line.end());
        padded_input.push_back(new_line);
    }
    padded_input.push_back(empty_row);


    bools_t_2d output (padded_input.size(), bools_t(padded_input.size(), pad_bool));
    for (size_t ii = 0; ii < output.size(); ++ii)
        for (size_t jj = 0; jj < output[ii].size(); ++jj)
            output[ii][jj] = get_pixel(padded_input, ii, jj, algorithm, infinite);

    enhance_flipper = !enhance_flipper;
    return output;
}

sll part1(bools_t_2d const& input_image, bools_t const& algorithm)
{
    bools_t_2d output1 = enhance_image(input_image, algorithm, "0");
    bools_t_2d output2 = enhance_image(output1, algorithm, algorithm[0] ? "1" : "0");
    return count_bools_t_2d(output2);
}

sll part2(bools_t_2d const& input_image, bools_t const& algorithm)
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

    std::cout << "\nPart 1\n\n";
    sll results_test_1 = part1(test_image, test_algo);
    sll expected_test_result_1 = 35;
    if (results(results_test_1, expected_test_result_1))
    {
        sll results_real_1 = part1(real_image, real_algo); //5431 and 5368 are too high
        std::cout << "Real result is " << results_real_1 << std::endl;
    }

    std::cout << "\nPart 2\n\n";
    sll results_test_2 = part2(test_image, test_algo);
    sll expected_test_result_2 = 0;
    if (results(results_test_2, expected_test_result_2))
    {
        sll results_real_2 = part2(real_image, real_algo);
        std::cout << "Real result is " << results_real_2 << "\n\nFinished" << std::endl;
    }

    return 0;
}
