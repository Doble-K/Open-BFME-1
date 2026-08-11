// cl: /DNDEBUG /MD /EHsc /ICode/Libraries/Source/WWVegas/WWLib /ICode/Libraries/Source/WWVegas/WWMath /ICode/Libraries/Source/WWVegas/WWDebug

#include "quat.h"
#include "matrix3d.h"

#include <math.h>

static int _nxt[3] = { 1, 2, 0 };

Quaternion Build_Quaternion(const Matrix3D &mat)
{
	float tr, s;
	int i, j, k;
	Quaternion q;

	tr = mat[0][0] + mat[1][1] + mat[2][2];

	if (tr > 0.0f) {
		s = sqrt(tr + 1.0f);
		q[3] = s * 0.5;
		s = 0.5 / s;

		q[0] = (mat[2][1] - mat[1][2]) * s;
		q[1] = (mat[0][2] - mat[2][0]) * s;
		q[2] = (mat[1][0] - mat[0][1]) * s;
	} else {
		i = 0;
		if (mat[1][1] > mat[0][0]) i = 1;
		if (mat[2][2] > mat[i][i]) i = 2;
		j = _nxt[i];
		k = _nxt[j];

		s = sqrt((mat[i][i] - (mat[j][j] + mat[k][k])) + 1.0);

		q[i] = s * 0.5;
		if (s != 0.0) {
			s = 0.5 / s;
		}

		q[3] = (mat[k][j] - mat[j][k]) * s;
		q[j] = (mat[j][i] + mat[i][j]) * s;
		q[k] = (mat[k][i] + mat[i][k]) * s;
	}

	return q;
}
