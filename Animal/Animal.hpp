/*! \file   Animal.hpp
 *  \brief  A demonstration class hierarchy.
 *  \author Peter C. Chapin <pchapin@vtc.edu>
 */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <vector>

// An enumeration type is a collection of user defined values. Give the values names that make
// sense in your program. C has a simpler enumeration type (without the word "class") that C++
// also has for compatibility. However, enum classes have some additional features and are safer
// to use (but are only supported in C++ 2011).
//
enum class EndangeredType { NotEndangered, Endangered };

// Class Animal is an abstract base class. It is abstract because it contains at least one pure
// virtual function. As a result it is not possible to create objects of type Animal. It is,
// however, possible to create pointers to Animals and references to Animals.
//
class Animal {
public:
    // The constructor initializes Animal's fields. Note that sleeping_flag could have been
    // defined with another enum class, but for purposes of comparison I used plain bool here.
    //
    Animal( int id, std::vector<double> initial_position, bool sleeping_flag = false );

    virtual ~Animal( ) { }

    // The bodies of the inline methods can refer to class members declared (in the private
    // section) below. This is the only place in C++ where it is permitted to make forward
    // references.
    //
    std::vector<double> get_position( ) const
        { return { x_position, y_position, z_position }; }

    bool is_sleeping( ) const
        { return sleeping; }

    int get_id( ) const
        { return id; }

    // The methods above are non-virtual. They can't be overridden and they don't dispatch. Not
    // all methods need dispatching behavior (in Java such methods could be declared as
    // "final"). Dispatching entails some, small runtime overhead.
    //
    // The method below is virtual so it will dispatch to an overriding version. The =0 means it
    // is "pure virtual" which is the C++ way to say it's an abstract method without an
    // implementation in this class.
    //
    // Simulate the animal for one "time step".
    virtual void time_step( ) = 0;

    // The protected section is accessible to the derived classes but not the client code
    // outside this class hierarchy. It can be used, as here, for convenience. Some programmers
    // feel protected sections should be avoided. A change here will require review and possible
    // change to the entire class hierarchy and the developer of the base class might not know
    // all the derived classes.
protected:
    bool   sleeping;
    double x_position, y_position, z_position;

    // The private section is private to this class only. Not even derived classes can access
    // private members. They can, however, use public (or protected) methods.
private:
    int id;
};


// A Feline is-a Animal. It's constructor uses the special initialization syntax to invoke the
// constructor of the base class (to initialize the base subobject). Note that the body of the
// constructor is empty here since nothing else needs to be done to initialize a Feline.
//
// Because Feline does not implement the pure virtual function it inherits from Animal it is
// still abstract.
//
// The "public" in the class derivation is the common case (probably well over 99% of all class
// derivations in C++ are public). It means the public section of the base class is public in
// the derived class. There is also private (and even protected) derivation, but they are rarely
// used. Some programmers feel they shouldn't have even been included in the language.
//
class Feline : public Animal {
public:
    Feline( int id, std::vector<double> initial_position, EndangeredType endangered_flag ) :
        Animal( id, initial_position ), endangered( endangered_flag ) { }

private:
    EndangeredType endangered;
};


// A Tiger is-a Feline. Here the pure virtual function is overridden with something concert. This
// allows Tiger objects to be created. The 'override' is a C++ 2011 feature that allows you to
// mark overriding methods and have the compiler check that the do, in fact, override something.
// Java has an @Override annotation for this purpose.
//
class Tiger : public Feline {
public:
    Tiger( int id, std::vector<double> initial_position ) :
        Feline( id, initial_position, EndangeredType::Endangered ) { }

    virtual void time_step( ) override;
};


// Like Feline, Primate is abstract.
class Primate : public Animal {
public:
    Primate( int id, std::vector<double> initial_position, EndangeredType endangered_flag ) :
        Animal( id, initial_position), endangered( endangered_flag ) { }

private:
    EndangeredType endangered;
};


// Human is a concrete class because it also overrides the time_step method.
class Human : public Primate {
public:
    Human( int id, std::vector<double> initial_position ) :
        Primate( id, initial_position, EndangeredType::NotEndangered ) { }
    
    virtual void time_step( ) override;
};


#endif
