#include "NJThread.h"
#include <iostream>
using namespace std;

namespace NJ::Libs {
    NJThread::NJThread() : m_Job(nullptr),m_JobThread(nullptr),m_RunFlag(false) {
    }

    bool NJThread::getRunFlag() {
        std::unique_lock<std::mutex> ul(m_RunFlagMut);
        return m_RunFlag;
    }

    void NJThread::setRunFlag(bool flag) {
        std::unique_lock<std::mutex> ul(m_RunFlagMut);
        m_RunFlag = flag;
    }

    void NJThread::start() {
        if( m_JobThread != nullptr) {
            return;
        }

        setRunFlag(true);
        m_JobThread = new std::thread(&NJThread::threadFunc,this);
        m_JobThread->detach();
        std::mutex tmp;
        m_StartCV.wait(tmp);
        cout<<"NJThread start"<<endl;
    }

    void NJThread::stop() {
        setRunFlag(false);
        m_JobCV.notify_all();
        delete m_JobThread;
    }

    bool NJThread::submitJob(std::shared_ptr<IRunnable> job) {
        m_JobMut.lock();
        if(m_Job != nullptr || job == nullptr) {
            m_JobMut.unlock();
            return false;
        }
        m_Job = job;
        m_JobMut.unlock();
        m_JobCV.notify_all();
        return true;
    }

    bool NJThread::isIdle() {
        bool res = true;
        if(m_JobMut.try_lock()) {
            res = (m_Job==nullptr);
            m_JobMut.unlock();
        }
        return  res;
    }

    void NJThread::threadFunc() {
        m_StartCV.notify_all();
        bool run = true;
        while(run) {
            m_JobCV.wait(m_CVMut);
            if(!getRunFlag()) {
                break;
            }
            m_JobMut.lock();
            if(m_Job != nullptr) {
                m_JobMut.unlock();
                m_Job->run();
                m_JobMut.lock();
                m_Job = nullptr;
                m_JobMut.unlock();
                continue;
            }
            m_JobMut.unlock();
        }
    }

    NJThread::~NJThread() {

    }
}