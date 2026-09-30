#pragma once

#include <initializer_list>
#include <vector>

namespace yuanGL {

    struct Vertex {
        Vertex(unsigned int degree, unsigned int split, unsigned int skew) :
            _degree(degree), _split(split), _skew(skew) {}
        Vertex(unsigned int degree, unsigned int split) :
            _degree(degree), _split(split), _skew(0) {
        }
        unsigned int _degree;
        unsigned int _split;
        unsigned int _skew;
    };

    class VertexAttribution {

    public:

        VertexAttribution(std::initializer_list<Vertex> init_list);
        ~VertexAttribution();

        void enable() const;

    private:
        std::vector<Vertex> _attributions;
    };

}
