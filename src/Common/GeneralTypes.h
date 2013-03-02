#ifndef GENERALTYPES_H
#define GENERALTYPES_H

#include <boost/date_time/posix_time/posix_time.hpp>

typedef unsigned int uint;
namespace Time = boost::posix_time;
typedef Time::ptime ptime;
typedef boost::posix_time::microsec_clock MClock;

#endif // GENERALTYPES_H
