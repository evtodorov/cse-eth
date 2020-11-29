#include <iostream>
#include <vector>

int main()
{
    std::vector<int> vector = {1,2,3,4,5};

    auto iter = vector.begin();
    std::advance(iter,2);
    iter = vector.insert(iter,30);

    for (auto v : vector){
        std::cout << v << std::endl;
    }

    return 0;
}
