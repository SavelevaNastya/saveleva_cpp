#pragma once
#include <utility>
#include <iostream> 
#include <bitset>
#include <unordered_map>

enum Nucleotide
{
	A, //0 00
	G, //1 01
	C, //2 10
	T //3 11
};

class RNK {
private:
	size_t size;
	//int* root;
	size_t* NuclArray;
	size_t capacity;
	size_t RealSize; 
public:
	/* NUCLREF*/ 
	class nuclref {
		size_t nucl_idx;
		//int* root; // BAD!!!
		RNK* rnk;
	public:
		nuclref(RNK* rnk, size_t nucl_idx);
		nuclref& operator=(Nucleotide nucl);
		nuclref& operator=(const nuclref nuclref);
		operator Nucleotide() const;
	};

	/*OPERATOR =*/
	RNK& operator=(const RNK& rnk);
	RNK& operator = (RNK&& rnk) noexcept;
	/*OPERATOR []*/ 
	nuclref operator[](size_t idx);
	const nuclref operator[](size_t number) const;

	/*OPERATOR +*/
	RNK operator+(const RNK & rnk) const;

	/*OPERATOR ==*/
	bool operator==(const RNK & r1) const; 

	/*OPERATOR !=*/
	bool operator!=(const RNK& r1) const;

	/*OPERATOR !*/
	void operator!();
	
	/*Constructors*/
	RNK();
	RNK(Nucleotide nucl, size_t amount);
	RNK(const RNK& rnk);
	RNK(RNK&& rnk);

	/*Methods*/
	size_t* FillNuclArray(size_t size);
	bool isComplementary(const RNK& rnk) const;
	std::pair<RNK, RNK> split(size_t index);
	void append(const Nucleotide& nucl);
	size_t length() const;
	size_t get_capacity() const;
	size_t get_real_size() const;
	size_t cardinality(Nucleotide nucl) const;
	std::unordered_map<Nucleotide, int, std::hash<int>> cardinality() const;
	void trim(size_t LastIndex);
	~RNK();
};

class DNK
{
private:
	size_t size;
	std::pair<RNK, RNK> dnk;
public:
	DNK(const RNK& first_rnk, const RNK& second_rnk);
};