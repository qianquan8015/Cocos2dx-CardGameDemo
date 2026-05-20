#pragma once

#include "cocos2d.h"
#include "Models/CardData.h"
#include <functional>

class CardView : public cocos2d::Node
{
public:
    static CardView* create(const CardData& data);

    bool initWithData(const CardData& data);

    int getCardId() const;
    void setFaceUp(bool faceUp);
    void setClickCallback(const std::function<void(int)>& callback);
    void moveToPosition(const cocos2d::Vec2& targetPos, float duration, const std::function<void()>& onComplete);

private:
    CardView();
    virtual ~CardView();

    void refreshDisplay();
    bool containsTouch(cocos2d::Touch* touch) const;

private:
    int _cardId;
    int _rank;
    Suit _suit;
    bool _faceUp;
    cocos2d::DrawNode* _background;
    cocos2d::Label* _label;
    cocos2d::EventListenerTouchOneByOne* _touchListener;
    std::function<void(int)> _clickCallback;
};
