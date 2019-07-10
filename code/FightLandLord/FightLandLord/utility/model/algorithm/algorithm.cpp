#include "../utility/model/model.h"

const RuleCardSet operator+(const RuleCardSet& left, const RuleCardSet& right)
{
	RuleCardSet tmp;
	for (int i = 0; i <= 17; i++) {
		tmp.cardLog[i] = left.cardLog[i] + right.cardLog[i];
	}
	return tmp;
}

const RuleCardSet operator-(const RuleCardSet& left, const RuleCardSet& right)
{
	RuleCardSet tmp;
	for (int i = 0; i <= 17; i++) {
		tmp.cardLog[i] = left.cardLog[i] - right.cardLog[i];
	}
	return tmp;
}

int operator<(const RuleCardSet& left, const RuleCardSet& right)
{
	return 0;
}

int operator>(const RuleCardSet& left, const RuleCardSet& right)
{
	return 0;
}