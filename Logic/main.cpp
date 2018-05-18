#include <QCoreApplication>
#include <iostream>
#include "gomokulogic.h"

using namespace std;

int main()
{
    //gumokulogic test
    Logic* b,*c;
    b = new GumokuLogic;
    c = new GumokuLogic;
    b->play_chess(0,0,White,nullptr);
    b->play_chess(1,1,White,nullptr);
    b->play_chess(2,2,Black,nullptr);
    b->play_chess(3,3,White,nullptr);
    b->play_chess(4,4,White,nullptr);
    b->print();
    b->save("b1.txt");
    cout << b->withdraw(Black) << endl;
    b->print();
    b->save("b2.txt");
    cout << b->withdraw(White) << endl;
    b->print();
    b->save("b3.txt");
    cout << b->withdraw(Black) << endl;
    cout << b->withdraw(none) << endl;
    c->load("b2.txt");
    c->print();

    delete b;

    //board test
    /*
    Board* a = new Board(5,4);
    a->set_color(1,2,White);
    a->set_color(0,0,Black);
    a->print();
    cout << a->get_color(1,2) << endl;
    delete a;
    */

    return 0;
}

