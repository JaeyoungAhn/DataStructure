//
// Created by Ahn on 2022/09/16.
//

#ifndef DS_LINEARLIST_H
#define DS_LINEARLIST_H

#define MAX_ITEMS_COUNTS 100
#define ERROR -1

typedef int ITEM;

class LinearList {
public:
    LinearList();
    ~LinearList(); // there's no garbage collection in cpp
    bool isEmpty() const;
    int length() const;
    ITEM Retrieve(int index);
    int IndexOf(ITEM x) const;
    ITEM Delete(const int & index);
    int Insert(int index, ITEM x);

private:
    ITEM * items;
    int count;

    bool isValidIndex(int index);
};


#endif //DS_LINEARLIST_H
