#ifndef __GEN_HPP__
#define __GEN_HPP__

#include <array>
#include <string>
#include <sstream>
#include <algorithm>

struct nolock_impl
{
	nolock_impl(bool) {}
	static void lock() {}
	static void unlock() {}
};

template <typename LOCK_IMPL_TYPE = nolock_impl>
class gen
{
	enum class state_kind
	{
		INIT = 0,
		NEXT,
		INVALID
	};
private:
	const char DASH_SYMBOL{ '-' };
	const int MAX_GROUP_COUNT{ 10 };
private:
	using char_arr_type = std::array<char, 19>;
	using int_arr_type = std::array<int, 9>;
	inline static char_arr_type _als{ 'A','B','C','E','H','I','K','L','N','O','P','R','S','T','U','W','X','Y','Z' };
	inline static int_arr_type _dts{ 1,2,3,4,5,6,7,8,9 };
private:
	state_kind _state{ state_kind::INIT };
	int _group_count{ 0 };
	std::stringstream _head;
private:
	using al_it_type = char_arr_type::iterator;
	using dt_it_type = int_arr_type::iterator;
	al_it_type _al_2nd_last_it, _al_last_it;
	dt_it_type _dt_2nd_last_it, _dt_last_it;
private:
	void init_id(std::stringstream& ss);
	void next_id(std::stringstream& ss);
public:
	gen() = default;
	~gen() = default;
	gen(const gen& that);
	gen(gen&& that);
	gen& operator=(const gen& that);
	gen& operator=(gen&& that);
public:
	bool has_err() const;
	const std::string next_id(bool lock = true);
	void set_id(const std::string& id, bool lock = true);
public:
	void lock();
	void unlock();
};

//implementation

template <typename LOCK_IMPL_TYPE>
gen<LOCK_IMPL_TYPE>::gen(const gen<LOCK_IMPL_TYPE>& that)
	: _state(that._state)
	, _group_count(that._group_count)
	, _head(that._head.str())
	, _al_2nd_last_it(that._al_2nd_last_it)
	, _dt_2nd_last_it(that._dt_2nd_last_it)
	, _al_last_it(that._al_last_it)
	, _dt_last_it(that._dt_last_it)
{
}

template <typename LOCK_IMPL_TYPE>
gen<LOCK_IMPL_TYPE>::gen(gen<LOCK_IMPL_TYPE>&& that)
	: _state(std::move(that._state))
	, _group_count(std::move(that._group_count))
	, _head(std::move(that._head))
	, _al_2nd_last_it(std::move(that._al_2nd_last_it))
	, _dt_2nd_last_it(std::move(that._dt_2nd_last_it))
	, _al_last_it(std::move(that._al_last_it))
	, _dt_last_it(std::move(that._dt_last_it))

{
}

template <typename LOCK_IMPL_TYPE>
gen<LOCK_IMPL_TYPE>& gen<LOCK_IMPL_TYPE>::operator=(const gen<LOCK_IMPL_TYPE>& other)
{
	_state = other._state;
	_group_count = other._group_count;
	_head << other._head.str();
	_al_2nd_last_it = other._al_2nd_last_it;
	_dt_2nd_last_it = other._dt_2nd_last_it;
	_al_last_it = other._al_last_it;
	_dt_last_it = other._dt_last_it;

	return *this;
}

template <typename LOCK_IMPL_TYPE>
gen<LOCK_IMPL_TYPE>& gen<LOCK_IMPL_TYPE>::operator=(gen<LOCK_IMPL_TYPE>&& other)
{
	_state = std::move(other._state);
	_group_count = std::move(other._group_count);
	_head = std::move(other._head);
	_al_2nd_last_it = std::move(other._al_2nd_last_it);
	_dt_2nd_last_it = std::move(other._dt_2nd_last_it);
	_al_last_it = std::move(other._al_last_it);
	_dt_last_it = std::move(other._dt_last_it);

	return *this;
}

template <typename LOCK_IMPL_TYPE>
void gen<LOCK_IMPL_TYPE>::init_id(std::stringstream& ss)
{
	_al_2nd_last_it = _al_last_it = std::begin(_als);
	_dt_2nd_last_it = _dt_last_it = std::begin(_dts);
	_state = state_kind::NEXT;
	_group_count = 1;
	_head.clear();
	ss << *_al_last_it << *_dt_last_it;
}

template <typename LOCK_IMPL_TYPE>
void gen<LOCK_IMPL_TYPE>::next_id(std::stringstream& ss)
{
	if (_group_count == 1)
	{
		if (++_dt_last_it != std::end(_dts))
			ss << *_al_last_it << *_dt_last_it;
		else if (++_al_last_it != std::end(_als))
		{
			_dt_last_it = std::begin(_dts);
			ss << *_al_last_it << *_dt_last_it;
		}
		else
		{
			_al_2nd_last_it = _al_last_it = std::begin(_als);
			_dt_2nd_last_it = _dt_last_it = std::begin(_dts);
			ss << *_al_2nd_last_it << *_dt_2nd_last_it << DASH_SYMBOL << *_al_last_it << *_dt_last_it;
			++_group_count;
		}
	}
	else if (_group_count <= MAX_GROUP_COUNT)
	{
		if (++_dt_last_it != std::end(_dts))
			ss << _head.str() << *_al_2nd_last_it << *_dt_2nd_last_it << DASH_SYMBOL << *_al_last_it << *_dt_last_it;
		else if (++_al_last_it != std::end(_als))
		{
			_dt_last_it = std::begin(_dts);
			ss << _head.str() << *_al_2nd_last_it << *_dt_2nd_last_it << DASH_SYMBOL << *_al_last_it << *_dt_last_it;
		}
		else if (auto n_dt_2nd_last_it = _dt_2nd_last_it; ++n_dt_2nd_last_it != std::end(_dts))
		{
			_dt_last_it = std::begin(_dts);
			_al_last_it = std::begin(_als);
			_dt_2nd_last_it = n_dt_2nd_last_it;
			ss << _head.str() << *_al_2nd_last_it << *_dt_2nd_last_it << DASH_SYMBOL << *_al_last_it << *_dt_last_it;
		}
		else if (auto n_al_2nd_last_it = _al_2nd_last_it; ++n_al_2nd_last_it != std::end(_als))
		{
			_dt_last_it = std::begin(_dts);
			_al_last_it = std::begin(_als);
			_dt_2nd_last_it = std::begin(_dts);
			_al_2nd_last_it = n_al_2nd_last_it;
			ss << _head.str() << *_al_2nd_last_it << *_dt_2nd_last_it << DASH_SYMBOL << *_al_last_it << *_dt_last_it;
		}
		else if (_group_count == MAX_GROUP_COUNT)
		{
			init_id(ss);
		}
		else
		{
			_head << *_al_2nd_last_it << *_dt_2nd_last_it << DASH_SYMBOL;
			_al_2nd_last_it = _al_last_it = std::begin(_als);
			_dt_2nd_last_it = _dt_last_it = std::begin(_dts);
			ss << _head.str() << *_al_2nd_last_it << *_dt_2nd_last_it << DASH_SYMBOL << *_al_last_it << *_dt_last_it;
			++_group_count;
		}
	}
}

template <typename LOCK_IMPL_TYPE>
bool gen<LOCK_IMPL_TYPE>::has_err() const
{
	return _state == state_kind::INVALID;
}

template <typename LOCK_IMPL_TYPE>
const std::string gen<LOCK_IMPL_TYPE>::next_id(bool lock /*= true*/)
{
	LOCK_IMPL_TYPE lock_impl(lock);

	if (has_err())
		return { "error" };

	std::stringstream res;

	if (_state == state_kind::INIT)
		init_id(res);
	else if (_state == state_kind::NEXT)
		next_id(res);

	return res.str();
}

template <typename LOCK_IMPL_TYPE>
void gen<LOCK_IMPL_TYPE>::set_id(const std::string& id, bool lock /*= true*/)
{
	LOCK_IMPL_TYPE lock_impl(lock);

	if (id.empty())
	{
		_state = state_kind::INIT;
		return;
	}

	auto offset{ 0 };
	auto group_closed{ false };
	for (auto i = 0; i < id.size(); ++i)
	{
		if (offset == 0)
		{
			_state = state_kind::INVALID;
			if (const auto it = std::find(std::begin(_als), std::end(_als), id[i]);
				it != std::end(_als))
			{
				_al_last_it = it;
				++offset;
				group_closed = false;
				continue;
			}
			break;
		}
		if (offset == 1)
		{
			_state = state_kind::INVALID;
			const auto d = id[i] - '0';
			if (const auto it = std::find(std::begin(_dts), std::end(_dts), d);
				it != std::end(_dts))
			{
				_dt_last_it = it;
				group_closed = true;
				++_group_count;
				++offset;
				group_closed = true;
				_state = state_kind::NEXT;
				continue;
			}
			break;
		}
		if (++offset % 3 == 0 && id[i] == '-')
		{
			_state = state_kind::INVALID;
			if (_group_count >= 2)
			{
				if (_al_2nd_last_it <= _al_last_it && _dt_2nd_last_it < _dt_last_it)
					break;
				if (_head.str().empty())
				{
					//_head <== [Z2-R6-AK- | AL...
					_head << id.substr(0, i - 2);
				}
				else
				{
					//_head{Z2-R6-AK-} <== BL- | BM...]
					_head << id.substr(i - 2, 3);
				}
			}
			_al_2nd_last_it = _al_last_it;
			_dt_2nd_last_it = _dt_last_it;
			group_closed = false;
			offset = 0;
			continue;
		}
		break;
	}

	if (!group_closed)
		_state = state_kind::INVALID;
}

template <typename LOCK_IMPL_TYPE>
void gen<LOCK_IMPL_TYPE>::lock()
{
	LOCK_IMPL_TYPE::lock();
}

template <typename LOCK_IMPL_TYPE>
void gen<LOCK_IMPL_TYPE>::unlock()
{
	LOCK_IMPL_TYPE::unlock();
}

#endif //__GEN_HPP__