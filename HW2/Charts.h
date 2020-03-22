/*
Andrew Mashhadi
ID: 905092387
PIC 10C
Programming Homework #2

Honor Pledge:

I pledge that I have neither given nor received
unauthorized assistance on this assignment.
*/

#ifndef CHARTS_H
#define CHARTS_H
#include <iostream>
#include <vector>


class Chart
{
public:

    class Iterator      
    {
    private:
        size_t position;
        const Chart* in_chart;

    public:
       
        /* Default constructor for nested Iterator class. Sets member variable position to 0 and 
        member variable in_chart to nullptr.
        */
        Iterator();    

        /* Constructor with parameters for nested Iterator class. 
        @param p is what the member variable position will be set to
        @param i is what the member variable in_chart will be pointing to
        */
        Iterator(size_t p, const Chart* i);

        /* Overloaded prefix increment operator for this nested Iterator. Increments the position member 
        variable. 
        @return a reference to this recently updated Iterator object.
        */
        Iterator& operator++();   

        /* Overloaded postfix increment operator for this nested Iterator. Increments the position member
        variable.
        @param dummy int variable to specify that this increment operator is postfix.
        @return a copy of this Iterator object before having position incremented.
        */
        Iterator operator++(int dummy);

        /* Overloaded equals to operator to return true if this Iterator's position variable is the same 
        as the right Iterators.
        @param right is the right Iterator we are comparing this Iterator object to.
        @return true if this is Iterator's position variable is the same as the right Iterator's. False otherwise
        */
        bool operator==(const Iterator& right) const;

        /* Overloaded not equals to operator to return true if this is Iterator's position variable is not the same
       as the right Iterators.
       @param right is the right Iterator we are comparing this Iterator object to.
       @return true if this is Iterator's position variable is not the same as the right Iterator's. False otherwise
       */
        bool operator!=(const Iterator& right) const;

        /* Overloaded de-referenceing operator to access the data from the Chart this Iterator is refering to.
        @return the data this Iterator is refering to, which is from the vector within the Chart that in_char is pointing at.
        */
        int operator*() const;   
    };

    /* Adds an item to the chart.
    @param item to add.
    @return void.
    */
    void add(int item);

    /* This function is a function meant to be redefined in the derived class to visually display the data 
    in the chart, but will only display a statement saying it cannot draw the data in this base class.
    @retun void.
    */
    virtual void draw() const;

    /* First item of the chart.
    */
    Iterator begin() const;

    /* Last item of the chart.
    */
    Iterator end() const;

    virtual ~Chart();

protected:
    std::vector<int> data;
};



class BarChart : public Chart
{
public: 

    /* This function redefines the draw function from base class Chart. It is used to visually display 
    the data in the base class's protected vector of ints, data.
    @retun void.
    */
    virtual void draw() const;
};

#endif
