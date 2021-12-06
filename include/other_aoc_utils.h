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

#endif // OTHER_AOC_UTILS_H
