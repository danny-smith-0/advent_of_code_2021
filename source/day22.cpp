#include <advent_of_code.h>

int max_x_ever = 0;
int min_x_ever = 0;
int max_y_ever = 0;
int min_y_ever = 0;
int max_z_ever = 0;
int min_z_ever = 0;

static constexpr int my_max_size = 124567 * 2 + 1; // 249135;

bools_t_3d parse(strings_t input, int max)
{
    // size_t max = 50;
    int total_cells = max * 2 + 1;
    std::array<bool, my_max_size> z_off_ar;
    z_off_ar.fill(false);
    // array(602): error C2148: total size of array must not exceed 0x7fffffff bytes = 2,147,483,647 in decimal
    std::array<std::array<bool, my_max_size>, my_max_size> yz_off_ar;
    // yz_off_ar.fill(z_off_ar);
    // bools_t z_off (total_cells, false);
    // bools_t_2d yz_off (total_cells, z_off);
    bools_t_3d xyz;// (total_cells, yz_off);

    for (auto str : input)
    {
        strings_t type_and_range = substrings_to_strings(str, " ");

        strings_t per_coordinate = substrings_to_strings(type_and_range[1], ",");

        //Trim "x=", "y=", & "z="
        per_coordinate[0] = per_coordinate[0].substr(2); // "x="
        per_coordinate[1] = per_coordinate[1].substr(2); // "y="
        per_coordinate[2] = per_coordinate[2].substr(2); // "z="

        ints_t x_min_max = substrings_to_ints(per_coordinate[0], ".");
        ints_t y_min_max = substrings_to_ints(per_coordinate[1], ".");
        ints_t z_min_max = substrings_to_ints(per_coordinate[2], ".");
        std::sort(x_min_max.begin(), x_min_max.end());
        std::sort(y_min_max.begin(), y_min_max.end());
        std::sort(z_min_max.begin(), z_min_max.end());

        min_x_ever = std::min(min_x_ever, x_min_max[0]);
        min_y_ever = std::min(min_y_ever, y_min_max[0]);
        min_z_ever = std::min(min_z_ever, z_min_max[0]);

        max_x_ever = std::max(max_x_ever, x_min_max[1]);
        max_y_ever = std::max(max_y_ever, y_min_max[1]);
        max_z_ever = std::max(max_z_ever, z_min_max[1]);


        bool x_hi = x_min_max[0] >  max && x_min_max[1] >  max;
        bool x_lo = x_min_max[0] < -max && x_min_max[1] < -max;
        bool y_hi = y_min_max[0] >  max && y_min_max[1] >  max;
        bool y_lo = y_min_max[0] < -max && y_min_max[1] < -max;
        bool z_hi = z_min_max[0] >  max && z_min_max[1] >  max;
        bool z_lo = z_min_max[0] < -max && z_min_max[1] < -max;

        if (x_hi || x_lo || y_hi || y_lo || z_hi || z_lo)
            continue;

        std::string on_string = type_and_range[0];
        // for (int ii = x_min_max[0] + max; ii <= x_min_max[1] + max; ++ii)
        //     for (int jj = y_min_max[0] + max; jj <= y_min_max[1] + max; ++jj)
        //         for (int kk = z_min_max[0] + max; kk <= z_min_max[1] + max; ++kk)
                {
                    int a = 0;//ii + jj + kk;
                    // a++;
                    // xyz[ii][jj][kk] = on_string == "on";
                }
    }
    std::cout << "x min/min: " << min_x_ever << " " << max_x_ever << ". Range: " << max_x_ever - min_x_ever + 1 << "\n";
    std::cout << "y min/min: " << min_y_ever << " " << max_y_ever << ". Range: " << max_y_ever - min_y_ever + 1 << "\n";
    std::cout << "z min/min: " << min_z_ever << " " << max_z_ever << ". Range: " << max_z_ever - min_z_ever + 1 << "\n";
    max_x_ever = 0;
    min_x_ever = 0;
    max_y_ever = 0;
    min_y_ever = 0;
    max_z_ever = 0;
    min_z_ever = 0;
    return xyz;
}

sll part1(strings_t input)
{

    int max = 50;
    steady_clock::time_point t1 = steady_clock::now();
    bools_t_3d xyz = parse(input, max);
    steady_clock::time_point t2 = steady_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << "Parsing took " << time_span.count() << " seconds.\n";
    sll count_cubes_on = 0;
    for (auto yz : xyz)
    {
        count_cubes_on += count_bools_t_2d(yz);
    }
    return count_cubes_on;
}

sll part2(strings_t input)
{
    int max = 124567; // Test3: -124565 120875. Real: -97425 97678
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
    bools_t_3d xyz = parse(input, max);
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    std::cout << "Parsing took " << time_span.count() << " seconds.\n";
    sll count_cubes_on = 0;
    for (auto yz : xyz)
    {
        count_cubes_on += count_bools_t_2d(yz);
    }
    return count_cubes_on;
}

int main ()
{
    std::string day_string = "22";
    std::cout << "Day " << day_string << std::endl;
    strings_t test_data_1 = get_strings_from_file("../inputs/day" + day_string + "_test_1.txt");
    strings_t test_data_2 = get_strings_from_file("../inputs/day" + day_string + "_test_2.txt");
    strings_t test_data_3 = get_strings_from_file("../inputs/day" + day_string + "_test_3.txt");
    strings_t real_data = get_strings_from_file("../inputs/day" + day_string + ".txt");


    std::cout << "\nPart 1\n\n";
    // sll results_test_1 = part1(test_data_1); sll expected_test_result_1 = 39;
    sll results_test_1 = part1(test_data_2); sll expected_test_result_1 = 590784;
    if (results(0, 0))//*/results_test_1, expected_test_result_1))
    {
        sll results_real_1 = part1(real_data);
        std::cout << "Real result is " << results_real_1 << std::endl;
    }

    std::cout << "\nPart 2\n\n";
    sll results_test_2 = part2(test_data_3);
    sll expected_test_result_2 = 0;//2758514936282235;
    if (results(results_test_2, expected_test_result_2))
    {
        sll results_real_2 = part2(real_data);
        std::cout << "Real result is " << results_real_2 << "\n\nFinished" << std::endl;
    }

    return 0;
}
