// Catch 1.0 Framework Testing
#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "priorityqueue.h"

using namespace std;

TEST_CASE("(0) no tests") {
    REQUIRE(true);
}
//// default constructor test ////
TEST_CASE("default constructor - empty priority queue") {
    priorityqueue<int> pq;
    REQUIRE(pq.Size() == 0);

}

//// enqueue tests ////
TEST_CASE("enqueue - single element - various data types") {
    SECTION("int") {
        priorityqueue<int> pq;
        pq.enqueue(42, 1);
        REQUIRE(pq.Size() == 1);
    }

    SECTION("float") {
        priorityqueue<float> pq;
        pq.enqueue(42.0f, 1);
        REQUIRE(pq.Size() == 1);
    }

    SECTION("double") {
        priorityqueue<double> pq;
        pq.enqueue(42.0, 1);
        REQUIRE(pq.Size() == 1);
    }

    SECTION("char") {
        priorityqueue<char> pq;
        pq.enqueue('A', 1);
        REQUIRE(pq.Size() == 1);
    }
}

TEST_CASE("enqueue - unique ") {
    priorityqueue<int> pq;
    pq.enqueue(10, 3);
    pq.enqueue(20, 1);
    pq.enqueue(30, 4);
    pq.enqueue(40, 2);

    REQUIRE(pq.Size() == 4);
}

TEST_CASE("enqueue -- duplicate ") {
    priorityqueue<int> pq;
    pq.enqueue(10, 1);
    pq.enqueue(20, 1);
    pq.enqueue(30, 1);
    pq.enqueue(40, 1);

    REQUIRE(pq.Size() == 4);
}

TEST_CASE("enqueue - unique & duplicate ") {
    priorityqueue<int> pq;
    pq.enqueue(10, 3);
    pq.enqueue(20, 1);
    pq.enqueue(30, 3);
    pq.enqueue(40, 2);
    pq.enqueue(50, 1);

    REQUIRE(pq.Size() == 5);
}

TEST_CASE("enqueue - different data types & duplicate priorities") {
    SECTION("float") {
        priorityqueue<float> pq;
        pq.enqueue(10.5f, 1);
        pq.enqueue(20.5f, 2);
        pq.enqueue(30.5f, 1);
        pq.enqueue(40.5f, 2);

        REQUIRE(pq.Size() == 4);
    }

    SECTION("double") {
        priorityqueue<double> pq;
        pq.enqueue(10.5, 3);
        pq.enqueue(20.5, 3);
        pq.enqueue(30.5, 1);
        pq.enqueue(40.5, 2);

        REQUIRE(pq.Size() == 4);
    }

    SECTION("char") {
        priorityqueue<char> pq;
        pq.enqueue('A', 1);
        pq.enqueue('B', 1);
        pq.enqueue('C', 2);
        pq.enqueue('D', 2);
        REQUIRE(pq.Size() == 4);
    }
}

//// toString tests ////
TEST_CASE("enqueue & toString  - unique") {
    priorityqueue<int> pq;
    pq.enqueue(10, 3);
    pq.enqueue(20, 1);
    pq.enqueue(30, 4);
    pq.enqueue(40, 2);

    REQUIRE(pq.Size() == 4);
    REQUIRE(pq.toString() == "1 value: 20\n2 value: 40\n3 value: 10\n4 value: 30\n");
}

TEST_CASE("enqueue & toString - duplicates") {
    priorityqueue<int> pq;
    pq.enqueue(10, 1);
    pq.enqueue(20, 1);
    pq.enqueue(30, 1);
    pq.enqueue(40, 1);

    REQUIRE(pq.Size() == 4);
    REQUIRE(pq.toString() == "1 value: 10\n1 value: 20\n1 value: 30\n1 value: 40\n");
}

TEST_CASE("enqueue & toString - unique & duplicate ") {
    priorityqueue<int> pq;
    pq.enqueue(10, 3);
    pq.enqueue(20, 1);
    pq.enqueue(30, 3);
    pq.enqueue(40, 2);
    pq.enqueue(50, 1);

    REQUIRE(pq.Size() == 5);
    REQUIRE(pq.toString() == "1 value: 20\n1 value: 50\n2 value: 40\n3 value: 10\n3 value: 30\n");
}

TEST_CASE("enqueue & toString -  different data types & duplicate priorities") {
    SECTION("float") {
        priorityqueue<float> pq;
        pq.enqueue(10.5f, 1);
        pq.enqueue(20.5f, 2);
        pq.enqueue(30.5f, 1);
        pq.enqueue(40.5f, 2);

        REQUIRE(pq.Size() == 4);
        REQUIRE(pq.toString() == "1 value: 10.5\n1 value: 30.5\n2 value: 20.5\n2 value: 40.5\n");
    }

    SECTION("double") {
        priorityqueue<double> pq;
        pq.enqueue(10.5, 3);
        pq.enqueue(20.5, 3);
        pq.enqueue(30.5, 1);
        pq.enqueue(40.5, 2);

        REQUIRE(pq.Size() == 4);
        REQUIRE(pq.toString() == "1 value: 30.5\n2 value: 40.5\n3 value: 10.5\n3 value: 20.5\n");
    }

    SECTION("char") {
        priorityqueue<char> pq;
        pq.enqueue('A', 1);
        pq.enqueue('B', 1);
        pq.enqueue('C', 2);
        pq.enqueue('D', 3);

        REQUIRE(pq.Size() == 4);
        REQUIRE(pq.toString() == "1 value: A\n1 value: B\n2 value: C\n3 value: D\n");
    }
}

///// clear tests /////
TEST_CASE("clear ") {

    priorityqueue<int> pq;

    SECTION("clear - empty priority queue") {
        pq.clear();
        REQUIRE(pq.toString() == "");
    }

    SECTION("clear - unique priorities") {
        pq.enqueue(10, 1);
        pq.enqueue(20, 2);
        pq.enqueue(30, 3);

        pq.clear();
        REQUIRE(pq.toString() == "");
    }

    SECTION("clear - duplicate priorities") {
        pq.enqueue(10, 1);
        pq.enqueue(20, 1);
        pq.enqueue(30, 1);
        pq.enqueue(40, 1);

        pq.clear();
        REQUIRE(pq.toString() == "");
    }

    SECTION("clear -  unique & duplicate priorities") {
        pq.enqueue(10, 1);
        pq.enqueue(20, 1);
        pq.enqueue(30, 2);
        pq.enqueue(40, 3);
        pq.enqueue(50, 3);

        pq.clear();
        REQUIRE(pq.toString() == "");
    }

    SECTION("clear - re-insert values") {
        pq.enqueue(10, 1);
        pq.enqueue(20, 1);
        pq.enqueue(30, 2);
        pq.enqueue(40, 3);
        pq.enqueue(50, 3);

        pq.clear();

        pq.enqueue(60, 1);
        pq.enqueue(70, 2);
        pq.enqueue(80, 3);
        pq.enqueue(90, 4);

        REQUIRE(pq.toString() == "1 value: 60\n2 value: 70\n3 value: 80\n4 value: 90\n");
    }
}

//// equals operator tests ////
TEST_CASE(" overload equals operator") {
    priorityqueue<int> pq1, pq2;

    SECTION("empty priority queue") {
        pq1 = pq2;
        REQUIRE(pq1.toString() == pq2.toString());
    }

    SECTION("unique priorities") {
        pq2.enqueue(10, 1);
        pq2.enqueue(20, 2);
        pq2.enqueue(30, 3);
        pq1 = pq2;
        REQUIRE(pq1.toString() == pq2.toString());
    }

    SECTION("duplicate priorities") {
        pq2.enqueue(40, 1);
        pq2.enqueue(50, 1);
        pq1 = pq2;
        REQUIRE(pq1.toString() == pq2.toString());
    }

    SECTION("unique and duplicate priorities") {
        pq2.enqueue(60, 4);
        pq1 = pq2;
        REQUIRE(pq1.toString() == pq2.toString());
    }
}

//// begin & next tests ////
TEST_CASE(" begin & next functions") {
    int value, priority;

    priorityqueue<int> pq_empty;
    pq_empty.begin();
    REQUIRE(pq_empty.next(value, priority) == false);

    priorityqueue<int> pq;
    pq.enqueue(10, 1);
    pq.begin();

    REQUIRE(pq.next(value, priority) == true);
    REQUIRE(value == 10);
    REQUIRE(priority == 1);
    REQUIRE(pq.next(value, priority) == true);

    
}

TEST_CASE("next & begin ") {
    priorityqueue<int> pq;
    pq.enqueue(10, 1);
    pq.enqueue(20, 2);
    pq.enqueue(30, 3);
    pq.enqueue(25, 3);
    pq.enqueue(40, 4);
    pq.enqueue(35, 4);

    vector< pair<int, vector<int>>> expected = {
        {1, {10}},
        {2, {20}},
        {3, {30, 25}},
        {4, {40, 35}}
    };

    int value;
    int priority;
    pq.begin();
    for (const auto &e : expected) {
        for (size_t i = 0; i < e.second.size(); ++i) {
            REQUIRE(pq.next(value, priority));
            REQUIRE(priority == e.first);
            REQUIRE(value == e.second[i]);
        }
    }
    REQUIRE_FALSE(pq.next(value, priority));
}

////// dequeue tests ////////
TEST_CASE("dequeue - empty priority queue") {
    priorityqueue<int> pq;
        
    REQUIRE(pq.Size() == 0);
    int result = pq.dequeue();
    REQUIRE(result == 0);
    
}

TEST_CASE("dequeue - single element") {
    priorityqueue<int> pq;
    pq.enqueue(10, 5);

    REQUIRE(pq.dequeue() == 10);
    REQUIRE(pq.Size() == 0);
}

TEST_CASE("dequeue - unique priorities") {
    priorityqueue<int> pq;
    pq.enqueue(10, 5);
    pq.enqueue(20, 3);
    pq.enqueue(30, 1);
    pq.enqueue(40, 4);

    REQUIRE(pq.dequeue() == 30);
    REQUIRE(pq.Size() == 3);
    REQUIRE(pq.dequeue() == 20);
    REQUIRE(pq.Size() == 2);
}

TEST_CASE("dequeue - duplicate priorities") {
    priorityqueue<int> pq;
    pq.enqueue(10, 3);
    pq.enqueue(20, 3);
    pq.enqueue(30, 2);
    pq.enqueue(40, 1);

    REQUIRE(pq.dequeue() == 40);
    REQUIRE(pq.Size() == 3);
    REQUIRE(pq.dequeue() == 30);
    REQUIRE(pq.Size() == 2);
}

TEST_CASE("dequeue - unique & duplicate priorities") {
    priorityqueue<int> pq;
    pq.enqueue(10, 3);
    pq.enqueue(20, 3);
    pq.enqueue(30, 2);
    pq.enqueue(40, 4);
    pq.enqueue(50, 4);

    REQUIRE(pq.dequeue() == 30);
    REQUIRE(pq.Size() == 4);
    REQUIRE(pq.dequeue() == 10);
    REQUIRE(pq.Size() == 3);
}

TEST_CASE("peek") {
    priorityqueue<int> pq;

    SECTION("peek - empty priority") {
        int result = pq.peek();
        REQUIRE(result == int());
    }

    SECTION("peek - single element") {
        pq.enqueue(10, 5);
        REQUIRE(pq.peek() == 10);
    }

    SECTION("peek - multiple priorities") {
        pq.enqueue(20, 3);
        pq.enqueue(10, 5);
        pq.enqueue(30, 1);
        pq.enqueue(40, 6);

        REQUIRE(pq.peek() == 30);
        pq.dequeue();
        REQUIRE(pq.peek() == 20);
    }

    SECTION("peek - duplicate priorities") {
        pq.enqueue(10, 5);
        pq.enqueue(20, 5);
        pq.enqueue(30, 1);
        pq.enqueue(40, 6);
        pq.enqueue(50, 5);

        REQUIRE(pq.peek() == 30);
        pq.dequeue();
        REQUIRE(pq.peek() == 10);
    }
}

TEST_CASE(" enqueue & dequeue") {
    priorityqueue<int> pq;
    pq.enqueue(10, 3);
    pq.enqueue(20, 2);
    pq.enqueue(30, 1);

    REQUIRE(pq.dequeue() == 30);
    REQUIRE(pq.Size() == 2);
    REQUIRE(pq.dequeue() == 20);
    REQUIRE(pq.Size() == 1);
    REQUIRE(pq.dequeue() == 10);
    REQUIRE(pq.Size() == 0);
}

TEST_CASE("peek - dupliactes") {
    priorityqueue<int> pq;
    pq.enqueue(10, 3);
    pq.enqueue(20, 3);
    pq.enqueue(30, 2);
    pq.enqueue(40, 1);

    REQUIRE(pq.peek() == 40);
    REQUIRE(pq.Size() == 4);
    REQUIRE(pq.dequeue() == 40);
    REQUIRE(pq.Size() == 3);
    REQUIRE(pq.peek() == 30);
    REQUIRE(pq.Size() == 3);
}

TEST_CASE("all duplicates") {
    priorityqueue<int> pq;
    pq.enqueue(10, 1);
    pq.enqueue(20, 1);
    pq.enqueue(30, 1);
    pq.enqueue(40, 1);

    REQUIRE(pq.dequeue() == 10);
    REQUIRE(pq.Size() == 3);
    REQUIRE(pq.dequeue() == 20);
    REQUIRE(pq.Size() == 2);
}

//// equality operator test ////
TEST_CASE("equality operator - equal ") {
    priorityqueue<int> pq1;
    pq1.enqueue(10, 3);
    pq1.enqueue(20, 2);
    pq1.enqueue(30, 1);

    priorityqueue<int> pq2;
    pq2.enqueue(10, 3);
    pq2.enqueue(20, 2);
    pq2.enqueue(30, 1);

    REQUIRE(pq1 == pq2);
}

TEST_CASE("equality operator - not equal") {
    priorityqueue<int> pq1;
    pq1.enqueue(10, 3);
    pq1.enqueue(20, 2);
    pq1.enqueue(30, 1);

    priorityqueue<int> pq2;
    pq2.enqueue(10, 3);
    pq2.enqueue(30, 1);

    REQUIRE_FALSE(pq1 == pq2);
}

TEST_CASE("equality operator - empty ") {
    priorityqueue<int> pq1;
    priorityqueue<int> pq2;

    REQUIRE(pq1 == pq2);
}

//////// more dequeue tests /////
TEST_CASE("dequeue2 - duplicate priorities") {
    priorityqueue<int> pq;
    pq.enqueue(1, 3);
    pq.enqueue(2, 3);
    pq.enqueue(3, 3);
    pq.enqueue(4, 3);

    int result;
    for (int i = 1; i <= 4; i++) {
        result = pq.dequeue();
        REQUIRE(result == i);
    }
    REQUIRE(pq.Size() == 0);
}

TEST_CASE("dequeue2 - unique and duplicate priorities") {
    priorityqueue<int> pq;
    pq.enqueue(1, 1);
    pq.enqueue(2, 2);
    pq.enqueue(3, 2);
    pq.enqueue(4, 3);
    pq.enqueue(5, 3);
    pq.enqueue(6, 4);
    pq.enqueue(7, 5);
    pq.enqueue(8, 5);

    int expectedResults[] = {1, 2, 3, 4, 5, 6, 7, 8};
    int result;
    for (int i = 0; i < 8; i++) {
        result = pq.dequeue();
        REQUIRE(result == expectedResults[i]);
    }
    REQUIRE(pq.Size() == 0);
}

TEST_CASE("dequeue2 - unique priorities and balanced BST structure") {
    priorityqueue<int> pq;
    pq.enqueue(4, 4);
    pq.enqueue(2, 2);
    pq.enqueue(6, 6);
    pq.enqueue(1, 1);
    pq.enqueue(3, 3);
    pq.enqueue(5, 5);
    pq.enqueue(7, 7);

    int expectedResults[] = {1, 2, 3, 4, 5, 6, 7};
    int result;
    for (int i = 0; i < 7; i++) {
        result = pq.dequeue();
        REQUIRE(result == expectedResults[i]);
    }
    REQUIRE(pq.Size() == 0);
}

TEST_CASE("dequeue2 - unique priorities and unbalanced BST") {
    priorityqueue<int> pq;
    pq.enqueue(1, 1);
    pq.enqueue(2, 2);
    pq.enqueue(3, 3);
    pq.enqueue(4, 4);
    pq.enqueue(5, 5);
    pq.enqueue(6, 6);
    pq.enqueue(7, 7);

    int expectedResults[] = {1, 2, 3, 4, 5, 6, 7};
    int result;
    for (int i = 0; i < 7; i++) {
        result = pq.dequeue();
        REQUIRE(result == expectedResults[i]);
    }
    REQUIRE(pq.Size() == 0);
}

////// operator== tests //////
TEST_CASE("operator== - empty priority queues, equal") {
    priorityqueue<int> pq1;
    priorityqueue<int> pq2;

    REQUIRE(pq1 == pq2);
}

TEST_CASE("operator== - single element, equal") {
    priorityqueue<int> pq1;
    priorityqueue<int> pq2;

    pq1.enqueue(1, 5);
    pq2.enqueue(1, 5);

    REQUIRE(pq1 == pq2);
}

TEST_CASE("operator== - different sizes, not equal") {
    priorityqueue<int> pq1;
    priorityqueue<int> pq2;

    pq1.enqueue(1, 5);
    pq1.enqueue(2, 10);

    pq2.enqueue(1, 5);

    REQUIRE_FALSE(pq1 == pq2);
}

TEST_CASE(" operator== - duplicate priorities are equal") {
    priorityqueue<int> pq1;
    priorityqueue<int> pq2;

    pq1.enqueue(1, 5);
    pq1.enqueue(2, 5);
    pq1.enqueue(3, 10);

    pq2.enqueue(1, 5);
    pq2.enqueue(2, 5);
    pq2.enqueue(3, 10);

    REQUIRE(pq1 == pq2);
}

TEST_CASE("operator== - different elements are not equal") {
    priorityqueue<int> pq1;
    priorityqueue<int> pq2;

    pq1.enqueue(1, 5);
    pq1.enqueue(2, 3);
    pq1.enqueue(3, 7);

    pq2.enqueue(4, 5);
    pq2.enqueue(2, 3);
    pq2.enqueue(3, 7);

    REQUIRE_FALSE(pq1 == pq2);
}


//// test case from others, with citations ////

//// tduy2@uic.edu, netID 667874765. Edit: updated it, last test case was goofy.
TEST_CASE("() Next() on a very messed up tree") {
    // tree structure based on vals, for visualization:
    //       6->6.3->6.5
    //        /     \
    //    2->3         7
    //   /   \          \
    // 1       5          9
    //        /          / \
    //       4          8    10->11->12->13

    // Above tree will test progressing to right parent node (1 to 2), dupes (2 and 10 with dupe root), finding next inorder node (5 and 8)
    // root traversal (6), nodes with only right child (7) and nodes with only left child (4) and
    // finding actual next inorder node and not just going up one parent (4 to 6)
    map <int, vector<double>> map;
    int n = 15;
    double vals[] = {6, 2, 6.3, 3, 1, 5, 7, 4, 9, 8, 10, 11, 6.5, 12, 13};
    int pris[] = {9, 4, 9, 4, 2, 7, 18, 5, 20, 19, 22, 22, 9, 22, 22};
    priorityqueue<double> d;
    // Insert elements into priority queue and store priority-value pairs of each node in
    // answer map
    for (int i = 0; i < n; i++) {
        d.enqueue(vals[i], pris[i]);
        map[pris[i]].push_back(vals[i]);
    }
    REQUIRE(d.Size() == 15);

    // Fill a stringstream of the expected output, using the answer map
    stringstream ss;
    for (auto e : map) {
        int pri = e.first;
        vector<double> vals = e.second;
        for (size_t x = 0; x < vals.size(); x++) {
        ss << pri << " value: " << vals[x] << endl;
        }
    }

    REQUIRE(d.toString() == ss.str());

    d.begin(); // point curr at correct beginning node
    double valu; int prio;
    int o = 0;
    // Call next through the whole tree, check that we have the correct value and priority at curr node
    double inorder[] = {1, 2, 3, 4, 5, 6, 6.3, 6.5, 7, 8, 9, 10, 11, 12, 13};
    int inprio[] = {2, 4, 4, 5, 7, 9, 9, 9, 18, 19, 20, 22, 22, 22, 22};
    while (d.next(valu, prio) || o < n) {
        REQUIRE(valu == inorder[o]);
        REQUIRE(prio == inprio[o]);
        o++;
    }

    REQUIRE(d.Size() == 15);
    REQUIRE(d.toString() == ss.str());
}

//// Miguel Valencia , mvalen43@uic.edu 
TEST_CASE("Test<int> next() non-empty tree")
{
    priorityqueue<int> pQueue;
    int results[8] = {2, 4, 5, 6, 8, 8, 8, 11};
    pQueue.enqueue(5, 5);
    pQueue.enqueue(4, 4);
    pQueue.enqueue(2, 2);
    pQueue.enqueue(8, 8);
    pQueue.enqueue(8, 8);
    pQueue.enqueue(8, 8);
    pQueue.enqueue(6, 6);
    pQueue.enqueue(11, 11);

    int value;
    int priority;
    pQueue.begin();
    for (int i = 0; i < 8; ++i)
    {
        bool moved = pQueue.next(value, priority);
        if (i == 7)
        {
            REQUIRE(moved == false);
        }
        else
        {
            REQUIRE(moved == true);
        }
        REQUIRE(results[i] == value);
        REQUIRE(results[i] == priority);
    }
    REQUIRE(pQueue.Size() == 8);
}

TEST_CASE("Test<int> next() empty tree")
{
    priorityqueue<int> pQueue;
    int value = 0;
    int priority = 0;
    pQueue.begin();
    REQUIRE(pQueue.next(value, priority) == false);
    REQUIRE(0 == value);
    REQUIRE(0 == priority);
    REQUIRE(0 == pQueue.Size());
}

//// Sammy Haddad, shadd3@uic.edu
TEST_CASE("enqueue, dequeue, toString, size") {
    map<int, vector<int> > map;
    int n = 9;
    int vals[] = {15, 16, 17, 6, 7, 8, 9, 2, 1};
    int prs[] = {1, 2, 3, 2, 2, 2, 2, 3, 3};
    priorityqueue<int> pq;
    for (int i = 0; i < n; i++) {
        pq.enqueue(vals[i], prs[i]);
        map[prs[i]].push_back(vals[i]);
    }
    REQUIRE(pq.Size() == 9);
    stringstream ss;
    for (auto e: map) {
        int priority = e.first;
        vector <int> values = e.second;
        for (size_t j = 0; j < values.size(); j++){
            ss << priority << " value: " << values[j] << endl;
            
        }
    }
    REQUIRE(pq.toString() == ss.str());

    for (auto e: map) {
        vector <int> values = e.second;
        for (size_t j = 0; j < values.size(); j++){
            REQUIRE(pq.dequeue() == values[j]);
            
        }
    }
    REQUIRE(pq.Size() == 0);
}