#include "libh.h"


std::mutex mu;
std::mutex m;
std::condition_variable cond;


int factorial(std::future<int>& f)
{
    int res = 1;

    int N = f.get();
    for (int i = N; i > 1; i--)res *= i;
    cout << "Result factorial is:" << res << endl;
    return res;
}

// https://www.youtube.com/watch?v=SZQ6-pf-5Us
// C++ Threading #7: Future, Promise and async()

// example async

void async_f()
{
    int x;

    std::promise<int> p;
    std::future<int> f = p.get_future();
    //std::shared_future<int> sf = f.share();

    std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f));
    std::future<int> fu2 = std::async(std::launch::async, factorial, std::ref(f));
    std::future<int> fu3 = std::async(std::launch::async, factorial, std::ref(f));

    std::this_thread::sleep_for(chrono::milliseconds(20));
    p.set_value(4);

    fu.get();
    fu2.get();
    fu3.get();
    //x = fu.get();
    //cout << "Get from child: " << x << endl;
}

void thfun1() {
    cout << "\n *************** 1 ***************** " << endl;
    cout << "Executing function1" << endl;
    std::this_thread::sleep_for(1500ms);
}

void thfun2(int i) {
    cout << "\n *************** 2 ***************** " << endl;
    cout << "Executing function2 with data " << i << endl;
    std::this_thread::sleep_for(1500ms);
}

void thfun3(int i, int j) {
    cout << "\n *************** 3 ***************** " << endl;
    cout << "Executing function3 with data " << i << " and " << j << endl;
    std::this_thread::sleep_for(1500ms);
}

int sum_thread(int thnum, int* a, int size, promise<int>& p) {
    cout << "\n *************** Summ ***************** " << endl;
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += a[i];
    }
    cout << "Output from thread t" << thnum << " is " << sum << endl;
    p.set_value(sum);
    return sum;
}

int sum_async_thread(int* a, int size) {
    cout << "\n *************** Async ***************** " << endl;
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += a[i];
    }
    return sum;
}

void exapmle()
{
    thread th1(thfun1);
    thread th2(thfun2, 2);
    thread th3(bind(thfun3, std::placeholders::_1, 2), 3);
    thread th4([](int i) {
        cout << " *************** 4 ***************** \n" << endl;
        cout << "Executing lambda function with data " << i << endl;
        std::this_thread::sleep_for(1500ms);
        }, 2);
    th1.join();
    th2.join();
    th3.join();
    th4.join();

    auto b = bind(thfun3, std::placeholders::_1, 2);
    b(4);



    int a[20];
    for (int i = 0; i < 20; i++) {
        a[i] = i;
    }

    thread t[4];
    promise<int> p[4];
    future<int> f[4];
    for (int i = 0; i < 4; i++) {
        f[i] = p[i].get_future();
        t[i] = thread(sum_thread, i, a + (i * 5), 5, std::ref(p[i]));
    }

    for (int i = 0; i < 4; i++) {
        t[i].join();
    }

    int intern_sums[4] = {};
    int sum = 0;
    for (int i = 0; i < 4; i++) {
        intern_sums[i] = f[i].get();
        sum += intern_sums[i];
    }
    cout << "Sum = " << sum << endl;

    future<int> fut = async(sum_async_thread, intern_sums, 4);
    cout << "Sum calculated by future is " << fut.get() << endl;
}


bool task(int n)
{
    cout << "\n********** task ************" << "\n";
    cout << n << "\n";
    sleep_for(1000ms);
    return true;
}

void task_f(future<int>& f)
{
    cout << "\n********** task_f ************" << "\n";
    int n = f.get();
    sleep_for(1000ms);
    cout << "\n********** task_f Done ************" << "\n";
}

// https://www.youtube.com/watch?v=vBxj-HK39Bo

void ex1()
{
    {
        int j = 245;

        future<bool> ft = std::async(task, j);

        if (ft.get())
        {
            cout << "Done 2" << endl;
        }
    }
}

void ex2()
{
    {
        packaged_task<bool(int)> tsk(task);
        future<bool> ret = tsk.get_future();
        thread th(move(tsk), 2);
        if (ret.get())
        {
            //cout << "Done 2" << endl;
        }
        th.join();
        cout << "Done 2" << endl;
    }
}

void ex3(){
    {
        promise<int> v;
        future<int> f = v.get_future();

        thread t1(task_f, ref(f));
        v.set_value(1);
        t1.join();
    }
       
}

struct foo__
{
    foo__() : a(0) {}
    void change() const { a++; }
    mutable int a;
};



int myfunc(int i) {
    m.lock();

    time_t curr_time;
    tm* curr_tm;
    char date_string[100];
    char time_string[100];

    time(&curr_time);
    curr_tm = localtime(&curr_time);

    strftime(date_string, 50, "Today is %B %d, %Y ", curr_tm);
    strftime(time_string, 50, "Current time is %T", curr_tm);

    cout << date_string << endl;
    cout << time_string << endl;

    cout << "\n Func: int myfunc() [x: " << i << "]" << endl;
    m.unlock();
    return i + 1;
}

void myfunc_reference(int& i) {
    m.lock();
    cout << "\n Func: void myfunc_reference() [x: " << i << "]" << endl;
    m.unlock();
    i = myfunc(i);
}

void ex5()
{
    const foo__ f;
    f.change();
    f.a = 100;
    cout << f.a;

    //ex1();

    unsigned int nthreads = 4;
    std::vector<int> inputs{ 1, 2, 3, 4 };
    std::vector<int> outputs_expect{ 2, 3, 4, 5 };

    // future and sync. Nirvana. When you are not fighting to death with types:
    // https://stackoverflow.com/questions/10620300/can-stdasync-be-use-with-template-functions
    {
        std::vector<std::future<int>> futures(nthreads);
        std::vector<int> outputs(nthreads);
        for (decltype(futures)::size_type i = 0; i < nthreads; ++i) {
            futures[i] = std::async(
                myfunc,
                inputs[i]
            );
        }
        for (decltype(futures)::size_type i = 0; i < nthreads; ++i) {
            outputs[i] = futures[i].get();
        }
        assert(outputs_expect == outputs);
    }

    // Reference arguments.
    //
    // Annoying because requires:
    //
    // - wrapping the return function to accept references
    // - keeping an array of outputs
    // - std::ref
    {
        std::vector<std::thread> threads(nthreads);
        std::vector<int> inouts(inputs);
        for (decltype(threads)::size_type i = 0; i < nthreads; ++i) {
            threads[i] = std::thread(myfunc_reference, std::ref(inouts[i]));
        }
        for (auto& thread : threads) {
            thread.join();
        }
        assert(outputs_expect == inouts);
    }


}



