#include "Graph/FighterVertex.hpp"

FighterVertex::FighterVertex() {}

FighterVertex::FighterVertex(Position p, int id) : Vertex(p, id) {}

void FighterVertex::doneParsing()
{
    parssingDone = true;
}

void FighterVertex::addFire(FireVertex f)
{
    if (parssingDone)
        return;
    fireLines.push_back(f);
}

FireVertex FighterVertex::getFireAt(int index) const
{
    return fireLines[index];
}

const std::vector<FireVertex>& FighterVertex::getFireLines() const
{
    return fireLines;
}
/*
true : tous les feu de f sont contenus dans la liste
false : un des feux de f n'est pas dans la liste
*/
bool FighterVertex::containsFighter(FighterVertex f) const
{
    std::vector<FireVertex> fLignes = f.getFireLines();
    for (FireVertex fire : fLignes)
    {
        bool find = false;
        for (FireVertex myFire : fireLines)
        {
            if (fire == myFire)
            {
                find = true;
                break;
            }
        }
        if (!find)
        {
            return false;
        }
    }
    return true;
}

bool FighterVertex::stopFire(FireVertex f) const
{
    for (FireVertex fire : fireLines)
    {
        if (fire == f)
        {
            return true;
        }
    }
    return false;
}

int FighterVertex::getFireCapacity() const
{
    return fireLines.size();
}