#ifndef SPARSECOUNTER_H
#define SPARSECOUNTER_H

#include <cstring>
#include <utility>

template<class SC>
class SparseCounterIt {
public:
  SparseCounterIt(const SC& sparse_counter, int i) : _sc(sparse_counter), _i(i) {}
  void operator++() { _i++; }
  std::pair<int,int> operator*() { return _sc.get_ith_key_value(_i); };
  bool operator!=(const SparseCounterIt<SC>& other) const {
    return (&_sc != &other._sc) || (_i != other._i);
  }
private:
  const SC& _sc;
  int _i;
};

class SparseCounter {
public:
  SparseCounter();
  SparseCounter(int n);
  SparseCounter(const SparseCounter& other);
  SparseCounter(SparseCounter&& other);
  ~SparseCounter();
  const SparseCounter& operator=(const SparseCounter& other);
  const SparseCounter& operator=(SparseCounter&& other);
 
  int operator[](int i) const { return _counts[i]; }
  void inc(int i, int count=1) {
    if (!_counts[i])
      _indices[_num_indices++] = i;
    _counts[i] += count;
  }
  int size() const { return _n; }
  int supp() const { return _num_indices; }
  void clear();
  void resize(int n);
  
  SparseCounterIt<SparseCounter> begin() const {
    return SparseCounterIt<SparseCounter>(*this,0);
  }
  SparseCounterIt<SparseCounter> end() const {
    return SparseCounterIt<SparseCounter>(*this,_num_indices);
  }
  std::pair<int,int> get_ith_key_value(int i) const {
    return std::make_pair(_indices[i],_counts[_indices[i]]);
  }
private:
  int _n;
  int _num_indices;
  int *_counts;
  int *_indices;
};

#endif
