#ifndef _INCLUDED_CASSM_TABLE_H
#define _INCLUDED_CASSM_TABLE_H

#include <string>
#include <unordered_map>
#include <functional>

namespace cassm
{

// ----------------------------------------------------------------------------
//      SymbolTable
// ----------------------------------------------------------------------------

template<typename T> class SymbolTable
{
public:
  SymbolTable() { }
  SymbolTable(std::function<void (SymbolTable&)> initializer);

  const T *get(const std::string& name) const;
  T *get(const std::string& name);

  template<class... Args> void emplace(const std::string& name, Args&&... args)
  {
    data_.emplace(std::piecewise_construct,
                  std::forward_as_tuple(name),
                  std::forward_as_tuple(args...));
  }

private:
  std::unordered_map<std::string, T> data_;
};

template<typename T> SymbolTable<T>::SymbolTable(std::function<void (SymbolTable&)> initializer)
{
  if (initializer)
    initializer(*this);
}

template<typename T> const T *SymbolTable<T>::get(const std::string& name) const
{
  const auto i = data_.find(name);
  return i != std::end(data_) ? &i->second : nullptr;
}

template<typename T> T *SymbolTable<T>::get(const std::string& name)
{
  auto i = data_.find(name);
  return i != std::end(data_) ? &i->second : nullptr;
}

}
#endif
