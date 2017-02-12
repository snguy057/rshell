/*
 * This is the abstract base class which will provide
 * a common interface for the rest of our composite
 * classes.
 */

#ifndef INPUT_H
#define INPUT_H

class Input {
public:
    virtual bool evaluate();
};
#endif
