
#ifndef ___MATH_VECTOR_H___
#define ___MATH_VECTOR_H___

void vec_add(float vd[], float v1[], float v2[]);
void vec_addv(float vd[], float v[]);

void vec_sub(float vd[], float v1[], float v2[]);
void vec_subv(float vd[], float v[]);

void vec_mul(float vd[], float v[], float s);
void vec_mulv(float vd[], float s);

float vec_dot(float v1[], float v2[]);
void vec_cross(float vd[], float v1[], float v2[]):

float vec_sqr(float v[]);
float vec_mod(float v[]);

void vec_norm(float vd[], float v[]);
void vec_normv(float vd[]);

void vec_unit_normal(float vd[], float v1[], float v2[]);

#endif

