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

class Window : public QMainWindow
{
	Q_OBJECT

public:
	Window(QWidget *parent = Q_NULLPTR);

private:
	Ui::FightLandLordClass ui;
	std::vector<QImage> cards; 
	// QPixmap* cardTempPixmap ;
	// QGraphicsPixmapItem* cardTempPixmapItem;
	// QGraphicsScene* Scene;
public slots:
	void showCardsInHand();
};

#endif
