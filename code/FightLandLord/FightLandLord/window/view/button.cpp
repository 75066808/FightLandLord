#include "button.h"

Button::Button()
{

}
Button::~Button()
{

}


void Button::initButtons(QGraphicsScene &scene, qint32 width, qint32 height)
{
	Button::initButton(scene, button[ENTER_BTN], "border-image: url(:/Button/Resources/button/connect.jpg);", BTN_WIDTH * width, BTN_HEIGHT * height);
	Button::initButton(scene, button[READY_BTN], "border-image: url(:/Button/Resources/button/ready.jpg);", BTN_WIDTH * width, BTN_HEIGHT * height);
	Button::initButton(scene, button[QUIT_BTN], "border-image: url(:/Button/Resources/button/disconnect.jpg);", BTN_WIDTH * width, BTN_HEIGHT * height);
	Button::initButton(scene, button[CHOOSE_LL_BTN], "border-image: url(:/Button/Resources/button/chooseLL.jpg);", BTN_WIDTH * width, BTN_HEIGHT * height);
	Button::initButton(scene, button[SKIP_LL_BTN], "border-image: url(:/Button/Resources/button/skipLL.jpg);", BTN_WIDTH * width, BTN_HEIGHT * height);
	Button::initButton(scene, button[PLAY_CARD_BTN], "border-image: url(:/Button/Resources/button/playCard.jpg);", BTN_WIDTH * width, BTN_HEIGHT * height);
	Button::initButton(scene, button[SKIP_CARD_BTN], "border-image: url(:/Button/Resources/button/skipCard.jpg);", BTN_WIDTH * width, BTN_HEIGHT * height);
	Button::initButton(scene, button[LOSE_BTN], "border-image: url(:/Button/Resources/button/lose.jpg);", BTN_WIDTH * width, BTN_HEIGHT * height);
	Button::initButton(scene, button[WIN_BTN], "border-image: url(:/Button/Resources/button/win.jpg);", BTN_WIDTH * width, BTN_HEIGHT * height);
}

void Button::setButtonNum(qint8 num)
{
	drawBtnNum = num;
}

void Button::drawButton(QGraphicsScene &scene, qint32 index, qint32 width, qint32 height)
{
	static qreal top;
	static qreal left;
	static bool over = true;

	if (over)
	{
		top = BTN_TOP;
		left = 0.5 - (BTN_WIDTH / 2 + (qreal)(drawBtnNum - 1) / 2 * (BTN_INT + BTN_WIDTH));
		over = false;
	}
	else
	{
		left += BTN_INT + BTN_WIDTH;
	}

	addButtonToScene(button[index], left * width, top * height);
	drawBtnNum--;

	if (drawBtnNum == 0)
		over = true;
}

QPushButton& Button::getButton(qint32 index)
{
	return button[index];
}

void Button::clearButton(void)
{
	for (qint32 i = 0;i < BTN_NUM;i++)
		button[i].setVisible(false);
}

void Button::initButton(QGraphicsScene &scene, QPushButton &button, QString path, qint32 w, qint32 h)
{
	button.setStyleSheet(path);
	button.setGeometry(0, 0, w, h);
	button.setVisible(false);
	scene.addWidget(&button);
}

void Button::addButtonToScene(QPushButton &button, qreal x, qreal y)
{
	button.setGeometry(x, y, button.width(), button.height());
	button.setVisible(true);
}