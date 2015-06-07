//
// scatteredPointBrush.cpp
//
// The implementation of Scattered Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredPointBrush.h"

extern float frand();
extern int irand(int max);

ScatteredPointBrush::ScatteredPointBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void ScatteredPointBrush::BrushBegin(const ImpBrush::Point source, const ImpBrush::Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();
	glPointSize(1);
	BrushMove(source, target);
}

void ScatteredPointBrush::BrushMove(const ImpBrush::Point source, const ImpBrush::Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredPointBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	int minPoints = 2 * size;
	int maxPoints = 4 * size;
	int pointsCount = irand(maxPoints - minPoints) + minPoints;
	glBegin(GL_POINTS);
		for (int i = 0; i < pointsCount; i++) {
			int pointCenterX = target.x + irand(size) - size / 2;
			int pointCenterY = target.y + irand(size) - size / 2;
			ImpBrush::Point newSource = ImpBrush::Point(pointCenterX, pointCenterY);
			SetColor(newSource);
			glVertex2d(pointCenterX, pointCenterY);
		}
	glEnd();
}

void ScatteredPointBrush::BrushEnd(const ImpBrush::Point source, const ImpBrush::Point target)
{
	// do nothing so far
}

