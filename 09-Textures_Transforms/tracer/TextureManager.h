#ifndef TEXTUREMANAGER_H_
#define TEXTUREMANAGER_H_
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Color.h"

struct Texture {
	std::string filename;
	int rows = 0;
	int cols = 0;
	int numPaddingBytes = 0;
	int* arr = nullptr;

	Texture(std::string t_filename) {
		filename = t_filename;
		bmpToArr(t_filename);
	}
	~Texture() {
		delete[] arr;
	}
	Texture(const Texture&) = delete;
	Texture(Texture&& rhs) noexcept : rows{rhs.rows}, cols{rhs.cols}, arr{rhs.arr}, filename{std::move(rhs.filename)} {
		rhs.arr = nullptr;
	}
	Texture& operator=(const Texture&) = delete;
	Texture& operator=(Texture&& rhs) noexcept {
		rows = rhs.rows;
		cols = rhs.cols;
		arr = rhs.arr;
		filename = std::move(rhs.filename);
		rhs.arr = nullptr;
		return *this;
	}

	Color getColor(float u, float v) {
      int index = (int)(v * (float)rows) * cols + (int)((1.f - u) * (float)cols);
      unsigned int col = 0;
      if(index < rows * cols) {
        col = arr[index];
      }
      float r = (float)(col >> 24) / 255.f;
      float g = (float)((col & 0xFF0000) >> 16) / 255.f;
      float b = (float)((col & 0xFF00) >> 8) / 255.f;
      return Color(r, g, b);
	}

	void bmpToArr(std::string filename) {
		std::ifstream f(filename,
			std::ios::in | std::ios::binary);
		if (!f) return;

		for(int i = 0; i < 18; ++i) {
			char x;
			f.get(x);
		}
		char a, b, c, d;
		f.get(a);
		f.get(b);
		f.get(c);
		f.get(d);
		cols = ((unsigned)d << 24) + ((unsigned)c << 16) + ((unsigned)b << 8) + (unsigned)((unsigned char)a);
		numPaddingBytes = cols % 4;
		f.get(a);
		f.get(b);
		f.get(c);
		f.get(d);
		rows = ((unsigned)d << 24) + ((unsigned)c << 16) + ((unsigned)b << 8) + (unsigned)((unsigned char)a);
		for(int i = 0; i <28; ++i) {
			char x;
			f.get(x);
		}

		arr = new int[cols * rows];
		for(int i = 0; i < rows; ++i) {
			for(int j = 0; j < cols; ++j) {
				char c1, c2, c3;
				f.get(c1);
				f.get(c2);
				f.get(c3);
				int col = (((int)c3) << 24) + (((int)c2) << 16) + (((int)c1) << 8);
				arr[i*cols + j] = col;
			}
			char dontcare;
			for (int i = 0; i < numPaddingBytes; ++i) {
				f.get(dontcare);
			}
		}
		f.close();
	}
};

class TextureManager {
private:
	std::vector<Texture> textures;

	TextureManager() {
		textures.emplace_back("floor.bmp");
		textures.emplace_back("escher.bmp");
		textures.emplace_back("escher2.bmp");
		textures.emplace_back("fireman3.bmp");
		textures.emplace_back("grass.bmp");
		textures.emplace_back("ada-toon.bmp");
		textures.emplace_back("bricks.bmp");
		textures.emplace_back("matterhorn.bmp");
		textures.emplace_back("rocket.bmp");
		textures.emplace_back("corrugated_metal.bmp");
	}

public:
	static TextureManager& instance() {
		static TextureManager inst;
		return inst;
	}

	Texture* getTexture(std::string textureId) {
		for(auto& tex : textures) {
			if(tex.filename == textureId) {
				return &tex;
			}
		}
		return nullptr;
	}
};

#endif
