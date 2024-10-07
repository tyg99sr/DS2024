#include <iostream>
#include <iomanip>
#include "Vector.cpp"
#include <cstdlib>
#include <ctime>

class Complex {
public:
    double real;
    double imag;
    double module;

    Complex() : real(0), imag(0), module(0) {}
    Complex(double real, double imag) {
        this->real = real;
        this->imag = imag;
        this->module = std::sqrt(real * real + imag * imag);
    }

    bool operator<(const Complex& other) const {
        if (std::abs(module - other.module) < 1e-9) {
            return real < other.real || (std::abs(real - other.real) < 1e-9 && imag < other.imag);
        }
        return module < other.module;
    }

    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }
};

double clock_v(std::function<void()> func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
}

void print(Complex& a) {
    std::cout << a.real << "+" << a.imag << "i   ";
}

void COMPLEX_interval_Search(Complex complex_min, Complex complex_max, Vector<Complex>& parent, Vector<Complex>& child) {
    for (int i = 0; i < parent.size(); i++) {
        Complex current = parent[i];
        if (current.module >= complex_min.module && current.module < complex_max.module) {
            child.push_Back(current);
        }
    }
}

int main() {
    int size_v;
    std::cout << "复数向量实验" << std::endl;
    std::cout << "输入复数向量数量：";
    std::cin >> size_v;

    srand(static_cast<unsigned int>(time(nullptr)));

    Complex defaultComplex;
    int num = size_v;
    Vector<Complex> complex_vector(num, 0, defaultComplex);
    for (int i = 0; i < num; i++) {
        Complex new_complex = Complex(double(rand() % 100) / 10, double(rand() % 100) / 10);
        complex_vector.push_Back(new_complex);
    }

    for (int i = 0; i < num / 3; i++) {
        complex_vector[i] = complex_vector[rand() % num];
    }

    std::cout << "\n生成复数向量: \n";
    complex_vector.traverse(print);
    std::cout << std::endl;

    std::cout << "\n置乱: \n";
    complex_vector.unsort();
    complex_vector.traverse(print);
    std::cout << std::endl;

    std::cout << "查找： \n";
    int chose_index = rand() % num;
    std::cout << "choose :" << complex_vector[chose_index].real << "+" << complex_vector[chose_index].imag << "i" << std::endl;
    Complex same_complex = Complex(complex_vector[chose_index].real, complex_vector[chose_index].imag);
    int place = complex_vector.find(same_complex);
    std::cout << "place :" << place << std::endl;
    std::cout << std::endl;

    std::cout << "\n插入: \n";
    Complex new_complex = Complex(rand() % 10, rand() % 10);
    std::cout << "new :" << new_complex.real << "+" << new_complex.imag << "i" << std::endl;
    place = rand() % num;
    std::cout << "insert_place :" << place << std::endl;
    complex_vector.insert(place, new_complex);
    complex_vector.traverse(print);
    std::cout << std::endl;

    std::cout << "\n删除: \n";
    place = rand() % num;
    std::cout << "delete :" << complex_vector[place].real << "+" << complex_vector[place].imag << "i" << std::endl;
    std::cout << "delete_place :" << place << std::endl;
    complex_vector.remove(place);
    complex_vector.traverse(print);
    std::cout << std::endl;

    std::cout << "\n唯一化: \n";
    complex_vector.deduplicate();
    complex_vector.traverse(print);
    std::cout << std::endl;

    Vector<Complex> tosort_vector(complex_vector);

    std::cout << "\n排序: \n";
    double time_b = clock_v([&]() {
        complex_vector.sort(1);
    });

    double time_m = clock_v([&]() {
        complex_vector.sort(3);
    });

    std::cout << "乱序冒泡排序时间：" << time_b << " us   " << "乱序归并排序时间：" << time_m << " us" << std::endl;

    time_b = clock_v([&]() {
        complex_vector.sort(1);
    });

    time_m = clock_v([&]() {
        complex_vector.sort(3);
    });

    std::cout << "有序冒泡排序时间：" << time_b << " us   " << "有序归并排序时间：" << time_m << " us" << std::endl;

    for (int i = 0; i < complex_vector.size(); i++) {
        tosort_vector[tosort_vector.size() - i - 1] = complex_vector[i];
    }

    complex_vector = tosort_vector;

    time_b = clock_v([&]() {
        tosort_vector.sort(1);
    });

    time_m = clock_v([&]() {
        complex_vector.sort(3);
    });

    std::cout << "逆序冒泡排序时间：" << time_b << " us   " << "逆序归并排序时间：" << time_m << " us" << std::endl;

    std::cout << "\n排序后复数向量: \n";
    complex_vector.traverse(print);
    std::cout << std::endl;

    std::cout << "\n区间查找: \n";
    Complex min = complex_vector[rand() % (complex_vector.size() / 2)];
    Complex max = complex_vector[complex_vector.size() / 2 + rand() % (complex_vector.size() / 2)];

    std::cout << "min :" << min.real << "+" << min.imag << "i       " << "max :" << max.real << "+" << max.imag << "i" << std::endl;
    Vector<Complex> interval_vector(0, 0, defaultComplex);
    COMPLEX_interval_Search(min, max, complex_vector, interval_vector);
    interval_vector.traverse(print);
    std::cout << std::endl;

    return 0;
}