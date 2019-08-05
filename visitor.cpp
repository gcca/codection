#include <iostream>
#include <vector>

class column {
public:
  virtual void accept(class visitor &v) = 0;

protected:
  std::vector<double> double_vector{3, 2, 1};
  std::vector<short> short_vector{3, 2, 1};
};

class double_column : public column {
public:
  void accept(visitor &v) override;
};

class short_column : public column {
public:
  void accept(visitor &v) override;
};

class visitor {
public:
  virtual void visit(std::vector<double> &vector) = 0;
  virtual void visit(std::vector<short> &vector) = 0;
};

void double_column::accept(visitor &v) { v.visit(double_vector); }

void short_column::accept(visitor &v) { v.visit(short_vector); }

class half_visitor : public visitor {
public:
  void visit(std::vector<double> &vector) override {
    std::cout << "half double:";
    for (const auto value : vector)
      std::cout << '\t' << value / 2;
    std::cout << std::endl;
  }

  void visit(std::vector<short> &vector) override {
    std::cout << "half short:";
    for (const auto value : vector)
      std::cout << '\t' << value / 2;
    std::cout << std::endl;
  }
};

class twice_visitor : public visitor {
public:
  void visit(std::vector<double> &vector) override {
    std::cout << "twice double:";
    for (const auto value : vector)
      std::cout << '\t' << value * 2;
    std::cout << std::endl;
  }

  void visit(std::vector<short> &vector) override {
    std::cout << "twice short:";
    for (const auto value : vector)
      std::cout << '\t' << value * 2;
    std::cout << std::endl;
  }
};

int main() {
  column *cols[] = {new double_column(), new short_column()};

  half_visitor half;
  twice_visitor twice;

  for (auto col : cols)
    col->accept(half);

  for (auto col : cols)
    col->accept(twice);

  return 0;
}
