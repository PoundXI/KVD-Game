#ifndef TIMELINE_HPP_INCLUDED
#define TIMELINE_HPP_INCLUDED

#include <vector>

class Timeline {
public:
    struct LineType {
        int id;
        int sec;
        bool marked;
        float x;
        float y;

        LineType(int _id, int _sec, float _x, float _y) {
            id = _id;
            sec = _sec;
            marked = false;
            x = _x;
            y = _y;
        }
    };

    bool Add(int id, int sec, float x, float y);
    bool Remove(int sec);
    void Clear();

    int GetId(int sec);
    float GetX(int sec);
    float GetY(int sec);

    bool IsExist(int sec);
    bool IsMarked(int sec);
    bool Mark(int sec);

    int GetFinishTime();

private:
    std::vector<LineType> _timeline;
};

#endif // TIMELINE_HPP_INCLUDED
