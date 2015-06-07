//
// lineBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "lineBrush.h"

#include <iostream>

extern float frand();

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name)
{
}

void LineBrush::BrushBegin(const ImpBrush::Point source, const ImpBrush::Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();
	int width = pDoc->getWidth();

	glLineWidth((float)width);

	BrushMove(source, target);
}

void LineBrush::BrushMove(const ImpBrush::Point source, const ImpBrush::Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("LineBrush::BrushMove  document is NULL\n");
		return;
	}
	int size = pDoc->getSize();
	double angle = pDoc->calcAngle(source.x, source.y);
	int Ax, Ay, Bx, By;
	double deltaX, deltaY;
	deltaX = cos(angle) * 0.5 * size;
	deltaY = sin(angle) * 0.5 * size;
	Ax = target.x - deltaX;
	Bx = target.x + deltaX;
	Ay = target.y - deltaY;
	By = target.y + deltaY;
	glBegin(GL_LINES);
		SetColor(source);
		glVertex2i(Ax, Ay);
		glVertex2i(Bx, By);
	glEnd();
}

void LineBrush::BrushEnd(const ImpBrush::Point source, const ImpBrush::Point target)
{
	// do nothing so far
}

