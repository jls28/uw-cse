// 
// impressionistDoc.h
//
// header file for Doc 
//

#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h

#include "impressionist.h"
#include "imageio.h"

class ImpressionistUI;

class ImpressionistDoc 
{
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use

	int		loadImage(const char *iname);			// called by the UI to load image
	int		saveImage(const char *iname, const char * type, int quality);// called by the UI to save image


	int     clearCanvas();                  // called by the UI to clear the drawing canvas

	void applyFilter( const unsigned char* sourceBuffer, //The filter kernel
		int srcBufferWidth, int srcBufferHeight,
		unsigned char* destBuffer,
		const double *filterKernel, 
		int knlWidth, int knlHeight, 
		double divisor, double offset );

	void precomputeSobelAngleBuffer();

	void	setBrushType(int type);			// called by the UI to set the brushType
	int		getSize();						// get the UI size
	void	setSize(int size);				// set the UI size
	int		getWidth();						// get the UI width
	void	setWidth(int width);			// set the UI width
	int		getAngle();						// get the UI angle
	void	setAngle(int angle);			// set the UI angle
	double	getAlpha();						// get the UI size
	void	setAlpha(double alpha);			// set the UI size
	bool	getUseSobelFilter();			// Returns true if the sobel filter should be used
	char*	getImageName();					// get the current image name
	double	calcAngle(int x, int y);	// calculates the angle to be used
	void	startRecordingRightClickDrag(int x, int y);
	void	finishRecordingRightClickDrag(int x, int y);
	void	swapContents();					// swaps the contents of the original and paint views
	

// Attributes
public:
	// Dimensions of original window.
	int				m_nWidth, 
					m_nHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth, 
					m_nPaintHeight;	
	// Images for original image and painting.
	unsigned char*	m_ucImage;
	unsigned char*	m_ucPainting;

	// Used by the filtering code so that we can
	// preview filters before applying.
	unsigned char*	m_ucPreviewBackup;

	// Precompute buffer for sobel filter
	// Used by brush to angle along gradient
	double* m_sobelAngleBuffer;

	// The current active brush.
	ImpBrush*			m_pCurrentBrush;	
	// Size of the brush.
	int m_nSize;		

	// X and Y values of the start of the right click drag
	int tempX = 0; 
	int tempY = 0;
	int sourceResetCounter = 0;

	ImpressionistUI*	m_pUI;

// Operations
public:
	// Get the color of the original picture at the specified coord
	GLubyte* GetOriginalPixel( int x, int y );   
	// Get the color of the original picture at the specified point	
	GLubyte* GetOriginalPixel( const ImpBrush::Point p );



private:
	char			m_imageName[256];

};

extern void MessageBox(char *message);

#endif
