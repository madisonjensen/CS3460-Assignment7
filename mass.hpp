#include <iomanip>
#include <iostream>
#include <ratio>

namespace usu {
template <typename RatioType, typename StorageType = std::uint64_t> class mass {
public:
  using conversion = RatioType;

  template <class RetType, class InType>
  friend RetType mass_cast(const InType &in);
  mass() { m_count = 0; }

  explicit mass(double givenNum) { m_count = givenNum; }

  double count() const { return m_count; }

  template <class InType> bool operator<(const InType &in) const {
    auto converted = mass_cast<mass<RatioType, StorageType>>(in);
    if (this->m_count < converted.m_count) {
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

  /*
    template <class InType> bool operator<=>(const InType &other) const {
      return *this <=> other;
    }
  */
  // DO SPACESHIP HERE
  template <class InClass>
  mass<RatioType, StorageType> operator+(const InClass &in) const {
    auto converted = mass_cast<mass<RatioType, StorageType>>(in);
    mass<RatioType, StorageType> retVal;
    retVal.m_count = this->m_count + converted.m_count;
    return retVal;
  }

  template <class InType>
  mass<RatioType, StorageType> operator-(const InType &in) const {
    auto converted = mass_cast<mass<RatioType, StorageType>>(in);
    mass<RatioType, StorageType> retVal;
    retVal.m_count = this->m_count - converted.m_count;
    return retVal;
  }

  mass<RatioType, StorageType> operator*(double scalar) const {
    mass<RatioType, StorageType> retVal;
    retVal.m_count = this->m_count * scalar;
    return retVal;
  }

  mass<RatioType, StorageType> operator/(double scalar) const {
    mass<RatioType, StorageType> retVal;
    retVal.m_count = this->m_count / scalar;
    return retVal;
  }

  template <class InType>
  mass<RatioType, StorageType> &operator+=(const InType &in) {
    auto converted = mass_cast<mass<RatioType, StorageType>>(in);
    this->m_count += converted.m_count;
    return *this;
  }

  template <class InType>
  mass<RatioType, StorageType> &operator-=(const InType &in) {
    auto converted = mass_cast<mass<RatioType, StorageType>>(in);
    this->m_count -= converted.m_count;
    return *this;
  }

  mass<RatioType, StorageType> operator*=(double scalar) {
    this->m_count *= scalar;
    return *this;
  }

  mass<RatioType, StorageType> operator/=(double scalar) {
    this->m_count /= scalar;
    return *this;
  }

  double m_count;
  RatioType m_ratio;
};

template <class RetType, class InType> RetType mass_cast(const InType &in) {
  RetType retVal;
  double newCount = in.m_count * in.m_ratio.num * retVal.m_ratio.den;
  newCount = newCount / (in.m_ratio.den * retVal.m_ratio.num);
  retVal.m_count = newCount;
  return retVal;
}

template <class RetType> RetType operator*(double scalar, const RetType &in) {
  return in * scalar;
}

template <class RetType> RetType operator/(double scalar, const RetType &in) {
  return in / scalar;
}

template <class RetType> RetType operator*=(double scalar, const RetType &in) {
  return in *= scalar;
}

template <class RetType> RetType operator/=(double scalar, const RetType &in) {
  return in /= scalar;
}

using microgram = mass<std::micro>;
using gram = mass<std::ratio<1, 1>>;
using kilogram = mass<std::kilo>;
using ounce = mass<std::ratio<28349523125, 1000000000>>;
using pound = mass<std::ratio<45359237, 100000>>;
using ton = mass<std::ratio<90718474, 100>>;
} // namespace usu