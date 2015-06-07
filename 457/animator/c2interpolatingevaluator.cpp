#include "c2interpolatingevaluator.h"
#include <cassert>
#include <algorithm>

using namespace Animator;
using namespace std;

#define C2_EPSILON 0.001

void C2InterpolatingCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts,
	std::vector<Point>& ptvEvaluatedCurvePts,
	const float& fAniLength,
	const bool& bWrap,
	const float default_val) const
{

	int iCtrlPtCount = ptvCtrlPts.size();
	ptvEvaluatedCurvePts.clear();

	if (iCtrlPtCount < 3) { // can't make a c2 interpolating curve with <4 points!
		ptvEvaluatedCurvePts.assign(ptvCtrlPts.begin(), ptvCtrlPts.end());
	}
	else {
		// set up u,p matrices
		int matrixSize = iCtrlPtCount;
		double** u = new double*[matrixSize];
		Point *p = new Point[matrixSize];
		Point *d = new Point[matrixSize];
		for (int i = 0; i < matrixSize; i++) {
			u[i] = new double[matrixSize];
		}

		// initialize u's, p's
		for (int i = 0; i < matrixSize; i++) {
			for (int j = 0; j < matrixSize; j++) {
				// set u values
				if (i == j) {
					if (i == 0 || i == matrixSize - 1) { // edge of diagonal
						u[i][j] = 2;
					} else { // diagonal
						u[i][j] = 4;
					}
				} else if (abs(i - j) == 1) { //next to diagonal
					u[i][j] = 1;
				} else {
					u[i][j] = 0;
				}
			}
			// set p values
			Point pi;
			if (i == 0) {
				pi.x = 3 * ptvCtrlPts[i + 1].x;
				pi.x -= 3 * ptvCtrlPts[i].x;
				pi.y = 3 * ptvCtrlPts[i + 1].y;
				pi.y -= 3 * ptvCtrlPts[i].y;
			} else if (i == matrixSize - 1) {
				pi.x = 3 * ptvCtrlPts[i].x;
				pi.x -= 3 * ptvCtrlPts[i - 1].x;
				pi.y = 3 * ptvCtrlPts[i].y;
				pi.y -= 3 * ptvCtrlPts[i - 1].y;
			} else {
				pi.x = 3 * ptvCtrlPts[i + 1].x;
				pi.x -= 3 * ptvCtrlPts[i - 1].x;
				pi.y = 3 * ptvCtrlPts[i + 1].y;
				pi.y -= 3 * ptvCtrlPts[i - 1].y;
			}

			p[i] = pi;
		}

		// forward elimination
		for (int i = 0; i < matrixSize - 1; i++) {
			for (int j = 0; j < matrixSize; j++) {
				u[i + 1][j] -= (u[i][j]) / 2.0;
			}
			Point pnew;
			pnew.x = p[i + 1].x - (p[i].x) / 2.0;
			pnew.y = p[i + 1].y - (p[i].y) / 2.0;
			p[i + 1] = pnew;
		}

		// back substitution
		Point dnew;
		dnew.x = p[matrixSize - 1].x / u[matrixSize - 1][matrixSize - 1];
		dnew.y = p[matrixSize - 1].y / u[matrixSize - 1][matrixSize - 1];
		d[matrixSize - 1] = dnew;
		for (int i = matrixSize - 2; i >= 0; i--) {
			Point dnew;
			dnew.x = (p[i].x - u[i][i + 1] * d[i + 1].x) / u[i][i];
			dnew.y = (p[i].y - u[i][i + 1] * d[i + 1].y) / u[i][i];
			d[i] = dnew;
		}

		// now to do some bezier
		for (int i = 0; i < matrixSize - 1; i++) {
			Point w0 = ptvCtrlPts[i];
			Point w3 = ptvCtrlPts[i + 1];
			Point w1;
			w1.x = w0.x + (1 / 3.0) * d[i].x;
			w1.y = w0.y + (1 / 3.0) * d[i].y;
			Point w2;
			w2.x = w3.x - (1 / 3.0) * d[i + 1].x;
			w2.y = w3.y - (1 / 3.0) * d[i + 1].y;

			// bound all x values in proper interval so no doubling back
			w1.x = max(w1.x, w0.x);
			w1.x = min(w1.x, w3.x);
			w2.x = max(w2.x, w1.x);
			w2.x = min(w2.x, w3.x);

			// fuck everything
			if (w3.x == w2.x) {
				w3.x += C2_EPSILON;
			}
			
			//have our control points established, now generate a ton of small points?
			float interval = w3.x - w0.x;

			for (float i = 0; i < 1; i += 1 / 100.0) {
				Point step;
				step.x = (-w0.x + 3 * w1.x - 3 * w2.x + w3.x) * pow(i, 3) + (3 * w0.x - 6 * w1.x + 3 * w2.x)*pow(i, 2) + (-3 * w0.x + 3 * w1.x) * i + w0.x;
				step.y = (-w0.y + 3 * w1.y - 3 * w2.y + w3.y) * pow(i, 3) + (3 * w0.y - 6 * w1.y + 3 * w2.y)*pow(i, 2) + (-3 * w0.y + 3 * w1.y) * i + w0.y;
				ptvEvaluatedCurvePts.push_back(step);
			}
		}

		// free things up
		for (int i = 0; i < matrixSize; i++) {
			delete u[i];
		}
		delete u;
		delete p;
		delete d;
	}

	float x = 0.0;
	float y1 = ptvCtrlPts[0].y;
	ptvEvaluatedCurvePts.push_back(Point(x, y1));

	float y2;
	x = fAniLength;
	y2 = ptvCtrlPts[iCtrlPtCount - 1].y;

	ptvEvaluatedCurvePts.push_back(Point(x, y2));
}

