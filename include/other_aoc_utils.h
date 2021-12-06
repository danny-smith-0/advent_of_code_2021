#ifndef OTHER_AOC_UTILS_H
#define OTHER_AOC_UTILS_H

typedef std::vector<int> ints_t;

ints_t matlab_colon(int first, int last)
{
    int incr = first < last ? 1 : -1;
    ints_t vector;
    for (int ii = first; ; ii += incr)
    {
        vector.push_back(ii);
        if ( ii == last)
            break;
    }
    return vector;
}

template <typename T>
void results(T test_result, T expected_test_result, T real_result)
{
    std::cout << "Test result is " << test_result;
    if (test_result == expected_test_result)
    {
        std::cout << ". Passed!\n";
        std::cout << "Real result is " << real_result << std::endl;
    }
    else
        std::cout << ". Failed. Looking for " << expected_test_result << "\n";
}

#endif // OTHER_AOC_UTILS_H
