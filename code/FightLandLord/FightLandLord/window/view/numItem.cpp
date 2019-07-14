#include "numItem.h"

NumItem::NumItem()
{

}
NumItem::~NumItem()
{

}

void NumItem::initNum(qint32 width, qint32 height)
{
	for (qint8 i = 0;i < NUM_NUM;i++)
	{
		QString path = "Resources/number/";
		path.append(QString::number(i));
		path.append(".png");
		Item::initItem(numItem[i][UPPERHOUSE], path, NUM_WIDTH * width, NUM_HEIGHT * height);
		Item::initItem(numItem[i][SELF], path, NUM_WIDTH * width, NUM_HEIGHT * height);
		Item::initItem(numItem[i][LOWERHOUSE], path, NUM_WIDTH * width, NUM_HEIGHT * height);
	}
}

void NumItem::drawUpperNum(QGraphicsScene &scene, qint32 num, qint32 width, qint32 height)
{
	Item::addItemToScene(scene, numItem[num][UPPERHOUSE], UPPER_NUM_LEFT * width, UPPER_NUM_TOP * height);
}

void NumItem::drawLowerNum(QGraphicsScene &scene, qint32 num, qint32 width, qint32 height)
{
	Item::addItemToScene(scene, numItem[num][LOWERHOUSE], (LOWER_NUM_RIGHT - NUM_WIDTH) * width, LOWER_NUM_TOP * height);
}

void NumItem::clearNum(QGraphicsScene &scene)
{
	auto itemList = scene.items();
	for (qint32 i = 0;i < NUM_NUM;i++)
		for (qint32 j = 0;j < PLAYER_NUM;j++)
			if (itemList.contains(&numItem[i][j]))
				scene.removeItem(&numItem[i][j]);
}