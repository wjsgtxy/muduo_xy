//#include "muduo/base/Timestamp.h"
#include "Timestamp.h" // todo 上面识别不了

#include <sys/time.h>
#include <stdio.h>

// SRS中广泛使用PRId64用来实现32位和64位系统通用
// https://www.cnblogs.com/lance-ehf/p/4146310.html
#ifndef __STDC_FORMAT_MACROS
#define __STDC_FORMAT_MACROS
#endif

// 进制宏 像下面这种 用来跨系统，c++要使用需要上面的宏一起使用
//#define PRId8 "d"
//#define PRId16 "d"
//#define PRId32 "d"
//# define PRId64     __PRI64_PREFIX "d"
#include <inttypes.h>

using namespace muduo;

// 编译器断言，也叫静态断言 static_assert(常量表达式，提示字符串) 为true或者非0，则不做任何事
static_assert(sizeof(Timestamp) == sizeof(int64_t), "Timestamp should be same size as int64_t");

string Timestamp::toString() const
{
    char buf[32] = {0};
    int64_t seconds = microSecondsSinceEpoch_ / kMicroSecondsPerSecond;
    int64_t microseconds = microSecondsSinceEpoch_ % kMicroSecondsPerSecond;
    snprintf(buf, sizeof(buf), "%" PRId64 ".%06" PRId64 "", seconds, microseconds);
    return buf;
}

string Timestamp::toFormattedString(bool showMicroseconds) const
{
    char buf[64] = {0};
    time_t seconds = static_cast<time_t>(microSecondsSinceEpoch_ / kMicroSecondsPerSecond);
    struct tm tm_time; // 时间，包含秒，分钟，小时，日。。。
    // 获取UTC格式的时间 gmtime通过返回值返回当前时间。gmtime_r通过指针返回当前时间。
    // gmtime_r 线程安全
    gmtime_r(&seconds, &tm_time); // todo

    if(showMicroseconds)
    {
        int microseconds = static_cast<int>(microSecondsSinceEpoch_ % kMicroSecondsPerSecond);
        snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d.%06d",
                 tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                 tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,
                 microseconds);
    }else{
        snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d",
                 tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                 tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
    }
    return buf;
}

Timestamp Timestamp::now()
{
    struct timeval tv; // 包含两个成员，秒数 tv_sec和微秒数 tv_usec
    gettimeofday(&tv, NULL);
    int64_t secondes = tv.tv_sec;
    return Timestamp(secondes * KMicroSecondsPerSecond + tv.tv_usec);
}
