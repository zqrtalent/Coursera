#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;

class JobQueue 
{
private:
    int num_workers_;
    vector<long long> jobs_;
    vector<long long> assigned_workers_;
    vector<long long> start_times_;

    struct JobInfo
    {
        long long jobIndex;
        long long workerIndex;
        long long priority; // Process time.
    } JobInfoStruct;

    vector<struct JobInfo> priority_queue;
    long long queue_size_;

    void WriteResponse() const 
    {
        for (long long i = 0; i < jobs_.size(); ++i) 
        {
            cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
        }
    }

    void ReadData() 
    {
        int m;
        cin >> num_workers_ >> m;
        //num_workers_ = 4; m = 6; 

        //int arr[] = {0, 0, 1, 1, 1};
        //int arr[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
        //int arr[] = {0, 0, 0, 0};
        //int arr[] = {2, 1, 4, 3, 0};
        int arr[] = {5, 9, 8, 4, 2, 7};

        jobs_.resize(m);
        for(int i = 0; i < m; ++i)
        {
            cin >> jobs_[i];
            //jobs_[i] = arr[i];
        }
    }

    int Parent(int index)
    {
        return index/2;
    }

    int LeftChild(int i)
    {
        return 2*i + 1;
    }

    int RightChild(int i)
    {
        return 2*i + 2;
    }

    bool HasHighPriority(struct JobInfo& job1, struct JobInfo& job2)
    {
        /*If processing time for both of them are the same then orken with lowest index gets priority over another.*/
        if(job1.priority == job2.priority)
            return job1.workerIndex < job2.workerIndex ;
        return job1.priority < job2.priority;
        // return (job1.priority < job2.priority) ||
        //     (job1.priority == job2.priority && job1.workerIndex < job2.workerIndex);
    }

    void Swap(JobInfo& job1, JobInfo& job2)
    {
        long long pr = job1.priority;
        long long jb = job1.jobIndex;
        long long wk = job1.workerIndex;

        job1.priority = job2.priority;
        job1.jobIndex = job2.jobIndex;
        job1.workerIndex = job2.workerIndex; 

        job2.priority = pr;
        job2.jobIndex = jb;
        job2.workerIndex = wk; 
    }

    void SiftUp(int index)
    {
        while(index > 0 && HasHighPriority(priority_queue[index], priority_queue[Parent(index)]))
        {
            Swap(priority_queue[Parent(index)], priority_queue[index]);

            // long long pr = priority_queue[parentIndex].priority;
            // long long jb = priority_queue[parentIndex].jobIndex;
            // long long wk = priority_queue[parentIndex].workerIndex;

            // priority_queue[parentIndex].priority = priority_queue[index].priority;
            // priority_queue[parentIndex].jobIndex = priority_queue[index].jobIndex;
            // priority_queue[parentIndex].workerIndex = priority_queue[index].workerIndex; 

            // priority_queue[index].priority = pr;
            // priority_queue[index].jobIndex = jb;
            // priority_queue[index].workerIndex = wk; 

            index = Parent(index);
        }
    }

    void SiftDown(int index)
    {
        int minIndex = index;
        int l = LeftChild(index);
        if(l < queue_size_ && HasHighPriority(priority_queue[l], priority_queue[minIndex]))
            minIndex = l;

        int r = RightChild(index);
        if(r < queue_size_ && HasHighPriority(priority_queue[r], priority_queue[minIndex]))
            minIndex = r;

        if(minIndex != index)
        {
            Swap(priority_queue[minIndex], priority_queue[index]);

            // long long pr = priority_queue[minIndex].priority;
            // long long jb = priority_queue[minIndex].jobIndex;
            // long long wk = priority_queue[minIndex].workerIndex;

            // priority_queue[minIndex].priority = priority_queue[index].priority;
            // priority_queue[minIndex].jobIndex = priority_queue[index].jobIndex;
            // priority_queue[minIndex].workerIndex = priority_queue[index].workerIndex; 

            // priority_queue[index].priority = pr;
            // priority_queue[index].jobIndex = jb;
            // priority_queue[index].workerIndex = wk; 

            SiftDown(minIndex);
        }
    }

    /*Returns job index or -1 if none.*/
    long long ExtractMin(long long& workerIndex)
    {
        if(queue_size_ == 0)
            return -1;

        long long jobIndex = priority_queue[0].jobIndex;
        workerIndex = priority_queue[0].workerIndex;
        queue_size_ --;

        if(queue_size_ > 0)
        {
            priority_queue[0].priority = priority_queue[queue_size_].priority;
            priority_queue[0].jobIndex = priority_queue[queue_size_].jobIndex;
            priority_queue[0].workerIndex = priority_queue[queue_size_].workerIndex; 

            SiftDown(0);
        }
        
        return jobIndex;
    }

    void ScheduleJob(long long jobIndex, long long workerIndex, long long priority)
    {
        if(queue_size_ >= priority_queue.size())
            return;

        priority_queue[queue_size_].jobIndex = jobIndex;
        priority_queue[queue_size_].workerIndex = workerIndex;
        priority_queue[queue_size_].priority = priority;
        queue_size_ ++;

        SiftUp(queue_size_-1);
    }

    void AssignJobs() 
    {
        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());

        // Initialize priority queue.
        queue_size_ = 0;
        priority_queue.resize(num_workers_);

        vector<long long> worker_start_times;
        worker_start_times.resize(num_workers_);

        long long jobsCompleted = (jobs_.size() < num_workers_ ? jobs_.size() : num_workers_);
        // Schedule jobs to all workers.
        long long currWorkerIndex = 0;
        for(int i=0; i<jobsCompleted; i++)
        {
            ScheduleJob(i, i, 0);
        }

        long long workerIndex = 0, jobIndex = 0, currTimeProcessing = 0, priority = 0;
        for(long long i=0; i<jobs_.size(); i++)
        {
            // Highest priority job.
            long long startTime = priority_queue[0].priority;
            
            jobIndex = ExtractMin(workerIndex);
            // Increase job start time for worker.
            assigned_workers_[i]   = workerIndex;
            start_times_[i]        = startTime;

            // Schedule job.
            priority = startTime + jobs_[i];
            ScheduleJob(i, workerIndex, priority);
        }
    }

public:
    void Solve() 
    {
        ReadData();
        AssignJobs();
        WriteResponse();
    }
};

int main() 
{
    std::ios_base::sync_with_stdio(false);
    JobQueue job_queue;
    job_queue.Solve();
    return 0;
}