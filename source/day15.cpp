#include <advent_of_code.h>

ints_t_2d parse(strings_t const& input)
{
    return strings_of_digits_to_ints(input);
}

sll score_path(coords_t_vec const& path, ints_t_2d const& map)
{
    sll score = 0;
    for (auto coords : path)
    {
        if (coords.first == 0 && coords.second == 0)
        {
            continue;
        }
        score += map[coords.first][coords.second];
    }
    return score;
}

coords_t_vec get_neighbors(coords_t const& cell1, ints_t_2d* map = 0)
{
    coords_t_vec possible_neighbors;
    if (cell1.first > 0)
        possible_neighbors.push_back(coords_t(cell1.first - 1, cell1.second));

    if (!map || cell1.first < map->size() - 1)
        possible_neighbors.push_back(coords_t(cell1.first + 1, cell1.second));

    if (cell1.second > 0)
        possible_neighbors.push_back(coords_t(cell1.first, cell1.second - 1));

    if (!map || cell1.second < map->at(0).size() - 1)
        possible_neighbors.push_back(coords_t(cell1.first, cell1.second + 1));

    return possible_neighbors;
}

bool cells_are_neighbors(coords_t const& cell1, coords_t const& cell2)
{
    for (auto neighbor : get_neighbors(cell1))
        if (neighbor == cell2)
            return true;
    return false;
}

coords_t_vec remove_options_next_to_path(coords_t_vec const& path, coords_t_vec const& possible_options)
{
    coords_t_vec next_options(possible_options);
    for (size_t ii = 0; ii < path.size() - 2; ++ii)
    {
        for (auto disallowed_cell : get_neighbors(path[ii]))
        {
            for (coords_t_vec::iterator option_iter = next_options.begin(); option_iter != next_options.end(); )
                if (*option_iter == disallowed_cell)
                    option_iter = next_options.erase(option_iter);
                else
                    ++option_iter;
        }
    }
    return next_options;
}

std::vector<coords_t_vec> plan_possible_paths(ints_t_2d map)
{
    std::vector<coords_t_vec> paths;
    size_t max_row = map.size() - 1;
    size_t max_col = map[0].size() - 1;

    {
        //I dont want to handle the beginning, so seed the paths.
        coords_t_vec path1; path1.push_back(coords_t(0, 0)); path1.push_back(coords_t(0, 1)); path1.push_back(coords_t(0, 2));
        coords_t_vec path2; path2.push_back(coords_t(0, 0)); path2.push_back(coords_t(0, 1)); path2.push_back(coords_t(1, 1));
        coords_t_vec path3; path3.push_back(coords_t(0, 0)); path3.push_back(coords_t(1, 0)); path3.push_back(coords_t(1, 1));
        coords_t_vec path4; path4.push_back(coords_t(0, 0)); path4.push_back(coords_t(1, 0)); path4.push_back(coords_t(2, 0));
        paths.push_back(path1);
        paths.push_back(score_path(path2, map) < score_path(path3, map) ? path2 : path3); // Both these end in the same spot. Only pick one.
        paths.push_back(path4);
    }

    for (std::vector<coords_t_vec>::iterator path_iter = paths.begin(); path_iter != paths.end(); )
    {
        static sll count = 0;
        ++count;
        if (count % 10000 == 0)
            std::cout << count << "\n";

        // Safety
        if (path_iter->empty())
        {
            path_iter = paths.erase(path_iter);
            continue;
        }

        // This path is done if it reached the end
        coords_t cell = path_iter->at(path_iter->size() - 1);
        if (cell.first == max_row && cell.second == max_col)
        {
            ++path_iter;
            continue;
        }
        coords_t_vec next_options = get_neighbors(cell, &map);
        next_options = remove_options_next_to_path(*path_iter, next_options);


        // Make the new paths if there are any to make
        if (next_options.empty())
        {
            path_iter = paths.erase(path_iter);
            continue; // maybe unecessary
        }
        else
        {
            // Save the 1st new path and append the rest of the new paths (if any)
            coords_t_vec base_path(*path_iter);
            paths.erase(path_iter);
            std::vector<coords_t_vec> new_paths;
            for (size_t ii = 0; ii < next_options.size(); ++ii)
            {
                coords_t_vec new_path(base_path);
                new_path.push_back(next_options[ii]);
                new_paths.push_back(new_path);
            }

            //First pass, only check if END-POINTS match
            std::vector<coords_t_vec> good_paths;
            for (auto path : new_paths)
            {
                bool good_path = true;
                for (std::vector<coords_t_vec>::iterator other_path_iter = paths.begin(); other_path_iter != paths.end(); ++other_path_iter)
                {
                    if (path.at(path.size() - 1) == other_path_iter->at(other_path_iter->size() - 1))
                    {
                        if ( score_path(path, map) < score_path(*other_path_iter, map))
                        {
                            *other_path_iter = path;
                        }
                        good_path = false;
                        break;
                    }
                }
                if (good_path)
                    good_paths.push_back(path);
            }

            for (auto path : good_paths)
                paths.push_back(path);


            // We invalidated the iterator, so lets start at the beginning and do a different path
            path_iter = paths.begin();

            // //////
            // std::vector<coords_t_vec> new_paths;
            // for (size_t ii = 0; ii < next_options.size(); ++ii)
            // {
            //     coords_t_vec new_path(base_path);
            //     new_path.push_back(next_options[ii]);
            //     new_paths.push_back(new_path);
            // }
            // //Check if these new paths end on a point inside of an already planned path. If so, score these two.
            // for (std::vector<coords_t_vec>::iterator other_path_iter = paths.begin(); other_path_iter != paths.end(); )
            // //////

        }

    }
    auto last = std::unique(paths.begin(), paths.end());
    if (last != paths.end())
    {
        std::cout << "There are non-unique paths\n";
    }
    return paths;
}

sll part1(ints_t_2d map)
{
    std::vector<coords_t_vec> paths = plan_possible_paths(map);
    std::cout << paths.size() << "\n";
    sll out = 0;
    if (paths.size() > 0)
        out = score_path(paths[0], map);
    return out;
}

sll part2(ints_t_2d input)
{
    sll out = 0;
    return out;
}

int main ()
{
    std::string day_string = "15";
    std::cout << "Day " << day_string << std::endl;
    ints_t_2d test_data = parse(get_strings_from_file("../inputs/day" + day_string + "_test.txt"));
    ints_t_2d real_data = parse(get_strings_from_file("../inputs/day" + day_string + ".txt"));

    ints_t_2d threebythree (3, ints_t(3, 1));
    ints_t_2d fourbyfour (4, ints_t(4, 1));

    sll res3 = part1(threebythree);
    sll res4 = part1(fourbyfour);

    sll expected_test_result_1 = 40;
    sll results_test_1 = part1(test_data);
    sll results_real_1 = 0;//part1(real_data);
    std::cout << "Test result is " << results_test_1;
    if (results_test_1 == expected_test_result_1)
    {
        std::cout << ". Passed!\n";
        std::cout << "Real result is ";
        results_real_1 = part1(real_data);
        std::cout << "\n" << part1(real_data) << std::endl;
    }
    else
        std::cout << ". Failed. Looking for " << expected_test_result_1 << "\n";

    sll results_test_2 = part2(test_data);
    sll results_real_2 = part2(real_data);
    sll expected_test_result_2 = 0;

    results(results_test_1, expected_test_result_1, results_real_1);
    results(results_test_2, expected_test_result_2, results_real_2);

    return 0;
}
