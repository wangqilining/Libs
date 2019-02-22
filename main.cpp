#include <iostream>
#include "ThreadPool/NJThread.h"
using namespace  NJ::Libs;
using namespace std;
class Job : public IRunnable {
public:
    void run() {
        cout<<"Job is Runing!"<<endl;
    }
};
int main() {
    NJThread thread;
    thread.start();
    shared_ptr<IRunnable> job(new Job());
    thread.submitJob(job);
    thread.stop();
    return 0;
}