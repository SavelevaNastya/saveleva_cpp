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
	//int* root;
	size_t* NuclArray;
	size_t capacity;
public:
	/* NUCLREF*/ 
	class nuclref {
		size_t nucl_idx;
		//int* root; // BAD!!!
		RNK* rnk;
	public:
		nuclref(RNK* rnk, size_t nucl_idx);//done
		nuclref& operator=(Nucleotide nucl);
		nuclref& operator=(const nuclref nuclref);//done
		operator Nucleotide() const;
	};

	/*OPERATOR =*/
	RNK& operator=(const RNK&);

	/*OPERATOR []*/ //done
	nuclref operator[](size_t idx);

	/*OPERATOR +*/
	RNK operator+(const RNK& r1, const RNK& r2);

	/*OPERATOR ==*/
	bool operator==(const RNK & r1) const; //done

	/*OPERATOR !=*/
	bool operator!=(const RNK& r1) const;//done

	/*OPERATOR !*/
	void operator!();
	
	/*Constructors*/
	RNK();
	RNK(Nucleotide nucl, size_t size);
	RNK(const RNK& rnk);
	RNK(RNK&& rnk);

	/*Methods*/
	size_t* FillNuclArray(size_t size);
	bool isComplementary(const RNK& rnk);
	std::pair<RNK, RNK> split(size_t index);//done
	void append(const Nucleotide& nucl);

	~RNK();//done
};
//done
class DNK
{
private:
	std::pair<RNK, RNK> dnk;
public:
	DNK(RNK& first_rnk, RNK& second_rnk);
};

