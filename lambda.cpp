#include <iostream>

int testbasic() {
    auto add = [](int a, int b) -> int {
        return a + b;
    };

    std::cout << "3 + 4 = " << add(3, 4) << std::endl;

    return 0;
}

int testTrapValFromOutside() {
    int x = 10;
    int y = 20;

    auto add = [x, y]() -> int {
        return x + y;
    };

    std::cout << "x + y = " << add() << std::endl;

    return 0;
}

int testTrapRefFromOutside() {
    int x = 10;

    auto increment = [&x]() {
        x += 1;
    };

    increment();
    std::cout << "x = " << x << std::endl; // 输出 x = 11

    return 0;
}

int testTrapAllValFromOutside() {
    int a = 1, b = 2, c = 3;

    auto sum = [=]() {
        return a + b + c;
    };

    std::cout << "Sum = " << sum() << std::endl; // 输出 Sum = 6

    return 0;
}
