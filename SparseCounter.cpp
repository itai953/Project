#include <algorithm>

#include "SparseCounter.h"

SparseCounter::SparseCounter() :
  _n(0), _num_indices(0), _counts(nullptr), _indices(nullptr) {}

SparseCounter::SparseCounter(int n) :
  _n(n), _num_indices(0),
  _counts(new int[n]), _indices(new int[n]) {
  memset(_counts,0,sizeof(int)*_n);
  }

SparseCounter::SparseCounter(const SparseCounter& other) :
  _n(other._n), _num_indices(other._num_indices),
  _counts(new int[_n]), _indices(new int[_n]) {
  memcpy(_indices, other._indices, sizeof(int)*_num_indices);
  memcpy(_counts, other._counts, sizeof(int)*_n);
}

SparseCounter::~SparseCounter() {
  delete[] _indices;
  delete[] _counts;
}

SparseCounter::SparseCounter(SparseCounter&& other) :
  _n(other._n), _num_indices(other._num_indices),
  _counts(other._counts), _indices(other._indices) {
  other._n = other._num_indices = 0;
  other._counts = other._indices = nullptr;
}

const SparseCounter& SparseCounter::operator=(const SparseCounter& other) {
  if (this != &other) {
    if (_n != other._n) {
      delete[] _indices;
      delete[] _counts;
      _n = other._n;
      _indices = new int[_n];
      _counts = new int[_n];
    }
    _num_indices = other._num_indices;
    memcpy(_indices, other._indices, sizeof(int)*_num_indices);
    memcpy(_counts, other._counts, sizeof(int)*_n);
  }
  return *this;
}

const SparseCounter& SparseCounter::operator=(SparseCounter&& other) {
  if (this != &other) {
    std::swap(_n, other._n);
    std::swap(_num_indices, other._num_indices);
    std::swap(_counts, other._counts);
    std::swap(_indices, other._indices);
  }
  return *this;
}

void SparseCounter::clear() {
  _num_indices = 0; 
  memset(_counts,0,sizeof(int)*_n);
}

void SparseCounter::resize(int n) {
  if (n == _n)
    clear();
  else {
    SparseCounter sc(n);
    std::swap(*this,sc);
  }
}
