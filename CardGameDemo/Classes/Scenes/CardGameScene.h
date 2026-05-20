#pragma once

#include "cocos2d.h"
#include "Logic/GameController.h"
#include "Models/GameState.h"
#include "Views/CardView.h"
#include <map>
#include <memory>

class CardGameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;
    CREATE_FUNC(CardGameScene);

private:
    void createBackground();
    void initFixedCards();
    void createCard(int cardId, int rank, Suit suit, CardArea area, bool faceUp, const cocos2d::Vec2& pos, int zOrder);
    void createUndoButton();
    void refreshUndoButton();

private:
    GameState _gameState;
    std::map<int, CardView*> _cardViews;
    std::unique_ptr<GameController> _controller;
    cocos2d::MenuItemLabel* _undoButton;
};
