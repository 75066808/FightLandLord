#include "item.h"

Item::Item()
{

}

Item::~Item()
{

}

void Item::initItem(QGraphicsPixmapItem &item, QString path, qreal w, qreal h)
{
	item.setPixmap(QPixmap(path).scaled(w, h));
}

void Item::addItemToScene(QGraphicsScene &scene, QGraphicsPixmapItem &item, qreal x, qreal y)
{
	item.setPos(x, y);
	scene.addItem(&item);
}

void Item::addParentItemToScene(QGraphicsScene &scene, QGraphicsRectItem &parent, qreal x, qreal y, qreal w, qreal h)
{
	parent.setRect(QRectF(x, y, w, h));
	scene.addItem(&parent);
}

void Item::addItemToParentItem(QGraphicsScene &scene, QGraphicsPixmapItem &item, QGraphicsRectItem &parent, qreal rx, qreal ry)
{
	item.setPos(parent.rect().left() + rx * parent.rect().width(), parent.rect().top() + ry * parent.rect().height());
	item.setParentItem(&parent);
}
