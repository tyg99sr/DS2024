#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
// 引入 Vector 模板类的实现文件
#include "Vector.cpp"

class Complex {
public:
    double real;
    double imag;

    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    double magnitude() const {
        return std::sqrt(real * real + imag * imag);
    }

    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    bool operator<(const Complex& other) const {
        double mag1 = magnitude();
        double mag2 = other.magnitude();
        if (mag1!= mag2) return mag1 < mag2;
        return real < other.real;
    }
};

// 随机生成复数向量
Vector<Complex> generateRandomComplexVector(int n) {
    Vector<Complex> v;
    srand(time(nullptr));
    for (int i = 0; i < n; i++) {
        double realPart = static_cast<double>(rand() % 100);
        double imagPart = static_cast<double>(rand() % 100);
        v.push_Back(Complex(realPart, imagPart));
    }
    return v;
}

int main() {
    // 1. 生成随机复数向量
    Vector<Complex> complexVector = generateRandomComplexVector(20);

    // 2. 测试无序向量的置乱、查找、插入、删除和唯一化操作
    std::cout << "Before shuffling: ";
    complexVector.traverse([](Complex& c) { std::cout << "(" << c.real << "," << c.imag << ") "; });
    std::cout << std::endl;

    complexVector.unsort();
    std::cout << "After shuffling: ";
    complexVector.traverse([](Complex& c) { std::cout << "(" << c.real << "," << c.imag << ") "; });
    std::cout << std::endl;

    Complex target(50, 50);
    Rank foundIndex = complexVector.find(target);
    if (foundIndex >= 0) {
        std::cout << "Found complex number (" << target.real << "," << target.imag << ") at index " << foundIndex << std::endl;
    } else {
        std::cout << "Complex number (" << target.real << "," << target.imag << ") not found." << std::endl;
    }

    complexVector.push_Back(Complex(100, 100));
    std::cout << "After inserting (100,100): ";
    complexVector.traverse([](Complex& c) { std::cout << "(" << c.real << "," << c.imag << ") "; });
    std::cout << std::endl;

    complexVector.remove(0);
    std::cout << "After removing element at index 0: ";
    complexVector.traverse([](Complex& c) { std::cout << "(" << c.real << "," << c.imag << ") "; });
    std::cout << std::endl;

    int duplicatesRemoved = complexVector.deduplicate();
    std::cout << "After deduplicating: " << duplicatesRemoved << " duplicates removed." << std::endl;
    complexVector.traverse([](Complex& c) { std::cout << "(" << c.real << "," << c.imag << ") "; });
    std::cout << std::endl;

    // 3. 测试排序效率
    Vector<Complex> orderedVector = complexVector;
    orderedVector.sort(3);
    Vector<Complex> reversedVector = orderedVector;
    reversedVector.unsort();
    reversedVector.sort(3);

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    orderedVector.sort(1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    std::cout << "Time taken for bubble sort on ordered vector: " << cpu_time_used << " seconds." << std::endl;

    start = clock();
    reversedVector.sort(1);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    std::cout << "Time taken for bubble sort on reversed vector: " << cpu_time_used << " seconds." << std::endl;

    start = clock();
    orderedVector.sort(3);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    std::cout << "Time taken for merge sort on ordered vector: " << cpu_time_used << " seconds." << std::endl;

    start = clock();
    reversedVector.sort(3);
    end = clock();
    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    std::cout << "Time taken for merge sort on reversed vector: " << cpu_time_used << " seconds." << std::endl;

    // 4. 实现区间查找算法
    double m1 = 5.0, m2 = 10.0;
    Vector<Complex> subVector;
    for (Rank i = 0; i < orderedVector.size(); i++) {
        double mag = orderedVector[i].magnitude();
        if (mag >= m1 && mag < m2) {
            subVector.push_Back(orderedVector[i]);
        }
    }
    std::cout << "Complex numbers with magnitude between " << m1 << " and " << m2 << ": ";
    subVector.traverse([](Complex& c) { std::cout << "(" << c.real << "," << c.imag << ") "; });
    std::cout << std::endl;

    return 0;
}