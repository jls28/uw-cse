#include "beziercurveevaluator.h"
#include <cassert>

using namespace Animator;

void BezierCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts,
	std::vector<Point>& ptvEvaluatedCurvePts,
	const float& fAniLength,
	const bool& bWrap,
	const float default_val) const
{

	int iCtrlPtCount = ptvCtrlPts.size();
	ptvEvaluatedCurvePts.clear();
	
	

	if (iCtrlPtCount < 4) { // can't make a bezier curve with <4 points!
		ptvEvaluatedCurvePts.assign(ptvCtrlPts.begin(), ptvCtrlPts.end());
	}
	else {

		int ptsToBezier = ((iCtrlPtCount - 4) / 3) * 3 + 4;
		std::cout << ptsToBezier << std::endl;
		int leftoverPts = (iCtrlPtCount - 4) % 3;

		for (int i = 0; i < ptsToBezier - 1; i += 3) {
			Point w0 = ptvCtrlPts[i];
			Point w1 = ptvCtrlPts[i + 1];
			Point w2 = ptvCtrlPts[i + 2];
			Point w3 = ptvCtrlPts[i + 3];

			//have our control points established, now generate a ton of small points?
			float interval = w3.x - w0.x;

			for (float i = 0; i < 1; i += 1 / 100.0) {
				Point step;
				step.x = (-w0.x + 3 * w1.x - 3 * w2.x + w3.x) * pow(i, 3) + (3 * w0.x - 6 * w1.x + 3 * w2.x)*pow(i, 2) + (-3 * w0.x + 3 * w1.x) * i + w0.x;
				step.y = (-w0.y + 3 * w1.y - 3 * w2.y + w3.y) * pow(i, 3) + (3 * w0.y - 6 * w1.y + 3 * w2.y)*pow(i, 2) + (-3 * w0.y + 3 * w1.y) * i + w0.y;
				ptvEvaluatedCurvePts.push_back(step);
			}
		}

		for (int i = ptsToBezier; i < leftoverPts + ptsToBezier; i++) {
			ptvEvaluatedCurvePts.push_back(ptvCtrlPts[i]);
		}
	}

	float x = 0.0;
	float y1 = ptvCtrlPts[0].y;
	ptvEvaluatedCurvePts.push_back(Point(x, y1));

	float y2;
	x = fAniLength;
	y2 = ptvCtrlPts[iCtrlPtCount - 1].y;

	ptvEvaluatedCurvePts.push_back(Point(x, y2));
}

