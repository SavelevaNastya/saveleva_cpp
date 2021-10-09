#include "Header.h"
#include <utility>

/*OPERATOR []*/
nuclref RNK::operator[](size_t idx) {
	return nuclref(idx, this);
};

/*OPERATOR +*/
RNK RNK::operator+(RNK& r1, RNK& r2){

};

/*	OPERATOR ==	*/
bool RNK::operator==(const RNK& r1, const RNK& r2){

	
};

/*	OPERATOR !=	*/
bool RNK::operator!=(RNK& r1, RNK& r2){

	
};

/*	OPERATOR !	*/
RNK RNK::operator!(RNK& r1) {
	
};

RNK::RNK(const& RNK) {};

bool RNK::isComplementary(RNK& rnk) {};
void RNK::split(size_t index) {};

RNK::~RNK() {
	delete[] this;
}

DNK::DNK(RNK& first_rnk,RNK& second_rnk) {
	if (first_rnk.isComplementary(second_rnk)) {
		dnk = std::make_pair(first_rnk, second_rnk);
	}
}

nuclref::nuclref(RNK* rnk, size_t num) {
	this->This = rnk;
	this->nucl_idx = num;
}