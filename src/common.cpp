/*
* Copyright (c) 2015 Accenture - All rights reserved
*
* Unauthorized copying of this file, via any medium is strictly prohibited.
* Proprietary and confidential.
*/

#include "common.h"
#include <tiffio.h>
#include <tiff.h>

vector<string> &split(const string &s, char delim, vector<string> &elems)
{
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

void WriteTiff(const string& filename, const Mat& m)
{
    BOOST_ASSERT(m.type() == CV_32FC1);

    TIFF* t = TIFFOpen(filename.c_str(), "w");
    TIFFSetField(t, TIFFTAG_IMAGEWIDTH, m.cols);
    TIFFSetField(t, TIFFTAG_IMAGELENGTH, m.rows);
    TIFFSetField(t, TIFFTAG_SAMPLESPERPIXEL, 1);
    TIFFSetField(t, TIFFTAG_BITSPERSAMPLE, 32);
    TIFFSetField(t, TIFFTAG_ORIENTATION, ORIENTATION_TOPLEFT);
    TIFFSetField(t, TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
    TIFFSetField(t, TIFFTAG_SAMPLEFORMAT, SAMPLEFORMAT_IEEEFP);
    TIFFSetField(t, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_MINISBLACK);
    TIFFSetField(t, TIFFTAG_COMPRESSION, COMPRESSION_LZW);

    tsize_t linebytes = sizeof(float) * m.cols;
    unsigned char *buf = NULL;
    if (TIFFScanlineSize(t) < linebytes) {
        buf = (unsigned char *)_TIFFmalloc(linebytes);
    } else {
        buf = (unsigned char *)_TIFFmalloc(TIFFScanlineSize(t));
    }

    TIFFSetField(t, TIFFTAG_ROWSPERSTRIP, 32);

    //Now writing image to the file one strip at a time
	int r = 0;
	for (int row = m.rows - 1; row >= 0; --row) {
        const float *p = m.ptr<float>(m.rows - row - 1);
        memcpy(buf, p, linebytes);
        if (TIFFWriteScanline(t, buf, r++, 0) < 0)
            break;
    }

    TIFFClose(t);
    if (buf) {
        _TIFFfree(buf);
    }
}
