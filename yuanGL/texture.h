#pragma once

namespace yuanGL {

	class Texture {

	public:

		Texture(const char* file_path);
		~Texture();

		void bind(unsigned int slot = 0u) const;
		static void unbind();

		inline int width() const noexcept { return _width; }
		inline int height() const noexcept { return _height; }



	private:
		unsigned int _id{ 0 };
		const char* _file_path;
		unsigned char* _local_buffer{ nullptr };
		int _width{ 0 };
		int _height{ 0 };
		int _bpp{ 0 };
	};
}
