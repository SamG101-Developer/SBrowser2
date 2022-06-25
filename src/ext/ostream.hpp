#ifndef SBROWSER2_OSTREAM_HPP
#define SBROWSER2_OSTREAM_HPP

#include <ostream>
#include <ext/map.hpp>
#include <ext/number.hpp>
#include <ext/vector.hpp>


template <typename _Valty>
std::ostream& operator<<(std::ostream& _Stream, const ext::vector<_Valty>& _Vector)
{
    _Stream << "Vector<" << typeid(_Valty).name() << "> " << "[" << _Vector.size() << "] [";
    for (auto _Iter = _Vector.begin(); _Iter != _Vector.end(); ++_Iter)
        _Stream << *_Iter << (_Iter != _Vector.end() - 1 ? ", " : "]");
    return _Stream;
}


template <typename _Keyty, typename _Valty>
std::ostream& operator<<(std::ostream& _Stream, const ext::map<_Keyty, _Valty>& _Map)
{
    _Stream << "Map<" << typeid(_Keyty).name() << ", " << typeid(_Valty).name() << "> " << "[" << _Map.size() << "] {";
    for (auto _Iter = _Map.begin(); _Iter != _Map.end(); ++_Iter)
        _Stream << "{" << (*_Iter).first << ": " << (*_Iter).second << "}" << (_Iter != _Map.end() - 1 ? ", " : "}");
    return _Stream;
}


template <typename _Keyty, typename _Valty>
std::ostream& operator<<(std::ostream& _Stream, const std::pair<_Keyty, _Valty>& _Pair)
{
    _Stream << "pair<" << typeid(_Keyty).name() << ", " << typeid(_Valty).name() << "> ";
    return _Stream << "{" << _Pair.first << ": " << _Pair.second << "}";
}


template <primitive_numeric _Tx>
auto operator<<(std::ostream& _Out, const ext::number<_Tx>& _Val) -> std::ostream&
{
    return _Out << typeid(_Val).name() << ": " << static_cast<_Tx>(_Val) << std::endl;
}



#endif //SBROWSER2_OSTREAM_HPP
