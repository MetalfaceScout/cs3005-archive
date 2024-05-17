#ifndef _THREADEDGRID_H_
#define _THREADEDGRID_H_
#include "NumberGrid.h"
#include "ThreadedVector.h"
#include <tuple>
#include <stdlib.h>
#include <mutex>

class ThreadedGridTask {
public:
    ThreadedGridTask(const int& row, const int& col, int* ptr);
    int getRow() const;
    int getCol() const;
    int* getPtr() const;  
private:
    int mRow;
    int mCol;
    int* mPtr;
};

class ThreadedGrid  : public NumberGrid {

public:
    ThreadedGrid();
    ThreadedGrid(const int& height, const int& width);
    virtual ~ThreadedGrid();
    virtual void calculateAllNumbers();
    virtual void worker();


protected:
    std::mutex mDataLock;
    std::mutex mVectorLock;
    std::vector<ThreadedGridTask*> mNumberTaskQueue;
};


#endif

