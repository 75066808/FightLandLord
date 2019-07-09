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
#include <QSize>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include "../utility/common/common.h"

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
	void addCardInScene(qreal x, qreal y, QPixmap *cardTempPixmap, QGraphicsScene* scene);

public slots:
	void buttonClick(void);
	void viewModelToWindowSlot(std::shared_ptr<Signal> signal);

signals:
	void windowToViewModelSignal(std::shared_ptr<Signal> signal);
};

#endif
