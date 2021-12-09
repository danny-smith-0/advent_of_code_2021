#include <advent_of_code.h>

bools_t_2d bools2d_less_than_9(ints_t_2d matrix)
{
    bools_t_2d bool_matrix;
    for (size_t ii = 0; ii < matrix.size() ; ++ii)\
    {
        bools_t bool_row;
        for (size_t jj = 0; jj < matrix[ii].size(); ++jj)
        {
            bool_row.push_back(matrix[ii][jj] < 9);
            // std::cout << (matrix[ii][jj] < 9);// << ',';
        }
        bool_matrix.push_back(bool_row);
        // std::cout << std::endl;
    }
    return bool_matrix;
}

bool less_than_adjacent(ints_t_2d matrix, size_t row_idx, size_t col_idx)
{
    //Assumes a non-empty square
    if (matrix.empty() || matrix.size() < row_idx + 1 || matrix[0].size() < col_idx + 1)
        return false;

    bool less = false;
    size_t max_row_idx = matrix.size() - 1;
    size_t max_col_idx = matrix[0].size() - 1;

    int value = matrix[row_idx][col_idx];

    bool compare_up    = (row_idx >           0) ? matrix[row_idx - 1][col_idx] > value : true;
    bool compare_down  = (row_idx < max_row_idx) ? matrix[row_idx + 1][col_idx] > value : true;
    bool compare_left  = (col_idx >           0) ? matrix[row_idx][col_idx - 1] > value : true;
    bool compare_right = (col_idx < max_col_idx) ? matrix[row_idx][col_idx + 1] > value : true;

    return compare_up && compare_down && compare_left && compare_right;
}

int part1(ints_t_2d matrix)
{
    int risk = 0;
    for (size_t ii = 0; ii < matrix.size() ; ++ii)
    {
        for (size_t jj = 0; jj < matrix[ii].size(); ++jj)
        {
            if (less_than_adjacent(matrix, ii, jj))
            {
                risk += matrix[ii][jj] + 1;
                // std::cout << "local pt found at (" << (int)ii << ", " << (int)jj << "): " << matrix[ii][jj];
                // std::cout << ". risk = " << matrix[ii][jj] + 1 << ". Total risk = " << risk << std::endl;
            }
        }
    }
    return risk;
}

bool adjacent_is_zero(ints_t_2d matrix, size_t row_idx, size_t col_idx, std::string direction)
{
    //Assumes a non-empty square
    if (matrix.empty() || matrix.size() < row_idx + 1 || matrix[0].size() < col_idx + 1)
        return false;

    bool zero = false;
    size_t max_row_idx = matrix.size() - 1;
    size_t max_col_idx = matrix[0].size() - 1;

    int value = matrix[row_idx][col_idx];

    bool compare_up    = (row_idx >           0) ? matrix[row_idx - 1][col_idx] > value : true;
    bool compare_down  = (row_idx < max_row_idx) ? matrix[row_idx + 1][col_idx] > value : true;
    bool compare_left  = (col_idx >           0) ? matrix[row_idx][col_idx - 1] > value : true;
    bool compare_right = (col_idx < max_col_idx) ? matrix[row_idx][col_idx + 1] > value : true;

    return compare_up && compare_down && compare_left && compare_right;
}

bool not_in_basin_yet(std::vector<coords_t> coords_2d, size_t ii, size_t jj)
{
    return std::find(coords_2d.begin(), coords_2d.end(), coords_t(ii, jj)) == coords_2d.end();
}

int part2(bools_t_2d map)
{
    bools_t_2d already_checked (map.size(), bools_t(map[0].size(), false)) ;

    size_t max_row_idx = map.size() - 1;
    size_t max_col_idx = map[0].size() - 1;

    std::array<size_t, 3> max_basins = {0}; //0 is smallest, 1 is middle, 2 is biggest
    for (size_t ii = 0; ii < map.size() ; ++ii)
    {
        for (size_t jj = 0; jj < map[ii].size(); ++jj)
        {
            if(!already_checked[ii][jj] && map[ii][jj])
            {
                //Build basin
                std::vector<coords_t> coords_in_basin;
                coords_in_basin.push_back( coords_t(ii, jj));
                for(size_t index = 0; index < coords_in_basin.size(); ++index)
                {
                    auto hi =coords_in_basin[index];
                    auto world2 = hi.first;
                    size_t i = coords_in_basin[index].first;
                    size_t j = coords_in_basin[index].second;
                    if(i > 0           && not_in_basin_yet(coords_in_basin, i - 1, j) && map[i - 1][j])
                    {
                        coords_in_basin.push_back(coords_t(i - 1, j));
                        already_checked[i - 1][j] = true;
                    }
                    if(i < max_row_idx && not_in_basin_yet(coords_in_basin, i + 1, j) && map[i + 1][j])
                    {
                        coords_in_basin.push_back(coords_t(i + 1, j));
                        already_checked[i + 1][j] = true;
                    }
                    if(j > 0           && not_in_basin_yet(coords_in_basin, i, j - 1) && map[i][j - 1])
                    {
                        coords_in_basin.push_back(coords_t(i, j - 1));
                        already_checked[i][j - 1] = true;
                    }
                    if(j < max_col_idx && not_in_basin_yet(coords_in_basin, i, j + 1) && map[i][j + 1])
                    {
                        coords_in_basin.push_back(coords_t(i, j + 1));
                        already_checked[i][j + 1] = true;
                    }
                }
                size_t basin_size = coords_in_basin.size();

                if(basin_size > max_basins[2])
                {
                    max_basins[0] = max_basins[1];
                    max_basins[1] = max_basins[2];
                    max_basins[2] = basin_size;
                }
                else if(basin_size > max_basins[1])
                {
                    max_basins[0] = max_basins[1];
                    max_basins[1] = basin_size;
                }
                else if(basin_size > max_basins[0])
                {
                    max_basins[0] = basin_size;
                }
            }
            // std::cout << (map[ii][jj] < 9);
        }
        // std::cout << std::endl;
    }
    return max_basins[0] * max_basins[1] * max_basins[2];
}

ints_t_2d parse9(strings_t input)
{
    ints_t_2d out;
    for (auto number_string : input)
    {
        ints_t line;
        for (auto digit : number_string)
        {
            line.push_back(digit - '0'); //Find distance from the char for zero.
            // std::cout << digit - '0';
        }
        out.push_back(line);
        // std::cout << std::endl;
    }
    return out;
}

int main ()
{
    strings_t test_data = get_strings_from_file("../inputs/day9_test.txt");
    strings_t real_data = get_strings_from_file("../inputs/day9.txt");

    parse9(test_data);

    // int results_test_1 = part1(parse9(test_data));
    // int results_real_1 = part1(parse9(real_data));

    // bools_t_2d hi = bools2d_less_than_9(parse9(test_data));
    // bools2d_less_than_9(parse9(real_data));
    int results_test_2 = part2(bools2d_less_than_9(parse9(test_data)));
    int results_real_2 = part2(bools2d_less_than_9(parse9(real_data)));

    // results(results_test_1, 15, results_real_1);
    results(results_test_2, 1134, results_real_2);

    return 0;
}
