
// Interface representing objects from which characters can be pulled.
class Source {
public:
    // Returns -1 on end-of-input; otherwise returns the next character.
    virtual int get( ) = 0;
};

// Interface representing objects to which characters can be pushed.
class Sink {
public:
    virtual void put( char ch ) = 0;
};
