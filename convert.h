// File: convert.h
    #include <iostream>
    #include <sstream>
    #include <string>
    #include <stdexcept>
class BadConversion : public std::runtime_error {
 public:
  BadConversion(const std::string& s)
    : std::runtime_error(s)
    { }
};
inline double convertToDouble(const std::string& s)
{
  std::istringstream i(s);
  double x;
  if (!(i >> x))
    throw BadConversion("convertToDouble(\"" + s + "\")");
  return x;
}
