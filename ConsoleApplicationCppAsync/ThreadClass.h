#pragma once

class A
{
public:
	void f(int x, char c) {
		cout << "\nclass A : f() [x: "<< x << "][c: " << c << "]\n"  << endl;
		sleep_for(1000ms);
	}
	long g(double x) { 
		cout << "\nclass A : long g(double x) [x: " << x << "]\n" << endl;		
		sleep_for(1000ms);
		return 0; 
	}
	int operator()(int N, std::string str) { 
		cout << "\nclass A : operator(int N) [N: " << N << "][Name: " << str << "]\n" << endl;
		sleep_for(1000ms);
		return 0; 
	}
};

void foo(int x) {}
int RunThread()
{
    cout << "\nclass A : RunThread() [Reurn: " << 999 << "]\n" << endl;
    return 999;
}

void ex4()
{
    A a;
    std::thread t1(a, 6, "t1");
    //std::thread t2(std::ref(a), 6, "t2");
    std::thread t2(std::move(a), 6, "t2");
    std::thread t3(A(), 6, "t3");
    std::thread t4([](int x)
        {
            cout << "\n t4 [x: " << (x * x) << "]\n" << endl;
            sleep_for(1000ms);
            return x * x;
        }, 6);
    std::thread t5(foo, 7);
    std::thread t6(&A::f, a, 8, 'W');
    std::thread t7(&A::f, &a, 8, 'W');

    packaged_task<int()> Run(RunThread);
    future<int> oRet = Run.get_future();
    thread t8(move(Run));
    t8.join();


    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    //std::async(std::launch::async, a, 6);
    //std::bind(a,6);
    //std::call_once(once_flag, a, 6);
}




