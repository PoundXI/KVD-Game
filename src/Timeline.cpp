#include "Timeline.hpp"
#include "Debug.hpp"

bool Timeline::IsExist(int sec) {
    std::vector<LineType>::iterator itr = _timeline.begin();
    while(itr != _timeline.end()) {
        if((*itr).sec == sec) {
            return true;
        }
        itr++;
    }
    return false;
}

bool Timeline::Add(int id, int sec, float x, float y) {
    if(IsExist(sec)) {
        return false;
    }
    _timeline.push_back(LineType(id, sec, x, y));
}

bool Timeline::Remove(int sec) {
    if(!IsExist(sec)) {
        return false;
    }

    std::vector<LineType>::iterator itr = _timeline.begin();
    while(itr != _timeline.end()) {
        if((*itr).sec == sec) {
            _timeline.erase(itr);
            break;
        }
        itr++;
    }
    return true;
}

bool Timeline::IsMarked(int sec) {
    std::vector<LineType>::iterator itr = _timeline.begin();
    while(itr != _timeline.end()) {
        if((*itr).sec == sec) {
            return (*itr).marked;
        }
        itr++;
    }
    return false;
}

bool Timeline::Mark(int sec) {
    std::vector<LineType>::iterator itr = _timeline.begin();
    while(itr != _timeline.end()) {
        if((*itr).sec == sec) {
            (*itr).marked = true;
            return true;
        }
        itr++;
    }
    return false;
}

int Timeline::GetFinishTime() {
    int maxTime = 0;
    std::vector<LineType>::iterator itr = _timeline.begin();
    while(itr != _timeline.end()) {
        if(maxTime < (*itr).sec) {
            maxTime = (*itr).sec;
        }
        itr++;
    }
    return maxTime;
}

void Timeline::Clear() {
    _timeline.clear();
}

int Timeline::GetId(int sec) {
    std::vector<LineType>::iterator itr = _timeline.begin();
    while(itr != _timeline.end()) {
        if((*itr).sec == sec) {
            return (*itr).id;
        }
        itr++;
    }
    return -1;
}

float Timeline::GetX(int sec) {
    std::vector<LineType>::iterator itr = _timeline.begin();
    while(itr != _timeline.end()) {
        if((*itr).sec == sec) {
            return (*itr).x;
        }
        itr++;
    }
    return -1;
}

float Timeline::GetY(int sec) {
    std::vector<LineType>::iterator itr = _timeline.begin();
    while(itr != _timeline.end()) {
        if((*itr).sec == sec) {
            return (*itr).y;
        }
        itr++;
    }
    return -1;
}
