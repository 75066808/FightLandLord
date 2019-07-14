#pragma once
#include "item.h"

#define PLAYER_NUM        3
#define NUM_NUM           21

#define NUM_WIDTH         0.1
#define NUM_HEIGHT        0.1

#define UPPER_NUM_LEFT    0.02
#define UPPER_NUM_TOP     0.37

#define LOWER_NUM_RIGHT   0.98
#define LOWER_NUM_TOP     0.37

class NumItem {

public:
	NumItem();
	~NumItem();

	void initNum(qint32 width, qint32 height);

	void drawUpperNum(QGraphicsScene &scene, qint32 num, qint32 width, qint32 height);
	void drawLowerNum(QGraphicsScene &scene, qint32 num, qint32 width, qint32 height);

	void clearNum(QGraphicsScene &scene);

private:
	QGraphicsPixmapItem numItem[NUM_NUM][PLAYER_NUM];


};