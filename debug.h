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


#ifndef _TLE_DEBUG_H
#define _TLE_DEBUG_H 1


size_t LINE_LENGTH = 50;


const std::string DEBUG_HEADING                = "> ";
const std::string DEBUG_SEPARATOR              = ", ";
const std::string DEBUG_EQUAL                  = " = ";

const std::string POINTER_MARK                 = "*";
const std::string ITERATOR_MARK                = "*";

const std::string PAIR_OPEN                    = "(";
const std::string TUPLE_OPEN                   = "(";
const std::string VECTOR_OPEN                  = "[";
const std::string SET_OPEN                     = "{";
const std::string MULTISET_OPEN                = "{";
const std::string MAP_OPEN                     = "{";
const std::string MULTIMAP_OPEN                = "{";
const std::string UNORDERED_SET_OPEN           = "[";
const std::string UNORDERED_MULTISET_OPEN      = "[";
const std::string UNORDERED_MAP_OPEN           = "[";
const std::string UNORDERED_MULTIMAP_OPEN      = "[";
const std::string STACK_OPEN                   = "[";
const std::string QUEUE_OPEN                   = "[";
const std::string DEQUE_OPEN                   = "[";
const std::string PRIORITY_QUEUE_OPEN          = "{";

const std::string PAIR_CLOSE                   = ")";
const std::string TUPLE_CLOSE                  = ")";
const std::string VECTOR_CLOSE                 = "]";
const std::string SET_CLOSE                    = "}";
const std::string MULTISET_CLOSE               = "}";
const std::string MAP_CLOSE                    = "}";
const std::string MULTIMAP_CLOSE               = "}";
const std::string UNORDERED_SET_CLOSE          = "]";
const std::string UNORDERED_MULTISET_CLOSE     = "]";
const std::string UNORDERED_MAP_CLOSE          = "]";
const std::string UNORDERED_MULTIMAP_CLOSE     = "]";
const std::string STACK_CLOSE                  = "]";
const std::string QUEUE_CLOSE                  = "]";
const std::string DEQUE_CLOSE                  = "]";
const std::string PRIORITY_QUEUE_CLOSE         = "}";

const std::string PAIR_SEPARATOR               = ", ";
const std::string TUPLE_SEPARATOR              = ", ";
const std::string VECTOR_SEPARATOR             = " ";
const std::string SET_SEPARATOR                = " ";
const std::string MULTISET_SEPARATOR           = " ";
const std::string MAP_SEPARATOR                = " ";
const std::string MULTIMAP_SEPARATOR           = " ";
const std::string UNORDERED_SET_SEPARATOR      = " ";
const std::string UNORDERED_MULTISET_SEPARATOR = " ";
const std::string UNORDERED_MAP_SEPARATOR      = " ";
const std::string UNORDERED_MULTIMAP_SEPARATOR = " ";
const std::string STACK_SEPARATOR              = " ";
const std::string QUEUE_SEPARATOR              = " ";
const std::string DEQUE_SEPARATOR              = " ";
const std::string PRIORITY_QUEUE_SEPARATOR     = " ";


class DEBUG
{
    template <typename T, typename = void>
    struct is_iterator : std::false_type {};

    template <typename T>
    struct is_iterator<T, std::void_t<typename std::iterator_traits<T>::iterator_category>> : std::true_type {};

private:
    // Variables
    bool force_horizontal = false;
    int unfold_depth = 1;

private:
    // System Variables
    std::string indent = "|";
    std::string label;
    std::deque<std::string> labels{DEBUG_HEADING};
    std::function<void()> delayed_print;
    int depth = 1;

private:
    // Main Control
    void generate_labels(std::string _label);

    template <typename _Tp>
    void print_output(_Tp _item);

    template <typename _Tp, typename... _Tps>
    void print_output(_Tp _item, const _Tps&... _items);

    // Print Opening and Closing
    void print_open(const std::string& _label);

    void print_close(const std::string& _label);

    // Print Different Container
    template <typename _Tp1, typename _Tp2>
    void print_content_pair(const std::string& _label, std::pair<_Tp1, _Tp2>& _item);

    template <typename... _Tps>
    void print_content_tuple(const std::string& _label, std::tuple<_Tps...>& _item);

    template <typename _Tp> 
    void print_content_container(const std::string& _label, _Tp& _item);

    template <typename _Tp> 
    void print_content_query_front(const std::string& _label, _Tp& _item);

    template <typename _Tp> 
    void print_content_query_top(const std::string& _label, _Tp& _item);

    // Print Various Data Types
    template <typename _Tp>
    void print(_Tp* _item);

    template <typename _Tp>
    void print(_Tp& _item);

    template <typename _Tp1, typename _Tp2>
    void print(std::pair<_Tp1, _Tp2>& _item);

    template <typename... _Tps>
    void print(std::tuple<_Tps...>& _item);

    template <typename _Tp, typename _Alloc>
    void print(std::vector<_Tp, _Alloc>& _item);

    template <typename _Key, typename _Compare, typename _Alloc>
    void print(std::set<_Key, _Compare, _Alloc>& _item);

    template <typename _Key, typename _Compare, typename _Alloc>
    void print(std::multiset<_Key, _Compare, _Alloc>& _item);

    template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    void print(std::map<_Key, _Tp, _Compare, _Alloc>& _item);

    template <typename _Key, typename _Tp, typename _Compare, typename _Alloc>
    void print(std::multimap<_Key, _Tp, _Compare, _Alloc>& _item);

    template <typename _Key, typename _Hash, typename _Pred, typename _Alloc>
    void print(std::unordered_set<_Key, _Hash, _Pred, _Alloc>& _item);

    template <typename _Key, typename _Hash, typename _Pred, typename _Alloc>
    void print(std::unordered_multiset<_Key, _Hash, _Pred, _Alloc>& _item);

    template <typename _Key, typename _Tp, typename _Hash, typename _Pred, typename _Alloc>
    void print(std::unordered_map<_Key, _Tp, _Hash, _Pred, _Alloc>& _item);

    template <typename _Key, typename _Tp, typename _Hash, typename _Pred, typename _Alloc>
    void print(std::unordered_multimap<_Key, _Tp, _Hash, _Pred, _Alloc>& _item);

    template <typename _Tp, typename _Sequence>
    void print(std::stack<_Tp, _Sequence>& _item);

    template <typename _Tp, typename _Sequence>
    void print(std::queue<_Tp, _Sequence>& _item);

    template <typename _Tp, typename _Alloc>
    void print(std::deque<_Tp, _Alloc>& _item);

    template <typename _Tp, typename _Sequence, typename _Compare>
    void print(std::priority_queue<_Tp, _Sequence, _Compare>& _item);

    template <typename _Key, typename _Tp, typename _Compare, typename _Tag, typename _Alloc>
    void print(__gnu_pbds::tree<_Key, _Tp, _Compare, _Tag, __gnu_pbds::tree_order_statistics_node_update, _Alloc>& _item);

public:
    // Constructor and Destructor
    DEBUG();
    template<typename... _TpS>
    DEBUG(std::string _label, _TpS... _items);

    ~DEBUG();

public:
    // External Parameters
    void operator () (const bool& _force_horizontal);

    void operator () (const int& _unfold_depth);
};


class LINE
{
private:
    // Variables
    size_t length = LINE_LENGTH;

private:
    // System Variables
    std::deque<std::string> patterns;
    std::function<void()> delayed_print;

public:
    // Constructor and Destructor
    LINE();
    template <typename... Tps>
    LINE(const Tps&... _patterns);

    ~LINE();

private:
    // Main Call
    void print_output();

    template <typename... _Tps>
    void print_output(const std::string& _item, const _Tps&... _items);

public:
    // External Parameters
    void operator () (const size_t& _length);
};


// Main Calls
/**
*  @brief  Print lines with customizable pattern and length.
*  @param  __VA_ARGS__  Patterns.
*/
#define dline(...) LINE(__VA_ARGS__)

/**
*  @brief  Print various data types.
*  @param  __VA_ARGS__  Items to debug.
*/
#define debug(...) DEBUG(#__VA_ARGS__, __VA_ARGS__)


#endif /* _TLE_DEBUG_H */