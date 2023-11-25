#include <iostream>
#include <ratio>

namespace usu {
template <typename RatioType, typename StorageType = std::uint64_t> class mass {
public:
  using conversion = RatioType;

  template <class RetType, class InType>
  friend RetType mass_cast(const InType &in);
  mass() { m_grams = 0; }

  explicit mass(StorageType givenNum) {
    m_grams = (givenNum * 1000000 * RatioType::num) / RatioType::den;
    // std::cout << "Num/Dem:" << RatioType::num << "/" << RatioType::den <<
    // std::endl; std::cout << "Setting count: " << m_grams << std::endl;
  }

  StorageType count() const {
    return (m_grams * RatioType::den) / (RatioType::num * 1000000);
  }

  StorageType getGrams() const { return m_grams; }

  template <class InType> bool operator<(const InType &rhs) const {
    if (this->m_grams < rhs.getGrams()) {
      return true;
    }
    return false;
  }

  template <class InType> bool operator>(const InType &other) const {
    if (other < *this) {
      return true;
    }
    return false;
  }

  template <class InType> bool operator==(const InType &other) const {
    if (*this > other || *this < other) {
      return false;
    }
    return true;
  }

  template <class InType> bool operator!=(const InType &other) const {
    return !(*this == other);
  }

  template <class InType> bool operator>=(const InType &other) const {
    if (*this < other) {
      return false;
    }
    return true;
  }
  template <class InType> bool operator<=(const InType &other) const {
    if (*this > other) {
      return false;
    }
    return true;
  }

  template <class InType>
  mass<RatioType, StorageType> operator+(const InType &rhs) const {
    mass<RatioType, StorageType> retVal;
    retVal.m_grams = this->m_grams + rhs.getGrams();
    return retVal;
  }

  template <class InType>
  mass<RatioType, StorageType> operator-(const InType &rhs) const {
    mass<RatioType, StorageType> retVal;
    retVal.m_grams = this->m_grams - rhs.getGrams();
    return retVal;
  }

  template <class InType>
  mass<RatioType, StorageType> &operator+=(const InType &rhs) {
    this->m_grams += rhs.getGrams();
    return *this;
  }

  template <class InType>
  mass<RatioType, StorageType> &operator-=(const InType &rhs) {
    this->m_grams -= rhs.getGrams();
    return *this;
  }

private:
  StorageType m_grams;
};

template <class RetType, class InType> RetType mass_cast(const InType &in) {
  RetType retVal;
  auto grams = in.m_grams;
  std::cout << "Grams in input: " << grams << std::endl;
  retVal.m_grams = grams;
  return retVal;
}

using microgram = mass<std::micro>;
using gram = mass<std::ratio<1, 1>>;
using kilogram = mass<std::kilo>;
using ounce = mass<std::ratio<28349523125, 1000000000>>;
using pound = mass<std::ratio<45359237, 100000>>;
using ton = mass<std::ratio<90718474, 100>>;
} // namespace usu