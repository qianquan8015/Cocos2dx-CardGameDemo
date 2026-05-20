#include "Scenes/CardGameScene.h"
#include "Config/GameConfig.h"

USING_NS_CC;

Scene* CardGameScene::createScene()
{
    return CardGameScene::create();
}

bool CardGameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    _undoButton = nullptr;

    createBackground();
    initFixedCards();

    _controller.reset(new GameController(&_gameState, &_cardViews));
    _controller->setUiRefreshCallback([this]() {
        refreshUndoButton();
    });

    for (std::map<int, CardView*>::iterator it = _cardViews.begin(); it != _cardViews.end(); ++it)
    {
        it->second->setClickCallback([this](int cardId) {
            if (_controller)
            {
                _controller->handleCardClicked(cardId);
            }
        });
    }

    createUndoButton();
    refreshUndoButton();

    return true;
}

void CardGameScene::createBackground()
{
    LayerColor* pileArea = LayerColor::create(
        GameConfig::PILE_BG_COLOR,
        GameConfig::PILE_AREA_WIDTH,
        GameConfig::PILE_AREA_HEIGHT);
    pileArea->setPosition(Vec2::ZERO);
    addChild(pileArea, 0);

    LayerColor* boardArea = LayerColor::create(
        GameConfig::BOARD_BG_COLOR,
        GameConfig::BOARD_AREA_WIDTH,
        GameConfig::BOARD_AREA_HEIGHT);
    boardArea->setPosition(Vec2(0.0f, GameConfig::PILE_AREA_HEIGHT));
    addChild(boardArea, 0);

    Label* stockLabel = Label::createWithSystemFont("备用牌", "Arial", 34);
    stockLabel->setTextColor(Color4B(225, 236, 231, 255));
    stockLabel->setPosition(GameConfig::STOCK_CARD_POS + Vec2(0.0f, 165.0f));
    addChild(stockLabel, 1);

    Label* handLabel = Label::createWithSystemFont("顶部牌", "Arial", 34);
    handLabel->setTextColor(Color4B(225, 236, 231, 255));
    handLabel->setPosition(GameConfig::HAND_TOP_CARD_POS + Vec2(0.0f, 165.0f));
    addChild(handLabel, 1);

    Label* boardLabel = Label::createWithSystemFont("桌面牌区", "Arial", 38);
    boardLabel->setTextColor(Color4B(225, 236, 231, 255));
    boardLabel->setPosition(Vec2(GameConfig::DESIGN_WIDTH * 0.5f, GameConfig::DESIGN_HEIGHT - 95.0f));
    addChild(boardLabel, 1);
}

void CardGameScene::initFixedCards()
{
    const Vec2 boardBase(0.0f, GameConfig::PILE_AREA_HEIGHT);

    createCard(1, 4, Suit::Clubs, CardArea::HandTop, true, GameConfig::HAND_TOP_CARD_POS, 10);
    _gameState.currentTopCardId = 1;

    createCard(2, 1, Suit::Hearts, CardArea::Stock, true, GameConfig::STOCK_CARD_POS, 10);
    _gameState.stockCardIds.push_back(2);

    createCard(3, 3, Suit::Diamonds, CardArea::Board, true, boardBase + Vec2(260.0f, 1060.0f), 10);
    createCard(4, 2, Suit::Spades, CardArea::Board, true, boardBase + Vec2(510.0f, 1220.0f), 10);
    createCard(5, 3, Suit::Clubs, CardArea::Board, true, boardBase + Vec2(760.0f, 1060.0f), 10);
    createCard(6, 13, Suit::Clubs, CardArea::Board, true, boardBase + Vec2(510.0f, 820.0f), 10);

    _gameState.boardCardIds.push_back(3);
    _gameState.boardCardIds.push_back(4);
    _gameState.boardCardIds.push_back(5);
    _gameState.boardCardIds.push_back(6);
}

void CardGameScene::createCard(int cardId, int rank, Suit suit, CardArea area, bool faceUp, const Vec2& pos, int zOrder)
{
    CardData data(cardId, rank, suit, area, faceUp, pos);
    _gameState.cards[cardId] = data;

    CardView* cardView = CardView::create(data);
    cardView->setLocalZOrder(zOrder);
    addChild(cardView, zOrder);

    _cardViews[cardId] = cardView;
}

void CardGameScene::createUndoButton()
{
    Label* undoLabel = Label::createWithSystemFont("撤销", "Arial", 48);
    undoLabel->setTextColor(Color4B(245, 248, 232, 255));
    _undoButton = MenuItemLabel::create(undoLabel, [this](Ref*) {
        if (_controller)
        {
            _controller->undoLastMove();
        }
    });
    _undoButton->setDisabledColor(Color3B(130, 140, 140));
    _undoButton->setPosition(Vec2(GameConfig::DESIGN_WIDTH * 0.5f, 88.0f));

    Menu* menu = Menu::create(_undoButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    addChild(menu, 30);
}

void CardGameScene::refreshUndoButton()
{
    if (!_undoButton || !_controller)
    {
        return;
    }

    const bool enabled = _controller->canUndo();
    _undoButton->setEnabled(enabled);
    _undoButton->setOpacity(enabled ? 255 : 120);
    _undoButton->setScale(enabled ? 1.08f : 1.0f);
    _undoButton->setColor(enabled ? Color3B(255, 226, 96) : Color3B(130, 140, 140));
}
