#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_window.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QTransform>

#include "../view/button.h"
#include "../view/numItem.h"
#include "../view/cardItem.h"
#include "../view/headItem.h"
#include "../view/stateItem.h"


class customScene : public QGraphicsScene
{
	Q_OBJECT

	void mousePressEvent(QGraphicsSceneMouseEvent* event);
signals:
	void windowCommandSignal(std::shared_ptr<Signal> signal);
};

class Window : public QMainWindow
{
	Q_OBJECT

public:
	Window(QWidget *parent = Q_NULLPTR);
	~Window();

	void initWindow(void);

	void setOnHandNum(std::shared_ptr<int> onHandNum) { this->onHandNum = onHandNum; }
	void setOnHandCard(std::shared_ptr<CARD20> onHandCard) { this->onHandCard = onHandCard; }
	void setOnHandSelected(std::shared_ptr<BOOL20> onHandSelected) { this->onHandSelected = onHandSelected; }
	void setSelfHandOutNum(std::shared_ptr<int> selfHandOutNum) { this->selfHandOutNum = selfHandOutNum; }
	void setSelfHandOut(std::shared_ptr<CARD20> selfHandOut) { this->selfHandOut = selfHandOut; }
	void setStatus(std::shared_ptr<int> selfStatus) { this->selfStatus = selfStatus; }

	void setLowerNum(std::shared_ptr<int> lowerNum) { this->lowerNum = lowerNum; }
	void setLowerCard(std::shared_ptr<CARD20> lowerCard) { this->lowerCard = lowerCard; }
	void setLowerHandOutNum(std::shared_ptr<int> lowerHandOutNum) { this->lowerHandOutNum = lowerHandOutNum; }
	void setLowerHandOut(std::shared_ptr<CARD20> lowerHandOut) { this->lowerHandOut = lowerHandOut; }
	void setLowerStatus(std::shared_ptr<int> lowerStatus) { this->lowerStatus = lowerStatus; }

	void setUpperNum(std::shared_ptr<int> upperNum) { this->upperNum = upperNum; }
	void setUpperCard(std::shared_ptr<CARD20> upperCard) { this->upperCard = upperCard; }
	void setUpperHandOutNum(std::shared_ptr<int> upperHandOutNum) { this->upperHandOutNum = upperHandOutNum; }
	void setUpperHandOut(std::shared_ptr<CARD20> upperHandOut) { this->upperHandOut = upperHandOut; }
	void setUpperStatus(std::shared_ptr<int> upperStatus) { this->upperStatus = upperStatus; }

	void setLandLordNum(std::shared_ptr<int> landLordNum) { this->landLordNum = landLordNum; }
	void setLandLordCard(std::shared_ptr<CARD20> landLordCard) { this->landLordCard = landLordCard; }
	void setLandLord(std::shared_ptr<int> landLord) { this->landLord = landLord; }
	void setTimeSec(std::shared_ptr<qint8> timeSec) { this->timeSec = timeSec; }
	customScene* getScene(void) { return &scene; }

protected:
	virtual void resizeEvent(QResizeEvent* size);

private:
	Ui::FightLandLordClass ui;
	
	std::shared_ptr<int> onHandNum;
	std::shared_ptr<CARD20> onHandCard;
	std::shared_ptr<BOOL20> onHandSelected;
	std::shared_ptr<int> selfHandOutNum;
	std::shared_ptr<CARD20> selfHandOut;
	std::shared_ptr<int> selfStatus;

	std::shared_ptr<int> lowerNum;
	std::shared_ptr<int> lowerHandOutNum;
	std::shared_ptr<CARD20> lowerCard;
	std::shared_ptr<CARD20> lowerHandOut;
	std::shared_ptr<int> lowerStatus;

	std::shared_ptr<int> upperNum;
	std::shared_ptr<int> upperHandOutNum;
	std::shared_ptr<CARD20> upperCard;
	std::shared_ptr<CARD20> upperHandOut;
	std::shared_ptr<int> upperStatus;

	std::shared_ptr<int> landLordNum;
	std::shared_ptr<CARD20> landLordCard;
	std::shared_ptr<int> landLord;
	std::shared_ptr<qint8> timeSec;

	customScene scene;
	Button buttonItems;
	NumItem numItems;
	CardItem cardItems;
	HeadItem headItems;
	StateItem stateItems;

	void clearWindow(void);
	void updateWindow(std::shared_ptr<Signal> signal);
	void drawBackGround(void);


signals:
	void windowCommandSignal(std::shared_ptr<Signal> signal);

public slots:
	void connectBtnClick(void);
	void disconnectBtnClick(void);
	void readyBtnClick(void);
	void chooseLandLordBtnClick(void);
	void skipLandLordBtnClick(void);
	void playCardBtnClick(void);
	void skipCardBtnClick(void);
	void proceedBtnClick(void);
	void endBtnClick(void);

	void windowNotificationSlot(std::shared_ptr<Signal> signal);
};
