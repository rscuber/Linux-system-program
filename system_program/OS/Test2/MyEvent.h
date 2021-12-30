/*************************************************************************
	> File Name: MyEvent.h
	> Author: godOfRang
	> Motto: Barefoot makes wheels
	> Created Time: Wed Nov  3 11:04:48 2021
 ************************************************************************/

#ifndef _MYEVENT_H
#define _MYEVENT_H

#include <iostream>
#include <pthread.h>
#include <errno.h>

using namespace std;

//class CEventImpl 
class CEventImpl {
protected:
    CEventImpl(bool manualReset);
    ~CEventImpl();
    void SetImpl();
    bool WaitImpl();
    bool WaitImpl(long milliseconds);
    void ResetImpl();
private:
    bool            m_manual;
    volatile bool   m_state;
    pthread_mutex_t m_mutex;
    pthread_cond_t  m_cond;
};

inline void CEventImpl::SetImpl() {
    if (pthread_mutex_lock(&m_mutex)) {
        cout<<"cannot signal event (lock)"<<endl;
    }
    m_state = true;
    //cout<<"CEventImpl::SetImpl m_state = "<<m_state<<endl;
    if (pthread_cond_broadcast(&m_cond)) {
        pthread_mutex_unlock(&m_mutex);
        cout<<"cannot signal event"<<endl;
    }
    pthread_mutex_unlock(&m_mutex);
}

inline void CEventImpl::ResetImpl() {
    if (pthread_mutex_lock(&m_mutex)) {
        cout<<"cannot reset event"<<endl;
    }
    m_state = false;
    //cout<<"CEventImpl::ResetImpl m_state = "<<m_state<<endl;
    pthread_mutex_unlock(&m_mutex);
}


//CMyEvent
class CMyEvent: private CEventImpl {
public:
    CMyEvent(bool bManualReset = true);
    ~CMyEvent();
    void Set();
    bool Wait();
    bool Wait(long milliseconds);
    bool TryWait(long milliseconds);
    void Reset();
private:
    CMyEvent(const CMyEvent&);
    CMyEvent& operator = (const CMyEvent&);
};


inline void CMyEvent::Set() {
    SetImpl();
}

inline bool CMyEvent::Wait() {
    return WaitImpl();
}

inline bool CMyEvent::Wait(long milliseconds) {
    if (!WaitImpl(milliseconds)) {
        cout<<"time out"<<endl;
        return false;
    } else {
        return true;
    }
}

inline bool CMyEvent::TryWait(long milliseconds) {
    return WaitImpl(milliseconds);
}

inline void CMyEvent::Reset() {
    ResetImpl();
}

#endif
