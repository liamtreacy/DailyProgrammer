// http://www.reddit.com/r/dailyprogrammer/comments/2o5tb7/2014123_challenge_191_intermediate_space_probe/

#include <iostream>
#include <vector>

#include "assert.h"

using namespace std;

struct mapNumbers
{
    mapNumbers() : empty(1), gravityWells(1), asteroids(1)
    {}

    int empty;
    int gravityWells;
    int asteroids;
};


mapNumbers getNumbersToBeAppliedToMap(int n)
{
    // 10% of spots on map are "A" asteroids
    // 30% are "G" gravity wells
    // 60% are "." empty space

    mapNumbers t;
    int total = n*n;

    t.asteroids = total/10;
    t.gravityWells = ((total*10)/3)/10;
    t.empty = total - t.asteroids - t.gravityWells;

    return t;
}

void drawMap(vector< vector<char> > map)
{
    for (vector< vector<char> >::iterator it = map.begin(); it != map.end(); ++it)
    {
        for (vector<char>::iterator st = (*it).begin(); st != (*it).end(); ++st)
        {
            cout << *st;
        }

        cout << endl;
    }
}


void generateMap(int n)
{
    getNumbersToBeAppliedToMap(n);

    vector< vector<char> > map;

    for (int i = 0; i < n; i++)
    {
        vector<char> tmp;
        for (int j = 0; j < n; j++)
        {
            tmp.push_back('.');     // initializing all to empty space
        }

        map.push_back(tmp);
    }

    drawMap(map);
}

void runTest(int val)
{
    mapNumbers testVal;
    testVal = getNumbersToBeAppliedToMap(val);
    assert((testVal.empty + testVal.asteroids + testVal.gravityWells) == val*val);
}

void callTests()
{
    runTest(5);
    runTest(10);
    runTest(11);
    runTest(2);
    cout << "Tests ok!" << endl << endl;
}


int main()
{
    int n = 0;

    callTests();

    /*cout << "Enter value to generate NxN 2-D space map:" << endl;
    cin >> n;
    cout << endl;

    generateMap(n);*/

    return 0;
}