#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Interval
{
private:
    int startTime_;
    int finishTime_;
    
public:
    Interval(int startTime, int finishTime) : startTime_(startTime), finishTime_(finishTime) {}
  
    bool operator<(const Interval& other) const
    {
        return finishTime_ <= other.finishTime_;
    }
    
    int startTime() const { return startTime_; }
    int finishTime() const { return finishTime_; }
    bool overlaps(const Interval& other) const
    {
        return min(other.finishTime_, finishTime_) >= max(other.startTime_, startTime_);
    }
};

ostream& operator<<(ostream& out, const Interval& interval)
{
    out << "[" << interval.startTime() << " - " << interval.finishTime() << "]";
    return out;
}

int main()
{
    int N;
    cin >> N; cin.ignore();
    set<Interval> intervals;
    for (int i = 0; i < N; i++) {
        int J;
        int D;
        cin >> J >> D; cin.ignore();
        intervals.insert(Interval(J, J + D - 1));
    }

    int c = 0;
    while (!intervals.empty())
    {
        const Interval ei = *intervals.begin();
        for (set<Interval>::iterator it = intervals.begin();
            ei.overlaps(*it) && it != intervals.end(); )
        {
            it = intervals.erase(it);
        }
        ++c;
    }

    cout << c << endl;
}