#include "../headers/Rabbit.h"
#include "../headers/Grid.h"
#include "../headers/RandomUtils.h"

void Rabbit::act(const Position pos, Grid &_grid, std::unique_ptr<Actor> actor)
{
    _nextPosition = {-1,-1};

    if (_currentEnergy <= 0)
    {
        die();
        return;
    }
        try
        {
            _nextPosition = chooseNextPosition(pos, _grid);
            if (_grid.inBounds(_nextPosition))
            {
                move(pos, _nextPosition, _grid, std::move(actor));
                _currentEnergy += _movementEnergyCost;
            }
        }
        catch (const std::exception& e)
        {
            _nextPosition = pos;
        }

    tryToEat(pos, _grid);
    if (_currentEnergy >= 75 && RandomUtils::get_random_float(0,1) > 0.5)
    {
        try
        {
             reproduce(pos, _grid);
        }
        catch (const std::exception& e)
        {

        }


    }

}

void Rabbit::tryToEat(Position pos, Grid &_grid)
{
    if (_grid.getGrassLevel(pos) != 0)
    {
        _grid.eat(pos);
        _currentEnergy +=  _energyPerMeal;
    }
}

void Rabbit::die()
{
    setAlive_(false);
}

Position Rabbit::chooseNextPosition(const Position pos, const Grid &_grid) const
{
    const std::vector<Position> adj = RandomUtils::positionsAdjacent(pos);

    if (_currentEnergy <= 50)
    {
        // Check if grass is nearby

        struct grassPos
        {
            Position pos;
            int grassLevel;
        };
        std::vector<grassPos> adjGrassLevels{};
        for (const auto a : adj)
        {
            if (_grid.inBounds(a))
            {
                grassPos helper{a, _grid.getGrassLevel(a)};
                adjGrassLevels.push_back(helper);
            }

        }

        int maxLevel = 0;

        Position grassPos{-1,-1};

        for (auto [position, grassLevel] : adjGrassLevels)
        {
            if (maxLevel < grassLevel)
            {
                maxLevel = grassLevel;
                grassPos = position;
            }
        }

        if (maxLevel > 0)
        {
            return grassPos;
        }
    }



    const int randomIndex = RandomUtils::get_random_num(0, adj.size() - 1);
    if (_grid.inBounds(adj[randomIndex]))
    {
        if (_grid.get(adj[randomIndex])->hasActor())
        {
            throw std::runtime_error("Rabbit can't move to occupied position");
        }
        return adj[randomIndex];
    }
    return pos;


}

void Rabbit::reproduce(Position pos, Grid &_grid)
{
        const std::vector<Position> adj = RandomUtils::positionsAdjacent(pos);
    const int randomIndex = RandomUtils::get_random_num(0, adj.size() - 1);
    if (_grid.inBounds(adj[randomIndex]))
    {
        if (_grid.get(adj[randomIndex])->hasActor())
        {
            throw std::runtime_error("Rabbit can't be born onto an occupied position");
        }
        _currentEnergy -= getReproductionCost_();
        _grid.appendReproductionRequest(pos, adj[randomIndex], getType_());
    }
}
