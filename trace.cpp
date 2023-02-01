#include<string>
#include<iostream>
#include<vector>
using namespace std;

class tint {
    private:
        struct ln {
            ln *last;
            int val;
            ln* next;

            ln (int v) { val = v; }
            ln (int v, ln *f) { val = v; last = f; }
        };
        bool move(ln *t, int steps = 1) {
            if (steps > 0) {
                for ( ; steps; steps --) {
                    t = t->next;
                }
            } else {
                for ( ; steps; steps ++) {
                    t = t->last;
                }
            }
            return steps!=0;
        }


        ln *begin;
        ln *history;
        vector<ln *> versions;

        int update(int v) {
            ln *fresh = new ln(v, history);
            history->next = fresh;
            history = fresh;
            i = v;
            return v;
        }

        void log (ln *listnode, int _v = 0) {

            ln *newbegin = (_v) ? versions[_v] : listnode;
            cout << (_v) << endl;

            do {
                cout << newbegin->val << " ";
            } while (move(newbegin));
            cout << endl;

        }

    public:
        int i;

        tint (int initial = 0) {
            i = initial;
            begin = new ln(initial);
            history = begin;
        }

        ln *operator&() { return begin; }

        bool operator==(int v) { return i == v; }
        bool operator>(int v) { return i > v; }
        bool operator<(int v) { return i < v; }
        bool operator>=(int v) { return i >= v; }
        bool operator<=(int v) { return i <= v; }
        bool operator!() { return i == 0; }

        int operator*(int v) { return i * v; }
        int operator/(int v) { return i / v; }
        int operator%(int v) { return i % v; }
        int operator+(int v) { return i + v; }
        int operator-(int v) { return i - v; }
        int operator*=(int v) { return update(i * v); }
        int operator/=(int v) { return update(i / v); }
        int operator+=(int v) { return update(i + v); }
        int operator-=(int v) { return update(i - v); }
        int operator++() { return update (i + 1); }
        int operator--() { return update (i - 1); }


        bool roll_back (int steps) {
            if (move(*&history, steps*-1)) {
                cout << "rolling" << endl;
                versions.push_back(history->next);
                history->next = nullptr;
                i = history->val;
                return true;
            } else return false;
        }

        void log_history (bool old_versions = false) {

            log(begin);

            tint ne;

            if (old_versions) {
                cout << "| overwritten segments NEWEST -> OLDEST" << endl;
                cout << versions.size() << endl;
                for (int vi = versions.size()-1; vi >= 0; vi --) {
                    cout << "| ";
                    log(nullptr, vi);
                }
            }
        }
        
};