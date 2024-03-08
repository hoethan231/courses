#include <iostream>
#include "./box.hpp"
using namespace std;

Box heaviestBox(Box arr[], int size) {
    Box heaviest = arr[0];
    for (int i = 1; i < size; i++) {
        if (arr[i] >= heaviest) {
            heaviest = arr[i];
        }
    }
    return heaviest;
}

ImperialWeight totalWeight(Box arr[], int size) {
    ImperialWeight total = arr[0].getWeight();
    for (int i = 0; i < size; i++) {
        total = total + arr[i].getWeight();
    }
    return total;
}

int main() {
    
    ImperialWeight w1{};
    ImperialWeight w2(10, 2);
    w1.setPounds(6);
    w1.setOunces(5);
    
    cout << "Weight1 = " << w1 << endl;
    cout << "Weight2 = " << w2 << endl;
    
    Box b1("Box", w1);
    Box b2("Box", w2);

    b1.setName("Box1");
    b2.setName("Box2");

    cout << "Is Box1 > Box2: " << (b1 > b2) << endl;
    cout << "Is Box1 < Box2: " << (b1 < b2) << endl;

    Box books("Books", ImperialWeight(25,12));
    Box leftTable("Table Left", ImperialWeight(5,4));
    Box rightTable("Table Right", ImperialWeight(10,5));
    Box paintings("Paintings", ImperialWeight(7,1));
    Box Room[4] = {books, leftTable, rightTable, paintings};
    int size = sizeof(Room) / sizeof(Room[0]);

    cout << "The heaviest box is: " << heaviestBox(Room, size).getName() << endl;
    cout << "The total weight in the room is: " << totalWeight(Room, size) << endl;

    return 0;
}