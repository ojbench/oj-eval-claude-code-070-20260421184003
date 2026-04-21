# ifndef _SJTU_CPP_FINAL_SRC_HPP_
# define _SJTU_CPP_FINAL_SRC_HPP_

# include "cpu.hpp"

namespace sjtu {

    // FCFS method based CPU.
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

    // SRTF method based CPU.
    class CPU_SRTF : public CPU {
    public:
        pair<CPUState, uint> run() override {
            if (tasks.empty()) {
                state = idle;
                return make_pair(idle, 0);
            }
            state = busy;
            int best_idx = 0;
            for (int i = 1; i < tasks.size(); ++i) {
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

    // priority method based CPU.
    class CPU_PRIORITY : public CPU {
    public:
        pair<CPUState, uint> run() override {
            if (tasks.empty()) {
                state = idle;
                return make_pair(idle, 0);
            }
            state = busy;
            int best_idx = 0;
            for (int i = 1; i < tasks.size(); ++i) {
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
