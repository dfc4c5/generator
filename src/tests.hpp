#ifndef __TESTS_HPP__
#define __TESTS_HPP__

#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <cassert>

#include "gen.hpp"

namespace details
{
	using gen_nl_type = gen<nolock_impl>;

	inline void test_Empty_A1()
	{
		gen_nl_type g;
		auto nid = g.next_id();

		assert(nid == "A1");
	}

	inline void test_A1_A2()
	{
		gen_nl_type g;
		g.set_id("A1");
		auto nid = g.next_id();

		assert(nid == "A2");
	}

	inline void test_A2_A3()
	{
		gen_nl_type g;
		g.set_id("A2");
		auto nid = g.next_id();

		assert(nid == "A3");
	}

	inline void test_A9_B1()
	{
		gen_nl_type g;
		g.set_id("A9");
		auto nid = g.next_id();

		assert(nid == "B1");
	}

	inline void test_Z9_A1dashA1()
	{
		gen_nl_type g;
		g.set_id("Z9");
		auto nid = g.next_id();

		assert(nid == "A1-A1");
	}

	inline void test_A1dashA1_A1dashA2()
	{
		gen_nl_type g;
		g.set_id("A1-A1");
		auto nid = g.next_id();

		assert(nid == "A1-A2");
	}

	inline void test_A1dashZ9_A2dashA1()
	{
		gen_nl_type g;
		g.set_id("A1-Z9");
		auto nid = g.next_id();

		assert(nid == "A2-A1");
	}

	inline void test_MAXGROUP_A1()
	{
		gen_nl_type g;
		g.set_id("Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9");
		auto nid = g.next_id();

		assert(nid == "A1");
	}

	inline void test_C9_notD1()
	{
		gen_nl_type g;
		g.set_id("C9");
		auto nid = g.next_id();

		assert(nid != "D1");
	}

	inline void test_D1_error()
	{
		gen_nl_type g;
		g.set_id("D1");
		auto nid = g.next_id();

		assert(nid == "error");
	}

	inline void test_E9_notF1()
	{
		gen_nl_type g;
		g.set_id("E9");
		auto nid = g.next_id();

		assert(nid != "F1");
	}

	inline void test_F2_error()
	{
		gen_nl_type g;
		g.set_id("F2");
		auto nid = g.next_id();

		assert(nid == "error");
	}

	inline void test_E9_notG1()
	{
		gen_nl_type g;
		g.set_id("E9");
		auto nid = g.next_id();

		assert(nid != "G1");
	}

	inline void test_G3_error()
	{
		gen_nl_type g;
		g.set_id("G3");
		auto nid = g.next_id();

		assert(nid == "error");
	}

	inline void test_I9_notJ1()
	{
		gen_nl_type g;
		g.set_id("I9");
		auto nid = g.next_id();

		assert(nid != "J1");
	}

	inline void test_J4_error()
	{
		gen_nl_type g;
		g.set_id("J4");
		auto nid = g.next_id();

		assert(nid == "error");
	}

	inline void test_L9_notM1()
	{
		gen_nl_type g;
		g.set_id("L9");
		auto nid = g.next_id();

		assert(nid != "M1");
	}

	inline void test_M5_error()
	{
		gen_nl_type g;
		g.set_id("M5");
		auto nid = g.next_id();

		assert(nid == "error");
	}

	inline void test_P9_notQ1()
	{
		gen_nl_type g;
		g.set_id("P9");
		auto nid = g.next_id();

		assert(nid != "Q1");
	}

	inline void test_Q6_error()
	{
		gen_nl_type g;
		g.set_id("Q6");
		auto nid = g.next_id();

		assert(nid == "error");
	}

	inline void test_U9_notV1()
	{
		gen_nl_type g;
		g.set_id("U9");
		auto nid = g.next_id();

		assert(nid != "V1");
	}

	inline void test_V7_error()
	{
		gen_nl_type g;
		g.set_id("V7");
		auto nid = g.next_id();

		assert(nid == "error");
	}

	inline void test_A1_E1()
	{
		gen_nl_type g;
		g.set_id("A1");
		std::string nid;

		for (auto i = 0; i < 27; ++i)
			nid = g.next_id();

		assert(nid != "D1" && nid == "E1");
	}

	inline void test_E1_H1()
	{
		gen_nl_type g;
		g.set_id("E1");
		std::string nid;

		for (auto i = 0; i < 9; ++i)
			nid = g.next_id();

		assert(nid != "F1" && nid != "G1" && nid == "H1");
	}

	inline void test_H1_K1()
	{
		gen_nl_type g;
		g.set_id("H1");
		std::string nid;

		for (auto i = 0; i < 18; ++i)
			nid = g.next_id();

		assert(nid != "J1" && nid == "K1");
	}

	inline void test_K1_N1()
	{
		gen_nl_type g;
		g.set_id("K1");
		std::string nid;

		for (auto i = 0; i < 18; ++i)
			nid = g.next_id();

		assert(nid != "J1" && nid == "N1");
	}

	inline void test_N1_R1()
	{
		gen_nl_type g;
		g.set_id("N1");
		std::string nid;

		for (auto i = 0; i < 27; ++i)
			nid = g.next_id();

		assert(nid != "Q1" && nid == "R1");
	}

	inline void test_R1_W1()
	{
		gen_nl_type g;
		g.set_id("R1");
		std::string nid;

		for (auto i = 0; i < 36; ++i)
		{
			nid = g.next_id();
		}

		assert(nid != "V1" && nid == "W1");
	}

	class mutex_lock_impl
	{
		inline static std::mutex _m;
		bool _need_lock;
	public:
		mutex_lock_impl(bool need_lock)
			: _need_lock(need_lock)
		{
			if (need_lock)
				_m.lock();
		}
		
		~mutex_lock_impl()
		{
			if (_need_lock)
				_m.unlock();
		}

		static void lock()
		{
			_m.lock();
		}

		static void unlock()
		{
			_m.unlock();
		}
	};

	using gen_ml_type = gen<mutex_lock_impl>;

	inline void test_multi_thread()
	{
		std::string expected{ "A1-A2-A3-A4-A5-A6-A7-A8-A9-B1-B2-B3-B4-B5-B6-B7-B8" };
		std::vector<std::thread> threads;

		std::string actual;
		gen_ml_type g;
		auto routine = [&actual, &g]()
		{
			g.lock();
			const auto id = g.next_id(false);

			if (!actual.empty())
				actual += "-";
			actual += id;
			g.unlock();
		};

		for (auto i = 0; i < 17; ++i)
			threads.emplace_back(std::thread(routine));

		for (auto& t : threads)
			t.join();

		assert(expected == actual);
	}
}


void run_all_tests()
{
	using namespace details;

	test_Empty_A1();
	test_A1_A2();
	test_A2_A3();
	test_A9_B1();
	test_Z9_A1dashA1();
	test_A1dashA1_A1dashA2();
	test_A1dashZ9_A2dashA1();
	test_MAXGROUP_A1();
	test_C9_notD1();
	test_D1_error();
	test_E9_notF1();
	test_F2_error();
	test_E9_notG1();
	test_G3_error();
	test_I9_notJ1();
	test_J4_error();
	test_L9_notM1();
	test_M5_error();
	test_P9_notQ1();
	test_Q6_error();
	test_U9_notV1();
	test_V7_error();
	test_A1_E1();
	test_E1_H1();
	test_H1_K1();
	test_K1_N1();
	test_N1_R1();
	test_R1_W1();
	test_multi_thread();
}

#endif //__TESTS_HPP__
