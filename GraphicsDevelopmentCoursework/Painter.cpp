#include "Painter.hpp"

Painter::Painter() { }
Painter::Painter(Painter && other) noexcept : data(other.data) { other.data.reset(); }
Painter::~Painter() noexcept {}
Painter & Painter::operator=(const Painter & other) {
	Painter tmp(other);			// re-use copy-constructor  
	*this = std::move(tmp);		// re-use move-assignment  
	return *this;
}
Painter & Painter::operator=(Painter && other) noexcept {
	// take precautions against `foo = std::move(foo)`
	if(this == &other)
		return *this;
	data = other.data;
	other.data.reset();
	return *this;
}
std::shared_ptr<std::vector<points>> Painter::getDataPointer() const { return data; }