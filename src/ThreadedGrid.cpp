#include "ThreadedGrid.h"
#include <cstdlib>
#include <thread>

ThreadedGridTask::ThreadedGridTask(const int& row, const int& col, int* ptr) : mRow(row), mCol(col), mPtr(ptr) {

}

int ThreadedGridTask::getRow() const { return mRow; }
int ThreadedGridTask::getCol() const { return mCol; }
int* ThreadedGridTask::getPtr() const { return mPtr; }


ThreadedGrid::ThreadedGrid() : NumberGrid() {}

ThreadedGrid::ThreadedGrid(const int& height, const int& width) : ThreadedGrid() {
    setGridSize(height, width);
}

ThreadedGrid::~ThreadedGrid() {}

void ThreadedGrid::calculateAllNumbers() {
    int col;
    int row;
    int* ptr_pixel;
    std::vector<std::thread> threads;
    unsigned char NumThreads = std::thread::hardware_concurrency();
    unsigned char i;

    //Assign tasks
    for (row = 0; row < mHeight; ++row) {
        for (col = 0; col < mWidth; ++col) {
            ptr_pixel = getNumberRef(row, col);
            ThreadedGridTask *task = new ThreadedGridTask(row, col, ptr_pixel);
            mNumberTaskQueue.push_back(task);
        }
    }// Each task is an instance of ThreadedGridTask on the heap
     // stores row, col, and a pointer to the int where the calculation goes

    //Spawn threads
    for (i = 0; i < NumThreads; i++) {
        threads.push_back(std::thread(&ThreadedGrid::worker, this));
    }

    //Destroy threads
    for (i = 0; i < NumThreads; i++) {
        threads[i].join();
    }
    return;
}

void ThreadedGrid::worker() {

    //This would be faster if pulled a bunch of tasks at once

    int taskQueueSize;
    int data;
    while (true) {

        mVectorLock.lock();
        //-----------------Queue Locked --------------------------------

        taskQueueSize = mNumberTaskQueue.size();
        if (taskQueueSize < 1) {
            mVectorLock.unlock(); // Don't leave this locked if we're done
            return;
        }
        ThreadedGridTask* taskPtr = mNumberTaskQueue[taskQueueSize-1];
        ThreadedGridTask task = *taskPtr;
        mNumberTaskQueue.pop_back();
        free(taskPtr);

        //----------------- Queue Unlocked --------------------------------
        mVectorLock.unlock();

        //Do the work (no lock needed)
        data = calculateNumber(task.getRow(), task.getCol());

        //Assign the data back to the grid
        *task.getPtr() = data;
    }
    return;
}