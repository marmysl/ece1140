#include "Train.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
    cout << "The argv is .... "<< *argv << endl;

    Train* train1 = new Train(1, argc, argv);//, argc, argv);

    train1->setPower(69);

    Train* train2 = new Train(1, argc, argv);//, argc, argv);

    return 0;
}
