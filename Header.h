#pragma once

enum Nucleotide
{
	A, //0
	G, //1
	C, //2
	T //3
};

class RNK {
private:
	size_t size;
	int* root;
	friend class nuclref;
public:
	/*OPERATOR =*/
	
	nuclref operator[] (size_t idx);

	/*OPERATOR +*/
	RNK operator+(RNK& r1, RNK& r2);

	/*OPERATOR ==*/
	bool operator==(const RNK & r1, const RNK & r2);

	/*OPERATOR !=*/
	bool operator!=(RNK& r1, RNK& r2);

	/*OPERATOR !*/
	RNK operator!(RNK& r1);

	RNK(const& RNK);
	bool isComplementary(RNK&);
	void split(size_t index);
	~RNK();
};

class DNK
{
private:
	std::pair<RNK, RNK> dnk;
public:
	DNK(RNK& first_rnk, RNK& second_rnk);
};

class nuclref{
private:
	size_t nucl_idx;
	//int* root;
	RNK* This;
public:
	nuclref(RNK* rnk, size_t num);
};