#include <advent_of_code.h>

struct ALU
{
    sll w = 0;
    sll x = 0;
    sll y = 0;
    sll z = 0;

    void add(char elem, sll val)
    {
        switch (elem)
        {
            case 'w' : w += val;
            case 'x' : x += val;
            case 'y' : y += val;
            case 'z' : z += val;
            default : { std::cout << "BAD add\n"; }
        }
    }

    void mul(char elem, sll val)
    {
        switch (elem)
        {
            case 'w' : w *= val;
            case 'x' : x *= val;
            case 'y' : y *= val;
            case 'z' : z *= val;
            default : { std::cout << "BAD mul\n"; }
        }
    }

    void div(char elem, sll val)
    {
        switch (elem)
        {
            case 'w' : w = static_cast<sll>(std::trunc( static_cast<double>(w) / static_cast<double>(val) ));
            case 'x' : x = static_cast<sll>(std::trunc( static_cast<double>(x) / static_cast<double>(val) ));
            case 'y' : y = static_cast<sll>(std::trunc( static_cast<double>(y) / static_cast<double>(val) ));
            case 'z' : z = static_cast<sll>(std::trunc( static_cast<double>(z) / static_cast<double>(val) ));
            default : { std::cout << "BAD div\n"; }
        }
    }
};

struct Inp
{
    strings_t strs;
};

std::vector<Inp> parse(strings_t input)
{
    std::vector<Inp> out;// = strings_of_digits_to_ints(input);
    Inp inp;
    for (auto line : input)
    {
        if (line[0] == 'i' && line[1] == 'n' && line[2] == 'p')
        {
            if (!inp.strs.empty())
                out.push_back(inp);
            inp = Inp();
            continue;
        }
        inp.strs.push_back(line);
        // for (auto my_char : line) {}
    }
    out.push_back(inp);
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
    std::string day_string = "24";
    std::cout << "Day " << day_string << std::endl;
    strings_t test_data = get_strings_from_file("../inputs/day" + day_string + "_test.txt");
    strings_t real_data = get_strings_from_file("../inputs/day" + day_string + ".txt");
    std::vector<Inp> test      = parse(get_strings_from_file("../inputs/day" + day_string + "_test.txt"));
    std::vector<Inp> real      = parse(get_strings_from_file("../inputs/day" + day_string + ".txt"));

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
