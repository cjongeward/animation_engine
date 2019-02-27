#ifndef ARRTOBMP_H_
#define ARRTOBMP_H_

#include <fstream>
#include <iostream>
#include <string>

namespace intarray2bmp
{

	//-------------------------------------------------------------------------- 
	// This little helper is to write little-endian values to file.
	//
	struct lwrite
	{
		unsigned long value;
		unsigned      size;
		lwrite(unsigned long value, unsigned size) :
			value(value), size(size)
		{ }
	};

	//--------------------------------------------------------------------------
	inline std::ostream& operator << (std::ostream& outs, const lwrite& v)
	{
		unsigned long value = v.value;
		for (unsigned cntr = 0; cntr < v.size; cntr++, value >>= 8)
			outs.put(static_cast <char> (value & 0xFF));
		return outs;
	}

	template <typename IntType>
	bool intarray2bmp(
		const std::string& filename,
		IntType*          intarray,
		unsigned           rows,
		unsigned           columns
	) {
		// Open the output BMP file
		std::ofstream f(filename.c_str(),
			std::ios::out | std::ios::trunc | std::ios::binary);
		if (!f) return false;

		// Some basic
		unsigned long headers_size = 14  // sizeof( BITMAPFILEHEADER )
			+ 40; // sizeof( BITMAPINFOHEADER )
		unsigned long padding_size = (4 - ((columns * 3) % 4)) % 4;
		unsigned long pixel_data_size = rows * ((columns * 3) + padding_size);

		// Write the BITMAPFILEHEADER
		f.put('B').put('M');                           // bfType
		f << lwrite(headers_size + pixel_data_size, 4);  // bfSize
		f << lwrite(0, 2);  // bfReserved1
		f << lwrite(0, 2);  // bfReserved2
		f << lwrite(headers_size, 4);  // bfOffBits

									   // Write the BITMAPINFOHEADER
		f << lwrite(40, 4);  // biSize
		f << lwrite(columns, 4);  // biWidth
		f << lwrite(rows, 4);  // biHeight
		f << lwrite(1, 2);  // biPlanes
		f << lwrite(24, 2);  // biBitCount
		f << lwrite(0, 4);  // biCompression=BI_RGB
		f << lwrite(pixel_data_size, 4);  // biSizeImage
		f << lwrite(0, 4);  // biXPelsPerMeter
		f << lwrite(0, 4);  // biYPelsPerMeter
		f << lwrite(0, 4);  // biClrUsed
		f << lwrite(0, 4);  // biClrImportant

							// Write the pixel data
		for (int row = rows - 1; row >= 0; row--)           // bottom-to-top
		{
			for (unsigned col = 0; col < columns; col++)  // left-to-right
			{
				const unsigned int pixel = intarray[row * columns + col];
				const auto red = static_cast<unsigned char>((pixel & 0xFF000000) >> 24);
				const auto green = static_cast<unsigned char>((pixel & 0x00FF0000) >> 16);
				const auto blue = static_cast<unsigned char>((pixel & 0x0000FF00) >> 8);
				f.put(static_cast <char> (blue))
					.put(static_cast <char> (green))
					.put(static_cast <char> (red));
			}

			if (padding_size) f << lwrite(0, padding_size);
		}

		// All done!
		return f.good();
	}

} // namespace intarray2bmp

#endif
