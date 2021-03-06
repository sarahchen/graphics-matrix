#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"

/*-------------- struct matrix *new_matrix() --------------
Inputs:  int rows
         int cols
Returns:

Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)...
*/
struct matrix *new_matrix(int rows, int cols) {
  double **tmp;
  int i;
  struct matrix *m;

  tmp = (double **)malloc(rows * sizeof(double *));
  for (i=0;i<rows;i++) {
      tmp[i]=(double *)malloc(cols * sizeof(double));
    }

  m=(struct matrix *)malloc(sizeof(struct matrix));
  m->m=tmp;
  m->rows = rows;
  m->cols = cols;
  m->lastcol = 0;

  return m;
}


/*-------------- void free_matrix() --------------
Inputs:  struct matrix *m
Returns:

1. free individual rows
2. free array holding row pointers
3. free actual matrix
*/
void free_matrix(struct matrix *m) {

  int i;
  for (i=0;i<m->rows;i++) {
      free(m->m[i]);
    }
  free(m->m);
  free(m);
}


/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
         int newcols
Returns:

Reallocates the memory for m->m such that it now has
newcols number of collumns
====================*/
void grow_matrix(struct matrix *m, int newcols) {

  int i;
  for (i=0;i<m->rows;i++) {
      m->m[i] = realloc(m->m[i],newcols*sizeof(double));
  }
  m->cols = newcols;
}


/*-------------- void print_matrix() --------------
Inputs:  struct matrix *m
Returns:

print the matrix
*/
void print_matrix(struct matrix *m) {
  int r, c;
  for(r=0; r<m->rows; r++) {
    for(c=0; c<m->cols; c++) {
      printf(" %G ", m->m[r][c]);
    }
    printf("\n");
  }
}

/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix
Returns:

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
  int num = m->rows;
  int a, b;

  for(a=0; a<num; a++){
    for(b=0; b<num; b++) {
      if(b == a) {m->m[a][b] = 1;}
      else {m->m[a][b] = 0;}
    }
  }
}


/*-------------- void scalar_mult() --------------
Inputs:  double x
         struct matrix *m
Returns:

multiply each element of m by x
*/
void scalar_mult(double x, struct matrix *m) {
  int i = 0;
  int j = 0;
  for(i=0; i<m->rows; i++)
    for(j=0; j<m->cols; j++)
      m->m[i][j] = m->m[i][j] * x;
}


/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b
Returns:

a*b -> b
*/
void matrix_mult(struct matrix *a, struct matrix *b) {

  struct matrix *tmp = new_matrix(a->rows, b->cols);
  int r, c;
  int ac, br;

  // Placement in tmp
  for(r=0; r<tmp->rows; r++)
    for(c=0; c<tmp->cols; c++)
      // Column in a changes
      for(ac=0; ac<a->cols; ac++)
        // Row in b changes
        for(br=0; br<b->rows; br++)
          tmp->m[r][c] = tmp->m[r][c] + a->m[r][ac]*b->m[br][c];
}



/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b
Returns:

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {

  int r, c;

  for (r=0; r < a->rows; r++)
    for (c=0; c < a->cols; c++)
      b->m[r][c] = a->m[r][c];
}

/*======== struct matrix * make_translate() ==========
Inputs:  int x
         int y
         int z
Returns: The translation matrix created using x, y and z
as the translation offsets.
====================*/
struct matrix * make_translate(double x, double y, double z) {
  struct matrix *T = new_matrix(4, 4);
  ident(T);

  T->m[0][3] = x;
  T->m[1][3] = y;
  T->m[2][3] = z;

  return T;
}

/*======== struct matrix * make_scale() ==========
Inputs:  int x
         int y
         int z
Returns: The translation matrix creates using x, y and z
as the scale factors
====================*/
struct matrix * make_scale(double x, double y, double z) {
  struct matrix *S = new_matrix(4, 4);
  ident(S);

  S->m[0][0] = x;
  S->m[1][1] = y;
  S->m[2][2] = z;

  return S;
}

/*======== struct matrix * make_rotX() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the
angle of rotation and X as the axis of rotation.
====================*/
struct matrix * make_rotX(double theta) {
  struct matrix *rotX = new_matrix(4, 4);
  ident(rotX);
  double angle = theta * (M_PI / 180);

  rotX->m[1][1] = cos(angle);
  rotX->m[1][2] = -sin(angle);
  rotX->m[2][1] = sin(angle);
  rotX->m[2][2] = cos(angle);

  return rotX;
}

/*======== struct matrix * make_rotY() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the
angle of rotation and Y as the axis of rotation.
====================*/
struct matrix * make_rotY(double theta) {
  struct matrix *rotY = new_matrix(4, 4);
  ident(rotY);
  double angle = theta * (M_PI / 180);

  rotY->m[0][0] = cos(angle);
  rotY->m[0][2] = -sin(angle);
  rotY->m[2][0] = sin(angle);
  rotY->m[2][2] = cos(angle);

  return rotY;
}

/*======== struct matrix * make_rotZ() ==========
Inputs:  double theta

Returns: The rotation matrix created using theta as the
angle of rotation and Z as the axis of rotation.
====================
struct matrix * make_rotZ(double theta) {
}
*/
