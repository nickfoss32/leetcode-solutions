#include <iostream>
#include <vector>
#include <tuple>
#include <unordered_map>

///
/// https://leetcode.com/problems/two-sum
///
class Solution {
public:
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        // we will use a hash table to keep track of visited nums and their associated index for O(1) lookup
        std::unordered_map<int,int> visitedNums;
        
        for (int i = 0; i < nums.size(); ++i) {
            int diff = target-nums[i];

            // the difference is the number we need to find.
            // if we visited this num before, then we are done
            if (visitedNums.find(diff) != visitedNums.end()) {
                return std::vector<int> {visitedNums[diff], i};
            }
            else {
                visitedNums[nums[i]] = i;
            }
        }

        return {};
    }
};

int main(int argc, char** argv) {
    Solution solution;

    // all test vectors are a tuple of a vector of numbers (the input array), and an integer target value
    std::vector<std::tuple<std::vector<int>, int>> inputVectors = {
        std::make_tuple(std::vector<int> {2,7,11,15}, 9)
    };

    //run solution on all test vectors
    for (auto vector : inputVectors) {

        std::cout << "**** BEGIN TEST ****" << std::endl;

        std::vector<int> nums = std::get<0>(vector);
        int target = std::get<1>(vector);

        // print input
        std::cout << "[";
        for (unsigned int i=0; i<nums.size(); ++i) {
            if (i > 0) {
                std::cout << ",";
            }
            std::cout << nums[i];
        }
        std::cout << "], target: " << target << std::endl;

        std::vector<int> output = solution.twoSum(nums,target);

        // print result
        std::cout << output[0] << " and " << output[1] << " add up to " << target << std::endl;

        std::cout << "**** END TEST ****" << std::endl << std::endl;
    }

    return 0;
}