#include <iostream>
#include <vector>


class Solution {
public:

    ///
    /// Given a sorted integer array arr, two integers k and x, return the k closest integers to x in the array.
    /// The result should also be sorted in ascending order.
    ///
    /// Example 1:
    ///   Input: arr = [1,2,3,4,5], k = 4, x = 3
    ///   Output: [1,2,3,4]
    ///
    /// Example 2:
    ///   Input: arr = [1,2,3,4,5], k = 4, x = -1
    ///   Output: [1,2,3,4]
    ///
    /// Constraints:
    ///   1 <= k <= arr.length
    ///   1 <= arr.length <= 10^4
    ///   arr is sorted in ascending order.
    ///   -10^4 <= arr[i], x <= 10^4
    ///
    std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x) {
        // return vector of k closest elements to x
        std::vector<int> closestElems;

        // window indicies
        unsigned int leftIdx = 0;
        unsigned int rightIdx = arr.size();

        // walk the array to figure out if there is a better set of k elements closer to x
        // worst case, the last k elements (what rightIdx is initialized to) is the best set

        // do a binary search on the array to try to shrink the window to size k
        while (rightIdx-leftIdx+1 > k) {
#if DEBUG
            std::cout << "findClosestElements() - leftIdx: " << leftIdx << " rightIdx: " << rightIdx << std::endl;
#endif

            //calculate midpoint of current subarray
            unsigned int mid = ( (leftIdx + rightIdx) / 2 );

#if DEBUG
            std::cout << "Calculated mid: " << mid << std::endl;
#endif

            if (isCloser(arr[mid], arr[mid+k], x)) {
                rightIdx = mid;
            }
            else {
                leftIdx = ++mid;
            }
        }

#if DEBUG
        std::cout << "findClosestElements() - leftIdx: " << leftIdx << " rightIdx: " << rightIdx << std::endl;
#endif

        for (unsigned int i = leftIdx; i < leftIdx+k; ++i) {
            closestElems.push_back(arr[i]);
        }

        return closestElems;
    }

private:

    ///
    /// Given two integers a and b, 
    /// return true if a is closer to some integer x than b.
    ///
    /// Constraints:
    ///   a != b
    ///
    bool isCloser(int a, int b, int x) {
#if DEBUG
        std::cout << "isCloser() - checking if " << a << " is closer to " << x << " than " << b << std::endl;
#endif
        // calculate distances a to x and b to x
        unsigned int dist_a_x = std::abs(a-x);
        unsigned int dist_b_x = std::abs(b-x);

        // if the distances are the same, use input value as tie breaker
        return (dist_a_x == dist_b_x ? a <= b : dist_a_x < dist_b_x);
    }
};

int main(int argc, char** argv) {
    Solution solution;

    std::vector<int> input = {1,2,3,4,5};

    std::vector<int> output = solution.findClosestElements(input,4,3);

    std::cout << "[";
    for (unsigned int i=0; i<output.size(); ++i) {
        if (i > 0) {
            std::cout << ",";
        }
        std::cout << output[i];
    }
    std::cout << "]" << std::endl;

    return 0;
}