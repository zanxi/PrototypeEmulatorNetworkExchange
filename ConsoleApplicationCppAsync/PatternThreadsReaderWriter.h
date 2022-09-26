#pragma once

//#include "libH.h"

struct Client {};

//std::mutex barbershop;
//std::condition_variable hasClient;
//
//const size_t ChairsNum = 5;
//std::queue<Client> clients;
//
//bool clientCame(Client c)
//{
//	{
//		std::unique_lock<std::mutex> lock(barbershop);
//		if (clients.size() == ChairsNum) return false;
//
//		clients.push(c);
//	}
//
//	hasClient.notify_one();
//	return true;
//}
//
//void barberThread()
//{
//	while (true)
//	{
//		Client c;
//		{
//			std::unique_lock<std::mutex> lock(barbershop);
//			while (clients.empty())
//			{
//				hasClient.wait(lock);
//			}
//
//			c = clients.front();
//			clients.pop();
//		}
//
//		//trim(c); // некая функция работы с клиентом
//
//	}
//}
//
//boost::shared_mutex mutex;
//
//void reader()
//{
//	boost::shared_lock<boost::shared_mutex> lock;
//}
//
//void writer()
//{
//	boost::unique_lock<boost::shared_mutex> lock;
//}
//
//void conditionalWriter()
//{
//	boost::upgrade_lock<boost::shared_mutex> need_to_write;
//	//if (need_to_write)
//	{
//		//boost::upgrade_to_unique_lock<boost::shared_mutex> uniqueuelock(lock);
//	}
//}
//
//struct Display {
//	void print(const std::string& message) {}
//};
//
//std::unique_ptr<Display> display;
//
//void print(const std::string& message)
//{
//	if (!display) display.reset(new Display());
//	display->print(message);
//}
//
//std::unique_ptr<Display> display;
//static std::once_flag displayInitFlag;
//
//void print(const std::string& message)
//{
//	std::call_once(displayInitFlag,
//		[]() {display.reset(new Display());
//		});
//	display->print(message);
//}
//
//static thread_local std::map<std::string, int> map;
//
//template <class T>
//class queue_
//{
//	bool empty() const {};
//	T pop() {};
//};
//
//class Task {};
//
//queue<Task> tasks;
//template <class T>
//class ThreadSafe
//{
//	bool tryPop(T& value)
//	{
//		std::lock_guard<std::mutex> lock(mutex);
//		if (data_.empty()) return false;
//		value = data_.front();
//		data_.pop();
//		return true;
//	}
//};
//
