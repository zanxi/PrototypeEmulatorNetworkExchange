#pragma once

#include "libH.h"

//struct resumable{
//public:
//	struct promise_type {
//		//using coro_handle = std::corouti
//	};
//};

/*
struct Task {
	// The coroutine level type
	struct promise_type {
		using coro_handle = std::experimental::coroutine_handle<promise_type>;
        auto get_return_object() { return coro_handle::from_promise(*this);  } 
		auto initial_suspend() { return std::experimental::suspend_always(); }
		auto final_suspend() noexcept { return std::experimental::suspend_always(); }
		void return_void() {}
		void unhandled_exception() { std::terminate(); }
	};

	using coro_handle = std::experimental::coroutine_handle<promise_type>;
	Task(coro_handle handle) : handle_(handle) { assert(handle); }
	Task(Task&) = delete;
	Task(Task&& rhs) :handle_(rhs.handle_) 
	{
		rhs.handle_ = nullptr;
	};

	bool resume()
	{
		if (!handle_.done()) handle_.resume();
		return !handle_.done();
	}

	~Task() {
		if (handle_)handle_.destroy();
	}


private:
	coro_handle handle_;

};

Task foo()
{
	std::cout<< "Hello"  << endl;
	co_await std::experimental::suspend_always();
	std::cout << "World" << endl;
}

void ex12()
{
	auto t = foo();
	t.resume();
	t.resume();
}
*/