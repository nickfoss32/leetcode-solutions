#include <iostream>
#include <vector>
#include <unordered_map>

///
/// https://leetcode.com/problems/longest-substring-without-repeating-characters
///
class Solution {
public:
    int lengthOfLongestSubstring(std::string s) {
        // hash map used to keep track of what characters have been seen mapped to their respective position in the string
        std::unordered_map<char, int> charMap;

        // loop over each character in the input string and keep incrementing currSubstringLength until we've seen a repeat character.
        // If the length of the current substring is larger (once a repeat has been seen), update the longestSubstringLength
        int longestSubstringLength = 0;
        int currSubstrStart = -1;
        for (int i=0; i<s.length(); ++i)
        {
            char c = s[i];

            if (charMap.find(c) != charMap.end() && charMap[c] > currSubstrStart)
            {
                //set the start of the next substr to the position c was last seen
                currSubstrStart = charMap[c];
#ifdef DEBUG
                std::cout << "We've already seen " << c << ". Setting new substr start to " << currSubstrStart << std::endl;
#endif
            }

            //log the latest position we've seen c at
            charMap[c] = i;

            //calculate a new longest substr length
            longestSubstringLength = std::max(longestSubstringLength, i-currSubstrStart);
        }

        return longestSubstringLength;
    }
};

int main(int argc, char** argv) {
    Solution solution;

    // all test vectors are a vector of strings
    std::vector<std::string> inputVectors = {
        "ab",
        "abcabcbb",
        "bbbbb",
        "pwwkew",
        "pwwkeway",
        "aab",
        "dvdf",
        "ckilbkd",
        "ckilbkdca",
        "bpfbhmipx",
        " "
    };

    //run solution on all test vectors
    for (auto input : inputVectors) {

        std::cout << "**** BEGIN TEST ****" << std::endl;

        // print input
        std::cout << "input: \"" << input << "\"" << std::endl;

        // run unit under test
        int output = solution.lengthOfLongestSubstring(input);

        // print result
        std::cout << "Length of longest repeating substr: " << output << std::endl;

        std::cout << "**** END TEST ****" << std::endl << std::endl;
    }

    return 0;
}