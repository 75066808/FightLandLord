#pragma once
#include "../model/model.h"
#include "../utility/socket/socket.h"

class modelView : public QObject {
	Q_OBJECT

public:
	modelView();
	void setSelf(const std::shared_ptr<Player>& model);
	void setUpper(const std::shared_ptr<Player>& model);
	void setLower(const std::shared_ptr<Player>& model);
	void setSocket(const std::shared_ptr<Socket>& model);

	std::shared_ptr<int> getOnHandNum();
	std::shared_ptr<CARD20> getOnHandCard();
	std::shared_ptr<BOOL20> getOnHandSelected();
	std::shared_ptr<int> getStatus();

	std::shared_ptr<int> getLowerNum();
	std::shared_ptr<CARD20> getLowerCard();
	std::shared_ptr<int> getLowerHandOutNum();
	std::shared_ptr<CARD20> getLowerHandOut();
	std::shared_ptr<int> getLowerStatus();

	std::shared_ptr<int> getUpperNum();
	std::shared_ptr<CARD20> getUpperCard();
	std::shared_ptr<int> getUpperHandOutNum();
	std::shared_ptr<CARD20> getUpperHandOut();
	std::shared_ptr<int> getUpperStatus();

signals:
	void viewModelCommandSignal(std::shared_ptr<Signal> signal);
	void viewModelNotificationSignal(std::shared_ptr<Signal> signal);

public slots:
	void viewModelCommandSlot(std::shared_ptr<Signal> signal);
	void viewModelNotificationSlot(std::shared_ptr<Signal> signal);

private:
	std::shared_ptr <Socket> socket;

	std::shared_ptr<Player> self;
	std::shared_ptr<Player> upperHouse;
	std::shared_ptr<Player> lowerHouse;

	std::shared_ptr<int> onHandNum;
	std::shared_ptr<CARD20> onHandCard;
	std::shared_ptr<BOOL20> onHandSelected;
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
};