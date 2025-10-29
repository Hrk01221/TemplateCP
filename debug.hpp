#pragma once
#include <bits/stdc++.h>
using namespace std;

#ifndef ONLINE_JUDGE

template <typename T>
void _print(const T &x);

// ====== Forward Declarations ======
template <typename A, typename B> void _print(const pair<A, B> &p);
template <typename... Ts> void _print(const tuple<Ts...> &t);
template <typename T> void _print(const vector<T> &v);
template <typename T> void _print(const vector<vector<T>> &v);
template <typename T> void _print(const set<T> &s);
template <typename T> void _print(const multiset<T> &s);
template <typename K, typename V> void _print(const map<K, V> &m);
template <typename K, typename V> void _print(const unordered_map<K, V> &m);
template <typename T, size_t N> void _print(const array<T, N> &a);
template <typename T> void _print(const deque<T> &d);
template <typename T> void _print(const stack<T> &st);
template <typename T> void _print(const queue<T> &q);
template <typename T> void _print(const priority_queue<T> &pq);
template <size_t N> void _print(const bitset<N> &b);

// ====== Core Printer ======
template <typename T>
void _print(const T &x) {
    cerr << x;
}

// ====== Specialized Overloads ======
template <typename A, typename B>
void _print(const pair<A, B> &p) {
    cerr << "(";
    _print(p.first);
    cerr << ", ";
    _print(p.second);
    cerr << ")";
}

template <typename... Ts>
void _print(const tuple<Ts...> &t) {
    cerr << "(";
    std::apply([](const auto &... args) {
        size_t n = 0;
        ((cerr << (n++ ? ", " : ""), _print(args)), ...);
    }, t);
    cerr << ")";
}

template <typename T>
void _print_container(const T &container, const string &open = "[", const string &close = "]" , const int &type = 1) {
    if(type==1)cerr << open;
    bool first = true;
    for (const auto &x : container) {
        if (!first and type != 2) cerr << ", ";
        if(type == 2 and !first)cerr << "\t ";
        _print(x);
        if(type==2)cerr << '\n';
        first = false;
    }
    if(type==1)cerr << close;
}
template <typename T> void _print(const vector<T> &v) { _print_container(v, "[", "]"); }
template <typename T> void _print(const vector<vector<T>> &v) { _print_container(v, "[", "]",2); }
template <typename T> void _print(const deque<T> &d) { _print_container(d, "[", "]"); }
template <typename T> void _print(const set<T> &s) { _print_container(s, "{", "}"); }
template <typename T> void _print(const multiset<T> &s) { _print_container(s, "{", "}"); }
template <typename K, typename V> void _print(const map<K, V> &m) { _print_container(m, "{", "}",2); }
template <typename K, typename V> void _print(const unordered_map<K, V> &m) { _print_container(m, "{", "}",2); }
template <typename T, size_t N> void _print(const array<T, N> &a) { _print_container(a, "[", "]"); }
template <typename T> void _print(const stack<T> &st) {
    auto tmp = st;
    vector<T> v;
    while (!tmp.empty()) v.push_back(tmp.top()), tmp.pop();
    reverse(v.begin(), v.end());
    _print(v);
}
template <typename T> void _print(const queue<T> &q) {
    auto tmp = q;
    vector<T> v;
    while (!tmp.empty()) v.push_back(tmp.front()), tmp.pop();
    _print(v);
}
template <typename T> void _print(const priority_queue<T> &pq) {
    auto tmp = pq;
    vector<T> v;
    while (!tmp.empty()) v.push_back(tmp.top()), tmp.pop();
    _print(v);
}
template <size_t N> void _print(const bitset<N> &b) { cerr << b.to_string(); }

// ====== Variadic Debug ======
template <typename T>
void _debug_one(const string &name, const T &value) {
    cerr << name << " = ";
    _print(value);
    cerr << "\n";
}

template <typename T, typename... Args>
void _debug_many(const string &names, const T &value, const Args &...args) {
    size_t comma = names.find(',');
    string first = names.substr(0, comma);
    string rest = (comma == string::npos ? "" : names.substr(comma + 1));
    _debug_one(first, value);
    if constexpr (sizeof...(args) > 0) _debug_many(rest, args...);
}

#define debug(...) _debug_many(#__VA_ARGS__, __VA_ARGS__)

#else
// When ONLINE_JUDGE is defined, all debug calls vanish
#define debug(...)
#endif

/*Add include "debug.hpp */
