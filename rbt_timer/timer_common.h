#ifndef _LIB_SRC_TIMER_COMMON_H_
#define _LIB_SRC_TIMER_COMMON_H_

#include<stdio.h>
#include<sys/time.h>

/* gets the timestamp in millseconds  */
time_t getMSec(){
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

/* definition of timer data strcuture */
template <typename _User_Data>
class Timer{
public:
    using TimeOutCbFunc = void (*)(_User_Data *);
    Timer() : _user_data(nullptr), _cb_func(nullptr) {};
    Timer(int msec) : _User_Data(nullptr), _cb_func(nullptr){
        this->_expire = getMSec() + msec;
    }
    ~Timer() {}

    void setTimeout (time_t timeout) {
        this->_expire = getMSec() + timeout;
    }

    time_t getExpire () {
        return _expire;
    }

    void setUserDate(_User_Data *userData) {
        this->_user_data = userData;
    }

    void handleTimeOut() {
        if (_cb_func) {
            _cb_func(_user_data);
        }
    }

    void setCallBack(TimeOutCbFunc callback) {
        this->_cb_func = callback;
    }


private:
    time_t _expire;              /* absolute time when the timer takes effect  */
    _User_Data *_user_data;     /* user's data */
    TimeOutCbFunc _cb_func;     /* timeout's callback func */
};

/* virtual parent class - ITimerContiainer */
template <typename _UData>
class ITmerContainer{
public:
    ITmerContainer() == default;
    ~ITmerContainer() == default;

public:
    virtual void tick() = 0;
    virtual Timer<_UData> *addTimer(time_t timeout) = 0;
    virtual void delTimer(Timer<_UData> *timer) = 0;
    virtual void resetTimer(Timer<_UData> *timer, time_t timeout) = 0;
    virtual int getMinExpire() = 0;
};
#endif /* _LIB_SRC_TIMER_COMMON_H_ */