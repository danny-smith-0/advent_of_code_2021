#include <advent_of_code.h>

int main ()
{
    strings_t test_data = get_strings_from_file("../inputs/day8_test.txt");
    strings_t real_data = get_strings_from_file("../inputs/day8.txt");


    int results_test_1 = 0;
    int results_real_1 = 0;

    int results_test_2 = 0;
    int results_real_2 = 0;

    results(results_test_1, 0, results_real_1);
    results(results_test_2, 0, results_real_2);

    return 0;
}
