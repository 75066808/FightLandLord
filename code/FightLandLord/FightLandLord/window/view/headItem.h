#pragma once
#include "item.h"

#define PLAYER_NUM        3
#define FARMER_HEAD       0
#define LANDLORD_HEAD     1

#define HEAD_NUM          2
#define HEAD_WIDTH        0.1
#define HEAD_HEIGHT       0.1

#define SELF_HEAD_LEFT    0.04
#define SELF_HEAD_TOP     0.8

#define UPPER_HEAD_LEFT   0.02
#define UPPER_HEAD_TOP    0.25

#define LOWER_HEAD_RIGHT  0.98
#define LOWER_HEAD_TOP    0.25


class HeadItem {

public:
	HeadItem();
	~HeadItem();

	void initHead(qint32 width, qint32 height);

	void drawSelfHead(QGraphicsScene &scene, qint32 index, qint32 width, qint32 height);
	void drawUpperHead(QGraphicsScene &scene, qint32 index, qint32 width, qint32 height);
	void drawLowerHead(QGraphicsScene &scene, qint32 index, qint32 width, qint32 height);

	void clearHead(QGraphicsScene &scene);
private:
	QGraphicsPixmapItem headItem[HEAD_NUM][PLAYER_NUM];
};