#pragma once

#include "Models/GameState.h"
#include "Views/CardView.h"
#include <functional>
#include <map>

class GameController
{
public:
    GameController(GameState* state, std::map<int, CardView*>* cardViews);

    void handleCardClicked(int cardId);
    void undoLastMove();

    bool canUndo() const;
    bool isInputLocked() const;
    void setUiRefreshCallback(const std::function<void()>& callback);

private:
    void tryMoveBoardCard(CardData* card);
    void tryMoveStockCard(CardData* card);
    void moveCardToHandTop(CardData* card, MoveType moveType);
    void setInputLocked(bool locked);
    void notifyUiChanged();

    static bool vectorContains(const std::vector<int>& values, int value);
    static void removeFromVector(std::vector<int>& values, int value);

private:
    GameState* _state;
    std::map<int, CardView*>* _cardViews;
    bool _inputLocked;
    int _nextZOrder;
    std::function<void()> _uiRefreshCallback;
};
