#include "alphanum.hpp"

using std::string;


namespace doj
{
  template<class Ty>
  struct alphanum_less : public std::binary_function<Ty, Ty, bool>
  {
    bool operator()(const Ty& left, const Ty& right) const
    {
      return alphanum_comp(left, right) < 0;
    }

    bool operator()(tab& left, tab& right) const
    {
    	return alphanum_comp(left.GetName(), right.GetName()) < 0;
    }
    bool operator()(item& left, item& right) const
    {
    	return alphanum_comp(left.GetPriority().GetPriorityIndex(),right.GetPriority().GetPriorityIndex()) <0;
    }
  };
}
