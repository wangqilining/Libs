#include <iostream>
#include "ThreadPool/NJThreadPool.h"
using namespace  NJ::Libs;
using namespace std;

    class Job : public IRunnable {
    public:
        Job(){}
        void run() {
            cout<<"Job is Runing!"<<endl;
        }
    };

int main() {

    NJThreadPool pool(10);
    cout<<"pool start"<<endl;
    std::shared_ptr<IRunnable> job1(new Job);
    std::shared_ptr<IRunnable> job2(new Job);
    std::shared_ptr<IRunnable> job3(new Job);
    std::shared_ptr<IRunnable> job4(new Job);
    std::shared_ptr<IRunnable> job5(new Job);
    std::shared_ptr<IRunnable> job6(new Job);
    int y;
    //cin>>y;
    cout<<pool.submitJob(job1)<<endl;
    //cin>>y;
    cout<<pool.submitJob(job2)<<endl;
    //cin>>y;
    cout<<pool.submitJob(job3)<<endl;
    //cin>>y;
    cout<<pool.submitJob(job4)<<endl;
    //cin>>y;
    cout<<pool.submitJob(job5)<<endl;
    //cin>>y;
    cout<<pool.submitJob(job6)<<endl;
    //cin>>y;

    for(int i=0;i<11;i++) {
        cout<<pool.submitJob(job1)<<endl;
    }
    int x;
    cin>>x;
    return 0;
}