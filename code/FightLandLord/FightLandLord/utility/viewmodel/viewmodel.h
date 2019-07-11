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
	void setTable(const std::shared_ptr<Table>& model);
	void setSocket(const std::shared_ptr<Socket>& model);

	std::shared_ptr<int> getOnHandNum();
	std::shared_ptr<CARD20> getOnHandCard();
	std::shared_ptr<BOOL20> getOnHandSelected();
	std::shared_ptr<int> getLowerNum();
	std::shared_ptr<CARD20> getLowerCard();
	std::shared_ptr<int> getUpperNum();
	std::shared_ptr<CARD20> getUpperCard();
	std::shared_ptr<int> getOnTableNum();
	std::shared_ptr<CARD20> getOnTableCard();
	std::shared_ptr<int> getLandLordNum();
	std::shared_ptr<CARD20> getLandLordCard();

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
	std::shared_ptr<Table> m_table;

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
};