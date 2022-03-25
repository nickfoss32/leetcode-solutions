#include <iostream>
#include <vector>
#include <tuple>

///
/// https://leetcode.com/problems/median-of-two-sorted-arrays
///
class Solution {
public:
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
        double median = 0.0;
        
        return median;
    }
};

void printArray(const std::vector<int>& arr) {
    std::cout << "[";
    for (unsigned int i=0; i<arr.size(); ++i) {
        if (i > 0) {
            std::cout << ",";
        }
        std::cout << arr[i];
    }
    std::cout << "]" << std::endl;
}

int main(int argc, char** argv) {
    Solution solution;

    // all test vectors are 2 std::vectors<int>
    std::vector<std::tuple<std::vector<int>,std::vector<int>>> inputVectors = {
        std::make_tuple(std::vector<int>{1,3}, std::vector<int>{2}),
        std::make_tuple(std::vector<int>{1,2}, std::vector<int>{3,4})
    };

    //run solution on all test vectors
    for (auto vector : inputVectors) {

        std::cout << "**** BEGIN TEST ****" << std::endl;

        std::vector<int> arr1 = std::get<0>(vector);
        std::vector<int> arr2 = std::get<1>(vector);

        // print input
        printArray(arr1);
        printArray(arr2);

        // run unit under test
        double median = solution.findMedianSortedArrays(arr1, arr2);

        // print result
        std::cout << "Median of two arrays: " << median << std::endl;

        std::cout << "**** END TEST ****" << std::endl << std::endl;
    }

    return 0;
}