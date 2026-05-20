#pragma once

#include "cocos2d.h"
#include "Models/CardData.h"

enum class MoveType
{
    MatchBoardCard,
    DrawStockCard
};

struct MoveRecord
{
    int cardId;
    CardArea fromArea;
    CardArea toArea;
    cocos2d::Vec2 fromPos;
    cocos2d::Vec2 toPos;
    int previousTopCardId;
    int newTopCardId;
    MoveType moveType;

    MoveRecord()
        : cardId(-1)
        , fromArea(CardArea::Board)
        , toArea(CardArea::HandTop)
        , fromPos(cocos2d::Vec2::ZERO)
        , toPos(cocos2d::Vec2::ZERO)
        , previousTopCardId(-1)
        , newTopCardId(-1)
        , moveType(MoveType::MatchBoardCard)
    {
    }
};
