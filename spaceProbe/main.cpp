// http://www.reddit.com/r/dailyprogrammer/comments/2o5tb7/2014123_challenge_191_intermediate_space_probe/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "assert.h"

using namespace std;


/*
    Grid is N x N

    30% of spots are "A" asteroids
    10% of spots are "G" gravity wells
    60% of spots are "." empty space

    Must be randomly populated

    Probes cannot enter Asteroids
    Spots around Gravity wells are un-unnavigable 'X'

    . = empty space
    S = start location
    E = end location
    G = gravity well
    A = Asteroid
    O = Path.
*/

enum SpotType
{
    Empty,
    Asteroid,
    GravityWell,
    GravityWellAdjacent
};

string typeToStr(SpotType type)
{
    switch (type)
    {
    case Empty:
        return ".";
    case Asteroid:
        return "A";
    case GravityWell:
        return "G";
    case GravityWellAdjacent:
        return "x";
    }
}

class Spot
{
public:
    Spot(SpotType _type) : type(_type)
    {
    }

    string toString()
    {
        return typeToStr(type);
    }

    SpotType getType()
    {
        return type;
    }

    void setAsGWAdjacent()
    {
        if (type == Empty)
        {
            type = SpotType::GravityWellAdjacent;
        }
    }

private:
    SpotType type;
};


class Grid
{
public:
    Grid(int n)
    {
        init(n);
    }

    void drawMap()
    {
        for (vector< vector<Spot> >::iterator it = map.begin(); it != map.end(); ++it)
        {
            for (vector<Spot>::iterator st = (*it).begin(); st != (*it).end(); ++st)
            {
                string tmp = (*st).toString(); 
                cout << tmp;
            }

            cout << endl;
        }
    }

private:
    void init(int n);

    vector< vector <Spot> > map;
};

void Grid::init(int n)
{
    int total = n*n;

    int numAsteroids = total / 10;
    int numGravityWells = ((total * 10) / 3) / 10;
    int numEmpty = total - numAsteroids - numGravityWells;

    vector<SpotType> gridTypes;

    // Get the numbers of each type of space obstacle needed
    for (int k = 0; k < total; k++)
    {
        if (k < numAsteroids)
        {
            gridTypes.push_back(SpotType::Asteroid);
        }
        else if (k < numGravityWells)
        {
            gridTypes.push_back(SpotType::GravityWell);
        }
        else
        {
            gridTypes.push_back(SpotType::Empty);
        }
    }

    std::random_shuffle(gridTypes.begin(), gridTypes.end());

    int count = 0;

    // Create the grid and populate with the randomised Spot values
    // Empty spots (on the same row currently) previous and after a GravityWell will be updated to
    // reflect the fact they are not navigatble
    for (int i = 0; i < n; i++)
    {
        vector<Spot> newRow;

        for (int j = 0; j < n; j++)
        {
            Spot n(gridTypes[count]);
            newRow.push_back(n);
            count++;
        }

        map.push_back(newRow);
    }

    for (vector< vector <Spot> >::iterator it = map.begin(); it != map.end(); ++it)
    {
        for (vector<Spot>::iterator jt = (*it).begin(); jt != (*it).end(); ++jt)
        {
            if ((*jt).getType() == SpotType::GravityWell)
            {
                // mark all empty spots around as adjacent
                auto j = jt;

                // previous
                if ((--j != (*it).begin()) && ((*j).getType() == SpotType::Empty))
                {
                    (*j).setAsGWAdjacent();
                }

                j++;

                // next
                if ((++j != (*it).end()) && ((*j).getType() == SpotType::Empty))
                {
                    (*j).setAsGWAdjacent();
                }

                // ::TODO:: Need to update the row previous and next to the current one
            }
        }
    }
}


int main()
{
    Grid g(50);

    cout << endl << "--Draw Map--" << endl;
    g.drawMap();
    cout << endl << "--Draw Map--" << endl;
    return 0;
}





