#include <advent_of_code.h>

struct Chunks
{
    int count_0x28 = 0; // ( - 28, ) - 29
    int count_0x3C = 0; // < - 3C, > - 3E
    int count_0x5B = 0; // [ - 5B, ] - 5D
    int count_0x7B = 0; // { = 7B, / - 7D

    std::string opened;
    char last_opened()
    {
        return opened.size() > 0 ?  opened.at(opened.size() - 1) : 0;
    }

    void open_chunk(char in)
    {
        switch (in)
        {
            case '(': { ++count_0x28; opened.push_back(in); break; }
            case '<': { ++count_0x3C; opened.push_back(in); break; }
            case '[': { ++count_0x5B; opened.push_back(in); break; }
            case '{': { ++count_0x7B; opened.push_back(in); break; }
            default:  std::cout << "fail\n";
        }
    }

    void close_chunk(char in)
    {
        switch (in)
        {
            case ')': { --count_0x28; opened.pop_back(); break; }
            case '>': { --count_0x3C; opened.pop_back(); break; }
            case ']': { --count_0x5B; opened.pop_back(); break; }
            case '}': { --count_0x7B; opened.pop_back(); break; }
            default:  std::cout << "fail\n";
        }
    }
};

bool is_open_char(char in)  { return in == '(' || in == '<' || in == '[' || in == '{'; }
bool is_close_char(char in) { return in == ')' || in == '>' || in == ']' || in == '}'; }

bool closes_last(char last, char closer)
{
    switch (last)
    {
        case '(': return closer == ')';
        case '<': return closer == '>';
        case '[': return closer == ']';
        case '{': return closer == '}';
        default:  std::cout << "fail\n";
    }
    return false;
}

bool closes_last(Chunks chunk, char closer)
{
    return closes_last(chunk.last_opened(), closer);
}

int score_closer(char in)
{
    switch (in)
    {
        case ')': { return     3; }
        case ']': { return    57; }
        case '}': { return  1197; }
        case '>': { return 25137; }
        default:  std::cout << "fail\n";
    }
    return 0;
}

int part1(strings_t input)
{
    int score = 0;
    int debug_line = -1;
    for (auto str : input)
    {
        ++debug_line;
        int debug_col = -1;
        Chunks chunks;
        bool success = true;
        for (auto my_char : str)
        {
            ++debug_col;
            if (is_open_char(my_char))
                chunks.open_chunk(my_char);
            else if (is_close_char(my_char))
            {
                if (closes_last(chunks, my_char))
                    chunks.close_chunk(my_char);
                else
                {
                    success = false;
                    int old_score = score;
                    int add_to_score = score_closer(my_char);
                    score += add_to_score;
                    std::cout << "Line " << debug_line << " ERROR. Remaining: " << chunks.opened << ". Input: " << my_char << /*"\n" <<*/ " at column " << debug_col << "";
                    std::cout << ". Score: " << old_score << " + " << add_to_score << " = " << score << "\n";
                    break;
                }

            }
            else
                std::cout << "whoops! (" << debug_line << ", " << debug_col << "\n";
        }
        if (success) { std::cout << "Line " << debug_line << " done.  Remaining: " << chunks.opened << "\n"; }
    }
    return score;
}

int main ()
{
    std::string day_string = "10";
    strings_t test_data = get_strings_from_file("../inputs/day" + day_string + "_test.txt");
    strings_t real_data = get_strings_from_file("../inputs/day" + day_string + ".txt");
    std::cout << "Day " << day_string << std::endl;


    std::cout << "test stuff: \n";
    int results_test_1 = part1(test_data);
    std::cout << "\nreal stuff: \n";
    int results_real_1 = part1(real_data);

    int results_test_2 = 0;
    int results_real_2 = 0;

    results(results_test_1, 26397, results_real_1); //266517 is too low
    results(results_test_2, 0, results_real_2);

    return 0;
}
