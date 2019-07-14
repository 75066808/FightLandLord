#include "cardItem.h"

CardItem::CardItem()
{

}
CardItem::~CardItem()
{

}

void CardItem::initCard(qint32 width, qint32 height)
{
	QString colorName[4];
	QString valueName[16];
	QString tempName("JQKA2");

	colorName[0] = "spade";
	colorName[1] = "heart";
	colorName[2] = "club";
	colorName[3] = "diamond";

	for (qint8 value = 3;value < 16;value++)
	{
		if (value >= 3 && value <= 10)
			valueName[value] = QString::number(value);
		else
			valueName[value] = tempName[value - 11];
	}

	for (qint32 color = 0;color < 4;color++)
	{
		for (qint32 value = 3;value <= 15;value++)
		{
			QString path;
			path.append("Resources/poker/");
			path.append(colorName[color]);
			path.append(valueName[value]);
			path.append(".jpg");
			Item::initItem(cardItem[color][value], path, CARD_WIDTH * width , CARD_HEIGHT * height);
		}
	}

	QString path;
	path = "Resources/poker/joker2.jpg";
	Item::initItem(cardItem[0][16], path, CARD_WIDTH * width, CARD_HEIGHT * height);
	path = "Resources/poker/joker1.jpg";
	Item::initItem(cardItem[0][17], path, CARD_WIDTH * width, CARD_HEIGHT * height);
	path = "Resources/poker/card_back.png";
	Item::initItem(landlordItem[0], path, CARD_WIDTH * width, CARD_HEIGHT * height);
	Item::initItem(landlordItem[1], path, CARD_WIDTH * width, CARD_HEIGHT * height);
	Item::initItem(landlordItem[2], path, CARD_WIDTH * width, CARD_HEIGHT * height);

}

void CardItem::drawSelfCard(QGraphicsScene &scene, qint32 width, qint32 height,
							std::shared_ptr<int> &onHandNum,
							std::shared_ptr<CARD20> &onHandCard,
							std::shared_ptr<BOOL20> &onHandSelected)
{
	qreal top = ON_HAND_TOP;
	qreal left = 0.5 - ((*onHandNum - 1) * ON_HAND_INT + CARD_WIDTH / SLOT_WIDTH) / 2;

	Item::addParentItemToScene(scene, cardSlot, SLOT_LEFT * width , SLOT_TOP * height, SLOT_WIDTH * width, SLOT_HEIGHT * height);
	for (qint32 i = 0; i < *onHandNum;i++)
	{
		qint32 color = onHandCard->cards[i].color;
		qint32 value = onHandCard->cards[i].i;
		if (onHandSelected->bools[i] != 1)
			Item::addItemToParentItem(scene, cardItem[color][value], cardSlot, left, top);
		else
			Item::addItemToParentItem(scene, cardItem[color][value], cardSlot, left, top - ON_HAND_RISE);
		left += ON_HAND_INT;
	}
}

void CardItem::drawSelfPlayCard(QGraphicsScene &scene, qint32 width, qint32 height,
								std::shared_ptr<int> &selfHandOutNum,
								std::shared_ptr<CARD20> &selfHandOut)
{
	qreal top = SELF_PLAY_TOP;
	qreal left = 0.5 - ((*selfHandOutNum - 1) * SELF_PLAY_INT + CARD_WIDTH) / 2;

	for (qint32 i = 0; i < *selfHandOutNum;i++)
	{
		qint32 color = selfHandOut->cards[i].color;
		qint32 value = selfHandOut->cards[i].i;
		Item::addItemToScene(scene, cardItem[color][value], left * width, top * height);
		left += SELF_PLAY_INT;
	}
}


void CardItem::drawUpperPlayCard(QGraphicsScene &scene, qint32 width, qint32 height,
								std::shared_ptr<int> &upperHandOutNum,
								std::shared_ptr<CARD20> &upperHandOut)
{
	qreal top = UPPER_PLAY_TOP;
	qreal left = UPPER_PLAY_LEFT;

	for (qint32 i = 0; i < *upperHandOutNum;i++)
	{
		qint32 color = upperHandOut->cards[i].color;
		qint32 value = upperHandOut->cards[i].i;
		Item::addItemToScene(scene, cardItem[color][value], left * width, top * height);
		left += UPPER_PLAY_INT;
	}
}


void CardItem::drawLowerPlayCard(QGraphicsScene &scene, qint32 width, qint32 height,
								std::shared_ptr<int> &lowerHandOutNum,
								std::shared_ptr<CARD20> &lowerHandOut)
{
	qreal top = LOWER_PLAY_TOP;
	qreal left = LOWER_PLAY_RIGHT - CARD_WIDTH - (*lowerHandOutNum - 1)*LOWER_PLAY_INT;

	for (qint32 i = 0; i < *lowerHandOutNum;i++)
	{
		qint32 color = lowerHandOut->cards[i].color;
		qint32 value = lowerHandOut->cards[i].i;
		Item::addItemToScene(scene, cardItem[color][value], left * width, top * height);
		left += LOWER_PLAY_INT;
	}
}



void CardItem::drawLandLordCard(QGraphicsScene &scene, qint32 width, qint32 height)
{
	qreal top = LL_TOP;
	qreal left = 0.5 - (2 * LL_INT + CARD_WIDTH) / 2;

	for (qint32 i = 0; i < 3;i++)
	{
		Item::addItemToScene(scene, landlordItem[i], left * width, top * height);
		left += SELF_PLAY_INT;
	}
}

void CardItem::clearCard(QGraphicsScene &scene)
{
	auto itemList = scene.items();
	auto childList = cardSlot.childItems();

	for (qint32 i = 0;i < COLOR_NUM;i++)
	{
		for (qint32 j = 0;j < POKER_NUM;j++)
		{
			if (itemList.contains(&cardItem[i][j]))
				scene.removeItem(&cardItem[i][j]);
			if (childList.contains(&cardItem[i][j]))
				cardItem[i][j].setParentItem(nullptr);
		}
	}


	for (qint32 i = 0;i < LL_NUM;i++)
		if (itemList.contains(&landlordItem[i]))
			scene.removeItem(&landlordItem[i]);

	if (itemList.contains(&cardSlot))
		scene.removeItem(&cardSlot);
}