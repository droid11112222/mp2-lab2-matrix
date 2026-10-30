// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор -
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz > MAX_VECTOR_SIZE)
        throw out_of_range("Vector size is too large");
    pMem = new T[sz]();// {}; // У типа T д.б. конструктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v) // копирование
  {
      sz = v.sz;
      pMem = new T[sz];
      for (size_t i = 0; i < sz; i++){
        pMem[i] = v.pMem[i];
      }
  }
  TDynamicVector(TDynamicVector&& v) noexcept // перемещение
  {
      sz = v.sz;
      pMem = v.pMem;
      v.pMem = nullptr;
      v.sz = 0;
  }
  ~TDynamicVector() //удаление
  {
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v) //
  {
      if (this != &v){
        delete [] pMem;
        sz = v.sz;
        pMem = new T[sz];
        for (size_t i = 0; i < sz; i++){
            pMem[i] = v.pMem[i];
        }
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      delete [] pMem;
      sz = v.sz;
      pMem = v.pMem;
      v.sz = 0;
      v.pMem = nullptr;
      return (*this); // заглушка
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator[](size_t ind)
  {
      return (pMem[ind]);
  }
  const T& operator[](size_t ind) const
  {
        return pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (ind < sz){
          return pMem[ind];
      }else{
          throw out_of_range("Vector size should be less than sz+1");
      }
  }
  const T& at(size_t ind) const
  {
     if (ind < sz){
          return pMem[ind];
      }else{
          throw out_of_range("Vector size should be less than sz+1");
      }
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      bool res;
      res = false;
      if (sz == v.sz){
        res = true;
        for (size_t i = 0; i < sz; i++){
            if (pMem[i] != v.pMem[i]) {
                return false;
            }
        }
      }
      return res;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      return !(*this == v);
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++){
            res[i] = pMem[i] + val;
        }
      return res;
  }
  TDynamicVector operator-(T val)
  {
       TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++){
            res[i] = pMem[i] - val;
        }
      return res;
  }
  TDynamicVector operator*(T val)
  {
       TDynamicVector res(sz);
        for (size_t i = 0; i < sz; i++){
            res[i] = pMem[i] * val;
        }
      return res;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      TDynamicVector res(sz);
      if (sz == v.size()){
        for (size_t i = 0; i < sz; i++){
            res[i] += v.pMem[i] + pMem[i];
        }
      }else{
          throw ("Vector size should be similar");
      }
      return res;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      TDynamicVector res(sz);
      if (sz == v.size()){
        for (size_t i = 0; i < sz; i++){
            res[i] +=  pMem[i] - v.pMem[i];
        }
      }else{
          throw ("Vector size should be similar");
      }
      return res;
  }
  T operator*(const TDynamicVector& v)
  {
      T res = T();
      if (sz == v.size()){
        for (size_t i = 0; i < sz; i++){
            res += v.pMem[i] * pMem[i];
        }
      }else{throw ("Vector size should be similar");}
      return res;
  }

  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};
// Динамическая матрица -
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
    using TDynamicVector<TDynamicVector<T>>::size;
    TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (sz > MAX_MATRIX_SIZE) {
        throw out_of_range("Matrix size is too large");
    }
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& m) const noexcept
  {
      if (sz == m.sz){
        for (size_t i = 0; i < sz; i++){
            if (pMem[i] != m.pMem[i]){return false;}
        }
      }else{return false;}
      return true;
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++){
            res.pMem[i] = pMem[i] * val;
        }
        return res;
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      if (v.size() != sz){
          throw ("Matrix and vector sizes should be similar");
      }
      TDynamicVector<T> res(sz);
      {
        for (size_t i = 0; i < sz; i++){
                res[i] = pMem[i] * v;
            }
      }
        return res;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (m.sz != sz) {
          throw ("Matrix sizes should be similar");
      }

      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] + m.pMem[i];
      }
      return res;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (m.sz != sz) { throw ("Matrix sizes should be similar"); }
      TDynamicMatrix res(sz);
      for (size_t i = 0; i < sz; i++) {
          res.pMem[i] = pMem[i] - m.pMem[i];
      }
      return res;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
{
    if (m.sz != sz) { throw ("Matrix size should be similar"); }

    TDynamicMatrix res(sz);
    for (size_t i = 0; i < sz; i++) {
        for (size_t j = 0; j < sz; j++) {
            T sum = T(); // Копилка
            for (size_t k = 0; k < sz; k++) {
                sum += pMem[i][k] * m.pMem[k][j];
            }
            res.pMem[i][j] = sum;
        }
    }
    return res;
}
  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      for (size_t i = 0; i < v.sz; i++) {
          istr >> v.pMem[i];
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
       for (size_t i = 0; i < v.sz; i++) {
          ostr << v.pMem[i] << '\n';
      }
      return ostr;
  }
};

#endif
