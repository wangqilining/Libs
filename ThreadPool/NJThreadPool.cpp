#include "NJThreadPool.h"
#include <iostream>
using namespace std;

namespace NJ::Libs {

    NJThreadPool::NJThreadPool(int num):m_ThreadNum(num) {
        m_ThreadArry = new NJThread[m_ThreadNum];
        initPool();
    }

    bool NJThreadPool::submitJob(std::shared_ptr<IRunnable> job) {
        std::unique_lock<std::mutex> ul(m_ThreadMut);
        for(int i=0;i<m_ThreadNum;i++) {
            if(m_ThreadArry[i].isIdle()) {
                m_ThreadArry[i].submitJob(job);
                return true;
            }
        }
        return false;
    }

    void NJThreadPool::initPool() {
        for(int i=0;i<m_ThreadNum;i++) {
            m_ThreadArry[i].start();
        }
    }

    NJThreadPool::~NJThreadPool() {
        for(int i=0;i<m_ThreadNum;i++) {
            m_ThreadArry[i].stop();
        }
        delete[] m_ThreadArry;
    }
}