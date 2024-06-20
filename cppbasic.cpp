void cmpWithZero() {
  bool isFlag = false;
  if (isFlag) {
  }
  int a = 10;
  if (a == 0) {
  }
  int *p = nullptr;

  if (p == nullptr) {
  }
  double d = 0.1;

  if (d > -0.0001 && d < 0.0001) {
  }
}

void countSizeOf() {
  char str[] = "Hello";
  cout << sizeof(str)
       << endl; // 5 是不对的，是6，末尾有个空字符 '\0'，表示字符串的结束

  string str1 =
      "Hello"; // 24，为什么呢`string str1 =
               // "Hello";`创建了一个C++中的string对象，而不是一个字符数组。
               // string类内部实际上包含了指向字符数组的指针以及一些其他的成员变量。
               // 因此，`sizeof(str1)`
               // 返回的是string对象本身的大小，包括其内部的指针和其他成员变量，通常是固定的大小（如在你的环境中是24）。
               // 这并不代表字符串本身的长度，只是string对象的大小。

  cout << sizeof(str1) << endl;
  cout << str1.size() << endl;   // 5
  cout << str1.length() << endl; // 5
  char *p = str;
  cout << sizeof(p) << endl; // 8

  int n = 10;
  cout << sizeof(n) << endl; // 4
}

void Func(char str[100]) {
  cout << sizeof(str) << endl; // 8
  void *p = malloc(100);
  cout << sizeof(100) << endl; // 4
  cout << *(int *)p << endl;
}

//在C++中，当数组作为函数参数传递时，它实际上会被转换成一个指向数组首元素的指针。因此，当你在函数中使用 `sizeof(str)` 时，它实际上返回的是指针的大小，而不是数组的大小。指针的大小在许多系统中通常是8个字节（64位操作系统）。

//另外，`sizeof(100)` 返回的是整数100的大小，而不是分配的内存大小。在您的环境中，整数通常占据4个字节。

//如果您想在函数内部获取传入数组的大小，您可以考虑使用另一个参数来传递数组的大小，或者使用标准库中的 `std::array` 或 `std::vector`，它们提供了获取大小的方法。

