// Erik Wood


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <deque>
#include <string>
#include <algorithm>
#include <numeric>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector; using std::deque;

struct Apples{
   double weight; // oz
   string color;  // red or green
   void print() const { cout << color << ", " <<  weight << endl; }
};



int main(){
   srand(time(nullptr));
   const double minWeight = 3.;
   const double maxWeight = 8.;

   cout << "Input crate size: ";
   int size;
   cin >> size;

   vector <Apples> crate(size);

   // assign random weight and color to apples in the crate
   // replace with generate()
   std::generate(crate.begin(), crate.end(), [minWeight, maxWeight]() {
        Apples a;
        a.weight = minWeight + static_cast<double>(rand()) / RAND_MAX * (maxWeight - minWeight);
        a.color  = rand() % 2 == 1 ? "green" : "red";
        return a;
   });

    // for_each() possibly
    cout << "All apples:" << endl;
   std::for_each(crate.begin(), crate.end(), [](const Apples& apple) { apple.print(); });

   
   cout << "Enter weight to find: ";
   double toFind;
   cin >> toFind;

   // count_if()
   
   int cnt = std::count_if(crate.begin(), crate.end(), [toFind](const Apples& apple) {
        return apple.weight > toFind;
    });

   cout << "There are " << cnt << " apples heavier than " 
	<< toFind << " oz" <<  endl;

   // find_if()
   cout << "At positions ";
   auto it = crate.begin();
    while (it != crate.end()) { 
        it = std::find_if(it, crate.end(), [toFind](const Apples& apple) {
            return apple.weight > toFind;
        });
        if (it != crate.end()) {
            std::cout << std::distance(crate.begin(), it) << ", ";
            ++it;
        }
    }
    std::cout << std::endl;


   // max_element()
   auto heaviest = std::max_element(crate.begin(), crate.end(), [](const Apples& a, const Apples& b) {
        return a.weight < b.weight;
   });
   cout << "Heaviest apple weighs: " << heaviest->weight << " oz" << endl;


   // for_each() or accumulate()
   double totalWeight = std::accumulate(crate.begin(), crate.end(), 0.0, [] (double sum, const Apples& apple) {
        return sum + apple.weight;
   });
   cout << "Total apple weight is: " << totalWeight << " oz" << endl;


   // transform();
   cout << "How much should they grow: ";
   double toGrow;
   cin >> toGrow;
   std::transform(crate.begin(), crate.end(), crate.begin(), [toGrow](Apples& apple) {
        apple.weight += toGrow;
        return apple;
   });

   // remove_if()
   cout << "Input minimum acceptable weight: ";
   double minAccept;
   cin >> minAccept;
   auto newEnd = std::remove_if(crate.begin(), crate.end(), [minAccept](const Apples& apple) {
        return apple.weight <= minAccept;
   });

   // removing small apples
   crate.erase(newEnd, crate.end());

   // nested loops, replace with a single loop modification idiom
   for (auto it = crate.begin(); it != crate.end(); ) {
        if (it->weight < minAccept) {
            it = crate.erase(it);
        } else {
            ++it;
        }
    }


   // bubble sort, replace with sort()
   std::sort(crate.begin(), crate.end(), [](const Apples& a, const Apples& b) {
        return a.weight < b.weight;
   });


   // for_each() possibly
   cout << "sorted remaining apples"<< endl;
   for(const auto &e: crate) {
      e.print();
   }

}
