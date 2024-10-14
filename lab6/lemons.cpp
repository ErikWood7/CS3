// Erik Wood

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <queue>

using std::cin; using std::cout; using std::endl;
using std::string;
using std::vector;
using std::priority_queue;

struct Lemon {
    double quality;
    friend bool operator<(const Lemon& left, const Lemon& right) {
        return left.quality < right.quality;
    }
};

const int maxBoxSize = 30;
const int highestQuality = 10;

int main() {
    srand(time(nullptr));
    vector <Lemon> box(rand() % maxBoxSize + 1); // random box size

    // random quality assingment
    for (auto& lemon : box)
        lemon.quality = static_cast<double>(rand()) / RAND_MAX * highestQuality;

    cout << "Here are the lemons (best first): ";

    priority_queue<Lemon> lemonQueue; // sorted priority queue

    for(const auto& lemon : box){
        lemonQueue.push(lemon); // pushing the lemons generated into the priority_queue
    }
    
    cout << "Here are the lemons (Best ones First): ";    

    while(!lemonQueue.empty()){
        cout << lemonQueue.top().quality << " "; // .top().quality returns the quality 
        lemonQueue.pop(); // pop off that lemon from the queue
    }
    cout << endl;
}
