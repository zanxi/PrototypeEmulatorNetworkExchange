// ConsoleApplicationCppAsync.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "Threaf_f.h"
#include "ConcurrentMap.h"
#include "ThreadClass.h"
#include "Task1rw.h"
#include "ServerDBrw.h"

//contfree_safe_ptr<std::map<string, int>> safe_map_string_int;

int main()
{
    //contfree_safe_ptr<std::map < long, string> >* map;
    //map = new contfree_safe_ptr<std::map < long, string> >;

    std::cout << "Begin read Devices: tcp, modbus, udp protocols !!!!\n";

    //***************************************************

	std::cout << "Пример чтения и записи в DataBase !!!!\n";
    
	const int nThreads = 8;
	const int nRuns = 8;

	mutex mtx;							// synchronized access to standard output cout
	ServerDBrw accountDB;				// synchronized Database accountDB
	double unsynchronizedaccountDB = 18;	// unsychronized Database accountDB
	thread t[nThreads];					// thread pool
	//std::map<int, int> *map_acc = new map<int,int>;
	std::map<int, int> map_acc;

	// parallel task
	auto task = [nRuns, &accountDB, &mtx, &unsynchronizedaccountDB, &map_acc] {
		srand((unsigned int)hash<thread::id>()(this_thread::get_id()));	// ensures that all threads have a different seed for the random number generator

		for (int i = 0; i < nRuns; i++) {
			if (i % 2) {
				const double amount = rand() % 10;// rand() * 1000 / RAND_MAX;
				const double b = unsynchronizedaccountDB + amount;
				accountDB.UpdateRecordDB(amount);
				//unsynchronizedaccountDB = b;
				mtx.lock();
				cout << "thread " << this_thread::get_id() << " UpdateRecord DataBase " << amount << endl;
				if (!(map_acc.find(amount) != map_acc.end()))map_acc.insert(pair<int, int>(amount, b));
				else
				{
					map_acc[amount] = b;
				}

				mtx.unlock();
			}
			const double balance = accountDB.getBalance();
			mtx.lock();
			//cout << "thread " << this_thread::get_id() << ": balance is = " << balance << ", unsychronized balance is = " << unsynchronizedaccountDB << endl;
			cout << "getReaders DataBase: [" << accountDB.getReaders() << "]" << endl;

			mtx.unlock();
		}
	};

	//map_acc->insert(pair<int,int>(1,1));

	cout << "main thread id = " << this_thread::get_id() << ", hw concurrency = " << thread::hardware_concurrency() << endl;

	// start threads
	for (int i = 0; i < nThreads; i++) {
		t[i] = thread(task);	// thread uses move-semantics: t[i] will run the task and the temporary thread will immediately finish
	}

	// join threads: main thread waits for parallel threads
	for (int i = 0; i < nThreads; i++) {
		//cout << "wait until thread " << t[i].get_id() << " has finished" << endl;
		t[i].join();
	}

	cout << "Press key!!!!!!!!!!\n" << endl;

	for (auto& v : map_acc)
	{
		std::cout << "[" << v.first << "; " << v.second << "]" << endl;
	}

	cout << "Press key!!!!!!!!!!" << endl;
	system("pause");
    
 

    cout << "Press key " << endl;
    std::getchar();
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
