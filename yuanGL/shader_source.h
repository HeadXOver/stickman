#pragma once

namespace yuanGL {

	class ShaderSource {

	public:
		ShaderSource(const char* filePath);
		~ShaderSource() {}

		std::string get_vertex_source() const { return _vertex_source; }
		std::string get_fragment_source() const { return _fragment_source; }

	private:
		std::string _vertex_source;
		std::string _fragment_source;
	};

}
