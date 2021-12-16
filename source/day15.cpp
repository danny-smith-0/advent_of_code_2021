#include <advent_of_code.h>

#define PRINT_LENGTH_ASSUMPTION_COMMENTS 0

ull count_assumed_calls = 0;
ull count_assumed_triggers = 0;

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

coords_t_vec remove_options_next_to_path(coords_t_vec const& path, coords_t_vec const& possible_options, ints_t_2d* map = 0, coords_t cell = coords_t(0,0))
{
    coords_t_vec next_options(possible_options);
    //Dont go left on the bottom or top, up on the right or left
    if(map && true)
    {
        coords_t_vec disallowed_cells;
        if (cell.second > 0 && (cell.first > map->size() - 3 || cell.first < 3))
            disallowed_cells.push_back(coords_t(cell.first, cell.second - 1));
        else if (cell.first > 0 && (cell.second > map[0].size() - 3 || cell.second < 3 ))
            disallowed_cells.push_back(coords_t(cell.first - 1, cell.second));

        for (auto disallowed_cell : disallowed_cells)
            for (coords_t_vec::iterator option_iter = next_options.begin(); option_iter != next_options.end(); )
                if (*option_iter == disallowed_cell)
                    option_iter = next_options.erase(option_iter);
                else
                    ++option_iter;
    }

    for (size_t ii = 0; ii < path.size() - 2; ++ii)
    {
        coords_t_vec neighbors = get_neighbors(path[ii]);
        for (auto disallowed_cell : neighbors)
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

bool my_func(std::vector<coords_t_vec>& paths, ints_t_2d const& map, coords_t_vec const& path)
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
    return good_path;
}

bool my_func2(std::vector<coords_t_vec>& paths, ints_t_2d const& map, coords_t_vec const& path)
{
    bool good_path = true;
    for (std::vector<coords_t_vec>::iterator other_path_iter = paths.begin(); other_path_iter != paths.end(); ++other_path_iter)
    {
        bool path_wins = false;
        coords_t_vec replacement_path(path);
        for (coords_t_vec::iterator cell_iter = other_path_iter->begin(); cell_iter != other_path_iter->end(); ++cell_iter)
        {
            if (path_wins)
            {
                replacement_path.push_back(*cell_iter);
            }
            else if (path.at(path.size() - 1) == *cell_iter)
            {

                coords_t_vec partial_path(other_path_iter->begin(), cell_iter + 1);
                sll path_score = score_path(path, map);
                sll partial_path_score = score_path(partial_path, map);
                if (path_score < partial_path_score)
                {
                    path_wins = true;
                }

                good_path = false;
            }
        }

        if (path_wins)
            *other_path_iter = replacement_path;
    }
    return good_path;
}

bool assume_the_optimal_path_doesnt_double_back_toooooo_much(coords_t_vec path)
{
    ++count_assumed_calls;
    size_t max_1st_idx = 0;
    size_t max_2nd_idx = 0;
    for (auto coords : path)
    {
        max_1st_idx = std::max(max_1st_idx, coords.first);
        max_2nd_idx = std::max(max_2nd_idx, coords.second);
    }

    size_t length_of_shortest_path_thru_bounding_box = max_1st_idx + max_2nd_idx + 1;
    // size_t assumed_max_path_length = (length_of_shortest_path_thru_bounding_box * 7) / 4 + 1;
    size_t assumed_max_path_length = (length_of_shortest_path_thru_bounding_box * 4) / 3 + 1;
    size_t path_length = path.size();
    bool not_toooooo_long = path_length < assumed_max_path_length;

    {
        count_assumed_triggers += not_toooooo_long ? 0 : 1;
        #if PRINT_LENGTH_ASSUMPTION_COMMENTS
            if (count_assumed_triggers > 0 && count_assumed_triggers % 1000 == 0)
                std::cout << "\"Assumed\" calls, triggers, and percentage: " << count_assumed_calls << ", " << count_assumed_triggers << ", " << static_cast<double>(count_assumed_triggers)/static_cast<double>(count_assumed_calls) << "\n";
        #endif // PRINT_LENGTH_ASSUMPTION_COMMENTS
    }
    return not_toooooo_long;
}

void print_path_map_to_file(std::string filename, std::vector<coords_t_vec> paths, size_t dimension = 0)
{
    std::ofstream outfile;
    outfile.open(filename);
    for (auto path : paths)
    {
        bools_t_2d path_map = coords_to_bools(path, dimension, dimension);
        std::string str = print_T_2d_to_string(path_map);
        outfile << str << "\n";
        outfile << "\n";
    }
    outfile.close();
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

    sll count = 0;
    count_assumed_calls = 0;
    count_assumed_triggers = 0;
    for (std::vector<coords_t_vec>::iterator path_iter = paths.begin(); path_iter != paths.end(); )
    {
        if (++count % 50000 == 0)
        {
            std::cout << count << " - paths.size() = " << paths.size() << " saving to file"<< "\n";
            if (true)
            {
                std::stringstream filename;
                filename << "day15_mapsize_" << map.size() << "_count_" << count << "_paths_" << paths.size() << ".txt";
                print_path_map_to_file(filename.str(), paths, map.size());
                std::cout << "Finished saving to file\n";
            }
        }
        else if (count % 10000 == 0)
        {
            std::cout << count << " - paths.size() = " << paths.size() << "\n";
        }
        // Safety
        if (path_iter->empty())
        {
            path_iter = paths.erase(path_iter);
            std::cout << "WOAH! EMPTY! BAD!\n";
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
        next_options = remove_options_next_to_path(*path_iter, next_options, &map, cell);


        // Make the new paths if there are any to make
        if (next_options.empty())
        {
            path_iter = paths.erase(path_iter);
            continue;
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
                if (assume_the_optimal_path_doesnt_double_back_toooooo_much(new_path))
                    new_paths.push_back(new_path);
            }

            //Check if the ends of these routes hit a previoulsy found route. Edit if necessary
            bool a_new_path_finished = false; //debug
            sll new_potential_answer = 0;
            std::vector<coords_t_vec> good_paths;
            for (auto path : new_paths)
            {
                coords_t cell = path[path.size() - 1];
                if (cell.first == max_row && cell.second == max_col)
                {
                    a_new_path_finished = true;
                    new_potential_answer = score_path(path, map);
                    std::cout << "new_potential_answer " << new_potential_answer << "\n";
                }

                // bool good_path = my_func(paths, map, path);
                bool good_path = my_func2(paths, map, path);
                if (good_path)
                    good_paths.push_back(path);
            }

            for (auto path : good_paths)
                paths.push_back(path);

            if (a_new_path_finished) //debug
            {
                std::stringstream filename;
                filename << "day15_mapsize_" << map.size() << "_count_" << count << "_paths_" << paths.size() << "_found_new_finish__score_" << new_potential_answer <<".txt";
                print_path_map_to_file(filename.str(), paths, map.size());
            }

            // We invalidated the iterator, so lets start at the beginning and do a different path
            path_iter = paths.begin();
        }

    }
    std::cout << "last count was " << count << ". paths.size() " << paths.size() << std::endl;
    #if PRINT_LENGTH_ASSUMPTION_COMMENTS
        std::cout << "\"Assumed\" calls, triggers, and percentage: " << count_assumed_calls << ", " << count_assumed_triggers << ", " << static_cast<double>(count_assumed_triggers)/static_cast<double>(count_assumed_calls) << "\n";
    #endif // PRINT_LENGTH_ASSUMPTION_COMMENTS

    std::stringstream filename;
    filename << "day15_mapsize_" << map.size() << "_final_count_" << count << "_paths_" << paths.size() << ".txt";
    print_path_map_to_file(filename.str(), paths, map.size());
    return paths;
}

sll part1(ints_t_2d map)
{
    std::vector<coords_t_vec> paths = plan_possible_paths(map);
    sll out = 0;
    if (paths.size() > 0)
        out = score_path(paths[0], map);
    std::cout << "Score = " << out << "\n";
    return out;
}

ints_t_2d tile_map(ints_t_2d map_in, size_t tiles)
{
    ints_t_2d complete_the_cols(map_in);
    for (auto& line : complete_the_cols)
    {
        ints_t orig = line;
        ints_t to_insert = orig;
        for (size_t ii = 0; ii < tiles - 1; ++ii)
        {
            for (auto& elem : to_insert)
                if (elem < 9)
                    ++elem;
                else
                    elem = 1;
            line.insert(line.end(), to_insert.begin(), to_insert.end());
        }
    }

    ints_t_2d map_out(complete_the_cols);
    for (size_t ii = 0; ii < tiles - 1; ++ii)
    {
        ints_t_2d to_insert = complete_the_cols;
        for (auto& line : complete_the_cols)
        {
            for (auto& elem : line)
                if (elem < 9)
                    ++elem;
                else
                    elem = 1;
        }
        map_out.insert(map_out.end(), complete_the_cols.begin(), complete_the_cols.end());
    }

    return map_out;
}

sll part2(ints_t_2d input, size_t tiles)
{
    ints_t_2d map = tile_map(input, tiles);
    return part1(map);
}

int main ()
{
    std::string day_string = "15";
    std::cout << "Day " << day_string << std::endl;
    ints_t_2d test_data = parse(get_strings_from_file("../inputs/day" + day_string + "_test.txt"));
    ints_t_2d real_data = parse(get_strings_from_file("../inputs/day" + day_string + ".txt"));

    // bool with_comma = true;
    // print_T_2d(test_data, with_comma); std::cout << "\n\n"; print_T_2d(real_data, with_comma);

    ints_t_2d threebythree (3, ints_t(3, 1));
    ints_t_2d fourbyfour (4, ints_t(4, 1));

    std::cout << "3x3: ";
    sll res3 = part1(threebythree);
    std::cout << "4x4: ";
    sll res4 = part1(fourbyfour);

    std::cout << "\n\nPart1\n\n";

    std::cout << "test: ";
    sll expected_test_result_1 = 40;
    sll results_test_1 = part1(test_data);
    sll results_real_1 = 498;
    std::cout << "Test result is " << results_test_1;
    if (results_test_1 == expected_test_result_1)
    {
        std::cout << ". Passed!\n";
        std::cout << "Real result is ";
        // results_real_1 = part1(real_data); // 594 is too high. 435 is right for someone else. That was weird. Not 501. Took about 37 minutes.  498 !!!!!!!! So close before
        std::cout << results_real_1 << std::endl;
    }
    else
        std::cout << ". Failed. Looking for " << expected_test_result_1 << "\n";


    std::cout << "\n\nPart2\n\n";
    static constexpr size_t tiles = 5;
    std::cout << "3x3 -> 15x15: ";
    sll res3_part2 = part2(threebythree, tiles);
    std::cout << "test: ";
    sll expected_test_result_2 = 315;
    sll results_test_2 = part2(test_data, tiles);
    sll results_real_2 = 0;
    std::cout << "Test result is " << results_test_2;
    if (results_test_2 == expected_test_result_2)
    {
        std::cout << ". Passed!\n";
        std::cout << "Real result is ";
        results_real_2 = part2(real_data, tiles);
        std::cout << results_real_2 << std::endl;
    }
    else
        std::cout << ". Failed. Looking for " << expected_test_result_2 << "\n";



    return 0;
}
