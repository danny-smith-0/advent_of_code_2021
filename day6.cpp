#include <iostream> //std::cout
#include <vector>
#include <array>

uint64_t count_my_fish(std::array<uint64_t, 9> const&  fishys)
{
    return fishys[0] + fishys[1] + fishys[2]
        + fishys[3] + fishys[4] + fishys[5]
        + fishys[6] + fishys[7] + fishys[8];
}

int main ()
{
    // Hooray for not having to read from a file today
    std::vector<int> fish_inputs = {3,4,3,1,2};
    // std::vector<int> fish_inputs = {5,1,2,1,5,3,1,1,1,1,1,2,5,4,1,1,1,1,2,1,2,1,1,1,1,1,2,1,5,1,1,1,3,1,1,1,3,1,1,3,1,1,4,3,1,1,4,1,1,1,1,2,1,1,1,5,1,1,5,1,1,1,4,4,2,5,1,1,5,1,1,2,2,1,2,1,1,5,3,1,2,1,1,3,1,4,3,3,1,1,3,1,5,1,1,3,1,1,4,4,1,1,1,5,1,1,1,4,4,1,3,1,4,1,1,4,5,1,1,1,4,3,1,4,1,1,4,4,3,5,1,2,2,1,2,2,1,1,1,2,1,1,1,4,1,1,3,1,1,2,1,4,1,1,1,1,1,1,1,1,2,2,1,1,5,5,1,1,1,5,1,1,1,1,5,1,3,2,1,1,5,2,3,1,2,2,2,5,1,1,3,1,1,1,5,1,4,1,1,1,3,2,1,3,3,1,3,1,1,1,1,1,1,1,2,3,1,5,1,4,1,3,5,1,1,1,2,2,1,1,1,1,5,4,1,1,3,1,2,4,2,1,1,3,5,1,1,1,3,1,1,1,5,1,1,1,1,1,3,1,1,1,4,1,1,1,1,2,2,1,1,1,1,5,3,1,2,3,4,1,1,5,1,2,4,2,1,1,1,2,1,1,1,1,1,1,1,4,1,5};

    // Process inputs
    std::array<uint64_t, 9> fishys = {0};
    for (auto fish : fish_inputs)
        ++fishys[fish];

    // Simulate fish
    static constexpr int days = 256;
    for (int ii = 1; ii <= days; ++ii)
    {
        uint64_t zeros = fishys[0];
        fishys[0] = fishys[1];
        fishys[1] = fishys[2];
        fishys[2] = fishys[3];
        fishys[3] = fishys[4];
        fishys[4] = fishys[5];
        fishys[5] = fishys[6];
        fishys[6] = fishys[7] + zeros;
        fishys[7] = fishys[8];
        fishys[8] = zeros;

        // std::cout << "after " << ii << " days, num fish: " << count_my_fish(fishys) << "\n";
    }

    std::cout << "after " << days << " days, num fish: " << count_my_fish(fishys);

    return 0;
}
