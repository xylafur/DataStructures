#ifndef MATDOUBLE_H
#define MATDOUBLE_H

#include <stdio.h>
#include <exception>

class MatDouble {
private:
  double ** values = NULL;
  unsigned int rows, cols;
  void initMat();
  void delMat();
  bool destructiveRangeCheck(unsigned int r, unsigned int c = 0, bool zero_based = false);
  bool destructiveDimCheck(const MatDouble &b);

public:
  //Matrix Constructor
  MatDouble(unsigned int r = 1, unsigned int c = 1);

  //Copy Constructor
  MatDouble(const MatDouble &copy_from);

  //Destructor
  ~MatDouble();

  //Both dimEquals return true if this matrix and matrix b have the same
  //Dimensions
  bool dimEquals(const MatDouble &b);
  bool dimEquals(const MatDouble *b);

  unsigned int Rows() const; // Returns number of rows
  unsigned int Cols() const; // Returns number of columns

  /****************************************************************************
  // Checks if indexes r and c are not outside of dimensions of this matrix  //
  // zero_based:    |            condition:                                  //
  // true           |       r < rows && c < cols                             //
  // false          |  0 < r <= rows && 0 < c <= cols                        //
  ****************************************************************************/
  bool rangeCheck(unsigned int r, unsigned int c = 0, bool zero_based = false);

  // Element accessor of matrix by copy of values
  // Is not zero based, must be: 0 < r <= rows && 0 < c <= cols
  double get(unsigned int r, unsigned int c);

  // Element setter of matrix
  // Is not zero based, must be: 0 < r <= rows && 0 < c <= cols
  bool set(unsigned int r, unsigned int c, double v);

  // Makes all elements in this matrix equal to 0.0
  void zero();

  // Makes all elements in this matrix equal to 1.0
  void ones();
  
  //Makes this identity matrix
  void identity();

  //Negates all values
  void negate();

  //Scales all elements by scalar
  void scale(double scalar);
  void scale(int scalar);
  
  MatDouble operator -() const;
  MatDouble& operator +=(MatDouble &other);
  MatDouble& operator -=(MatDouble &other);
  MatDouble& operator *=(double scalar);
  MatDouble& operator *=(int scalar);

  double& operator ()(unsigned int i, unsigned int j);

  friend MatDouble operator +(MatDouble op1, MatDouble &op2);
  friend MatDouble operator -(MatDouble op1, MatDouble &op2);
  friend MatDouble operator *(const MatDouble &op1, const MatDouble &op2);
  friend MatDouble operator *(double scalar, MatDouble op2);
  friend MatDouble operator *(int scalar, MatDouble op2);
};

MatDouble operator +(MatDouble op1, MatDouble &op2);
MatDouble operator -(MatDouble op1, MatDouble &op2);
MatDouble operator *(const MatDouble &op1, const MatDouble &op2);
MatDouble operator *(double scalar, MatDouble op2);
MatDouble operator *(int scalar, MatDouble op2);



//DEFINITIONS



void MatDouble::initMat() {
  if (values) delMat();
  values = new double *[rows];
  for (unsigned int r = 0; r < rows; ++r)
    values[r] = new double[cols]{};
}

void MatDouble::delMat() {
  for (unsigned int r = 0; r < rows; ++r)
    delete[] (values[r]);
  delete[] values;
  values = NULL;
}

bool MatDouble::rangeCheck(unsigned int r, unsigned int c, bool zero_based) {
  if (zero_based) return r < rows && c < cols;
  return r > 0 && r <= rows && c > 0 && c <= cols;
}

bool MatDouble::destructiveRangeCheck(unsigned int r, unsigned int c, bool zero_based) {
  if (!(this->rangeCheck(r, c, zero_based))) {
    fprintf(
      stderr,
      "Indexes [%d][%d] out of bounds of row size %d and col size %d\n",
      r, c, rows, cols
    );
    throw std::exception(); //throw a fit
  }
  return true;
}

bool MatDouble::destructiveDimCheck(const MatDouble &b) {
  if (!dimEquals(b)) {
    fprintf(
      stderr,
      "Index mismatch, [%d][%d] != [%d][%d]\n",
      rows, cols, b.rows, b.cols
    );
    throw std::exception(); //throw a fit
  }
  return true;
}

//constructor
MatDouble::MatDouble(unsigned int r, unsigned int c) {
  rows = r;
  cols = c;
  this->destructiveRangeCheck(r, c);
  initMat();
}

//Copy Constructor
MatDouble::MatDouble(const MatDouble &copy_from) {
  if (values != NULL) delMat();
  rows = copy_from.rows;
  cols = copy_from.cols;
  initMat();
  unsigned int r, c;
  for (r = 0; r < rows; ++r)
    for (c = 0; c < cols; ++c)
      values[r][c] = copy_from.values[r][c];
}

MatDouble::~MatDouble() {
  delMat();
}

bool MatDouble::dimEquals(const MatDouble &b) {
  return rows == b.rows && cols == b.cols;
}
bool MatDouble::dimEquals(const MatDouble *b) {
  return rows == b->rows && cols == b->cols;
}

unsigned int MatDouble::Rows() const { return rows; }
unsigned int MatDouble::Cols() const { return cols; }

double MatDouble::get(unsigned int r, unsigned int c) {
  destructiveRangeCheck(r, c);
  return values[r-1][c-1];
}

bool MatDouble::set(unsigned int r, unsigned int c, double v) {
  destructiveRangeCheck(r, c);
  values[r-1][c-1] = v;
  return true;
}

void MatDouble::zero() {
  initMat();
}

void MatDouble::ones() {
  unsigned int r, c;
  for (r = 0; r < rows; ++r) {
    for (c = 0; c < cols; ++c) {
      values[r][c] = 1.0;
    }
  }

}

void MatDouble::identity() {
  zero();
  unsigned int r, c;
  for (r = 0, c = 0; ++r <= rows && ++c <= cols; values[r-1][c-1] = 1.0);
}

void MatDouble::negate() {
  /*
  unsigned int r, c;
  for (r = 0; r < rows; ++r)
    for (c = 0; c < cols; ++c)
      values[r][c] = -values[r][c];
   */
  scale(-1.0);
}

void MatDouble::scale(double scalar) {
  unsigned int r, c;
  for (r = 0; r < rows; ++r)
    for (c = 0; c < cols; ++c)
      values[r][c] *= scalar;
}

void MatDouble::scale(int scalar) {
  return scale(double(scalar));
}

MatDouble MatDouble::operator -() const {
  MatDouble md(*this);
  md.negate();
  return md;
}

MatDouble& MatDouble::operator +=(MatDouble &other) {
  this->destructiveDimCheck(other);
  unsigned int r, c;
  for (r = 0; r < rows; ++r)
    for (c = 0; c < rows; ++c)
      values[r][c] += other.values[r][c];
  return *this;
}

MatDouble& MatDouble::operator -=(MatDouble &other) {
  this->destructiveDimCheck(other);
  unsigned int r, c;
  for (r = 0; r < rows; ++r)
    for (c = 0; c < rows; ++c)
      values[r][c] -= other.values[r][c];
  return *this;
}

MatDouble& MatDouble::operator *=(double scalar) {
  this->scale(scalar);
  return *this;
}

MatDouble& MatDouble::operator *=(int scalar) {
  return (*this) *= double(scalar);
}

double& MatDouble::operator ()(unsigned int i, unsigned int j) {
  this->destructiveRangeCheck(i, j);
  return values[i-1][j-1];
}

MatDouble operator +(MatDouble op1, MatDouble &op2) {
  op1 += op2;
  return op1;
}

MatDouble operator -(MatDouble op1, MatDouble &op2) {
  op1 -= op2;
  return op1;
}

MatDouble operator *(const MatDouble &op1, const MatDouble &op2) {
  if (op1.cols != op2.rows) {
    fprintf(
      stderr,
      "Invalid operand dimensions for matrix multiplication: op1[%d][%d], op2[%d][%d]\n",
      op1.rows, op1.cols, op2.rows, op2.cols
    );
    throw std::exception();
  }

  MatDouble output(op1.rows, op2.cols);
  double sum = 0.0;
  unsigned int r, c, j;
  for (r = 0; r < op1.rows; ++r) {
    for (c = 0; c < op2.cols; ++c) {
      for (j = 0, sum = 0.0; j < op2.rows; ++j) //Perform dot product
        sum += op1.values[r][j]* op2.values[j][c];
      output.values[r][c] = sum;
    }
  }
  return output;
}

MatDouble operator *(double scalar, MatDouble op2) {
  return op2 *= scalar;
}
MatDouble operator *(int scalar, MatDouble op2) {
  return op2 *= scalar;
}

#endif
