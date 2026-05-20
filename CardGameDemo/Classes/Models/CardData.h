#pragma once

#include "cocos2d.h"
#include <string>

enum class Suit
{
    Clubs,
    Diamonds,
    Hearts,
    Spades
};

enum class CardArea
{
    Board,
    HandTop,
    Stock
};

struct CardData
{
    int id;
    int rank;
    Suit suit;
    CardArea area;
    bool faceUp;
    cocos2d::Vec2 originalPos;
    cocos2d::Vec2 currentPos;

    CardData()
        : id(-1)
        , rank(1)
        , suit(Suit::Clubs)
        , area(CardArea::Board)
        , faceUp(true)
        , originalPos(cocos2d::Vec2::ZERO)
        , currentPos(cocos2d::Vec2::ZERO)
    {
    }

    CardData(int cardId, int cardRank, Suit cardSuit, CardArea cardArea, bool isFaceUp, const cocos2d::Vec2& pos)
        : id(cardId)
        , rank(cardRank)
        , suit(cardSuit)
        , area(cardArea)
        , faceUp(isFaceUp)
        , originalPos(pos)
        , currentPos(pos)
    {
    }
};

inline std::string suitToString(Suit suit)
{
    switch (suit)
    {
    case Suit::Clubs:
        return "\xE2\x99\xA3";
    case Suit::Diamonds:
        return "\xE2\x99\xA6";
    case Suit::Hearts:
        return "\xE2\x99\xA5";
    case Suit::Spades:
        return "\xE2\x99\xA0";
    default:
        return "?";
    }
}

inline std::string rankToString(int rank)
{
    switch (rank)
    {
    case 1:
        return "A";
    case 11:
        return "J";
    case 12:
        return "Q";
    case 13:
        return "K";
    default:
        return cocos2d::StringUtils::format("%d", rank);
    }
}

inline std::string cardToString(const CardData& card)
{
    return suitToString(card.suit) + rankToString(card.rank);
}
