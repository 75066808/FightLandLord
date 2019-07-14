#pragma once
#include "item.h"

#define PLAYER_NUM        3

#define STATE_NUM         4
#define READY_STATE       0
#define SKIP_LL_STATE     1
#define SKIP_CARD_STATE   2
#define INVALID_STATE     3

#define STATE_WIDTH       0.16
#define STATE_HEIGHT      0.08

#define SELF_STATE_TOP    0.50

#define UPPER_STATE_LEFT  0.2
#define UPPER_STATE_TOP   0.25

#define LOWER_STATE_RIGHT 0.8
#define LOWER_STATE_TOP   0.25

 
class StateItem {
	
public:
	StateItem();
	~StateItem();

	void initState(qint32 width, qint32 height);

	void drawSelfState(QGraphicsScene &scene, qint32 index, qint32 width, qint32 height);
	void drawUpperState(QGraphicsScene &scene, qint32 index, qint32 width, qint32 height);
	void drawLowerState(QGraphicsScene &scene, qint32 index, qint32 width, qint32 height);
	void clearState(QGraphicsScene &scene);

private:
	QGraphicsPixmapItem stateItem[STATE_NUM][PLAYER_NUM];
	
};