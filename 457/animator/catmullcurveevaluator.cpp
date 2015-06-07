#include "catmullcurveevaluator.h"
#include <cassert>
#include <algorithm>

using namespace Animator;
using namespace std;

#define CATMULL_EPSILON 0.001

static float getSign(float x) {
	if (x < 0) {
		return -1.0;
	} else {
		return 1.0;
	}
}

void CatmullCurveEvaluator::evaluateCurve(const std::vector<Point>& ptvCtrlPts,
	std::vector<Point>& ptvEvaluatedCurvePts,
	const float& fAniLength,
	const bool& bWrap,
	const float default_val) const
{
	int iCtrlPtCount = ptvCtrlPts.size();
	ptvEvaluatedCurvePts.clear();

	if (iCtrlPtCount < 3) { // can't make a catmull curve with <4 points!
		ptvEvaluatedCurvePts.assign(ptvCtrlPts.begin(), ptvCtrlPts.end());
	}
	else {
		//temp vector so we can push back one more of the first/last points
		std::vector<Point> temp;
		//extra point for beginning
		temp.push_back(ptvCtrlPts[0]);
		//add all the points
		temp.insert(temp.end(), ptvCtrlPts.begin(), ptvCtrlPts.end());
		//extra point for end
		temp.push_back(ptvCtrlPts[iCtrlPtCount - 1]);
		for (int i = 0; i < temp.size() - 3; i++) {
			Point p0 = temp[i];
			Point p1 = temp[i + 1];
			Point p2 = temp[i + 2];
			Point p3 = temp[i + 3];

			Point w0 = p1;
			Point w1 = p1;
			w1.x += (p2.x - p0.x) / 6.0;
			w1.y += (p2.y - p0.y) / 6.0;
			Point w2 = p2;
			w2.x -= (p3.x - p1.x) / 6.0;
			w2.y -= (p3.y - p1.y) / 6.0;
			Point w3 = p2;

			// bound all x values in proper interval so no doubling back
			w1.x = max(w1.x, w0.x);
			w1.x = min(w1.x, w3.x);
			w2.x = max(w2.x, w1.x);
			w2.x = min(w2.x, w3.x);

			// fuck everything
			if (w3.x == w2.x) {
				w3.x += CATMULL_EPSILON;
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
		
	}

	float x = 0.0;
	float y1 = ptvCtrlPts[0].y;
	ptvEvaluatedCurvePts.push_back(Point(x, y1));

	float y2;
	x = fAniLength;
	y2 = ptvCtrlPts[iCtrlPtCount - 1].y;

	ptvEvaluatedCurvePts.push_back(Point(x, y2));
}

