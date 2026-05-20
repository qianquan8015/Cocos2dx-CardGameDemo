#include "Views/CardView.h"
#include "Config/GameConfig.h"
#include <new>

USING_NS_CC;

CardView::CardView()
    : _cardId(-1)
    , _rank(1)
    , _suit(Suit::Clubs)
    , _faceUp(true)
    , _background(nullptr)
    , _label(nullptr)
    , _touchListener(nullptr)
{
}

CardView::~CardView()
{
    if (_touchListener)
    {
        Director::getInstance()->getEventDispatcher()->removeEventListener(_touchListener);
        CC_SAFE_RELEASE_NULL(_touchListener);
    }
}

CardView* CardView::create(const CardData& data)
{
    CardView* ret = new (std::nothrow) CardView();
    if (ret && ret->initWithData(data))
    {
        ret->autorelease();
        return ret;
    }

    CC_SAFE_DELETE(ret);
    return nullptr;
}

bool CardView::initWithData(const CardData& data)
{
    if (!Node::init())
    {
        return false;
    }

    _cardId = data.id;
    _rank = data.rank;
    _suit = data.suit;
    _faceUp = data.faceUp;

    setContentSize(Size(GameConfig::CARD_WIDTH, GameConfig::CARD_HEIGHT));
    setAnchorPoint(Vec2(0.5f, 0.5f));
    setPosition(data.currentPos);

    _background = DrawNode::create();
    addChild(_background);

    _label = Label::createWithSystemFont("", "Arial", 56);
    _label->setPosition(Vec2::ZERO);
    addChild(_label);

    refreshDisplay();

    _touchListener = EventListenerTouchOneByOne::create();
    CC_SAFE_RETAIN(_touchListener);
    _touchListener->setSwallowTouches(true);
    _touchListener->onTouchBegan = [this](Touch* touch, Event*) {
        if (!isVisible() || !containsTouch(touch))
        {
            return false;
        }

        return true;
    };
    _touchListener->onTouchEnded = [this](Touch*, Event*) {
        if (_clickCallback)
        {
            _clickCallback(_cardId);
        }
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, this);

    return true;
}

int CardView::getCardId() const
{
    return _cardId;
}

void CardView::setFaceUp(bool faceUp)
{
    _faceUp = faceUp;
    refreshDisplay();
}

void CardView::setClickCallback(const std::function<void(int)>& callback)
{
    _clickCallback = callback;
}

void CardView::moveToPosition(const Vec2& targetPos, float duration, const std::function<void()>& onComplete)
{
    stopAllActions();

    FiniteTimeAction* move = MoveTo::create(duration, targetPos);
    FiniteTimeAction* done = CallFunc::create([onComplete]() {
        if (onComplete)
        {
            onComplete();
        }
    });
    runAction(Sequence::create(move, done, nullptr));
}

void CardView::refreshDisplay()
{
    _background->clear();

    const float halfW = GameConfig::CARD_WIDTH * 0.5f;
    const float halfH = GameConfig::CARD_HEIGHT * 0.5f;
    Color4F fillColor = _faceUp ? Color4F::WHITE : Color4F(0.35f, 0.45f, 0.55f, 1.0f);
    Color4F borderColor = Color4F::BLACK;

    Vec2 verts[4] = {
        Vec2(-halfW, -halfH),
        Vec2(halfW, -halfH),
        Vec2(halfW, halfH),
        Vec2(-halfW, halfH)
    };

    _background->drawSolidPoly(verts, 4, fillColor);
    _background->drawPoly(verts, 4, true, borderColor);

    if (_faceUp)
    {
        CardData temp(_cardId, _rank, _suit, CardArea::Board, true, Vec2::ZERO);
        _label->setString(cardToString(temp));
        if (_suit == Suit::Hearts || _suit == Suit::Diamonds)
        {
            _label->setTextColor(Color4B(190, 32, 45, 255));
        }
        else
        {
            _label->setTextColor(Color4B::BLACK);
        }
    }
    else
    {
        _label->setString("?");
        _label->setTextColor(Color4B::WHITE);
    }
}

bool CardView::containsTouch(Touch* touch) const
{
    Vec2 localPos = convertToNodeSpace(touch->getLocation());
    Rect bounds(
        -GameConfig::CARD_WIDTH * 0.5f,
        -GameConfig::CARD_HEIGHT * 0.5f,
        GameConfig::CARD_WIDTH,
        GameConfig::CARD_HEIGHT);

    return bounds.containsPoint(localPos);
}
