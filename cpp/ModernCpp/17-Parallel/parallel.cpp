#include <execution>
#include <iostream>

void par_discount() {
    std::vector<double> prices = {1.0, 2.0, 3.0, 4.0, 5.0};
    std::vector<double> discounted(prices.size());

    std::transform(std::execution::par, prices.begin(), prices.end(),
                   discounted.begin(),
                   [](double price) { return price * 0.9; });

    std::for_each(std::execution::par, discounted.begin(), discounted.end(),
                  [](double price) { std::cout << price << std::endl; });
}

void par_score() {
    std::vector<int> scores = {1, 2, 3, 4, 5};
    std::sort(std::execution::par, scores.begin(), scores.end());
    std::for_each(std::execution::par, scores.begin(), scores.end(),
                  [](int score) { std::cout << score << " "; });
    std::cout << std::endl;

    auto pass_score = 60;
    auto it =
        std::find_if(std::execution::par, scores.begin(), scores.end(),
                     [pass_score](int score) { return score >= pass_score; });

    if (it != scores.end()) {
        std::cout << "The first pass score is " << *it << std::endl;
    } else {
        std::cout << "No pass score" << std::endl;
    }
}

int main() {
    std::vector<int> data = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    // std::accumulate is a sequential algorithm
    auto sum = std::accumulate(data.begin(), data.end(), 0);
    std::cout << sum << std::endl;
    // std::reduce is a parallel algorithm
    // par_unseq, No guarantees about operation order are provided
    sum = std::reduce(std::execution::par, data.begin(), data.end(), 0);
    std::cout << sum << std::endl;

    par_discount();
    par_score();
    return 0;
}