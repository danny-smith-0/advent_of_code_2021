#include <advent_of_code.h>

struct ALU
{
    sll w = 0;
    sll x = 0;
    sll y = 0;
    sll z = 0;

    std::optional<sll> add(char elem, sll val)
    {
        switch (elem)
        {
            case 'w' : { w += val; return w; }
            case 'x' : { x += val; return x; }
            case 'y' : { y += val; return y; }
            case 'z' : { z += val; return z; }
            default : { std::cout << "BAD add\n"; return std::nullopt; }
        }
    }
    std::optional<sll> mul(char elem, sll val)
    {
        switch (elem)
        {
            case 'w' : { w *= val; return w; }
            case 'x' : { x *= val; return x; }
            case 'y' : { y *= val; return y; }
            case 'z' : { z *= val; return z; }
            default : { std::cout << "BAD mul\n"; return std::nullopt; }
        }
    }
    std::optional<sll> div(char elem, double long val)
    {
        if (val == 0) return std::nullopt;

        switch (elem)
        {
            case 'w' : { sll res = static_cast<sll>(std::trunc( static_cast<double>(w) / val)); w = res; return res; }
            case 'x' : { sll res = static_cast<sll>(std::trunc( static_cast<double>(x) / val)); x = res; return res; }
            case 'y' : { sll res = static_cast<sll>(std::trunc( static_cast<double>(y) / val)); y = res; return res; }
            case 'z' : { sll res = static_cast<sll>(std::trunc( static_cast<double>(z) / val)); z = res; return res; }
            default : { std::cout << "BAD div\n"; return std::nullopt; }
        }
    }
    std::optional<sll> mod(char elem, sll val)
    {
        if (val <= 0) return std::nullopt;

        switch (elem)
        {
            case 'w' : { sll res = w % val; w = res; return res; }
            case 'x' : { sll res = x % val; x = res; return res; }
            case 'y' : { sll res = y % val; y = res; return res; }
            case 'z' : { sll res = z % val; z = res; return res; }
            default : { std::cout << "BAD mod\n"; return std::nullopt; }
        }
    }
    std::optional<sll> eql(char elem, sll val)
    {
        switch (elem)
        {
            case 'w' : { sll res = w == val ? 1 : 0; w = res; return res; }
            case 'x' : { sll res = x == val ? 1 : 0; x = res; return res; }
            case 'y' : { sll res = y == val ? 1 : 0; y = res; return res; }
            case 'z' : { sll res = z == val ? 1 : 0; z = res; return res; }
            default : { std::cout << "BAD eql\n"; return std::nullopt; }
        }
    }
};

struct Inp
{
    strings_t strs;
};

std::vector<Inp> parse_inps(strings_t input)
{
    std::vector<Inp> out;
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
    }
    out.push_back(inp);
    return out;
}

void inp_to_ALU(Inp const& inp, sll w, ALU& alu)
{
    alu.w = w;
    for (auto instruction : inp.strs)
    {
        strings_t parts = substrings_to_strings(instruction, " ");

        sll b = 0;
        switch (parts[2][0])
        {
            case 'w': b = alu.w; break;
            case 'x': b = alu.x; break;
            case 'y': b = alu.y; break;
            case 'z': b = alu.z; break;
            default: b = std::stoll(parts[2]);
        }

        if (parts[0] == "add")
            alu.add(parts[1][0], b);
        else if (parts[0] == "mul")
            alu.mul(parts[1][0], b);
        else if (parts[0] == "div")
            alu.div(parts[1][0], static_cast<double>(b));
        else if (parts[0] == "mod")
            alu.mod(parts[1][0], b);
        else if (parts[0] == "eql")
            alu.eql(parts[1][0], b);
    }
}

sll part1(std::vector<Inp> inps)
{
    steady_clock::time_point t1 = steady_clock::now();
    sll biggest_number = 99999999999999;
    while (1)
    {
        if (biggest_number % 50000 == 0)
        {
            steady_clock::time_point t2 = steady_clock::now();
            duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
            std::cout << biggest_number << " - " << time_span.count() / 60. << "\n";
        }
        sll temp_biggest_number = biggest_number;
        ALU alu;
        for (auto inp = inps.begin(); inp < inps.end(); ++inp)
        {
            sll steps = std::distance(inps.begin(), inp);
            sll divisor = static_cast<sll>(pow(10, 13 - steps));
            sll w = temp_biggest_number / divisor;
            temp_biggest_number -= w * divisor;
            inp_to_ALU(*inp, w, alu);
        }
        if (alu.z == 0)
            break;
        else
            --biggest_number;
    }
    return biggest_number;
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
    std::vector<Inp> test = parse_inps(get_strings_from_file("../inputs/day" + day_string + "_test.txt"));
    std::vector<Inp> real = parse_inps(get_strings_from_file("../inputs/day" + day_string + ".txt"));

    std::cout << "\nPart 1\n\n";
    // sll results_test_1 = part1(test);
    // sll expected_test_result_1 = 0;
    if (results(0,0))//(results_test_1, expected_test_result_1))
    {
        sll results_real_1 = part1(real);
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
