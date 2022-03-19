#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>


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

#ifdef DEBUG
        std::cout << "Input: [";
        for (unsigned int i=0; i<arr.size(); ++i) {
            if (i > 0) {
                std::cout << ",";
            }
            std::cout << arr[i];
        }
        std::cout << "], k=" << k << ", x=" << x << std::endl;
#endif

        //perform a binary search to find the closest element to x in the array
        int left = 0;
        int mid = 0;
        int right = arr.size() - 1;

        while (left < right) {
            mid = left + ( (right-left) / 2 ) ;

#ifdef DEBUG
            std::cout << "indicies {left,mid,right}: {" << left << "," << mid << "," << right << "}" << std::endl;
#endif

            // break if we found x
            if (arr[mid] == x) {
#ifdef DEBUG
            std::cout << "x was found in the array at idx " << mid << std::endl;
#endif
                break;
            }

            //if x is less than the current mid, closest element to x must be in the left subarray
            if (x < arr[mid]) {
                // look at the first element in the left subarray.
                // if x is in between arr[mid] and arr[mid-1], then the closest element is one of these two
                if (mid > 0 && x > arr[mid-1]) {
#ifdef DEBUG
            std::cout << "x is in between indicies " << mid-1 << " and " << mid << std::endl;
#endif
                    if (isCloser(arr[mid-1], arr[mid], x)) {
                        mid--;
                    } // else mid is pointing to the closest element

                    break;
                }

                // repeat the search on the left subarray
                else {
                    right = mid;
                }
            }

            //closest element to x must be in right subarray
            else {
                // look at the first element in the right subarray.
                // if x is in between arr[mid] and arr[mid+1], then the closest element is one of these two
                if (mid < arr.size() && x < arr[mid+1]) { 
#ifdef DEBUG
            std::cout << "x is in between indicies " << mid << " and " << mid+1 << std::endl;
#endif
                    if (isCloser(arr[mid+1], arr[mid], x)) {
                        mid++;
                    } // else mid is pointing to the closest element
                    break;
                }

                //repeat the search on the right subarray
                else {
                    left = mid + 1;
                }
            }
        }
  
#ifdef DEBUG
        std::cout << "Closest element to " << x << " in the array is " << arr[mid] << std::endl;
#endif

        // add the closest element to the array
        unsigned int numElemsAdded = 1;
        closestElems.push_back(arr[mid]);
        
        //now that we've found the closest element in the array, expand a window of k elements and return it
        left = mid-1;
        right = mid+1;
        while (numElemsAdded < k) {
            // if there are no more elements left of mid, just add the element right of mid
            if (left < 0) {
                closestElems.push_back(arr[right]);
                right++;
            }

            // if there are no more elements right of mid, just add the element to the left of mid
            else if (right > arr.size()-1) {
                closestElems.push_back(arr[left]);
                left--;
            }
            
            //otherwise, add the closer element
            else {
                if (isCloser(arr[left], arr[right], x)) {
                    closestElems.push_back(arr[left]);
                    left--;
                }
                else {
                    closestElems.push_back(arr[right]);
                    right++;
                }
            }

            numElemsAdded++;
        }

        //finally, sort the output
        std::sort(closestElems.begin(), closestElems.end());

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
    int isCloser(int a, int b, int x) {
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

    // all test vectors are a tuple of a vector of numbers (the sorted array), an integer k value, and an integer x value
    std::vector<std::tuple<std::vector<int>, int, int>> inputVectors = {
        std::make_tuple(std::vector<int> {1,2,3,4,5}, 4, 3),
        std::make_tuple(std::vector<int> {1,2,3,4,5}, 4, 1),
        std::make_tuple(std::vector<int> {1,2,3,4,5}, 4, -6),
        std::make_tuple(std::vector<int> {1,2,3,4,5}, 4, 10),
        std::make_tuple(std::vector<int> {1,2,2,4,5}, 4, 3),
        std::make_tuple(std::vector<int> {1,1,1,10,10,10}, 1, 9),
        std::make_tuple(std::vector<int> {0,1,1,1,2,3,6,7,8,9}, 9, 4),
    };

    //run solution on all test vectors
    for (auto vector : inputVectors) {

        std::cout << "**** BEGIN TEST ****" << std::endl;

        std::vector<int> output = solution.findClosestElements(std::get<0>(vector),std::get<1>(vector),std::get<2>(vector));

        // print result array
        std::cout << "[";
        for (unsigned int i=0; i<output.size(); ++i) {
            if (i > 0) {
                std::cout << ",";
            }
            std::cout << output[i];
        }
        std::cout << "]" << std::endl;

        std::cout << "**** END TEST ****" << std::endl << std::endl;
    }

    return 0;
}