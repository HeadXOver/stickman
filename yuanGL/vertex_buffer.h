#pragma once

namespace yuanGL {

	enum class DrawMode;

	class VertexBuffer {

	public:

		VertexBuffer(float* data, unsigned int size);
		VertexBuffer(float* date, unsigned int size, DrawMode mode);
		~VertexBuffer();

		void bind() const;
		void unbind() const;

	private:
		unsigned int _id{ 0u };
	};

}
