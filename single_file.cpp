# ifndef _SJTU_CPP_FINAL_TASK_HPP_
# define _SJTU_CPP_FINAL_TASK_HPP_

typedef unsigned int uint;

namespace sjtu {
    struct Task {
        uint task_id;
        uint priority;
        uint time;

        explicit Task(uint _task_id = 0, uint _priority = 0, uint _time = 0) {
            task_id = _task_id;
            priority = _priority;
            time = _time;
        }

        Task(const Task &rhs) {
            task_id = rhs.task_id;
            priority = rhs.priority;
            time = rhs.time;
        }

        ~ Task() = default;
    };

    enum CPUState {
        idle = 0, busy = 1
    };
}
# endif

# ifndef _SJTU_CPP_FINAL_CPU_HPP_
# define _SJTU_CPP_FINAL_CPU_HPP_

# include <vector>

using namespace std;

typedef unsigned int uint;

namespace sjtu {
    class CPU {
    protected:
        CPUState state;
        vector<Task> tasks;

    public:
        CPU() : tasks() {
            state = idle;
        }

        int addTask(const Task &t) {
            tasks.push_back(t);
            return 1;
        }

        int changePriority(uint task_id, uint priority) {
            for (auto &task: tasks)
                if (task.task_id == task_id) {
                    task.priority = priority;
                    return 1;
                }
            return 0;
        }

        virtual pair<CPUState, uint> run() = 0;

        virtual ~ CPU() = default;
    };
}

# endif

# ifndef _SJTU_CPP_FINAL_SRC_HPP_
# define _SJTU_CPP_FINAL_SRC_HPP_

namespace sjtu {

    class CPU_FCFS : public CPU {
    public:
        pair<CPUState, uint> run() override {
            if (tasks.empty()) {
                state = idle;
                return make_pair(idle, 0);
            }
            state = busy;
            uint tid = tasks[0].task_id;
            tasks[0].time--;
            if (tasks[0].time == 0) {
                tasks.erase(tasks.begin());
            }
            return make_pair(busy, tid);
        }
    };

    class CPU_SRTF : public CPU {
    public:
        pair<CPUState, uint> run() override {
            if (tasks.empty()) {
                state = idle;
                return make_pair(idle, 0);
            }
            state = busy;
            int best_idx = 0;
            for (int i = 1; i < (int)tasks.size(); ++i) {
                if (tasks[i].time < tasks[best_idx].time) {
                    best_idx = i;
                }
            }
            uint tid = tasks[best_idx].task_id;
            tasks[best_idx].time--;
            if (tasks[best_idx].time == 0) {
                tasks.erase(tasks.begin() + best_idx);
            }
            return make_pair(busy, tid);
        }
    };

    class CPU_PRIORITY : public CPU {
    public:
        pair<CPUState, uint> run() override {
            if (tasks.empty()) {
                state = idle;
                return make_pair(idle, 0);
            }
            state = busy;
            int best_idx = 0;
            for (int i = 1; i < (int)tasks.size(); ++i) {
                if (tasks[i].priority < tasks[best_idx].priority) {
                    best_idx = i;
                }
            }
            uint tid = tasks[best_idx].task_id;
            tasks[best_idx].time--;
            if (tasks[best_idx].time == 0) {
                tasks.erase(tasks.begin() + best_idx);
            }
            return make_pair(busy, tid);
        }
    };
}

# endif
