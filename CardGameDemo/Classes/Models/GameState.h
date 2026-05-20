#pragma once

#include "Models/CardData.h"
#include "Models/MoveRecord.h"
#include <map>
#include <vector>

struct GameState
{
    std::map<int, CardData> cards;
    int currentTopCardId;
    std::vector<int> boardCardIds;
    std::vector<int> stockCardIds;
    std::vector<MoveRecord> history;

    GameState()
        : currentTopCardId(-1)
    {
    }

    CardData* getCard(int cardId)
    {
        std::map<int, CardData>::iterator it = cards.find(cardId);
        if (it == cards.end())
        {
            return nullptr;
        }
        return &it->second;
    }

    const CardData* getCard(int cardId) const
    {
        std::map<int, CardData>::const_iterator it = cards.find(cardId);
        if (it == cards.end())
        {
            return nullptr;
        }
        return &it->second;
    }

    CardData* getCurrentTopCard()
    {
        return getCard(currentTopCardId);
    }
};
