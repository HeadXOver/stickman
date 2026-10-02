#pragma once

#include <vector>

namespace yuanGL {

	class VertexBuffer;
	class VertexAttribution;
	class ElementBuffer;

	class VertexArray {

	public:

		VertexArray();
		~VertexArray();

		void attach_buffer(const VertexBuffer* vb, const VertexAttribution& attribution);
		void attach_buffer(const VertexBuffer* vb, const std::vector<int>& attribution);
		void attach_element_buffer(const ElementBuffer* eb);

		void bind() const;
		void unbind() const;

	private:

		unsigned int _id{ 0u };
	};

}
