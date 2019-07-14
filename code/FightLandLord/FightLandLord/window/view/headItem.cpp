#include "headItem.h"

HeadItem::HeadItem()
{

}

HeadItem::~HeadItem()
{

}

void HeadItem::initHead(qint32 width, qint32 height)
{
	Item::initItem(headItem[FARMER_HEAD][UPPERHOUSE], "Resources/head/farmer.png", HEAD_WIDTH * width, HEAD_HEIGHT * height);
	Item::initItem(headItem[FARMER_HEAD][SELF], "Resources/head/farmer.png", HEAD_WIDTH * width, HEAD_HEIGHT * height);
	Item::initItem(headItem[FARMER_HEAD][LOWERHOUSE], "Resources/head/farmer.png", HEAD_WIDTH * width, HEAD_HEIGHT * height);

	Item::initItem(headItem[LANDLORD_HEAD][UPPERHOUSE], "Resources/head/landlord.png", HEAD_WIDTH * width, HEAD_HEIGHT * height);
	Item::initItem(headItem[LANDLORD_HEAD][SELF], "Resources/head/landlord.png", HEAD_WIDTH * width, HEAD_HEIGHT * height);
	Item::initItem(headItem[LANDLORD_HEAD][LOWERHOUSE], "Resources/head/landlord.png", HEAD_WIDTH * width, HEAD_HEIGHT * height);
}

void HeadItem::drawSelfHead(QGraphicsScene &scene, qint32 index, qint32 width, qint32 height)
{
	Item::addItemToScene(scene, headItem[index][SELF], SELF_HEAD_LEFT * width, SELF_HEAD_TOP * height);
}

void HeadItem::drawUpperHead(QGraphicsScene &scene, qint32 index, qint32 width, qint32 height)
{
	Item::addItemToScene(scene,headItem[index][UPPERHOUSE], UPPER_HEAD_LEFT * width, UPPER_HEAD_TOP * height);
}

void HeadItem::drawLowerHead(QGraphicsScene &scene, qint32 index, qint32 width, qint32 height)
{
	Item::addItemToScene(scene, headItem[index][LOWERHOUSE],(LOWER_HEAD_RIGHT - HEAD_WIDTH) * width, LOWER_HEAD_TOP * height);
}

void HeadItem::clearHead(QGraphicsScene &scene)
{
	auto itemList = scene.items();
	for (qint32 i = 0;i < HEAD_NUM;i++)
		for (qint32 j = 0;j < PLAYER_NUM;j++)
			if (itemList.contains(&headItem[i][j]))
				scene.removeItem(&headItem[i][j]);
}