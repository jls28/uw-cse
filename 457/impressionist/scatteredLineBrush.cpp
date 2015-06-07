//
// scatteredLineBrush.cpp
//
// The implementation of Scattered Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "scatteredLineBrush.h"
#include <cmath>

extern float frand();
extern int irand(int max);

ScatteredLineBrush::ScatteredLineBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void ScatteredLineBrush::BrushBegin(const ImpBrush::Point source, const ImpBrush::Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();

	int width = pDoc->getWidth();

	glLineWidth((float)width);

	BrushMove(source, target);
}

void ScatteredLineBrush::BrushMove(const ImpBrush::Point source, const ImpBrush::Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredLineBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	int line_count = irand(2) + 2; // random number between 2 and 4
	double angle;

	int Ax, Ay, Bx, By;
	double deltaX, deltaY;
	
	glBegin(GL_LINES);
		for (int i = 0; i < line_count; i++) {
			int lineCenterX = target.x + irand(size) - size / 2;
			int lineCenterY = target.y + irand(size) - size / 2;
			angle = pDoc->calcAngle(lineCenterX, lineCenterY);
			deltaX = cos(angle) * 0.5 * size;
			deltaY = sin(angle) * 0.5 * size;
			Ax = lineCenterX - deltaX;
			Bx = lineCenterX + deltaX;
			Ay = lineCenterY - deltaY;
			By = lineCenterY + deltaY;
			ImpBrush::Point newSource = ImpBrush::Point(lineCenterX, lineCenterY);
			SetColor(newSource);
			glVertex2i(Ax, Ay);
			glVertex2i(Bx, By);
		}
		
	glEnd();
}

void ScatteredLineBrush::BrushEnd(const ImpBrush::Point source, const ImpBrush::Point target)
{
	// do nothing so far
}

