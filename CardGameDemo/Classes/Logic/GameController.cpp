#include "Logic/GameController.h"
#include "Config/GameConfig.h"
#include "Logic/CardRule.h"
#include "cocos2d.h"
#include <algorithm>

GameController::GameController(GameState* state, std::map<int, CardView*>* cardViews)
    : _state(state)
    , _cardViews(cardViews)
    , _inputLocked(false)
    , _nextZOrder(100)
{
}

void GameController::handleCardClicked(int cardId)
{
    if (_inputLocked || !_state)
    {
        return;
    }

    CardData* card = _state->getCard(cardId);
    if (!card)
    {
        return;
    }

    if (card->area == CardArea::Board)
    {
        tryMoveBoardCard(card);
        return;
    }

    if (card->area == CardArea::Stock)
    {
        tryMoveStockCard(card);
    }
}

void GameController::undoLastMove()
{
    if (_inputLocked || !_state)
    {
        return;
    }

    if (_state->history.empty())
    {
        CCLOG("[CardGame] 撤销失败：没有历史记录。");
        return;
    }

    MoveRecord record = _state->history.back();
    _state->history.pop_back();

    CardData* card = _state->getCard(record.cardId);
    std::map<int, CardView*>::iterator viewIt = _cardViews->find(record.cardId);
    if (!card || viewIt == _cardViews->end())
    {
        notifyUiChanged();
        return;
    }

    setInputLocked(true);

    CardView* cardView = viewIt->second;
    cardView->setLocalZOrder(++_nextZOrder);
    cardView->moveToPosition(record.fromPos, GameConfig::CARD_MOVE_DURATION, [this, record, card]() {
        card->area = record.fromArea;
        card->currentPos = record.fromPos;
        _state->currentTopCardId = record.previousTopCardId;

        if (record.fromArea == CardArea::Board && !vectorContains(_state->boardCardIds, record.cardId))
        {
            _state->boardCardIds.push_back(record.cardId);
        }
        else if (record.fromArea == CardArea::Stock && !vectorContains(_state->stockCardIds, record.cardId))
        {
            _state->stockCardIds.push_back(record.cardId);
        }

        setInputLocked(false);
        CCLOG("[CardGame] 撤销成功：%s 已回到原位置，顶部牌恢复为 id=%d。",
            cardToString(*card).c_str(),
            record.previousTopCardId);
        notifyUiChanged();
    });
}

bool GameController::canUndo() const
{
    return _state && !_state->history.empty() && !_inputLocked;
}

bool GameController::isInputLocked() const
{
    return _inputLocked;
}

void GameController::setUiRefreshCallback(const std::function<void()>& callback)
{
    _uiRefreshCallback = callback;
}

void GameController::tryMoveBoardCard(CardData* card)
{
    if (!card->faceUp)
    {
        CCLOG("[CardGame] 匹配失败：card id=%d 未翻开。", card->id);
        return;
    }

    CardData* topCard = _state->getCurrentTopCard();
    if (!topCard || !CardRule::canMatch(*card, *topCard))
    {
        if (topCard)
        {
            CCLOG("[CardGame] 匹配失败：%s 不能匹配当前顶部牌 %s。",
                cardToString(*card).c_str(),
                cardToString(*topCard).c_str());
        }
        else
        {
            CCLOG("[CardGame] 匹配失败：当前顶部牌不存在。");
        }
        return;
    }

    CCLOG("[CardGame] 桌面牌匹配成功：%s 匹配顶部牌 %s。",
        cardToString(*card).c_str(),
        cardToString(*topCard).c_str());
    moveCardToHandTop(card, MoveType::MatchBoardCard);
}

void GameController::tryMoveStockCard(CardData* card)
{
    if (_state->stockCardIds.empty() || _state->stockCardIds.back() != card->id)
    {
        CCLOG("[CardGame] 备用牌点击无效：%s 不是当前可用备用牌。",
            cardToString(*card).c_str());
        return;
    }

    CCLOG("[CardGame] 点击备用牌：%s 移动到顶部牌位置。", cardToString(*card).c_str());
    moveCardToHandTop(card, MoveType::DrawStockCard);
}

void GameController::moveCardToHandTop(CardData* card, MoveType moveType)
{
    CardData* previousTopCard = _state->getCurrentTopCard();
    if (!previousTopCard)
    {
        return;
    }

    std::map<int, CardView*>::iterator viewIt = _cardViews->find(card->id);
    if (viewIt == _cardViews->end())
    {
        return;
    }

    MoveRecord record;
    record.cardId = card->id;
    record.fromArea = card->area;
    record.toArea = CardArea::HandTop;
    record.fromPos = card->currentPos;
    record.toPos = previousTopCard->currentPos;
    record.previousTopCardId = previousTopCard->id;
    record.newTopCardId = card->id;
    record.moveType = moveType;

    removeFromVector(_state->boardCardIds, card->id);
    removeFromVector(_state->stockCardIds, card->id);

    setInputLocked(true);

    CardView* cardView = viewIt->second;
    cardView->setLocalZOrder(++_nextZOrder);
    cardView->moveToPosition(record.toPos, GameConfig::CARD_MOVE_DURATION, [this, record, card]() {
        card->area = CardArea::HandTop;
        card->currentPos = record.toPos;
        _state->currentTopCardId = record.newTopCardId;
        _state->history.push_back(record);

        setInputLocked(false);
        notifyUiChanged();
    });
}

void GameController::setInputLocked(bool locked)
{
    _inputLocked = locked;
    notifyUiChanged();
}

void GameController::notifyUiChanged()
{
    if (_uiRefreshCallback)
    {
        _uiRefreshCallback();
    }
}

bool GameController::vectorContains(const std::vector<int>& values, int value)
{
    return std::find(values.begin(), values.end(), value) != values.end();
}

void GameController::removeFromVector(std::vector<int>& values, int value)
{
    values.erase(std::remove(values.begin(), values.end(), value), values.end());
}
