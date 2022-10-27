//
// Created by Ahn on 2022/09/16.
//

#include "02.LinearList.h"
LinearList::LinearList() {
    items = new ITEM[MAX_ITEMS_COUNTS];
    count = 0;
}

LinearList::~LinearList() {
    delete[] items;
}

bool LinearList::isEmpty() const
// return true iff the list is empty, false otherwise
{
    if(count <= 0) return true;
    else           return false;
}

int LinearList::length() const
// return the list size (i.e., number of elements in the list
{
    return count;
}

ITEM LinearList::Retrieve(int index)
// return the indexth element of the list
{
    if(!isValidIndex(index))
        return ERROR;
    ITEM ret = items[index];
    return ret;
}

int LinearList::IndexOf(ITEM x) const
// return the index of the first occurrence of x in the list
{
    int ret = - 1;
    for(int i=0; i<count; i++)
        if(items[i] == x) {
            ret = i;
            break;
        }
    return ret;
}

ITEM LinearList::Delete(const int & index)
// remove and return the indexth element, elements with higher index have their index reduced by 1
{
    if (!isValidIndex(index))
        return ERROR;
    int ret = items[index];
    for (int i=index; i<count-1; i++)
        items[i] = items[i+1];
    count--;
    return ret;
}

int LinearList::Insert(int index, ITEM x)
// insert x as the indexth element, elements with theIndex >= index have their index incrased by 1
{
    if(index < 0 || count >= MAX_ITEMS_COUNTS)
        return ERROR;

    // count = 6, index=3, x=7
    // 1 2 3 4 5 6
    // 1 2 3 7 4 5 6
    for(int i=count-1; i>=index; i--)
        items[i+1] = items[i];
    items[index] = x;
    count++;
    return 0;
}

bool LinearList::isValidIndex(int index) {
    if(index >= count || index < 0) return false;
    else return true;
}
