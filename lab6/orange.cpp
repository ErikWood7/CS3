// Erik Wood

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <map>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;
using std::multimap;

enum class Variety {orange, pear, apple};
vector<string> colors = {"red", "green", "yellow"};

struct Fruit{
   Variety v;
   string color; // red, green or orange
};


int main(){
   srand(time(nullptr));
   vector <Fruit> tree(rand()%100+1);

   // random fruit and color selection
   for(auto& fruit : tree){
    fruit.v = static_cast<Variety>(rand() % 3);
    fruit.color = colors[rand() % 3];
   }

    multimap<Variety, Fruit> fruitmultimap;

    for(const auto& fruit : tree){
        fruitmultimap.emplace(fruit.v, fruit);
    }

    cout << "Colors of the orange: ";

    auto lower = fruitmultimap.lower_bound(Variety::orange);
    auto upper = fruitmultimap.upper_bound(Variety::orange);
   // printing colors of oranges
   for (auto it = lower; it != upper; ++it){
        cout << it->second.color << ", ";
   }

   cout << endl;
}
