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

#endif
