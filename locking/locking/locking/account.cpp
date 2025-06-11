#include <cstdio>
#include <string>
#include <mutex>
#include "account.h"

using std::string;
using std::mutex;

void Account::add(unsigned int tpounds, unsigned int tpence)
{
	mutex bill_mutex;

	std::unique_lock<std::mutex> lock(bill_mutex);

	pounds_ += tpounds;
	pence_ += tpence;

	// Ensure pence_ stays in the range 0-99.
	if (pence_ >= 100) {
		pounds_++;
		pence_ -= 100;
	}
}

string Account::total()
{
	char buf[40];
	snprintf(buf, sizeof buf, "GBP %u.%02u", pounds_, pence_);
	return string(buf);
}