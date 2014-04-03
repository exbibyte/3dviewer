#ifndef MATRIXMATH_H
#define MATRIXMATH_H

///methods for matrix arithmetic in column major format
namespace MatrixMath{
  /// provides matrix inversion
  /// from http://stackoverflow.com/questions/1148309/inverting-a-4x4-matrix
  bool InvertMatrix(const float m[16], float invOut[16]);

  /// provides 4x1 * 4x4 matrix operation 
  void Mat4x4Mult4x1(float FourByOne[], float FourbyFour[], float out[]);

  /// provides 4x4 * 4x4 matrix operation 
  void Mat4x4Mult4x4(float Left[], float Right[], float out[]);

  /// transposes 4x4 matrix
  void Mat4x4Transpose(float in[], float out[]);
  
  /// normalizes transformation matrix
  void Mat4x4Normalize(float in[], float out[]);
  void Mat4x1Normalize(float in[], float out[]);

  /// prints matrix
  void PrintMat4x4(float in[]);
  void PrintMat4x1(float in[]);

  void GetMat4x4Identity(float out[]);
}
#endif
