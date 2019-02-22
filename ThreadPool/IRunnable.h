#ifndef LIBS_IRUNNABLE_H
#define LIBS_IRUNNABLE_H
namespace NJ::Libs {
    class IRunnable {
    public:
        IRunnable(){}
        virtual void run() = 0;
        virtual ~IRunnable(){}
    private:
        IRunnable(const IRunnable&);
    };
}
#endif //LIBS_IRUNNABLE_H
