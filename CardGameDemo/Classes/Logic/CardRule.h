#pragma once

#include "Models/CardData.h"
#include <cstdlib>

class CardRule
{
public:
    static bool canMatch(const CardData& selectedCard, const CardData& topCard)
    {
        return std::abs(selectedCard.rank - topCard.rank) == 1;
    }
};
