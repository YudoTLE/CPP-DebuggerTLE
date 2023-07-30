// MIT License

// Copyright (c) 2023 Ariyudo Pertama

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#ifndef _TLE_DEBUG_CPP
#define _TLE_DEBUG_CPP 1


// Constructor and Destructor
DEBUG::DEBUG()
    {}

template <typename... _Tps>
DEBUG::DEBUG(std::string _label, const _Tps&... _items)
    : label(_label), delayed_print([&, _items...]() { return print_output(_items...); })
    {}

DEBUG::~DEBUG()
{
    depth *= !force_horizontal;
    generate_labels(label);
    delayed_print();
}


// Main Control
void DEBUG::generate_labels(std::string _label)
{
    int  indent_depth    = 0;
    bool on_quote        = false;
    bool on_double_quote = false;

    for (char& c : _label)
    {
        if (c == ' ' && !on_quote && !on_double_quote)
            continue;

        indent_depth    += c == '(' || c == '{' || c == '[' || c == '<';
        indent_depth    -= c == ')' || c == '}' || c == ']' || c == '>';
        on_quote        ^= c == '\'';
        on_double_quote ^= c == '\"';

        if (c == ',' && !indent_depth && !on_quote && !on_double_quote)
        {
            if (force_horizontal)
                labels.back() += DEBUG_SEPARATOR;
            else
                labels.push_back(depth ? DEBUG_HEADING : "");
            continue;
        }
        labels.back() += c;
    }
}


template <typename _Tp>
void DEBUG::print_output(const _Tp& _item)
{
    if (!labels.empty())
    {
        std::cout << labels.front() << DEBUG_EQUAL;
        labels.pop_front();
    }
    print(_item);
    std::cout << '\n';
}

template <typename _Tp, typename... _Tps>
void DEBUG::print_output(const _Tp& _item, const _Tps&... _items)
{
    if (!labels.empty())
    {
        std::cout << labels.front() << DEBUG_EQUAL;
        labels.pop_front();
    }
    print(_item);
    std::cout << ((depth == 0) ? DEBUG_SEPARATOR : "\n");
    print_output(_items...);
}


// Print Opening and Closing
void DEBUG::print_open(const std::string& _label)
{
    --depth;
    std::cout << _label;
    indent += "  ";
}

void DEBUG::print_close(const std::string& _label)
{
    indent.resize(indent.size() - 2);
    std::cout << (depth <= 0 ? "" : "\n" + indent) << _label;
    ++depth;
}


// Print Different Container
template <typename _Tp1, typename _Tp2>
void DEBUG::print_content_pair(const std::string& _label, const std::pair<_Tp1, _Tp2>& _item)
{
    std::cout << (depth <= 0 ? "" : "\n" + indent), print(_item.first);
    std::cout << _label;
    std::cout << (depth <= 0 ? "" : "\n" + indent), print(_item.second);
}

template <typename... _Tps>
void DEBUG::print_content_tuple(const std::string& _label, const std::tuple<_Tps...>& _item)
{
    std::apply(
        [&](auto&&... args)
        {
            int k = sizeof...(_Tps);
            ((std::cout << (depth <= 0 ? "" : "\n" + indent), print(args), std::cout << (--k ? _label : "")), ...);
        },
        _item
    );  
}

template <typename _Tp> 
void DEBUG::print_content_container(const std::string& _label, const _Tp& _item)
{
    for (auto it = _item.begin(); it != _item.end(); it++) {
        std::cout << (depth <= 0 ? "" : "\n" + indent), print(*it);
        if (next(it) != _item.end())
            std::cout << _label;
    }
}

template <typename _Tp> 
void DEBUG::print_content_query_front(const std::string& _label, const _Tp& _item)
{
    _Tp item = _item;
    while (!item.empty())
    {
        std::cout << (depth <= 0 ? "" : "\n" + indent), print(item.front());
        item.pop();
        if (!item.empty())
            std::cout << _label;
    }
}

template <typename _Tp> 
void DEBUG::print_content_query_top(const std::string& _label, const _Tp& _item)
{
    _Tp item = _item;
    while (!item.empty())
    {
        std::cout << (depth <= 0 ? "" : "\n" + indent), print(item.top());
        item.pop();
        if (!item.empty())
            std::cout << _label;
    }
}


// Print Various Data Types
template <typename _Tp>
void DEBUG::print(const _Tp* _item)
{
    if constexpr (is_same_v<_Tp, char> || is_same_v<_Tp, const char>)
        std::cout << _item;
    else
        std::cout << POINTER_MARK, print(*_item);
}

template <typename _Tp>
void DEBUG::print(const _Tp& _item)
{
    if constexpr (is_iterator<_Tp>::value)
        std::cout << ITERATOR_MARK, print(*_item);
    else
        std::cout << _item;
}

template <typename _Tp1, typename _Tp2>
void DEBUG::print(const std::pair<_Tp1, _Tp2>& _item)
{
    print_open(PAIR_OPEN);
    print_content_pair(PAIR_SEPARATOR, _item);
    print_close(PAIR_CLOSE);
}

template <typename... _Tps>
void DEBUG::print(const std::tuple<_Tps...>& _item)
{
    print_open(TUPLE_OPEN);
    print_content_tuple(TUPLE_SEPARATOR, _item);
    print_close(TUPLE_CLOSE);
}

template <typename _Tp, typename ALLOCATOR>
void DEBUG::print(const std::vector<_Tp, ALLOCATOR>& _item)
{
    print_open(VECTOR_OPEN);
    print_content_container(VECTOR_SEPARATOR, _item);
    print_close(VECTOR_CLOSE);
}

template <typename _Key, typename _Compare, typename _Alloc>
void DEBUG::print(const std::set<_Key, _Compare, _Alloc>& _item)
{
    print_open(SET_OPEN);
    print_content_container(SET_SEPARATOR, _item);
    print_close(SET_CLOSE);
}

template <typename _Key, typename _Compare, typename _Alloc>
void DEBUG::print(const std::multiset<_Key, _Compare, _Alloc>& _item)
{
    print_open(MULTISET_OPEN);
    print_content_container(MULTISET_SEPARATOR, _item);
    print_close(MULTISET_CLOSE);
}

template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
void DEBUG::print(const std::map<_Key, _Tp, _Compare, _Alloc>& _item)
{
    print_open(MAP_OPEN);
    print_content_container(MAP_SEPARATOR, _item);
    print_close(MAP_CLOSE);
}

template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
void DEBUG::print(const std::multimap<_Key, _Tp, _Compare, _Alloc>& _item)
{
    print_open(MULTIMAP_OPEN);
    print_content_container(MULTIMAP_SEPARATOR, _item);
    print_close(MULTIMAP_CLOSE);
}

template <typename _Key, typename _Hash, typename _Pred, typename _Alloc>
void DEBUG::print(const std::unordered_set<_Key, _Hash, _Pred, _Alloc>& _item)
{
    print_open(UNORDERED_SET_OPEN);
    print_content_container(UNORDERED_SET_SEPARATOR, _item);
    print_close(UNORDERED_SET_CLOSE);
}

template <typename _Key, typename _Hash, typename _Pred, typename _Alloc>
void DEBUG::print(const std::unordered_multiset<_Key, _Hash, _Pred, _Alloc>& _item)
{
    print_open(UNORDERED_MULTISET_OPEN);
    print_content_container(UNORDERED_MULTISET_SEPARATOR, _item);
    print_close(UNORDERED_MULTISET_CLOSE);
}

template <typename _Key, typename _Tp, typename _Hash, typename _Pred, typename _Alloc>
void DEBUG::print(const std::unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>& _item)
{
    print_open(UNORDERED_MAP_OPEN);
    print_content_container(UNORDERED_MAP_SEPARATOR, _item);
    print_close(UNORDERED_MAP_CLOSE);
}

template <typename _Key, typename _Tp, typename _Hash, typename _Pred, typename _Alloc>
void DEBUG::print(const std::unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>& _item)
{
    print_open(UNORDERED_MULTIMAP_OPEN);
    print_content_container(UNORDERED_MULTIMAP_SEPARATOR, _item);
    print_close(UNORDERED_MULTIMAP_CLOSE);
}

template <typename _Tp, typename _Sequence>
void DEBUG::print(const std::stack<_Tp, _Sequence>& _item)
{
    print_open(STACK_OPEN);
    print_content_query_top(STACK_SEPARATOR, _item);
    print_close(STACK_CLOSE);
}

template <typename _Tp, typename _Sequence>
void DEBUG::print(const std::queue<_Tp, _Sequence>& _item)
{
    print_open(QUEUE_OPEN);
    print_content_query_front(QUEUE_SEPARATOR, _item);
    print_close(QUEUE_CLOSE);
}

template <typename _Tp, typename _Alloc>
void DEBUG::print(const std::deque<_Tp, _Alloc>& _item)
{
    print_open(DEQUE_OPEN);
    print_content_container(DEQUE_SEPARATOR, _item);
    print_close(DEQUE_CLOSE);
}

template <typename _Tp, typename _Sequence, typename _Compare>
void DEBUG::print(const std::priority_queue<_Tp, _Sequence, _Compare>& _item)
{
    print_open(PRIORITY_QUEUE_OPEN);
    print_content_query_top(PRIORITY_QUEUE_SEPARATOR, _item);
    print_close(PRIORITY_QUEUE_CLOSE);
}

template <typename _Key, typename _Tp, typename _Compare, typename _Tag, typename _Alloc>
void DEBUG::print(const __gnu_pbds::tree<_Key, _Tp, _Compare, _Tag, __gnu_pbds::tree_order_statistics_node_update, _Alloc>& _item)
{
    print_open(PRIORITY_QUEUE_OPEN);
    print_content_container(PRIORITY_QUEUE_SEPARATOR, _item);
    print_close(PRIORITY_QUEUE_CLOSE);
}


// External Parameter
void DEBUG::operator() (const bool& _force_horizontal)
    { force_horizontal = _force_horizontal; }

void DEBUG::operator() (const int& _unfold_depth)
    { unfold_depth = _unfold_depth, depth = _unfold_depth; }



// Construector and Destructor
LINE::LINE()
    {}

template <typename... _Tps>
LINE::LINE(const _Tps&... _items)
    : delayed_print([&, _items...]() { return print_output(_items...); })
    {}

LINE::~LINE()
    { delayed_print(); }   


// Main Control
void LINE::print_output() {}

template <typename... _Tps>
void LINE::print_output(const std::string& _item, const _Tps&... _items)
{
    std::string result;
    for (size_t i = 0; i < length; i++)
        result += _item[i % _item.size()];
    std::cout << result << '\n';
    print_output(_items...);
}


// External Parameter
void LINE::operator() (const size_t& _length)
    { length = _length; }


#endif /* _TLE_DEBUG_CPP */
