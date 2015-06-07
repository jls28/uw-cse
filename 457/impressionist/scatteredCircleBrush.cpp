//
// scatteredCircleBrush.cpp
//
// The implementation of Scattered Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredCircleBrush.h"

#include <cmath>

#define CIRCLE_POINTS 360

extern float frand();
extern int irand(int max);

ScatteredCircleBrush::ScatteredCircleBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void ScatteredCircleBrush::BrushBegin(const ImpBrush::Point source, const ImpBrush::Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();


	BrushMove(source, target);
}

void ScatteredCircleBrush::BrushMove(const ImpBrush::Point source, const ImpBrush::Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredCircleBrush::BrushMove  document is NULL\n");
		return;
	}
	int size = pDoc->getSize();
	int radius = size / 2;
	int Ax, Ay;
	int circlesCount = irand(2) + 2; //random number between 2 and 4
	double maxRadians = 2 * M_PI;
	
	
	for (int i = 0; i < circlesCount; i++) {
		glBegin(GL_POLYGON);
		int circleCenterX = target.x + irand(size) - size / 2;
		int circleCenterY = target.y + irand(size) - size / 2;
		ImpBrush::Point newSource = ImpBrush::Point(circleCenterX, circleCenterY);
		SetColor(newSource);
		for (double radians = 0; radians < maxRadians; radians += maxRadians / CIRCLE_POINTS) {
			Ax = circleCenterX + radius * cos(radians);
			Ay = circleCenterY + radius * sin(radians);
			glVertex2i(Ax, Ay);
		}
		glEnd();
	}
}

void ScatteredCircleBrush::BrushEnd(const ImpBrush::Point source, const ImpBrush::Point target)
{
	// do nothing so far
}

