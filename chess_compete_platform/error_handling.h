#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H
class Error_handling{
public:
    Error_handling(){}
    virtual ~Error_handling(){}
    virtual void handle_error(int x, int y) = 0;
};

#endif // ERROR_HANDLING_H

