#include "Matrices.h"
using std::fixed;
using std::setprecision;
using std::setw;

namespace Matrices {

  Matrix::Matrix(int _rows, int _cols) : rows{ _rows }, cols{ _cols } {
    this->a.assign(rows, vector<double>(cols, 0));
  }

  Matrix::Matrix(const vector<vector<double>>& a) : a(a) {
    this->rows = this->a.size();
    this->cols = this->a[0].size();
  }

  Matrix operator+(const Matrix& a, const Matrix& b) {
    int rows = a.getRows();
    int cols = a.getCols();
    Matrices::Matrix c(rows, cols);

    if (rows != b.getRows() || cols != b.getCols()) {
      throw runtime_error("Error: dimensions must agree");
    }

    for (unsigned short i = 0; i < rows; i++) {
      for (unsigned short j = 0; j < cols; j++) {
        c(i, j) = a(i, j) + b(i, j);
      }
    }

    return c;
  }

  ///Matrix multiply.  See description.
  ///usage:  c = a * b;
  Matrix operator*(const Matrix& a, const Matrix& b) {
    int rows = a.getRows();
    int cols = a.getCols();
    int colsb = b.getCols();
    Matrices::Matrix c(rows, colsb);

    if (cols != b.getRows()) {
      throw runtime_error("Error: dimensions must agree");
    }

    for (unsigned short i = 0; i < rows; i++) {
      for (unsigned short j = 0; j < colsb; j++) {
        for (unsigned short k = 0; k < cols; k++) {
          c(i, j) += a(i, k) * b(k, j);
        }
      }
    }
    return c;
  }

  ///Matrix comparison.  See description.
  ///usage:  a == b
  bool operator==(const Matrix& a, const Matrix& b) {
    int rows = a.getRows();
    int cols = a.getCols();
    bool equivalent = true;

    if (rows != b.getRows() || cols != b.getCols()) {
      equivalent = false;
    }

    for (unsigned short i = 0; i < rows; i++) {
      for (unsigned short j = 0; j < cols; j++) {
        if (abs(a(i, j)) - b(i, j) >= 0.001) {
          equivalent = false;
        }
      }
    }
    return equivalent;
  }

  ///Matrix comparison.  See description.
  ///usage:  a != b
  bool operator!=(const Matrix& a, const Matrix& b) {
    return !(a == b);
  }

  ///Output matrix.
  ///Separate columns by ' ' and rows by '\n'
  std::ostream& operator<<(std::ostream& os, const Matrix& a) {
    for (unsigned short i = 0; i < a.getRows(); i++) {
      for (unsigned short j = 0; j < a.getCols(); j++) {
        os << setw(11) << setprecision(6) << a(i, j) << " ";
      }
      os << "\n";
    }
    return os;
  }

}

