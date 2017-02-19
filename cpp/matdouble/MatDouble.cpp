
#include "./MatDouble.h"

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
