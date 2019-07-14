#pragma once
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "../utility/common/common.h"

class Item {

public:
	Item();
	~Item();

	static void initItem(QGraphicsPixmapItem &item, QString path, qreal rw, qreal rh);
	static void addItemToScene(QGraphicsScene &scene, QGraphicsPixmapItem &item, qreal rx, qreal ry);
	static void addParentItemToScene(QGraphicsScene &scene, QGraphicsRectItem &parent, qreal rx, qreal ry, qreal rw, qreal rh);
	static void addItemToParentItem(QGraphicsScene &scene, QGraphicsPixmapItem &item, QGraphicsRectItem &parent, qreal rx, qreal ry);
};