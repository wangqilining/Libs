#include "NJThread.h"

namespace NJ::Libs {
    NJThread::NJThread() : m_Job(nullptr),m_JobThread(nullptr),m_RunFlag(false) {

    }

    std::shared_ptr<IRunnable> NJThread::getJob() {
        std::unique_lock<std::mutex> ul(m_JobMut);
        return m_Job;
    }

    void NJThread::setJob(std::shared_ptr<IRunnable> job) {
        std::unique_lock<std::mutex> ul(m_JobMut);
        m_Job = job;
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
    }

    void NJThread::stop() {
        setRunFlag(false);
        while(getJob()!=nullptr) {
        }
        m_JobCV.notify_all();
    }

    bool NJThread::submitJob(std::shared_ptr<IRunnable> job) {
        if(getJob() != nullptr || job == nullptr) {
            return false;
        }
        setJob(job);
        m_JobCV.notify_all();
        return true;
    }

    bool NJThread::isIdle() {
        return (getJob()==nullptr);
    }

    void NJThread::threadFunc() {
        while(getRunFlag()) {

            if(getJob() != nullptr) {
                m_Job->run();
            }
            setJob(nullptr);
            m_JobCV.wait(m_JobMut);
        }
    }

    NJThread::~NJThread() {

    }
}