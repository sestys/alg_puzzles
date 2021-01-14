#include <iostream>
#include <memory>
#include <numeric>
#include <vector>

class Shape {
public:
    virtual int GetArea() const = 0;
    virtual ~Shape() = default;;
};

class Rectangle : public Shape {
public:
    Rectangle(int height, int width) : height_(height), width_(width) {};
    int GetArea() const override {
        return height_ * width_;
    }
    ~Rectangle() override = default;

private:
    int height_;
    int width_;
};

class Triangle : public Shape {
public:
    Triangle(int height, int width) : height_(height), width_(width) {};
    int GetArea() const override {
        return static_cast<int>((height_ * width_) / 2.0 + 0.5);
    }
    ~Triangle() override = default;;
private:
    int height_;
    int width_;
};

class Circle : public Shape {
public:
    explicit Circle(int radius) : radius_(radius) {};
    int GetArea() const override {
        return static_cast<int>(3.14 * radius_ * radius_ + 0.5);
    }
    ~Circle() override = default;

private:
    int radius_;
};
int main() {
    int rectangleHeight = 0, rectangleWidth = 0;
    int triangleHeight = 0, triangleWidth = 0;
    int circleRadius = 0;

    std::cin >> rectangleHeight >> rectangleWidth >> triangleHeight >> triangleWidth >> circleRadius;

    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.emplace_back(std::make_unique<Rectangle>(rectangleHeight, rectangleWidth));
    shapes.emplace_back(std::make_unique<Triangle>(triangleHeight, triangleWidth));
    shapes.emplace_back(std::make_unique<Circle>(circleRadius));

    const int totalArea = std::accumulate(shapes.begin(),
                                          shapes.end(),
                                          0,
                                          [](int total, const auto &shape) { return total + shape->GetArea(); });
    std::cout << totalArea << "\n";

    return 0;
}
