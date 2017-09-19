

#include <iostream>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>
using namespace std;

/********* constant variables *********/
const int NO_OF_WORK_POOLS = 3; // number of wwork pools
const int NO_OF_WORKERS = 5; // number of workers in each work pool
const int MAX_NO_OF_TASKS = 5; // the maximum number of tasks a worker can generate.
const int INFINITY = 1000;
const int EMPTY_TASK = -1;

/********* define a taskQueue with infinity length *********/
struct taskQueue{
    int fifo[INFINITY];
};

/********* global variables *********/
int statusOfWorkPool[NO_OF_WORK_POOLS+1]; // t
// when statusOfWorkPool>0, indicated the number of tasks in each workpool
// when statusOfWorkPool<0, indicated the number of idle workers
sem_t statusLockerOfWorkPool[NO_OF_WORK_POOLS+1]; // s
// lock for synchronizing access to statusOfWorkPool
int poolIDtoPlaceWork[NO_OF_WORKERS*NO_OF_WORK_POOLS+1]; // d
// identifies the work pool that a new task will be placed
int emptyWorkPools;
// number of empty work pools
taskQueue tasksInWorkPool[NO_OF_WORK_POOLS+1]; // w
// each one of these is a FIFO queue into which new tasks are placed
sem_t emptyWorkPoolsLocker; // e
// lock for synchronizing access to emptyWorkPools
int head[NO_OF_WORK_POOLS+1];
// index for head of workpool
int tail[NO_OF_WORK_POOLS+1];
// index for tail of workpool
sem_t screenLock;
// lock for outputting to screen
int allTasks = 1;
// global task counter, when this hits 25, workers will stop making new tasks
pthread_t pid;
// parent thread
pthread_t *tids;
// child threads
int numOfTasksNeedToCreate[NO_OF_WORKERS*NO_OF_WORK_POOLS+1];
// maximum number of new tasks a worker will create

/********* function prototypes *********/
void *Worker(void*);
int GetWork(int);
int RemoveTask(int);
void PutWork(int,int);
void InsertTask (int,int);
void DoWork(int,int);
void Init (sem_t *sem);
void Lock (sem_t *sem);
void Unlock (sem_t *sem);
void Destroy (sem_t *sem);


int main(){
    //initialization
    srand(time(0));
    int startTask = 1;
    int totalNumberOfTasks = 0;
    Init(&emptyWorkPoolsLocker);
    Init(&screenLock);
    
    for(int i = 1;i <= NO_OF_WORK_POOLS; i++){
        statusOfWorkPool[i] = 0;
        Init(&statusLockerOfWorkPool[i]);
        for(int j = ((i - 1) * NO_OF_WORKERS + 1);j <= i * NO_OF_WORKERS; j++){
            poolIDtoPlaceWork[j] = i % NO_OF_WORK_POOLS + 1;
        }
        head[i] = 0;
        tail[i] = 0;
    }
    poolIDtoPlaceWork[1] = 1;
    emptyWorkPools = 0;
    
    // random generate the number of tasks each worker will create. The number is in the range of [0, MAX_NO_OF_TASKS]
    for(int i = 1; i <= (NO_OF_WORKERS * NO_OF_WORK_POOLS); i++){
        numOfTasksNeedToCreate[i] = rand()%(MAX_NO_OF_TASKS+1);
        cout<< "Worker "<< i<< " will generate "<< numOfTasksNeedToCreate[i]<< " works"<<endl;
        totalNumberOfTasks += numOfTasksNeedToCreate[i];
    }
    cout<< "Total number of tasks will be generated by child threads = "<< totalNumberOfTasks<< endl<< endl;
    
    
    //create first task
    pid = pthread_self ();
    cout << "Pid: " << pid << " has started." << endl;
    PutWork (1,startTask);
    cout << "Pid: " << pid << " has created task 1 in workPoolID 1" << endl;
    
    
    // create a thread for each replicated worker
    tids = new pthread_t[(NO_OF_WORKERS * NO_OF_WORK_POOLS) + 1];
    
    // let replicated to do their works
    for(int i = 1; i <= (NO_OF_WORKERS * NO_OF_WORK_POOLS); i++){
        pthread_create (&tids[i], NULL, &Worker, (void*)tids);
    }
    
    for(int i = 1; i <= (NO_OF_WORKERS * NO_OF_WORK_POOLS); i++){
        pthread_join (tids[i], NULL);
    }
    
    // clear semaphores
    for (int i = 1; i <= NO_OF_WORK_POOLS; i++){
        Destroy(&statusLockerOfWorkPool[i]);
    }
    Destroy(&emptyWorkPoolsLocker);
    Destroy(&screenLock);
    
    // end program
    cout << "pid: " << pid << " has terminated." << endl << endl;
    
    return 0;
}


// Purpose: get tasks from the corresponding work pool and do work until there is not work in the work pool
//
// Input: tids[] from main function
//
// Called by main function when creating repliacted workers
// Will call DoWork and GetWork
void* Worker(void* arg){
    int workerID = 0; // NOTSURE: initialize it to 0 or 1?
    pthread_t *tids = (pthread_t*)arg;
    
    // convert its own worker id to int
    pthread_t tid = pthread_self ();
    for (int i=1; i<NO_OF_WORKERS*NO_OF_WORK_POOLS+1; i++){
        if (pthread_equal (tid, tids[i])){
            workerID = i;
            break;
        }
    }
    
    // get a task from the corresponding work pool
    int task = GetWork(workerID);
    while(task != EMPTY_TASK){
        DoWork(workerID, task);
        task = GetWork(workerID);
    }
    
    // worker finished all the tasks
    Lock(&screenLock);
    cout<< "workerID: "<< workerID<< " has terminated."<< endl;
    Unlock(&screenLock);
    
    pthread_exit(0);
}

// Purpose: get a task from the work pool
//
// Input: workerID
//
// Output: return a task from the work pool where the worker stays
//
// Called by Worker
// Will call InsertTask and RemoveTask
int GetWork(int workerID){
    int task;
    // get work from the correspoinding work pool
    int workPoolID = ((workerID-1)/NO_OF_WORKERS)+1;
    // workerID: 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15
    // workPoID: 1 1 1 1 1 2 2 2 2 2  3  3  3  3  3
    
    Lock(&statusLockerOfWorkPool[workPoolID]);
    Lock(&emptyWorkPoolsLocker);
    
    // decrement the number of tasks in the work pool
    // or incrememnt the number of idel workers in the work pool
    statusOfWorkPool[workPoolID]--;
    
    // if all workers in the work pool are idle
    if(statusOfWorkPool[workPoolID] == -NO_OF_WORKERS){
        // increment the number of empty work pools by 1
        emptyWorkPools++;
        // if all the work pools are empty, which means the worker calling GetWork functions is the last worker who has work to do
        if(emptyWorkPools == NO_OF_WORK_POOLS){
            Unlock(&emptyWorkPoolsLocker);
            Unlock(&statusLockerOfWorkPool[workPoolID]);
            // insert [NO_OF_WORKERS] NULL tasks to all the work pools
            for(int i=1; i<=NO_OF_WORK_POOLS; i++){
                for(int j=1; j<=NO_OF_WORKERS; j++){
                    InsertTask(i, EMPTY_TASK); // (workPoolID = i, task = NULL)
                }
            }
        }
        else{
            Unlock(&emptyWorkPoolsLocker);
            Unlock(&statusLockerOfWorkPool[workPoolID]);
        }
    }
    else{
        Unlock(&emptyWorkPoolsLocker);
        Unlock(&statusLockerOfWorkPool[workPoolID]);
    }
    
    // pull a task out from work pool
    task = RemoveTask(workPoolID);
    
    return task;
}

// Purpose: return a task from the work pool where worker is in
// Called by GetWork
int RemoveTask(int workPoolID){
    int task;
    
    // Why do we do this lock and unlock thing????
    Lock(&statusLockerOfWorkPool[workPoolID]);
    while(1){
        // if the work pool is empty, unlcok its status
        if(tail[workPoolID] == head[workPoolID]){
            Unlock(&statusLockerOfWorkPool[workPoolID]);
        }
        // if the work pool is not empty, quit looping
        else{
            break;
        }
        Lock(&statusLockerOfWorkPool[workPoolID]);
    }
    
    // get the first task in the task queue out
    head[workPoolID]++;
    task = tasksInWorkPool[workPoolID].fifo[head[workPoolID]];
    // remove the task that has been got i.e. make it an empty task
    tasksInWorkPool[workPoolID].fifo[head[workPoolID]] = EMPTY_TASK;
    Unlock(&statusLockerOfWorkPool[workPoolID]);
    
    return task;
}

// Purpose: worker put work into the work pool which it should put work in
// Called by main, DoWork, and GetWork
// Will call InsertTask
void PutWork(int workerID, int task){
    // get the current work pool ID where the worker is
    int workPoolID = poolIDtoPlaceWork[workerID];
    
    Lock(&statusLockerOfWorkPool[workPoolID]); // lock the synchronizing access to statusOfWorkPool
    Lock(&emptyWorkPoolsLocker); // lock the synchronizing access to emptyWorkPools
    
    statusOfWorkPool[workPoolID]++; // update the status of the work pool
    // if there is one worker from the work pool doing work, work pool status is no longer an empty work pool
    if(statusOfWorkPool[workPoolID] == -NO_OF_WORKERS+1){
        emptyWorkPools--;
    }
    Unlock(&emptyWorkPoolsLocker);
    Unlock(&statusLockerOfWorkPool[workPoolID]);
    
    // insert a new work is in that work pool
    InsertTask(workPoolID, task);
    
    // next time if the worker needs to put work, make the worker put work into next workpool
    poolIDtoPlaceWork[workerID] = workPoolID%NO_OF_WORK_POOLS+1;
    
    return;
}

// Purpose: put a task into a work pool
//
// Input: workPoolID, task
//
// Called by PutWork
void InsertTask(int workPoolID, int task){
    Lock(&statusLockerOfWorkPool[workPoolID]); // lock the synchronizing access to statusOfWorkPool
    tail[workPoolID] ++;
    tasksInWorkPool[workPoolID].fifo[tail[workPoolID]] = task; // add task into task queue
    Unlock(&statusLockerOfWorkPool[workPoolID]);
    return;
}

// Purpose: a worker does his task and create more tasks if needed
//
// Input: workerID, task
//
// Called by Worker
// Will call PutWork
void DoWork(int workerID, int task){
    int workPoolID = ((workerID-1)/NO_OF_WORKERS)+1; // the work pool where the worker stays
    
    Lock(&screenLock);
    cout << "WorkerID " << workerID << " has started task " << task << " from workPoolID " << workPoolID << endl;
    Unlock(&screenLock);
    
    // generate random amount of time to similate work of varying length
    struct timespec randomTime;
    randomTime.tv_sec = rand() % 5;
    randomTime.tv_nsec = rand();
    nanosleep (&randomTime, NULL);
    
    // as long as the worker still have tasks to create, he will create tasks and put in the work pool
    while(numOfTasksNeedToCreate[workerID]>0){
        // worker generate a new task and put it into the work pool
        allTasks++;
        PutWork(workerID, allTasks);
        numOfTasksNeedToCreate[workerID]--;
        
        // print to screen that a worker created a new task
        Lock(&screenLock);
        cout << "WorkerID " << workerID << " has created task " << allTasks << " in workPoolID " << poolIDtoPlaceWork[workerID] << endl;
        Unlock(&screenLock);
    }
    
    // generate random amount of time to similate work of varying length
    randomTime.tv_sec = rand() % 5;
    randomTime.tv_nsec = rand();
    nanosleep (&randomTime, NULL);
    
    Lock(&screenLock);
    cout << "WorkerID " << workerID << " has finished task " << task << " from workPoolID " << workPoolID << endl;
    Unlock(&screenLock);
    
    return;
}


///////// The following functions are from semaphoreFunctions.c //////////
void Init (sem_t *sem)
{
    if (sem_init (sem, 0, 1) == -1)
    {
        cerr << "Failed to initialize semaphore";
        exit (1);
    }
    
    return;
}

void Lock (sem_t *sem)
{
    while (sem_wait (sem) == -1)
    {
        if(errno != EINTR)
        {
            cout << "Thread failed to lock semaphore\n";
            exit (1);
        }
    }
    
    return;
}

void Unlock (sem_t *sem)
{
    if (sem_post (sem) == -1)
    {
        cout << "Thread failed to unlock semaphore\n";
        exit (1);
    }
    
    return;
}

void Destroy (sem_t *sem)
{
    if (sem_destroy (sem) == -1)
    {
        cerr << "Failed to destroy semaphore";
        exit (1);
    }
    
    return;
}