#ifndef LIBS_NJTHREAD_H
#define LIBS_NJTHREAD_H

#include "IRunnable.h"
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>

namespace NJ::Libs {

    class NJThread {
    public:
        NJThread();
        void start();
        void stop();
        bool submitJob(std::shared_ptr<IRunnable> job);
        bool isIdle();
        virtual ~NJThread();
    private:
        bool getRunFlag();
        void setRunFlag(bool);

        void threadFunc();
        NJThread(const NJThread&);
        std::shared_ptr<IRunnable> m_Job;
        std::thread* m_JobThread;
        bool  m_RunFlag;
        std::mutex m_RunFlagMut;
        std::mutex m_CVMut;
        std::mutex m_JobMut;
        std::condition_variable_any m_JobCV;
        std::condition_variable_any m_StartCV;
    };

}



#endif //LIBS_NJTHREAD_H
