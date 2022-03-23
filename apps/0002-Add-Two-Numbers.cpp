#include <iostream>
#include <vector>
#include <tuple>


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void printList(ListNode* listPtr) {
    ListNode* nodePtr = listPtr;
    std::cout << "[";
    while (nodePtr) {
        if (nodePtr != listPtr) {
            std::cout << "-->";
        }
        std::cout << nodePtr->val;

        nodePtr = nodePtr->next;
    }
    std::cout << "]" << std::endl;
}


///
/// https://leetcode.com/problems/add-two-numbers
///
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* outputList = 0;
        ListNode* outputListIter = 0;

        //iterate through both lists simultaneously
        ListNode* iter1 = l1;
        ListNode* iter2 = l2;
        int carry = 0;
        while (iter1 || iter2) {
            int sum = 0;

            //if there's only data left in the 1st list
            if (iter1 && !iter2) {
                sum = iter1->val + carry;
                carry = 0;
                
                //continue traversing the first list
                iter1 = iter1->next;
            }

            //if there's only data left in the 2nd list
            else if (!iter1 && iter2) {
                sum = iter2->val + carry;
                carry = 0;

                //continue traversing the second list
                iter2 = iter2->next;
            }

            //data must be in both lists
            else {
                sum = iter1->val + iter2->val + carry;
                carry = 0;

                //continue traversing each list
                iter1 = iter1->next;
                iter2 = iter2->next;
            }

            //if sum is greater than 9, save carry over value for next iteration
            if (sum > 9) {
                carry = 1;
                sum %= 10;
            }

#ifdef DEBUG
            std::cout << "sum: " << sum << ", carry: " << carry << std::endl;
#endif

            //add sum of current digits to output list
            if (!outputList) {
                outputList = new ListNode(sum);
                outputListIter = outputList;
            }
            else {
                outputListIter->next = new ListNode(sum);
                outputListIter = outputListIter->next;
            }
        }

        //if we have a trailing carry, add a final "1"
        if (carry) {
            outputListIter->next = new ListNode(1);
            outputListIter = outputListIter->next;
        }

        return outputList;
    }
};

int main(int argc, char** argv) {
    Solution solution;

    ListNode* input1 = new ListNode(2);
    input1->next = new ListNode(4);
    input1->next->next = new ListNode(3);

    ListNode* input2 = new ListNode(5);
    input2->next = new ListNode(6);
    input2->next->next = new ListNode(4);

    ListNode* input3 = new ListNode(0);
    ListNode* input4 = new ListNode(0);

    ListNode* input5 = new ListNode(9);
    ListNode* input6 = new ListNode(1);
    //add nine 9s
    ListNode* testNode = input6;
    for (int i=0; i<9; ++i) {
        testNode->next = new ListNode(9);
        testNode = testNode->next;
    }

    // all test vectors are a tuple of 2 linked lists containing the input numbers
    std::vector<std::tuple<ListNode*, ListNode*>> inputVectors = {
        std::make_tuple(input1,input2),
        std::make_tuple(input3,input4),
        std::make_tuple(input5,input6)
    };

    //run solution on all test vectors
    for (auto vector : inputVectors) {

        std::cout << "**** BEGIN TEST ****" << std::endl;

        ListNode* l1 = std::get<0>(vector);
        ListNode* l2 = std::get<1>(vector);

#ifdef DEBUG
        // print input
        printList(l1);
        printList(l2);
#endif

        // call the solution method
        ListNode* output = solution.addTwoNumbers(l1,l2);

#ifdef DEBUG
        // print result
        printList(output);
#endif

        std::cout << "**** END TEST ****" << std::endl << std::endl;
    }

    //free up memory of allocated test lists
    delete input1->next->next;
    delete input1->next;
    delete input1;

    delete input2->next->next;
    delete input2->next;
    delete input2;

    delete input3;
    delete input4;

    delete input5;
    testNode = input6;
    for (int i=0; i<9; ++i) {
        ListNode* nextNode = testNode->next;
        delete testNode;
        testNode = nextNode;
    }

    return 0;
}