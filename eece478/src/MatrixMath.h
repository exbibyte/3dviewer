// from http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix

#ifndef MATRIXMATH_H
#define MATRIXMATH_H

namespace MatrixMath{
  /// provides matrix inversion
  bool InvertMatrix(const float m[16], float invOut[16]);

  /// provides 4x1 * 4x4 matrix operation 
  void Mat4x4Mult4x1(float FourByOne[], float FourbyFour[], float out[]);

  /// provides 4x4 * 4x4 matrix operation 
  void Mat4x4Mult4x4(float Left[], float Right[], float out[]);

  void Mat4x4Transpose(float in[], float out[]);
}
#endif
