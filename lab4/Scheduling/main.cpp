#include <bits/stdc++.h>

using namespace std;

bool IS_RMS = false;


class _proc {
public:
    char id;
    float exec;
    float period;

    _proc(char id, float exec, float period) {
        this->id = id;
        this->exec = exec;
        this->period = period;
    }
};

bool operator>(const _proc &p1, const _proc &p2) {
    if (!IS_RMS) return p1.period > p2.period;
    else return p1.exec > p2.exec;
}

class _cpu {
private:
    int clk = 0;
    float util = 0;
    multimap<int, _proc> proc_map;
    priority_queue<_proc, vector<_proc>, greater<>> buffer;
    map<char, string> display;
public:
    void appendProcess(const _proc &p) {
        util += p.exec / p.period;
        proc_map.insert(make_pair(p.period, p));
    }

    void period_check() {
        if (clk == 0) {
            for (auto i = proc_map.begin(); i != proc_map.end(); i++) {
                buffer.push((*i).second);
            }
        } else {
            pair<multimap<int, _proc>::iterator, multimap<int, _proc>::iterator> some_proc_iter = proc_map.equal_range(
                    clk);
            for (auto i = some_proc_iter.first; i != some_proc_iter.second; i++) {
                buffer.push((*i).second);
            }
        }
    }

    void appendDisplay(_proc *p) {
        for (auto &s:display) {
            if (p == nullptr) s.second.push_back('-');
            else if (s.first == (*p).id) s.second.push_back('#');
            else s.second.push_back('-');
        }
    }

    void print() {

        cout << "$From t="
             << to_string((clk < 50) ? 0 : clk - 50) << " to t="
             << to_string(clk) << endl;
        for (const auto &s:display) {
            cout << string(s.second.begin(), s.second.begin() + 5)
                 << string(s.second.begin() + 5 + ((clk < 50) ? 0 : clk - 50), s.second.end())
                 << endl;
        }
    }


    void clock_edge() {
        period_check();
        if (!buffer.empty()) {
            _proc proc = buffer.top();
            proc.exec = proc.exec - 1;
            appendDisplay(&proc);
            buffer.pop();
            if (proc.exec > 0) buffer.push(proc);
        } else appendDisplay(nullptr);
        clk = clk + 1;
        print();
    }

    void init(int length) {
        for (const auto &p:proc_map) {
            if (display.find(p.second.id) != display.end()) throw runtime_error("ID Duplicates found");
            display.insert(make_pair(p.second.id, to_string(p.second.id - '0') + " : #"));
        }
        if (util > 1) throw runtime_error("Util > 1 :: CANNOT SCHEDULE");
        for (; clk < length;) clock_edge();
    }
};


int main() {
    _cpu cpu;
    cpu.appendProcess(_proc('1', 10, 20));
    cpu.appendProcess(_proc('2', 25, 50));
    cpu.init(150);
}