// 
// impressionistDoc.cpp
//
// It basically maintain the Image for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//


#include <FL/fl_ask.H>

#include <algorithm>
#include <iostream>

#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "impBrush.h"

// Include individual brush headers here.
#include "pointBrush.h"
#include "lineBrush.h"
#include "triangleBrush.h"
#include "circleBrush.h"
#include "scatteredPointBrush.h"
#include "scatteredLineBrush.h"
#include "scatteredCircleBrush.h"


#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }

ImpressionistDoc::ImpressionistDoc() 
{
	// Set NULL image name as init. 
	m_imageName[0]	='\0';	

	m_nWidth		= -1;
	m_ucImage		= NULL;
	m_ucPainting	= NULL;
	m_ucPreviewBackup = NULL;


	// create one instance of each brush
	ImpBrush::c_nBrushCount	= NUM_BRUSH_TYPE;
	ImpBrush::c_pBrushes	= new ImpBrush* [ImpBrush::c_nBrushCount];

	ImpBrush::c_pBrushes[BRUSH_POINTS]	= new PointBrush( this, "Points" );

	// Note: You should implement these 5 brushes.  They are set the same (PointBrush) for now
	ImpBrush::c_pBrushes[BRUSH_LINES]				
		= new LineBrush( this, "Lines" );
	ImpBrush::c_pBrushes[BRUSH_CIRCLES]				
		= new CircleBrush( this, "Circles" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS]	
		= new ScatteredPointBrush( this, "Scattered Points" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]		
		= new ScatteredLineBrush(this, "Scattered Lines");
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES]	
		= new ScatteredCircleBrush(this, "Scattered Circles");
	ImpBrush::c_pBrushes[BRUSH_TRIANGLE] 
		= new TriangleBrush(this, "Triangle Brush");

	// make one of the brushes current
	m_pCurrentBrush	= ImpBrush::c_pBrushes[0];
}


//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui) 
{
	m_pUI	= ui;
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImpressionistDoc::getImageName() 
{
	return m_imageName;
}

//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setBrushType(int type)
{
	m_pCurrentBrush	= ImpBrush::c_pBrushes[type];
}

//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getSize()
{
	return m_pUI->getSize();
}

//---------------------------------------------------------
// Returns the width of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getWidth()
{
	return m_pUI->getWidth();
}

//---------------------------------------------------------
// Returns the angle of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getAngle()
{
	return m_pUI->getAngle();
}

//---------------------------------------------------------
// Interface method to get the correct angle based on setting
// Returns the angle in radians that should be used
//---------------------------------------------------------
double ImpressionistDoc::calcAngle(int x, int y) {
	const int ITERATIONS_BEFORE_RESET = 10;
	double angle;
	if (getUseSobelFilter()) 
	{
		angle = m_sobelAngleBuffer[(m_nWidth * y) + x];
	}
	else if (m_pUI->useBrushAngle())
	{
		angle = atan2(y - tempY, x - tempX);
		// By only sourcing a pixel every ITERATIONS_BEFORE_RESET,
		// Or when the distance exceeds something reasonable
		// we can easily smooth out mouse noise
		if (sourceResetCounter == 0 || sqrt(pow(x - tempX, 2) + pow(y - tempY,2)) > 6) 
		{
			tempY = y;
			tempX = x;
			sourceResetCounter = ITERATIONS_BEFORE_RESET;
		}
		else
		{
			sourceResetCounter--;
		}
		
	}
	else 
	{
		angle = (getAngle() * M_PI) / 180.0;
	}
	return angle;
}

//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------
double ImpressionistDoc::getAlpha()
{
	return m_pUI->getAlpha();
}

//---------------------------------------------------------
// Returns the boolean status of the sobel filter setting
//---------------------------------------------------------
bool ImpressionistDoc::getUseSobelFilter()
{
	return m_pUI->getSobel();
}

//---------------------------------------------------------
// Saves the starting point of a right click drag
//---------------------------------------------------------
void ImpressionistDoc::startRecordingRightClickDrag(int x, int y)
{
	tempX = x;
	tempY = y;
}

//---------------------------------------------------------
// Calculates the angle based on a right click drag
// and then sets the current angle to that angle
//---------------------------------------------------------
void ImpressionistDoc::finishRecordingRightClickDrag(int x, int y) 
{
	if (!(tempX == x && tempY == y)) {
		// x and y actually changed, meaning it was a drag
		double angle = atan2(y - tempY, x - tempX);
		int degrees = ((int)(angle / M_PI * 180.0) + 360) % 360;
		m_pUI->setAngle(degrees);
	}
	tempX = 0;
	tempY = 0;
}

//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(const char *iname) 
{
	// try to open the image to read
	unsigned char*	data;
	int				width, 
					height;

	if ( (data=load(iname, width, height))==NULL ) 
	{
		fl_alert("Can't load image file");
		return 0;
	}

	// reflect the fact of loading the new image
	m_nWidth		= width;
	m_nPaintWidth	= width;
	m_nHeight		= height;
	m_nPaintHeight	= height;

	// release old storage
	delete [] m_ucImage;
	delete [] m_ucPainting;
	delete [] m_ucPreviewBackup;

	m_ucImage		= data;

	// allocate space for draw view
	m_ucPainting		= new unsigned char [width*height*3];
	m_ucPreviewBackup	= new unsigned char [width*height*3];
	memset(m_ucPainting, 0, width*height*3);

	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), 
								m_pUI->m_mainWindow->y(), 
								width*2, 
								height+25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);	
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);	
	m_pUI->m_paintView->refresh();

	precomputeSobelAngleBuffer();

	return 1;
}

void ImpressionistDoc::swapContents()
{
	unsigned char* temp = m_ucImage;
	m_ucImage = m_ucPainting;
	m_ucPainting = temp;
	m_pUI->m_paintView->refresh();
	m_pUI->m_origView->refresh();
}

void ImpressionistDoc::precomputeSobelAngleBuffer() {
	// initialze field
	m_sobelAngleBuffer = new double[m_nWidth * m_nHeight];

	// initialze x, y sobel kernels
	const double ySobelKernel[9] = { -1, -2, -1, 0, 0, 0, 1, 2, 1};
	const double xSobelKernel[9] = { -1, 0, 1, -2, 0, 2, -1, 0, 1 };

	const int kernelMidpointX = 1;
	const int kernelMidpointY = 1;

	const int knlWidth = 3;
	const int knlHeight = 3;

	// loop through all pixels in the image
	for (int pixelRow = 0; pixelRow < m_nHeight; pixelRow++) {
		for (int pixelCol = 0; pixelCol < m_nWidth; pixelCol++) {
			// handle R, G, and B values
			for (int color = 0; color < 3; color++) {
				double angle;
				double computedSobelX = 0;
				double computedSobelY = 0;

				for (int kernelRow = 0; kernelRow < knlHeight; kernelRow++) {
					for (int kernelCol = 0; kernelCol < knlWidth; kernelCol++) {
						int filterPixelCol = pixelCol + kernelCol - kernelMidpointX;
						int filterPixelRow = pixelRow + (kernelRow - kernelMidpointY);
						// If kernel goes off the edge of the image, fill in missing values with nearby boundary values
						filterPixelCol = min(max(filterPixelCol, 0), m_nWidth - 1);
						filterPixelRow = min(max(filterPixelRow, 0), m_nHeight - 1);
						
						// add weighted pixel to computedSobel, which stores our filtered mean
						// do x derivative first
						double kernelVal = xSobelKernel[kernelRow * knlWidth + kernelCol];
						computedSobelX += kernelVal * m_ucImage[3 * (filterPixelRow * m_nWidth + filterPixelCol) + color];

						// do y derivative
						kernelVal = ySobelKernel[kernelRow * knlWidth + kernelCol];
						// add weighted pixel to computedSobel, which stores our filtered mean
						computedSobelY += kernelVal * m_ucImage[3 * (filterPixelRow * m_nWidth + filterPixelCol) + color];
					}
				}
				
				angle = atan2(computedSobelY, computedSobelX) + (M_PI / 2);
				m_sobelAngleBuffer[(pixelRow * m_nWidth) + pixelCol] = angle;
			}
		}
	}
}


//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(const char *iname, const char * type, int quality) 
{

	save(iname, m_ucPainting, m_nPaintWidth, m_nPaintHeight, type, quality);

	return 1;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas() 
{

	// Release old storage
	if ( m_ucPainting ) 
	{
		delete [] m_ucPainting;

		// allocate space for draw view
		m_ucPainting	= new unsigned char [m_nPaintWidth*m_nPaintHeight*3];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight*3);

		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}
	
	return 0;
}

// Apply the filter specified by filter_kernel to the 
// each pixel in the source buffer and place the resulting
// pixel in the destination buffer.  

// This is called from the UI when the
// "preview" or "apply" button is pressed in the filter dialog.



/*
 *	INPUT: 
 *		sourceBuffer:		the original image buffer, 
 *		srcBufferWidth:		the width of the image buffer
 *		srcBufferHeight:	the height of the image buffer
 *							the buffer is arranged such that 
 *							origImg[3*(row*srcBufferWidth+column)+0], 
 *							origImg[3*(row*srcBufferWidth+column)+1], 
 *							origImg[3*(row*srcBufferWidth+column)+2]
 *							are R, G, B values for pixel at (column, row).
 *		destBuffer:			the image buffer to put the resulting
 *							image in.  It is always the same size
 *							as the source buffer.
 *
 *      filterKernel:		the 2D filter kernel,
 *		knlWidth:			the width of the kernel
 *		knlHeight:			the height of the kernel
 *
 *		divisor, offset:	each pixel after filtering should be
 *							divided by divisor and then added by offset
 */
void ImpressionistDoc::applyFilter( const unsigned char* sourceBuffer,
		int srcBufferWidth, int srcBufferHeight,
		unsigned char* destBuffer,
		const double *filterKernel, 
		int knlWidth, int knlHeight, 
		double divisor, double offset )
{
	const int kernelMidpointX = knlHeight / 2;
	const int kernelMidpointY = knlWidth / 2;

	// loop through all pixels in the image
	for (int pixelRow = 0; pixelRow < srcBufferHeight; pixelRow++) {
		for (int pixelCol = 0; pixelCol < srcBufferWidth; pixelCol++) {
			// handle R, G, and B values
			for (int color = 0; color < 3; color++) {

				const int subpixelLocation = 3 * (pixelRow * srcBufferWidth + pixelCol) + color;
				double destSubpixel = 0;

				for (int kernelRow = 0; kernelRow < knlHeight; kernelRow++) {
					for (int kernelCol = 0; kernelCol < knlWidth; kernelCol++) {
						double kernelVal = filterKernel[kernelRow * knlWidth + kernelCol];
						if (kernelVal == 0) { continue; } // skip if it's zero bc who cares
						int filterPixelCol = pixelCol + kernelCol - kernelMidpointX;
						int filterPixelRow = pixelRow + (kernelRow - kernelMidpointY);
						// If kernel goes off the edge of the image, fill in missing values with nearby boundary values
						filterPixelCol = min(max(filterPixelCol, 0), srcBufferWidth - 1);
						filterPixelRow = min(max(filterPixelRow, 0), srcBufferHeight - 1);
						// add weighted pixel to destSubpixel, which stores our filtered mean
						destSubpixel += kernelVal * sourceBuffer[3 * (filterPixelRow * srcBufferWidth + filterPixelCol) + color];
					}
				}
				if (divisor == 0) divisor = 1;
				destSubpixel = destSubpixel / divisor + offset;
				// make sure no pixel value is out of range
				destSubpixel = max(min(255, destSubpixel), 0);
				destBuffer[subpixelLocation] = (unsigned char) destSubpixel;
			}
		}
	}
}


//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( int x, int y )
{
	if ( x < 0 ) 
		x = 0;
	else if ( x >= m_nWidth ) 
		x = m_nWidth-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= m_nHeight ) 
		y = m_nHeight-1;

	return (GLubyte*)(m_ucImage + 3 * (y*m_nWidth + x));
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( const ImpBrush::Point p )
{
	return GetOriginalPixel( p.x, p.y );
}



