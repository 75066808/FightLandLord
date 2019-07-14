#pragma once
#include "item.h"

#define PLAYER_NUM        3
#define NUM_NUM           21
#define CLOCK_NUM         16

#define NUM_WIDTH         0.1
#define NUM_HEIGHT        0.1

#define CLOCK_WIDTH       0.16
#define CLOCK_HEIGHT      0.08

#define UPPER_NUM_LEFT    0.02
#define UPPER_NUM_TOP     0.37

#define LOWER_NUM_RIGHT   0.98
#define LOWER_NUM_TOP     0.37

#define SELF_CLOCK_LEFT   0.42
#define SELF_CLOCK_TOP    0.50

#define UPPER_CLOCK_LEFT  0.15
#define UPPER_CLOCK_TOP   0.25

#define LOWER_CLOCK_RIGHT 0.8
#define LOWER_CLOCK_TOP   0.25

class NumItem {

public:
	NumItem();
	~NumItem();

	void initNum(qint32 width, qint32 height);

	void drawUpperNum(QGraphicsScene &scene, qint32 num, qint32 width, qint32 height);
	void drawLowerNum(QGraphicsScene &scene, qint32 num, qint32 width, qint32 height);

	void drawSelfClock(QGraphicsScene &scene, qint32 num, qint32 width, qint32 height);
	void drawUpperClock(QGraphicsScene &scene, qint32 num, qint32 width, qint32 height);
	void drawLowerClock(QGraphicsScene &scene, qint32 num, qint32 width, qint32 height);

	void clearNum(QGraphicsScene &scene);

private:
	QGraphicsPixmapItem numItem[NUM_NUM][PLAYER_NUM];
	QGraphicsPixmapItem clockItem[CLOCK_NUM][PLAYER_NUM];

};