#pragma once
#ifndef WINDOW_H
#define WINDOW_H
#include <QtWidgets/QMainWindow>
#include "ui_window.h"
#include <vector>
#include <QImage>
#include <QMessageBox>
#include <QPainter>
#include <QRect>
#include <QPoint>
#include <QPointF>
#include <QSize>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QTransform>
#include "../utility/common/common.h"

class customScene : public QGraphicsScene
{
	void mousePressEvent(QGraphicsSceneMouseEvent* event);
};

class Window : public QMainWindow
{
	Q_OBJECT

public:
	Window(QWidget *parent = Q_NULLPTR);
	void setCurrentCardsInHand(const qint8* cards);

private:
	Ui::FightLandLordClass ui;
	const qint8 *currentCardsInHand;
	// QPixmap* cardTempPixmap ;
	// QGraphicsPixmapItem* cardTempPixmapItem;
	// QGraphicsScene* Scene;
	void addCardInScene(qreal x, qreal y, QPixmap *cardTempPixmap, customScene* scene);
	void addHandInScene(QPixmap *cardTempPixmap, customScene *Scene);
signals:
	void windowCommandSignal(std::shared_ptr<Signal> signal);

public slots:
	void buttonClick(void);
	void windowNotificationSlot(std::shared_ptr<Signal> signal);

};

#endif
