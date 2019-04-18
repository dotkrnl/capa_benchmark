#ifndef _RGB_2_YUV_
#define _RGB_2_YUV_

void rgb2yuv(int r, int g, int b, float& y, float& u, float& v)
{
	float _y = (0.299*r + 0.587*g + 0.114*b)/255.0;
	float _u = (-0.147*r - 0.289*g + 0.436*b)/255.0;
	float _v = (0.615*r - 0.515*g - 0.100*b)/255.0;
	
	y = _y;
	u = _u;
	v = _v;
}

#endif