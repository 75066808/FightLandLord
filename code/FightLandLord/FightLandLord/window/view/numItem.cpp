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
	for (qint8 i = 0;i < CLOCK_NUM;i++)
	{
		QString path = "Resources/clock/clock_";
		path.append(QString::number(i));
		path.append(".png");
		Item::initItem(clockItem[i][UPPERHOUSE], path, CLOCK_WIDTH * width, CLOCK_HEIGHT * height);
		Item::initItem(clockItem[i][SELF], path, CLOCK_WIDTH * width, CLOCK_HEIGHT * height);
		Item::initItem(clockItem[i][LOWERHOUSE], path, CLOCK_WIDTH * width, CLOCK_HEIGHT * height);
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

void NumItem::drawSelfClock(QGraphicsScene &scene, qint32 num, qint32 width, qint32 height)
{
	Item::addItemToScene(scene, clockItem[num][SELF], SELF_CLOCK_LEFT * width, SELF_CLOCK_TOP * height);
}
void NumItem::drawUpperClock(QGraphicsScene &scene, qint32 num, qint32 width, qint32 height)
{
	Item::addItemToScene(scene, clockItem[num][UPPERHOUSE], UPPER_CLOCK_LEFT * width, UPPER_CLOCK_TOP * height);
}
void NumItem::drawLowerClock(QGraphicsScene &scene, qint32 num, qint32 width, qint32 height)
{
	Item::addItemToScene(scene, clockItem[num][LOWERHOUSE], (LOWER_CLOCK_RIGHT - NUM_WIDTH) * width, LOWER_CLOCK_TOP * height);
}

void NumItem::clearNum(QGraphicsScene &scene)
{
	auto itemList = scene.items();
	for (qint32 i = 0;i < NUM_NUM;i++)
		for (qint32 j = 0;j < PLAYER_NUM;j++)
			if (itemList.contains(&numItem[i][j]))
				scene.removeItem(&numItem[i][j]);

	for (qint32 i = 0;i < CLOCK_NUM;i++)
		for (qint32 j = 0;j < PLAYER_NUM;j++)
			if (itemList.contains(&clockItem[i][j]))
				scene.removeItem(&clockItem[i][j]);

}