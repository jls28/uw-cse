//
// circleBrush.cpp
//
// The implementation of Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "circleBrush.h"

#include <cmath>

#define CIRCLE_POINTS 360

extern float frand();

CircleBrush::CircleBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void CircleBrush::BrushBegin(const ImpBrush::Point source, const ImpBrush::Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();



	glPointSize((float)size);

	BrushMove(source, target);
}

void CircleBrush::BrushMove(const ImpBrush::Point source, const ImpBrush::Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
		return;
	}
	int radius = pDoc->getSize() / 2;
	int Ax, Ay;
	double maxRadians = 2 * M_PI;
	glBegin(GL_POLYGON);
		SetColor(source);
		
		for (double radians = 0; radians < maxRadians; radians += maxRadians / CIRCLE_POINTS) {
			Ax = target.x + radius * cos(radians);
			Ay = target.y + radius * sin(radians);
			glVertex2i(Ax, Ay);
		}
	glEnd();
}

void CircleBrush::BrushEnd(const ImpBrush::Point source, const ImpBrush::Point target)
{
	// do nothing so far
}

