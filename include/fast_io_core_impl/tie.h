#pragma once

namespace fast_io
{

template<stream T,output_stream out>
class tie
{
	out* o;
public:
	using native_handle_type = T;
	using char_type = typename native_handle_type::char_type;
private:
	T t;
public:
	template<typename ...Args>
	requires std::constructible_from<T,Args...>
	constexpr tie(out &oo,Args&& ...args):o(std::addressof(oo)),t(std::forward<Args>(args)...){}
	constexpr auto& to() {return *o;}
	constexpr auto& native_handle() {return t;}
};
/*
template<bool err=false,character_input_stream T,output_stream out>
inline constexpr auto get(tie<T,out>& t)
{
	flush(t.to());
	return get<err>(t.native_handle());
}
*/
template<character_output_stream T,output_stream out>
inline constexpr void put(tie<T,out>& t,typename T::char_type ch)
{
	flush(t.to());
	put(t.native_handle(),ch);
}

template<input_stream T,output_stream O,std::contiguous_iterator Iter>
inline constexpr Iter read(tie<T,O>& t,Iter begin,Iter end)
{
	flush(t.to());
	return read(t.native_handle(),begin,end);
}

template<output_stream T,output_stream out>
inline constexpr void flush(tie<T,out>& t)
{
	flush(t.to());
	flush(t.native_handle());
}

template<output_stream T,output_stream out,std::contiguous_iterator Iter>
inline constexpr auto write(tie<T,out>& t,Iter begin,Iter end)
{
	flush(t.to());
	return write(t.native_handle(),begin,end);
}

template<character_output_stream T,output_stream out>
inline constexpr void fill_nc(tie<T,out>& ob,std::size_t count,typename T::char_type const& ch)
{
	flush(ob.to());
	fill_nc(ob.native_handle(),count,ch);
}

template<random_access_stream T,output_stream out,typename... Args>
inline constexpr auto seek(tie<T,out>& t,Args&& ...args)
{
	flush(t.to());
	return seek(t.native_handle(),std::forward<Args>(args)...);
}

template<io_stream T>
class self_tie
{
public:
	using native_handle_type = T;
	using char_type = typename native_handle_type::char_type;
private:
	T t;
public:
	template<typename ...Args>
	requires std::constructible_from<T,Args...>
	constexpr self_tie(Args&& ...args):t(std::forward<Args>(args)...){}
	constexpr auto& native_handle() {return t;}
};

template<io_stream T>
inline constexpr void flush(self_tie<T>& t)
{
	flush(t.native_handle());
}

template<character_output_stream T>
inline constexpr auto put(self_tie<T>& t,typename T::char_type ch)
{
	flush(t);
	return put(t.native_handle(),ch);
}

template<input_stream T,std::contiguous_iterator Iter>
inline constexpr Iter read(self_tie<T>& t,Iter begin,Iter end)
{
	flush(t);
	return read(t.native_handle(),begin,end);
}

template<output_stream T,std::contiguous_iterator Iter>
inline constexpr auto write(self_tie<T>& t,Iter begin,Iter end)
{
	flush(t);
	return write(t.native_handle(),begin,end);
}

template<character_output_stream T>
inline constexpr void fill_nc(self_tie<T>& t,std::size_t count,typename T::char_type ch)
{
	flush(t);
	fill_nc(t.native_handle(),count,ch);
}

template<random_access_stream T,typename... Args>
inline constexpr auto seek(self_tie<T>& t,Args&& ...args)
{
	flush(t);
	return seek(t.native_handle(),std::forward<Args>(args)...);
}

}