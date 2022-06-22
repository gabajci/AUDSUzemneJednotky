#include "vector.h"
#include "../utils.h"
#include <cstdlib>
#include <cstring>

namespace structures
{
	Vector::Vector(size_t size) :
		memory_(std::calloc(size, 1)), // pamat //calloc vsetko aj vynuluje
		size_(size) //kolko bajtov ideme zaberat
	{	
	}

	Vector::Vector(Vector& other) :
		Vector(other.size_)
	{
		std::memcpy(this->memory_, other.memory_, this->size_);
	}

	Vector::~Vector()
	{ //ak by sme vytvarali cez new, mazeme cez delete

		free(this->memory_); // ak sme alokovali pamet, tak uvolnime
		this->memory_ = nullptr;
		this->size_ = 0;
	}

	size_t Vector::size()
	{
		return this->size_;
	}
		//posielanie & referencie je rychlejsie, nevytvara samotny obejkt znova aby sa poslal
		// a zaroven ho modifikujeme
	Structure& Vector::assign(Structure& other) // pri & robim priamo s objektom
	{ //obsah jedneho vektora priradime do druheho vektora
		//prv zistime, ci neprirazdujem do sameho seba
		if (this != &other) { // this je adresa uz sama o sebe // &pred nazvom odkazujeme na uz existujucu premennu
			Vector& otherVector = dynamic_cast<Vector&>(other); // pretypovanie na predka Vector
				// dalsi otherVector, nezabera v pameti nic, len odkaz
			this->memory_ = std::realloc(this->memory_,otherVector.size_); //obsadime velkost pamata ako ma other.size a priradime do mojej memory 
			std::memcpy(this->memory_, otherVector.memory_, this->size_);//skopirujeme obsah pamate do nasej
			this->size_ = otherVector.size_;

		}
		return *this;  //aby som dostal objekt, musim zreferencovat
	}

	bool Vector::equals(Structure& other)
	{
		Vector* otherVector = dynamic_cast<Vector*>(&other); // pretypovanie na predka Vector
		//ak nieje vector a padne chyba pri dynamic caste tak sa nemozu rovnat
		//ak to robim cez smerniky tak nepadne, ale hodi nullptr
		if (otherVector == nullptr) {
			return false;
		}

		//ak maju rovnaku velkost a zaroven rovnaky obsah pamate
		return this->size_ == otherVector->size_ &&
			memcmp(this->memory_, otherVector->memory_, this->size_) == 0;
	}

	byte& Vector::operator[](int index)
	{
		return at(index);
	}

	byte& Vector::at(int index) //vrati data na indexe
	{
		return *this->getBytePointer(index);
	}

	void Vector::copy(Vector& src, int srcStartIndex, Vector& dest, int destStartIndex, int length)
	{
		if (length > 0) {
			if (srcStartIndex < 0 || srcStartIndex >= src.size_) {
				throw std::out_of_range("Vector::copy: Invalid srcStartIndex.");
			}
			if (srcStartIndex + length - 1 < 0 || srcStartIndex + length - 1 >= src.size_) {
				throw std::out_of_range("Vector::copy: Invalid srcStartIndex + length - 1.");
			}
			if (destStartIndex < 0 || destStartIndex >= src.size_) {
				throw std::out_of_range("Vector::copy: Invalid destStartIndex.");
			}
			if (destStartIndex + length - 1 < 0 || destStartIndex + length - 1 >= src.size_) {
				throw std::out_of_range("Vector::copy: Invalid destStartIndex + length - 1.");
			}
			if (&src == &dest && 
				( (srcStartIndex >= destStartIndex && srcStartIndex < destStartIndex + length) ||
				(destStartIndex >= srcStartIndex && destStartIndex < srcStartIndex + length) ) ) {
				//ak priradzujem do sameho seba a prekryvaju sa tak memmove
				std::memmove(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
			}
			else {
				std::memcpy(dest.getBytePointer(destStartIndex), src.getBytePointer(srcStartIndex), length);
			}
		}
	}

	byte* Vector::getBytePointer(int index)
	{
		//pretypujem na byte aby som skakal po bytoch, 
		//lebo ak to mam int tak budem skakat po 4roch,..
		if (index < 0 || index >= this->size_) {
			throw std::out_of_range("Vector::getBytePointe: invalid index");
		}
		return reinterpret_cast<byte*>(this->memory_) + index;
	}
}