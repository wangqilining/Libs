
#ifndef LIBS_NJTHREADPOOL_H
#define LIBS_NJTHREADPOOL_H
#include "NJThread.h"
#include "IRunnable.h"

namespace NJ::Libs {

    class NJThreadPool {
    public:
        NJThreadPool(int threadNum);
        bool submitJob(std::shared_ptr<IRunnable> job);
        virtual ~NJThreadPool();
    private:
        void initPool();
        NJThreadPool(const NJThreadPool&);
        int m_ThreadNum;
        NJThread* m_ThreadArry;
        std::mutex m_ThreadMut;
    };

}




#endif //LIBS_NJTHREADPOOL_H
