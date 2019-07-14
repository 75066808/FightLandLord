#pragma once
#include "item.h"

#define LL_NUM            3
#define COLOR_NUM         4
#define POKER_NUM         18
#define CARD_WIDTH        0.10
#define CARD_HEIGHT       0.15

#define SLOT_LEFT         0.15
#define SLOT_TOP          0.75
#define SLOT_WIDTH        0.7
#define SLOT_HEIGHT       0.25

#define ON_HAND_TOP       0.3
#define ON_HAND_INT       0.04 
#define ON_HAND_RISE      0.2

#define LL_TOP            0.02
#define LL_INT            0.05

#define SELF_PLAY_TOP     0.45
#define SELF_PLAY_INT     0.02

#define UPPER_PLAY_LEFT   0.15
#define UPPER_PLAY_TOP    0.225
#define UPPER_PLAY_INT    0.02

#define LOWER_PLAY_RIGHT  0.8
#define LOWER_PLAY_TOP    0.225
#define LOWER_PLAY_INT    0.02


class CardItem {

public:
	CardItem();
	~CardItem();

	void initCard(qint32 width, qint32 height);

	void drawSelfCard(QGraphicsScene &scene, qint32 width, qint32 height,
					  std::shared_ptr<int> &onHandNum,
					  std::shared_ptr<CARD20> &onHandCard,
					  std::shared_ptr<BOOL20> &onHandSelected);

	void drawSelfPlayCard(QGraphicsScene &scene, qint32 width, qint32 height,
					std::shared_ptr<int> &selfHandOutNum,
					std::shared_ptr<CARD20> &selfHandOut);


	void drawUpperPlayCard(QGraphicsScene &scene, qint32 width, qint32 height,
					std::shared_ptr<int> &upperHandOutNum,
					std::shared_ptr<CARD20> &upperHandOut);

	
	void drawLowerPlayCard(QGraphicsScene &scene, qint32 width, qint32 height,
				std::shared_ptr<int> &lowerHandOutNum,
				std::shared_ptr<CARD20> &lowerHandOut);

	void drawLandLordCard(QGraphicsScene &scene, qint32 width, qint32 height);

	void clearCard(QGraphicsScene &scene);

	void setLandLord(qint32 width, qint32 height, std::shared_ptr<CARD20> &landLordCard);

	void resetLandLord(qint32 width, qint32 height);

private:
	QGraphicsRectItem cardSlot;
	QGraphicsPixmapItem cardItem[COLOR_NUM][POKER_NUM];
	QGraphicsPixmapItem landlordItem[LL_NUM];


};