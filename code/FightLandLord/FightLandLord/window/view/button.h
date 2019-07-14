#pragma once
#include <QPushButton>
#include <QGraphicsScene>

#define BTN_NUM           9

#define ENTER_BTN         0
#define QUIT_BTN          1
#define READY_BTN         2
#define CHOOSE_LL_BTN     3
#define SKIP_LL_BTN       4
#define PLAY_CARD_BTN     5
#define SKIP_CARD_BTN     6
#define PROCEED_BTN       7
#define END_BTN           8

#define BTN_WIDTH         0.16
#define BTN_HEIGHT        0.08

#define BTN_TOP           0.64
#define BTN_INT           0.05

class Button {

public:
	Button();
	~Button();

	void initButtons(QGraphicsScene &scene, qint32 width, qint32 height);
	void setButtonNum(qint8 num);
	void drawButton(QGraphicsScene &scene, qint32 index, qint32 width, qint32 height);

	QPushButton& getButton(qint32 index);
	void clearButton(void);

	static void addButtonToScene(QPushButton &button, qreal rx, qreal ry);
	static void initButton(QGraphicsScene &scene, QPushButton &button, QString path, qint32 w, qint32 h);

private:
	QPushButton button[BTN_NUM];
	qint8 drawBtnNum;
};