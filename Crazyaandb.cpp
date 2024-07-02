#include <iostream>
#include <thread>
#include <future>
#include <vector>
#include <stdexcept>
#include <functional>
#include <chrono>

// 模板类用于处理不同类型的数据
template<typename T>
class Calculator {
public:
    Calculator(T a, T b) : a_(a), b_(b) {}

    T add() const {
        return a_ + b_;
    }

    void validateResult(T expected) const {
        T result = add();
        if (result != expected) {
            throw std::logic_error("Validation failed: result does not match expected value.");
        }
    }

private:
    T a_;
    T b_;
};

// 异步计算函数
template<typename T>
T asyncAdd(T a, T b) {
    return std::async(std::launch::async, [a, b]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(100)); // 模拟计算延迟
        return a + b;
    }).get();
}

// 多线程计算并验证结果
template<typename T>
void complexAddition(T a, T b, T expected) {
    std::vector<std::thread> threads;

    // 线程1: 进行同步计算并验证
    threads.emplace_back([=]() {
        try {
            Calculator<T> calc(a, b);
            calc.validateResult(expected);
            std::cout << "Validation successful: " << a << " + " << b << " = " << expected << std::endl;
        } catch (const std::exception& e) {
            std::cout << "Validation error: " << e.what() << std::endl;
        }
    });

    // 线程2: 进行异步计算
    threads.emplace_back([=]() {
        T result = asyncAdd(a, b);
        if (result == expected) {
            std::cout << "Asynchronous addition successful: " << a << " + " << b << " = " << result << std::endl;
        } else {
            std::cout << "Asynchronous addition error: expected " << expected << " but got " << result << std::endl;
        }
    });

    // 等待所有线程完成
    for (auto& thread : threads) {
        thread.join();
    }
}

int main() {
    try {
        int a, b;
        std::cout << "Enter the first number (A): ";
        std::cin >> a;
        std::cout << "Enter the second number (B): ";
        std::cin >> b;

        // 计算预期结果
        int expected = a + b;

        std::cout << "Starting complex addition for: " << a << " + " << b << std::endl;
        complexAddition(a, b, expected);
    } catch (const std::exception& e) {
        std::cout << "Exception caught in main: " << e.what() << std::endl;
    }

    return 0;
}