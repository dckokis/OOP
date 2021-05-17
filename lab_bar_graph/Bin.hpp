#pragma once


class Bin {
private:
    int id;
    size_t height;
public:
    Bin (int _id, int _height) : id(_id), height(_height) {};
    void changeHeight(size_t newHeight);
    int GetId();
    size_t GetHeight();
    bool operator==(const Bin & that) const = default;
};
