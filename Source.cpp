#include "Header.h"


/* NUCLREF*/
RNK::nuclref& RNK::nuclref::operator=(Nucleotide nucl) {
	size_t step = sizeof(size_t) * 8 - (2 * nucl_idx) % (sizeof(size_t) * 8) - 1; 
	size_t Size_tPerNucl = (sizeof(size_t) * 8) / 2;
	std::bitset<sizeof(size_t) * 8> bytes(nucl); 
	if (bytes[0] == 0) {
		rnk->NuclArray[nucl_idx / Size_tPerNucl] &= ~(1 << (step - 1));
	}
	else {
		rnk->NuclArray[nucl_idx / Size_tPerNucl] |= (1 << (step - 1));
	}
	if (bytes[1] == 0) {
		rnk->NuclArray[nucl_idx / Size_tPerNucl] &= ~(1 << step);
	}
	else {
		rnk->NuclArray[nucl_idx / Size_tPerNucl] |= (1 << step);
	}

	return *this;

};

RNK::nuclref::nuclref(RNK* rnk, size_t nucl_idx) {
	this->rnk = rnk;
	this->nucl_idx = nucl_idx;
}

RNK::nuclref::operator Nucleotide() const {
	size_t nucl;
	size_t step = sizeof(size_t) * 8 - (2 * nucl_idx) % (sizeof(size_t) * 8) - 2; 
	size_t Size_tPerNucl = (sizeof(size_t) * 8) / 2; 
	nucl = (rnk->NuclArray[nucl_idx/ Size_tPerNucl] >> step) & 3; 
	Nucleotide current_nucl = static_cast<Nucleotide>(nucl);
	return current_nucl;
}

RNK::nuclref& RNK::nuclref::operator=(const nuclref nuclref) {
	rnk->operator[](nucl_idx).operator=((Nucleotide)nuclref);
	return *this;
}

/*OPERATOR []*/
RNK::nuclref RNK::operator[](size_t idx){
	nuclref ref(this, idx);
	return ref;
}

const RNK::nuclref RNK::operator[](size_t number) const {
	nuclref ref(const_cast<RNK*>(this), number);
	return ref;
}

/*OPERATOR =*/
RNK& RNK::operator=(const RNK& rnk) {
	if (this == &rnk) {
		return *this;
	}
	if (rnk.NuclArray != nullptr) {
		this->RealSize = rnk.RealSize;
		this->capacity = rnk.capacity;
		this->size = rnk.size;
		NuclArray = FillNuclArray(size);
		memcpy(NuclArray, rnk.NuclArray, RealSize * sizeof(size_t));
	}
	else {
		NuclArray = nullptr;
	}
	
	return *this;
}

/*OPERATOR =*/
RNK& RNK::operator=(RNK&& rnk) noexcept {
	if (this == &rnk) {
		return *this;
	}
	this->capacity = rnk.capacity;
	this->size = rnk.size;
	this->RealSize = rnk.RealSize;
	this->NuclArray = rnk.NuclArray;
	rnk.NuclArray = nullptr;
	return *this;
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

/*OPERATOR +*/
RNK RNK::operator+(const RNK& rnk) const {
	Nucleotide x, y;

	x = rnk[0];
	y = this->operator[](this->size - 1);

	if ((x ^ 3) == y) {
		RNK newRNK(*this);
		for (int i = 0; i < rnk.size; i++) {
			newRNK.append(rnk[i]);
		}
		return newRNK;
	}

	return RNK();
}

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

/*	OPERATOR ! */
void RNK::operator!() {
	for (int i = 0; i < this->size; i++) {
		(*this)[i] = static_cast<Nucleotide>((*this)[i] ^ 3);
	}
}

/*Constructors*/
RNK::RNK():size(0), capacity(16) {
	NuclArray = FillNuclArray(1);
}
RNK::RNK(Nucleotide nucl, size_t amount): size(amount) {

	NuclArray = FillNuclArray(size);
	size_t step = 0;
	size_t Size_tPerNucl = (sizeof(size_t) * 8) / 2;

	if (size <= 16) {
		capacity = 16;
	}else{
		capacity = ceil(1.0 * size / 16) * 16;
	}

	for (size_t i = 0; i < size; i++) {
		if (step == Size_tPerNucl) {
			step = 0;
		}
		NuclArray[i / Size_tPerNucl] = NuclArray[i / Size_tPerNucl] | (nucl << 2 * (Size_tPerNucl - step - 1));
		step++;
	}
	
}
RNK::RNK(const RNK& rnk) {
	if (rnk.NuclArray != nullptr) {
		this->RealSize = rnk.RealSize;
		this->capacity = rnk.capacity;
		this->size = rnk.size;
		NuclArray = FillNuclArray(size);
		memcpy(NuclArray, rnk.NuclArray, RealSize * sizeof(size_t));
	}
	else {
		NuclArray = nullptr;
	}
}
RNK::RNK(RNK&& rnk) {
	this->capacity = rnk.capacity;
	this->size = rnk.size;
	this->RealSize = rnk.RealSize;
	this->NuclArray = rnk.NuclArray;
	rnk.NuclArray = nullptr;
}

/*Methods*/

size_t * RNK::FillNuclArray(size_t size) {
	size_t Size_tPerNucl = (sizeof(size_t) * 8) / 2;
	RealSize = ceil(size / (1.0 * Size_tPerNucl));

	size_t* NewNuclArray = new size_t[RealSize];

	for (size_t i = 0; i < RealSize; i++) {
		NewNuclArray[i] = 0;
	}
	return NewNuclArray;
}

bool RNK::isComplementary(const RNK& rnk) const {
	if (this->size != rnk.size) {
		return false;
	}else{
		for (int i = 0; i < this->size; i++) {
			if ((*this)[i] != static_cast<Nucleotide>(rnk[i] ^ 3)) {
				return false;
			}
		}
	}
	return true;
};

void RNK::append(const Nucleotide& nucl) {

	size_t Size_tPerNucl = (sizeof(size_t) * 8) / 2;
	if (size == capacity) {
		capacity *= 2;
		size_t* tmp = FillNuclArray(capacity);
		memcpy(tmp, NuclArray, size * 2 / 8);
		delete[] NuclArray;
		NuclArray = tmp;
		tmp = nullptr;
		size_t ContainerIndex = size / Size_tPerNucl;
		NuclArray[ContainerIndex] = NuclArray[ContainerIndex] | (nucl << sizeof(size_t) * 8 - 2);
		size++;
	}
	else {
		size_t AmountOfNotEmptyCells = 2 * (size % Size_tPerNucl);
		size_t ContainerIndex = size / Size_tPerNucl;
		NuclArray[ContainerIndex] = NuclArray[ContainerIndex] | (nucl << sizeof(size_t) * 8 - AmountOfNotEmptyCells - 2);
		size++;
	}
};

std::pair<RNK, RNK> RNK::split(size_t index) {
	RNK r1, r2;

	for (int i = 0; i < size; i++) {
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

DNK::DNK(const RNK& first_rnk, const RNK& second_rnk) {
	if (first_rnk.isComplementary(second_rnk)) {
		dnk = std::make_pair(first_rnk, second_rnk);
	}
}

RNK::~RNK() {
	delete[] NuclArray;
}

size_t RNK::length() const {
	return this->size;
}

size_t RNK::get_capacity() const {
	return this->capacity;
}

size_t RNK::get_real_size() const {
	return this->RealSize * sizeof(size_t);
}

size_t RNK::cardinality(Nucleotide nucl) const {
	size_t nucl_counter = 0, ContainerIndex = 0, nucleotid, step;
	size_t Size_tPerNucl = (sizeof(size_t) * 8) / 2;
	for (int i = 0; i < size; i++) {
		nucleotid = this->operator[](i);
		if (nucl == static_cast<Nucleotide>(nucleotid)) {
			nucl_counter++;
		}
	}
	return nucl_counter;
}

void RNK::trim(size_t LastIndex) {
	if (LastIndex >= 0 && LastIndex < size) {
		size = LastIndex;
		capacity = LastIndex;
		size_t* tmp = FillNuclArray(size);
		memcpy(tmp, this->NuclArray, this->RealSize * sizeof(size_t));
		delete[] this->NuclArray;
		this->NuclArray = tmp;
		tmp = nullptr;
	}
};

std::unordered_map<Nucleotide, int, std::hash<int>> RNK::cardinality() const {
	std::unordered_map<Nucleotide, int, std::hash<int>> map;
	for (int i = 0; i < size; i++) {
		map[(*this)[i]]++;
	}
	return map;
};

