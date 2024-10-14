// Erik Wood


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <iterator>
#include <numeric> 


using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;

struct Peaches{
   double weight; // oz
   bool ripe;  // ripe or not
   void print() const { cout << (ripe?"ripe":"green") << ", " <<  weight << endl; }
};



int main(){
   srand(time(nullptr));
   const double minWeight = 3.;
   const double maxWeight = 8.;

   cout << "Input basket size: ";
   int size;
   cin >> size;

   vector <Peaches> basket(size);

   // assign random weight and ripeness peaches in the basket
   // replace with generate()
   std::generate(basket.begin(), basket.end(), [minWeight, maxWeight]() {
        Peaches p;
        p.weight = minWeight + static_cast<double>(rand()) / RAND_MAX * (maxWeight - minWeight);
        p.ripe = rand() % 2;
        return p;
   });

   
   // for_each() possibly
   cout << "all peaches"<< endl;
   std::for_each(basket.begin(), basket.end(), [] (const Peaches& p) {
        p.print();
   });

   // moving all the ripe peaches from basket to peck
   // remove_copy_if() with back_inserter()/front_inserter() or equivalents
   deque<Peaches> peck;
   std::remove_copy_if(basket.begin(), basket.end(), std::back_inserter(peck), [](const Peaches& p) {
        return !p.ripe;
   });

   basket.erase(std::remove_if(basket.begin(), basket.end(), [](const Peaches& p) {
        return p.ripe;
   }), basket.end());

   // for_each() possibly
   cout << "peaches remainng in the basket"<< endl;
   std::for_each(basket.begin(), basket.end(), [](const Peaches& p) {
        p.print();
   });

   cout << endl;

   // for_each() possibly
   cout << "peaches moved to the peck"<< endl;
   std::for_each(peck.begin(), peck.end(), [](const Peaches& p) {
        p.print();
   });


   // prints every "space" peach in the peck
   const int space=3; 
   cout << "\nevery " << space << "\'d peach in the peck"<< endl;
   for (auto it = peck.cbegin(); it != peck.cend(); it = std::next(it, space)) {
      it->print();
    }


   // putting all small ripe peaches in a jam
   // use a binder to create a functor with configurable max weight
   // accumulate() or count_if() then remove_if()
   const double weightToJam = 10.0;
   double jamWeight = std::accumulate(peck.begin(), peck.end(), 0.0, 
   [weightToJam](double total, const Peaches& p) {
       return (p.weight < weightToJam) ? total + p.weight : total;
   });

    peck.erase(std::remove_if(peck.begin(), peck.end(), [weightToJam](const Peaches& p) {
        return p.weight < weightToJam;
    }), peck.end());

   cout << "Weight of jam is: " << jamWeight << endl;

}
