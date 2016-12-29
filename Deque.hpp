/* BLAL ZAFAR - CS 540 - FALL 2016 */
#ifndef DEQUE_HPP
#define DEQUE_HPP

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
//
#include <iostream>

#define TYPE "Deque_"
//initial elements to put in the array
#define INIT_SIZE 5
//upper bound of the array
#define CAP (INIT_SIZE)

#define Deque_DEFINE(T)                                                             \
/*forward declarations for structures */                                            \
struct Deque_##T##_Iterator;                                                        \
struct Deque_##T;                                                                   \
                                                                                    \
struct Deque_##T##_Iterator                                                         \
{                                                                                   \
    /*This is the pointer to the Deque*/                                            \
    Deque_##T* ptr;                                                                 \
    /*where the the item will be inserted*/                                         \
    int loc;                                                                        \
    /*this will move the iterator forward*/                                         \
    void (*inc)(Deque_##T##_Iterator *);                                            \
    /*this will move the iterator backward*/                                        \
    void (*dec)(Deque_##T##_Iterator *);                                            \
    /*this will return the item stored at the*/                                     \
    /*location*/                                                                    \
    T & (*deref)(Deque_##T##_Iterator *);                                           \
};                                                                                  \
                                                                                    \
struct Deque_##T                                                                    \
{                                                                                   \
    /**** instance variables *****/                                                 \
                                                                                    \
    /*this will point to the main data structure*/                                  \
    T* container;                                                                   \
    /*how many elements are in the container thus far*/                             \
    int Container_Size;                                                             \
    /*what is actual capacity of the container*/                                    \
    int Capacity;                                                                   \
    /*size of the array*/                                                           \
    int size_array;                                                                 \
                                                                                    \
    /*HEAD POINTER*/                                                                \
    Deque_##T##_Iterator head;                                                      \
                                                                                    \
    /*TAIL POINTER*/                                                                \
    Deque_##T##_Iterator tail;                                                      \
                                                                                    \
    /*type name*/                                                                   \
    char type_name [sizeof(TYPE#T)];                                                \
                                                                                    \
    /*** FUNCTIONS START HERE *****/                                                \
    void (*push_front)(Deque_##T*, const T &data);                                  \
    void (*push_back)(Deque_##T *, const T &data);                                  \
    void (*pop_back)(Deque_##T *);                                                  \
    void (*pop_front)(Deque_##T *);                                                 \
    T & (*back)(Deque_##T *);                                                       \
    T & (*front)(Deque_##T *);                                                      \
    /*This will return the item at the given index x*/                              \
    T & (*at)(Deque_##T *, int x);                                                  \
    bool (*empty)(Deque_##T *);                                                     \
    const int& (*size)(Deque_##T *);                                                \
    bool (*lessby)(const T &, const T &);                                           \
    void (*clear)(Deque_##T *);                                                     \
    void (*dtor)(Deque_##T *);                                                      \
    Deque_##T##_Iterator (*begin)(Deque_##T *);                                     \
    Deque_##T##_Iterator (*end)(Deque_##T *);                                       \
};                                                                                  \
                                                                                    \
/*+++++++ HELPER FUNCTIONS +++++++*/                                                \
                                                                                    \
/*** forward declarations ***/                                                      \
void Deque_##T##_ctor(Deque_##T *x, bool(*func)(const T &y, const T &z));           \
T* increase_size(Deque_##T* &x);                                                    \
bool empty(Deque_##T *x);                                                           \
void push_front(Deque_##T *x, const T &y);                                          \
void push_back(Deque_##T *x, const T &y);                                           \
void pop_back(Deque_##T *x);                                                        \
void pop_front(Deque_##T *x);                                                       \
T & back(Deque_##T *x);                                                             \
T & front(Deque_##T *x);                                                            \
T & at(Deque_##T *x, int y);                                                        \
const int& size(Deque_##T *x);                                                      \
void clear(Deque_##T *x);                                                           \
void dtor(Deque_##T *x);                                                            \
Deque_##T##_Iterator begin(Deque_##T *x);                                           \
Deque_##T##_Iterator end(Deque_##T *x);                                             \
void inc(Deque_##T##_Iterator *x);                                                  \
void dec(Deque_##T##_Iterator *x);                                                  \
T& deref(Deque_##T##_Iterator *x);                                                  \
bool Deque_##T##_Iterator_equal(const Deque_##T##_Iterator & in, const Deque_##T##_Iterator & in2); \
bool Deque_##T##_equal(Deque_##T &x, Deque_##T &y);                                 \
/**************************/                                                        \
                                                                                    \
/*CONSTRUCTOR*/                                                                     \
void Deque_##T##_ctor(Deque_##T *ap, bool(*func)(const T & objOne, const T & objTwo))   \
{                                                                                   \
    /*initialization of instance variables*/                                        \
    ap->container = (T*)calloc(sizeof(T), INIT_SIZE);                               \
    ap->Container_Size = 0;                                                         \
    ap->Capacity = CAP;                                                             \
    ap->size_array = INIT_SIZE;                                                     \
    memcpy(ap->type_name, TYPE#T, strlen(TYPE#T)+1);                                \
                                                                                    \
    /*initialization of functions*/                                                 \
                                                                                    \
    ap->pop_back = &pop_back;                                                       \
    ap->push_back = &push_back;                                                     \
    ap->pop_front = &pop_front;                                                     \
    ap->front = &front;                                                             \
    ap->push_front = &push_front;                                                   \
    ap->back = &back;                                                               \
                                                                                    \
    ap->at = &at;                                                                   \
    ap->empty = &empty;                                                             \
    ap->size = &size;                                                               \
                                                                                    \
    ap->lessby = func;                                                              \
    ap->end = &end;                                                                 \
    ap->clear = &clear;                                                             \
    ap->dtor = &dtor;                                                               \
    ap->begin = &begin;                                                             \
                                                                                    \
    ap->head.loc = INIT_SIZE / 2;                                                   \
    ap->head.inc = &inc;                                                            \
    ap->head.dec = &dec;                                                            \
    ap->head.deref = &deref;                                                        \
    ap->head.ptr = ap;                                                              \
                                                                                    \
    ap->tail.loc = INIT_SIZE / 2;                                                   \
    ap->tail.inc = &inc;                                                            \
    ap->tail.dec = &dec;                                                            \
    ap->tail.deref = &deref;                                                        \
    ap->tail.ptr = ap;                                                              \
}                                                                                   \
T* increase_size(Deque_##T* &ptr)                                                   \
{   /* Double the capacity */                                                       \
    int x = (ptr->size_array)*2;                                                    \
    int newContainerSize = 0;                                                       \
    /*new head will be at*/                                                         \
    int newHeadLocation = x/2;                                                      \
    /*new tail will be at*/                                                         \
    int newTailLocation = x/2;                                                      \
                                                                                    \
    /*allocate more space*/                                                         \
    T* newCont = (T*)calloc(sizeof(T),x);                                           \
    int currentLoc = newTailLocation;                                               \
    int prevLoc = currentLoc;                                                       \
                                                                                    \
    /*copy old item into the new container*/                                        \
    for(Deque_##T##_Iterator it = ptr->begin(ptr); !Deque_##T##_Iterator_equal(it, ptr->end(ptr)); it.inc(&it)) \
    {                                                                               \
        newCont[currentLoc] = it.deref(&it);                                        \
        prevLoc = currentLoc;                                                       \
        currentLoc = (currentLoc + 1) % x;                                          \
        newContainerSize++;                                                         \
    }                                                                               \
                                                                                    \
    ptr->size_array = x;                                                            \
    ptr->Capacity = ptr->size_array -1;                                             \
    ptr->Container_Size = newContainerSize;                                         \
    ptr->head.loc = newHeadLocation;                                                \
    ptr->tail.loc = prevLoc;                                                        \
    free(ptr->container);                                                           \
    return newCont;                                                                 \
}                                                                                   \
bool empty(Deque_##T *ptr)                                                          \
{                                                                                   \
    if(ptr->Container_Size == 0)                                                    \
    {                                                                               \
        return true;                                                                \
    }                                                                               \
    return false;                                                                   \
}                                                                                   \
                                                                                    \
void push_front(Deque_##T *ptr, const T &data)                                      \
{                                                                                   \
    /*enough space is available*/                                                   \
    if(ptr->Capacity > ptr->Container_Size)                                         \
    {                                                                               \
        /*the container is empty*/                                                  \
        if(ptr->Container_Size == 0)                                                \
        {                                                                           \
            (ptr->container)[ptr->head.loc] = data;                                 \
            (ptr->Container_Size)++;                                                \
            return;                                                                 \
        }                                                                           \
        ptr->head.dec(&ptr->head);                                                  \
        (ptr->container)[ptr->head.loc] = data;                                     \
        (ptr->Container_Size)++;                                                    \
    }                                                                               \
    /*There is not enough so allocate more space*/                                  \
    else                                                                            \
    {                                                                               \
        ptr->container = increase_size(ptr);                                        \
        ptr->head.dec(&ptr->head);                                                  \
        (ptr->container)[ptr->head.loc] = data;                                     \
        (ptr->Container_Size)++;                                                    \
    }                                                                               \
}                                                                                   \
void push_back(Deque_##T *ptr, const T &data)                                       \
{                                                                                   \
    if(ptr->Capacity > ptr->Container_Size)                                         \
    {                                                                               \
        if(ptr->Container_Size == 0)                                                \
        {                                                                           \
            (ptr->container)[ptr->tail.loc] = data;                                 \
            (ptr->Container_Size)++;                                                \
            return;                                                                 \
        }                                                                           \
        ptr->tail.inc(&ptr->tail);                                                  \
        (ptr->container)[ptr->tail.loc] = data;                                     \
        (ptr->Container_Size)++;                                                    \
    }                                                                               \
    else                                                                            \
    {                                                                               \
        ptr->container = increase_size(ptr);                                        \
        ptr->tail.inc(&ptr->tail);                                                  \
        (ptr->container)[ptr->tail.loc] = data;                                     \
        (ptr->Container_Size)++;                                                    \
    }                                                                               \
}                                                                                   \
void pop_back(Deque_##T *ptr)                                                       \
{                                                                                   \
    if(!empty(ptr))                                                                 \
    {                                                                               \
        ptr->tail.dec(&ptr->tail);                                                  \
        (ptr->Container_Size)--;                                                    \
    }                                                                               \
}                                                                                   \
void pop_front(Deque_##T *ptr)                                                      \
{                                                                                   \
    if(!empty(ptr))                                                                 \
    {                                                                               \
        ptr->head.inc(&ptr->head);                                                  \
        (ptr->Container_Size)--;                                                    \
    }                                                                               \
}                                                                                   \
T& back(Deque_##T *ptr)                                                             \
{                                                                                   \
    return (ptr->container)[ptr->tail.loc];                                         \
}                                                                                   \
T& front(Deque_##T *ptr)                                                            \
{                                                                                   \
    return (ptr->container)[ptr->head.loc];                                         \
}                                                                                   \
T& at(Deque_##T *ptr, int loc)                                                      \
{                                                                                   \
    Deque_##T##_Iterator start = ptr->head;                                         \
    for(int i = 0; i < loc; i++)                                                    \
    {                                                                               \
        start.inc(&start);                                                          \
    }                                                                               \
    return (ptr->container)[start.loc];                                             \
}                                                                                   \
const int& size(Deque_##T *x)                                                       \
{                                                                                   \
    return (x->Container_Size);                                                     \
}                                                                                   \
void clear(Deque_##T *x)                                                            \
{                                                                                   \
    free(x->container);                                                             \
    x->container = (T*)malloc(sizeof(T)*INIT_SIZE);                                 \
    x->head.loc = INIT_SIZE;                                                        \
    x->tail.loc = INIT_SIZE;                                                        \
                                                                                    \
    x->Container_Size = 0;                                                          \
    x->Capacity = CAP;                                                              \
}                                                                                   \
void dtor(Deque_##T *ptr)                                                           \
{                                                                                   \
    free(ptr->container);                                                           \
}                                                                                   \
Deque_##T##_Iterator begin(Deque_##T *x)                                            \
{                                                                                   \
    return x->head;                                                                 \
}                                                                                   \
Deque_##T##_Iterator end(Deque_##T *x)                                              \
{                                                                                   \
    Deque_##T##_Iterator temp = x->tail;                                            \
    temp.inc(&temp);                                                                \
    return temp;                                                                    \
}                                                                                   \
void inc(Deque_##T##_Iterator *x)                                                   \
{                                                                                   \
    /*size*/                                                                        \
    int s = (x->ptr->Capacity) + 1;                                                 \
    int& it_index = x->loc;                                                         \
    it_index = (it_index+1) % s;                                                    \
}                                                                                   \
void dec(Deque_##T##_Iterator *x)                                                   \
{                                                                                   \
    int s = (x->ptr->Capacity) + 1;                                                 \
    int & it_index = x->loc;                                                        \
    it_index = (it_index + s - 1)%s;                                                \
}                                                                                   \
T& deref(Deque_##T##_Iterator *x)                                                   \
{                                                                                   \
    const int& in = x->loc;                                                         \
    return (x->ptr->container)[in];                                                 \
}                                                                                   \
bool Deque_##T##_equal(Deque_##T &input_one, Deque_##T &input_two)                  \
{                                                                                   \
    Deque_##T##_Iterator input_one_start = input_one.begin(&input_one);             \
    Deque_##T##_Iterator input_two_start = input_two.begin(&input_two);             \
                                                                                    \
    if(input_one.Container_Size != input_two.Container_Size)                        \
    {                                                                               \
        return false;                                                               \
    }                                                                               \
                                                                                    \
    for(;!Deque_##T##_Iterator_equal(input_one_start,input_one.end(&input_one));    \
    input_one_start.inc(&input_one_start),input_two_start.inc(&input_two_start))    \
    {                                                                               \
        if(input_one.lessby(input_one_start.deref(&input_one_start), input_two_start.deref(&input_two_start)) || input_one.lessby(input_two_start.deref(&input_two_start), input_one_start.deref(&input_one_start)))   \
        {                                                                           \
            return false;                                                           \
        }                                                                           \
    }                                                                               \
    return true;                                                                    \
}                                                                                   \
bool Deque_##T##_Iterator_equal(const Deque_##T##_Iterator &beg, const Deque_##T##_Iterator &endp)    \
{                                                                                   \
    if(beg.loc == endp.loc)                                                         \
    {                                                                               \
        return true;                                                                \
    }                                                                               \
    return false;                                                                   \
}

//+++++++++++ END OF HELPER FUNCTIONS +++++++++++//

#endif // DEQUE_HPP
