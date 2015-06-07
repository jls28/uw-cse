#include "bsplinecurveevaluator.h"
#include <cassert>

using namespace Animator;

void BSplineCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts,
	std::vector<Point>& ptvEvaluatedCurvePts,
	const float& fAniLength,
	const bool& bWrap,
	const float default_val) const
{
	//still linear lmao
	int iCtrlPtCount = ptvCtrlPts.size();
	ptvEvaluatedCurvePts.clear();

	if (iCtrlPtCount < 3) {
		ptvEvaluatedCurvePts.assign(ptvCtrlPts.begin(), ptvCtrlPts.end());
	}
	else {
		//temp vector so we can push back two more of the last point so the spline will go to the end
		std::vector<Point> temp;
		//two extra points for beginning
		temp.push_back(ptvCtrlPts[0]);
		temp.push_back(ptvCtrlPts[0]);
		//add all the points
		temp.insert(temp.end(), ptvCtrlPts.begin(), ptvCtrlPts.end());
		//two extra points for end
		temp.push_back(ptvCtrlPts[iCtrlPtCount - 1]);
		temp.push_back(ptvCtrlPts[iCtrlPtCount - 1]);
		int finalPtCount = temp.size();
		for (int i = 0; i < finalPtCount - 3; i++) {
			Point b0 = temp[i];
			Point b1 = temp[i + 1];
			Point b2 = temp[i + 2];
			Point b3 = temp[i + 3];

			Point w0;
			Point w1;
			Point w2;
			Point w3;

			w0.x = (1.0 / 6.0) * b0.x + (2.0 / 3.0) * b1.x + (1.0 / 6.0) * b2.x;
			w1.x = (2.0 / 3.0) * b1.x + (1.0 / 3.0) * b2.x;
			w2.x = (1.0 / 3.0) * b1.x + (2.0 / 3.0) * b2.x;
			w3.x = (1.0 / 6.0) * b1.x + (2.0 / 3.0) * b2.x + (1.0 / 6.0) * b3.x;

			w0.y = (1.0 / 6.0) * b0.y + (2.0 / 3.0) * b1.y + (1.0 / 6.0) * b2.y;
			w1.y = (2.0 / 3.0) * b1.y + (1.0 / 3.0) * b2.y;
			w2.y = (1.0 / 3.0) * b1.y + (2.0 / 3.0) * b2.y;
			w3.y = (1.0 / 6.0) * b1.y + (2.0 / 3.0) * b2.y + (1.0 / 6.0) * b3.y;

			for (float i = 0; i < 1; i += 1 / 1000.0) {
				Point step;
				step.x = (-w0.x + 3 * w1.x - 3 * w2.x + w3.x) * pow(i, 3) + (3 * w0.x - 6 * w1.x + 3 * w2.x)*pow(i, 2) + (-3 * w0.x + 3 * w1.x) * i + w0.x;
				step.y = (-w0.y + 3 * w1.y - 3 * w2.y + w3.y) * pow(i, 3) + (3 * w0.y - 6 * w1.y + 3 * w2.y)*pow(i, 2) + (-3 * w0.y + 3 * w1.y) * i + w0.y;
				ptvEvaluatedCurvePts.push_back(step);
			}
		}
	}


	// bookend points
	float x = 0.0;
	float y1 = ptvCtrlPts[0].y;
	ptvEvaluatedCurvePts.push_back(Point(x, y1));

	float y2;
	x = fAniLength;
	y2 = ptvCtrlPts[iCtrlPtCount - 1].y;

	ptvEvaluatedCurvePts.push_back(Point(x, y2));
}

