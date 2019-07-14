#pragma once
#include <QGraphicsPixmapItem>

#define STATE_NUM   4
#define PLAYER_NUM  3

class StateItem {
	
public:
	StateItem();
	~StateItem();

	void init();

	void drawSelfState(qint32 index);
	void drawUpperState(qint32 index);
	void drawLowerState(qint32 index);

private:
	QGraphicsPixmapItem stateItem[STATE_NUM][PLAYER_NUM];
};