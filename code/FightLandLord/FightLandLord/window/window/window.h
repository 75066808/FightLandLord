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

	void setOnHandNum(std::shared_ptr<int> m_onHandNum) { onHandNum = m_onHandNum; }
	void setOnHandCard(std::shared_ptr<CARD20> m_onHandCard) { onHandCard = m_onHandCard; }
	void setOnHandSelected(std::shared_ptr<BOOL20> m_onHandSelected) { onHandSelected = m_onHandSelected; }
	void setLowerNum(std::shared_ptr<int> m_lowerNum) { lowerNum = m_lowerNum; }
	void setLowerCard(std::shared_ptr<CARD20> m_lowerCard) { lowerCard = m_lowerCard; }
	void setUpperNum(std::shared_ptr<int> m_upperNum) { upperNum = m_upperNum; }
	void setUpperCard(std::shared_ptr<CARD20> m_upperCard) { upperCard = m_upperCard; }
	void setOnTableNum(std::shared_ptr<int> m_onTableNum) { onTableNum = m_onTableNum; }
	void setOnTableCard(std::shared_ptr<CARD20> m_onTableCard) { onTableCard = m_onTableCard; }
	void setLandLordNum(std::shared_ptr<int> m_landLordNum) { landLordNum = m_landLordNum; }
	void setLandLordCard(std::shared_ptr<CARD20> m_landLordCard) { landLordCard = m_landLordCard; }

protected:
	virtual void resizeEvent(QResizeEvent* size);

private:
	Ui::FightLandLordClass ui;
	
	std::shared_ptr<int> onHandNum;
	std::shared_ptr<CARD20> onHandCard;
	std::shared_ptr<BOOL20> onHandSelected;
	std::shared_ptr<int> lowerNum;
	std::shared_ptr<CARD20> lowerCard;
	std::shared_ptr<int> upperNum;
	std::shared_ptr<CARD20> upperCard;
	std::shared_ptr<int> onTableNum;
	std::shared_ptr<CARD20> onTableCard;
	std::shared_ptr<int> landLordNum;
	std::shared_ptr<CARD20> landLordCard;

	QGraphicsScene scene;
	QPixmap pixmap[4][18];
	QGraphicsPixmapItem item[4][18];
	

	void Window::addToScene(int color, int value, qreal rx, qreal ry, qreal rw, qreal rh);
	void getRatio(int x, int y, qreal &rx, qreal &ry);
	void moveItem(QGraphicsPixmapItem &item, qreal rx, qreal ry);

signals:
	void windowCommandSignal(std::shared_ptr<Signal> signal);

public slots:
	void buttonClick(void);
	void windowNotificationSlot(std::shared_ptr<Signal> signal);

};

#endif
