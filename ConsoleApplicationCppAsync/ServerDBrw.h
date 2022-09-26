#pragma once

#include "RWLockDBServer.h"
#include "libh.h"


class ServerDBrw {
	mutable RWLockDBServer m_lock;	// mutable: can be modified even in const methods
	double m_RecordDB = 0;	// Database accountDB balance

public:
	void UpdateRecordDB(double amount) {
		m_lock.lockW();
		m_RecordDB += amount;

		//std::cout << "\nUpdateRecordDB [" << m_RecordDB << "]\n" << endl;

		this_thread::sleep_for(chrono::milliseconds(90));
		m_lock.unlockW();
	}

	double getBalance() const {
		m_lock.lockR();
		this_thread::sleep_for(chrono::milliseconds(50));
		m_lock.unlockR();
		return m_RecordDB;
	}

	size_t getReaders() const {
		return m_lock.getReaders();
	}
};