#pragma once

#include "cocos2d.h"

namespace GameConfig
{
    static const float DESIGN_WIDTH = 1080.0f;
    static const float DESIGN_HEIGHT = 2080.0f;

    static const float BOARD_AREA_WIDTH = 1080.0f;
    static const float BOARD_AREA_HEIGHT = 1500.0f;
    static const float PILE_AREA_WIDTH = 1080.0f;
    static const float PILE_AREA_HEIGHT = 580.0f;

    static const float CARD_WIDTH = 160.0f;
    static const float CARD_HEIGHT = 220.0f;
    static const float CARD_MOVE_DURATION = 0.28f;

    static const cocos2d::Vec2 STOCK_CARD_POS(290.0f, 290.0f);
    static const cocos2d::Vec2 HAND_TOP_CARD_POS(790.0f, 290.0f);

    static const cocos2d::Color4B BOARD_BG_COLOR(42, 116, 82, 255);
    static const cocos2d::Color4B PILE_BG_COLOR(32, 64, 72, 255);
}
