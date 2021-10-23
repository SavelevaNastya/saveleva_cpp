#include "Header.h"
#include <utility>
#include <iostream> 


/* NUCLREF*/
RNK::nuclref& RNK::nuclref::operator=(Nucleotide nucl) {
	// Побитово?
};

RNK::nuclref::nuclref(RNK* rnk, size_t nucl_idx) {
	this->rnk = rnk;
	this->nucl_idx = nucl_idx;
}

RNK::nuclref::operator Nucleotide() const {
	// Преобразование в Nucl?
}

RNK::nuclref& RNK::nuclref::operator=(const nuclref nuclref) {
	rnk->operator[](nucl_idx).operator=((Nucleotide)nuclref);
	return *this;
}

/*OPERATOR []*/
RNK::nuclref RNK::operator[](size_t idx) {
	return nuclref(this, idx );
}

/*OPERATOR =*/
RNK& RNK::operator=(const RNK& rnk) {
	if (this == &rnk) {
		return *this;
	}
	this->capacity = rnk.capacity;
	this->size = rnk.size;
	NuclArray = FillNuclArray(size);
	return *this;
}

/*OPERATOR +*/
RNK RNK::operator+(const RNK& r1, const RNK& r2){
	
	RNK newRNK(r1);

	for (int i = 0; i < r2.size; i++) {
		newRNK.append(r2.NuclArray[i]);
	}

	return newRNK;
}

/*	OPERATOR ==	*/
bool RNK::operator==(const RNK& rnk) const {
	if (size != rnk.size) {
		return false;
	}

	for (int i = 0; i < size; i++) {
		if ((Nucleotide)rnk[i] != (Nucleotide)(*this)[i]) {
			return false;
		}
	}
	return true;
	
};

/*	OPERATOR !=	*/
bool RNK::operator!=(const RNK& rnk) const{
	if (size != rnk.size) {
		return true;
	}
	for (int i = 0; i < size; i++) {
		if ((Nucleotide)rnk[i] != (Nucleotide)(*this)[i]) {
			return true;
		}
	}
	return false;
	
};

/*	OPERATOR !	*/
void RNK::operator!() {
	for (int i = 0; i < size; i++) {
		(*this)[i] = !(*this)[i];
	}
}

/*Constructors*/
RNK::RNK():size(0), capacity(16) {
	NuclArray = FillNuclArray(1);
}
RNK::RNK(Nucleotide nucl, size_t size) {
	this->size = size;

	if (size <= 16) {
		capacity = 16;
	}else{
		capacity = ceil(1.0 * size / 16) * 16;
	}

	NuclArray = FillNuclArray(size);
}
RNK::RNK(const RNK& rnk) {
	this->capacity = rnk.capacity;
	this->size = rnk.size;
	NuclArray = FillNuclArray(size);
}
RNK::RNK(RNK&& rnk) {
	this->capacity = rnk.capacity;
	this->size = rnk.size;
	this->NuclArray = FillNuclArray(size);
}

/*Methods*/

size_t * RNK::FillNuclArray(size_t size) {
	size_t realSize = ceil(size / ((sizeof(size_t) * 8) / 2));

	size_t* NewNuclArray = new size_t[realSize];

	for (int i = 0; i < realSize; i++) {
		NewNuclArray[i] = 0;
	}
	return NewNuclArray;
}
bool RNK::isComplementary(const RNK& rnk) {
	if (size != rnk.size) {
		return false;
	}else{
		for (int i = 0; i < size; i++) {
			if ( (*this)[i] != (Nucleotide)rnk[i] ) {
				return false;
			}
		}
	}
	return true;
};

void RNK::append(const Nucleotide& nucl) {
	// Сделать новый NuclArray с новой capacity
	// Запихать в него старый
	// Побитово прибавить новые элементы
	// Это если он полностью заполнен, т.е. if size == capacity
	// Если нет, то вычислить количество пустых элементов и потом уже добавлять новые элементы
	// ???
};

std::pair<RNK, RNK> RNK::split(size_t index) {
	RNK r1, r2;

	for (int i = 0; i < this->size; i++) {
		if (i <= index) {
			r1.append((*this)[i]);
		}
		else {
			r2.append((*this)[i]);
		}
	}

	std::pair<RNK, RNK> two_rnk;
	two_rnk = std::make_pair(r1, r2);
	return two_rnk;

};

DNK::DNK(RNK& first_rnk,RNK& second_rnk) {
	if (first_rnk.isComplementary(second_rnk)) {
		dnk = std::make_pair(first_rnk, second_rnk);
	}
}

RNK::~RNK() {
	delete[] NuclArray;
}