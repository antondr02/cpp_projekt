/*
 * GraphicsGems.h
 * Version 1.0 - Andrew Glassner
 * from "Graphics Gems", Academic Press, 1990
 */

#ifndef GG_H

#define GG_H 1

/*********************/
/* 2d geometry types */
/*********************/

typedef struct Point2Struct { /* 2d point */
  double x, y;
} Point2;
typedef Point2 Vector2;

typedef struct IntPoint2Struct { /* 2d integer point */
  int x, y;
} IntPoint2;

typedef struct Matrix3Struct { /* 3-by-3 matrix */
  double element[3][3];
} Matrix3;

typedef struct Box2dStruct { /* 2d box */
  Point2 min, max;
} Box2;

/*********************/
/* 3d geometry types */
/*********************/

typedef struct Point3Struct { /* 3d point */
  double x, y, z;
} Point3;
typedef Point3 Vector3;

typedef struct IntPoint3Struct { /* 3d integer point */
  int x, y, z;
} IntPoint3;

typedef struct Matrix4Struct { /* 4-by-4 matrix */
  double element[4][4];
} Matrix4;

typedef struct Box3dStruct { /* 3d box */
  Point3 min, max;
} Box3;

/***********************/
/* one-argument macros */
/***********************/

/* absolute value of a */
#define ABS(a) (((a) < 0) ? -(a) : (a))

/* round a to nearest int */
#define ROUND(a) floor((a) + 0.5)

/* take sign of a, either -1, 0, or 1 */
#define ZSGN(a) (((a) < 0) ? -1 : (a) > 0 ? 1 : 0)

/* take binary sign of a, either -1, or 1 if >= 0 */
#define SGN(a) (((a) < 0) ? -1 : 1)

/* shout if something that should be true isn't */
#define ASSERT(x)                                                              \
  if (!(x))                                                                    \
    fprintf(stderr, " Assert failed: x\n");

/* square a */
#define SQR(a) ((a) * (a))

/***********************/
/* two-argument macros */
/***********************/

/* find minimum of a and b */
#define MIN(a, b) (((a) < (b)) ? (a) : (b))

/* find maximum of a and b */
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

/* swap a and b (see Gem by Wyvill) */
#define SWAP(a, b)                                                             \
  {                                                                            \
    a ^= b;                                                                    \
    b ^= a;                                                                    \
    a ^= b;                                                                    \
  }

/* linear interpolation from l (when a=0) to h (when a=1)*/
/* (equal to (a*h)+((1-a)*l) */
#define LERP(a, l, h) ((l) + (((h) - (l)) * (a)))

/* clamp the input to the specified range */
#define CLAMP(v, l, h) ((v) < (l) ? (l) : (v) > (h) ? (h) : v)

/****************************/
/* memory allocation macros */
/****************************/

/* create a new instance of a structure (see Gem by Hultquist) */
#define NEWSTRUCT(x) (struct x *)(malloc((unsigned)sizeof(struct x)))

/* create a new instance of a type */
#define NEWTYPE(x) (x *)(malloc((unsigned)sizeof(x)))

/********************/
/* useful constants */
/********************/

#define PI 3.141592f       /* the venerable pi */
#define PITIMES2 6.283185f /* 2 * pi */
#define PIOVER2 1.570796f  /* pi / 2 */
#define E 2.718282f        /* the venerable e */
#define SQRT2 1.414214f    /* sqrt(2) */
#define SQRT3 1.732051f    /* sqrt(3) */
#define GOLDEN 1.618034f   /* the golden ratio */
#define DTOR 0.017453f     /* convert degrees to radians */
#define RTOD 57.29578f     /* convert radians to degrees */

/************/
/* booleans */
/************/

#define TRUE 1
#define FALSE 0
#define ON 1
#define OFF 0
typedef int boolean;  /* boolean data type */
typedef boolean flag; /* flag data type */

extern double V2Length();
extern double V2SquaredLength(Vector2 *a);
extern double V2DistanceBetween2Points();
extern Vector2 *V2Negate(), *V2Normalize(), *V2Add();
extern double V2Dot(Vector2 *a, Vector2 *b);
extern Vector2 *V2Scale(Vector2 *v, double newlen);
extern Vector2 *V2Sub(Vector2 *a, Vector2 *b, Vector2 *c);
extern Vector2 *V2Lerp(), *V2Combine(), *V2Mul(), *V2MakePerpendicular();
extern Vector2 *V2New(), *V2Duplicate();
extern Point2 *V2MulPointByProjMatrix();
extern Matrix3 *V2MatMul(), *TransposeMatrix3();

extern double V3SquaredLength(), V3Length();
extern double V3Dot(), V3DistanceBetween2Points();
extern Vector3 *V3Normalize(), *V3Scale(), *V3Add(), *V3Sub();
extern Vector3 *V3Lerp(), *V3Combine(), *V3Mul(), *V3Cross();
extern Vector3 *V3New(), *V3Duplicate();
extern Point3 *V3MulPointByMatrix(), *V3MulPointByProjMatrix();
extern Point3 *V3MulPointByMatrix4(), *V3MulVectorByMatrix4();
extern Matrix4 *V3MatMul();

extern double RegulaFalsi(), NewtonRaphson(), findroot();

Vector3 *V3Negate(Vector3 *v);

#ifdef __cplusplus
extern "C" {
#endif

// Constants Declarations for NearestPoint.c
#define MAXDEPTH 64                         // Maximum depth for recursion
#define EPSILON (ldexp(1.0, -MAXDEPTH - 1)) // Flatness control value
#define DEGREE 3                            // Cubic Bezier curve
#define W_DEGREE 5 // Degree of equation to find roots of

Point2 NearestPointOnCurve(Point2 P, Point2 *V);
int FindRoots(Point2 *w, int degree, double *t, int depth);
Point2 *ConvertToBezierForm(Point2 P, Point2 *V);
double ComputeXIntercept(Point2 *V, int degree);
int ControlPolygonFlatEnough(Point2 *V, int degree);
int CrossingCount(Point2 *V, int degree);
Point2 Bezier(Point2 *V, int degree, double t, Point2 *Left, Point2 *Right);
Vector2 V2ScaleII(Vector2 *v, double s);

#ifdef __cplusplus
}
#endif

#endif
