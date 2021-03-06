#include <advent_of_code.h>

ints_t x_range(int x_step)
{
    ints_t range(1, 0);
    while (x_step > 0)
    {
        range.push_back(x_step-- + range[range.size() - 1]);
    }
    return range;
}

struct Trench
{
    int x_min = 0;
    int x_max = 0;
    int y_min = 0;
    int y_max = 0;

    Trench(){}
    Trench(int x_min_in, int x_max_in, int y_min_in, int y_max_in)
    : x_min(x_min_in), x_max(x_max_in), y_min(y_min_in), y_max(y_max_in) {}

    std::vector<std::tuple<int, int, int>> x_steps_in_x_range(int x_step)
    {
        std::vector<std::tuple<int, int, int>> results;
        ints_t_2d step_idxs;
        ints_t x_steps = x_range(x_step);
        for (int step_idx = 1; step_idx < static_cast<int>(x_steps.size()); ++step_idx)
            if (x_steps[step_idx] >= x_min && x_steps[step_idx] <= x_max)
            {
                results.push_back(std::make_tuple(x_step, step_idx, x_steps[step_idx]));
            }
        return results;
    }

    std::vector<std::tuple<int, int, int>> y_steps_in_y_range(int y_stepsize)
    {
        std::vector<std::tuple<int, int, int>> results;
        ints_t_2d step_idxs;
        int depth = 0;
        int step_idx = 0;
        int y_step = y_stepsize;
        if (y_stepsize > 0)
        {
            step_idx = 2 * y_stepsize + 1; // The above zero depth takes this many steps to return to zero
            y_stepsize = -y_stepsize - 1;
        }
        while (depth > y_min)
        {
            depth += y_stepsize--;
            ++step_idx;
            if (depth >= y_min && depth <= y_max)
            {
                results.push_back(std::make_tuple(y_step, step_idx, depth));
            }
        }
        return results;
    }

    std::vector<std::tuple<int, int, int>> possible_x_stepsize_nsteps_ending()
    {
        std::vector<std::tuple<int, int, int>> possible_x_stepsize_nsteps_ending;
        for (int x_stepsize = 1; x_stepsize <= this->x_max; ++x_stepsize)
        {
            std::vector<std::tuple<int, int, int>> stepsize_nsteps_ending = this->x_steps_in_x_range(x_stepsize);
            if (!stepsize_nsteps_ending.empty())
            {
                possible_x_stepsize_nsteps_ending.insert(possible_x_stepsize_nsteps_ending.end(), stepsize_nsteps_ending.begin(), stepsize_nsteps_ending.end());
            }
        }
        return possible_x_stepsize_nsteps_ending;
    }

    std::vector<std::tuple<int, int, int>> possible_y_stepsize_nsteps_ending()
    {
        std::vector<std::tuple<int, int, int>> possible_y_stepsize_nsteps_ending;
        // Assuming y_min is negative. Also, y must be positive to reach the highest
        for (int y_stepsize = this->y_min; y_stepsize <= -this->y_min; ++y_stepsize)
        {
            std::vector<std::tuple<int, int, int>> stepsize_nsteps_ending = this->y_steps_in_y_range(y_stepsize);
            if (!stepsize_nsteps_ending.empty())
            {
                possible_y_stepsize_nsteps_ending.insert(possible_y_stepsize_nsteps_ending.end(), stepsize_nsteps_ending.begin(), stepsize_nsteps_ending.end());
            }
        }
        return possible_y_stepsize_nsteps_ending;
    }
};

Trench parse(strings_t input)
{
    //Assumes 1 line that starts with "target area: "
    std::string trim_front = input[0].substr(13);
    strings_t per_coordinate = substrings_to_strings(trim_front, ",");

    //Trim "x=" & " y="
    per_coordinate[0] = per_coordinate[0].substr(2); // "x="
    per_coordinate[1] = per_coordinate[1].substr(3); // " y="

    ints_t x_min_max = substrings_to_ints(per_coordinate[0], ".");
    ints_t y_min_max = substrings_to_ints(per_coordinate[1], ".");
    std::sort(x_min_max.begin(), x_min_max.end());
    std::sort(y_min_max.begin(), y_min_max.end());
    return Trench(x_min_max[0], x_min_max[1], y_min_max[0], y_min_max[1]);
}

ints_t get_step_options_from_x(std::vector<std::tuple<int, int, int>> possible_x_stepsize_nsteps_ending)
{
    ints_t step_range;
    for (auto stepsize_nsteps_ending : possible_x_stepsize_nsteps_ending)
    {
        step_range.push_back(std::get<1>(stepsize_nsteps_ending));
    }
    std::sort(step_range.begin(), step_range.end());
    auto last = std::unique(step_range.begin(), step_range.end());
    step_range.erase(last, step_range.end());
    return step_range;
}

sll part1(Trench trench)
{
    //Find all possible x's
    std::vector<std::tuple<int, int, int>> possible_x_stepsize_nsteps_ending = trench.possible_x_stepsize_nsteps_ending();

    //Find all possible y's
    std::vector<std::tuple<int, int, int>> possible_y_stepsize_nsteps_ending = trench.possible_y_stepsize_nsteps_ending();

    ints_t step_range = get_step_options_from_x(possible_x_stepsize_nsteps_ending);
    //Max steps is hopefully one that hits zero x_vel in the trench. This is an assumption that thankfully works, but might not be guaranteed
    int max_steps = step_range[step_range.size() - 1];

    sll max_y_height = 0;
    for (auto stepsize_nsteps_ending : possible_y_stepsize_nsteps_ending)
    {
        int nsteps_y = std::get<1>(stepsize_nsteps_ending);
        if (nsteps_y >= max_steps)
        {
            int step_size = std::get<0>(stepsize_nsteps_ending);
            sll y_height = sum_of_first_n_integers(step_size);
            max_y_height = y_height > max_y_height ? y_height : max_y_height;
        }
    }
    return max_y_height;
}

sll part2(Trench trench)
{
    //Find all possible x's
    std::vector<std::tuple<int, int, int>> possible_x_stepsize_nsteps_ending = trench.possible_x_stepsize_nsteps_ending();

    //Find all possible y's
    std::vector<std::tuple<int, int, int>> possible_y_stepsize_nsteps_ending = trench.possible_y_stepsize_nsteps_ending();

    std::vector<std::pair<int, int>> velocities;
    for (auto x_tuple : possible_x_stepsize_nsteps_ending)
    {
        int x_vel = std::get<0>(x_tuple);
        int nsteps_x = std::get<1>(x_tuple);
        for (auto y_tuple : possible_y_stepsize_nsteps_ending)
        {
            int y_vel = std::get<0>(y_tuple);
            int nsteps_y = std::get<1>(y_tuple);
            if (nsteps_y == nsteps_x || (nsteps_x == x_vel) && nsteps_y > nsteps_x)
                velocities.push_back(std::make_pair(x_vel, y_vel));
        }
    }
    std::sort(velocities.begin(), velocities.end());
    auto last = std::unique(velocities.begin(), velocities.end());
    velocities.erase(last, velocities.end());
    sll total_velocities = velocities.size();
    return total_velocities;
}

int main ()
{
    std::string day_string = "17";
    std::cout << "Day " << day_string << std::endl;
    Trench test_trench  = parse(get_strings_from_file("../inputs/day" + day_string + "_test.txt"));
    Trench real_trench  = parse(get_strings_from_file("../inputs/day" + day_string + ".txt"));

    std::cout << "\nPart 1\n\n";
    sll results_test_1 = part1(test_trench);
    sll expected_test_result_1 = 45;
    if (results(results_test_1, expected_test_result_1))
    {
        sll results_real_1 = part1(real_trench);
        std::cout << "Real result is " << results_real_1 << std::endl;
    }

    std::cout << "\nPart 2\n\n";
    sll results_test_2 = part2(test_trench);
    sll expected_test_result_2 = 112;
    if (results(results_test_2, expected_test_result_2))
    {
        sll results_real_2 = part2(real_trench);
        std::cout << "Real result is " << results_real_2 << "\n\nFinished" << std::endl;
    }

    return 0;
}
