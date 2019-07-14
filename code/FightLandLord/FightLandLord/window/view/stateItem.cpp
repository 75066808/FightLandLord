#include "stateItem.h"

StateItem::StateItem()
{

}
StateItem::~StateItem()
{

}

void StateItem::initState(qint32 width, qint32 height)
{
	Item::initItem(stateItem[READY_STATE][UPPERHOUSE], "Resources/state/readyState.png", STATE_WIDTH * width , STATE_HEIGHT * height);
	Item::initItem(stateItem[READY_STATE][SELF], "Resources/state/readyState.png", STATE_WIDTH * width, STATE_HEIGHT * height);
	Item::initItem(stateItem[READY_STATE][LOWERHOUSE], "Resources/state/readyState.png", STATE_WIDTH * width, STATE_HEIGHT * height);
	Item::initItem(stateItem[SKIP_LL_STATE][UPPERHOUSE], "Resources/state/skipLLState.png", STATE_WIDTH * width, STATE_HEIGHT * height);
	Item::initItem(stateItem[SKIP_LL_STATE][SELF], "Resources/state/skipLLState.png", STATE_WIDTH * width, STATE_HEIGHT * height);
	Item::initItem(stateItem[SKIP_LL_STATE][LOWERHOUSE], "Resources/state/skipLLState.png", STATE_WIDTH * width, STATE_HEIGHT * height);
	Item::initItem(stateItem[SKIP_CARD_STATE][UPPERHOUSE], "Resources/state/skipCardState.png", STATE_WIDTH * width, STATE_HEIGHT * height);
	Item::initItem(stateItem[SKIP_CARD_STATE][SELF], "Resources/state/skipCardState.png", STATE_WIDTH * width, STATE_HEIGHT * height);
	Item::initItem(stateItem[SKIP_CARD_STATE][LOWERHOUSE], "Resources/state/skipCardState.png", STATE_WIDTH * width, STATE_HEIGHT * height);
	Item::initItem(stateItem[INVALID_STATE][UPPERHOUSE], "Resources/state/invalidState.png", STATE_WIDTH * width, STATE_HEIGHT * height);
	Item::initItem(stateItem[INVALID_STATE][SELF], "Resources/state/invalidState.png", STATE_WIDTH * width, STATE_HEIGHT * height);
	Item::initItem(stateItem[INVALID_STATE][LOWERHOUSE], "Resources/state/invalidState.png", STATE_WIDTH * width, STATE_HEIGHT * height);
	Item::initItem(stateItem[WIN_STATE][SELF], "Resources/state/winState.png", STATE_WIDTH * 2 * width, STATE_HEIGHT * 2 * height);
	Item::initItem(stateItem[LOSE_STATE][SELF], "Resources/state/loseState.png", STATE_WIDTH * 2 * width, STATE_HEIGHT * 2 * height);
}

void StateItem::drawSelfState(QGraphicsScene &scene, qint32 index, qint32 width, qint32 height)
{
	if(index != WIN_STATE && index != LOSE_STATE)
		Item::addItemToScene(scene, stateItem[index][SELF], (0.5 - (STATE_WIDTH / 2)) * width, SELF_STATE_TOP * height);
	else
		Item::addItemToScene(scene, stateItem[index][SELF], (0.5 - (STATE_WIDTH / 2) - 0.1) * width, (SELF_STATE_TOP) * height);
}

void StateItem::drawUpperState(QGraphicsScene &scene, qint32 index, qint32 width, qint32 height)
{
	Item::addItemToScene(scene, stateItem[index][UPPERHOUSE], UPPER_STATE_LEFT * width, UPPER_STATE_TOP * height);
}

void StateItem::drawLowerState(QGraphicsScene &scene, qint32 index, qint32 width, qint32 height)
{
	Item::addItemToScene(scene, stateItem[index][LOWERHOUSE], (LOWER_STATE_RIGHT - STATE_WIDTH) * width, LOWER_STATE_TOP * height);
}

void StateItem::clearState(QGraphicsScene &scene)
{
	auto itemList = scene.items();

	for (qint32 i = 0;i < STATE_NUM;i++)
		for (qint32 j = 0;j < PLAYER_NUM;j++)
			if (itemList.contains(&stateItem[i][j]))
				scene.removeItem(&stateItem[i][j]);
}