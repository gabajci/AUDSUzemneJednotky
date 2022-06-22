#pragma once

#include "../structure.h"
#include "../vector/vector.h"
#include "../utils.h"
#include <stdexcept>

namespace structures
{
	/// <summary> Pole. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v poli. </typepram>
	template<typename T> //sablona
	class Array : public Structure  
	{
	public:
		/// <summary> Konstruktor vytvori pole o velkosti size prvkov. </summary>
		/// <param name = "size"> Pocet prvkov vo vytvorenom poli. </param>
		Array(size_t size);

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> Pole, z ktoreho sa prevezmu vlastnosti. </param>
		Array(Array<T>& other);

		/// <summary> Destruktor. </summary>
		~Array();

		/// <summary> Vrati pocet prvkov v poli. </summary>
		/// <returns> Pocet prvkov v poli. </returns>
		size_t size() override;

		/// <summary> Priradenie struktury. </summary>
		/// <param name = "other"> Struktura, z ktorej ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa struktura nachadza. </returns>
		Structure& assign(Structure& other) override;

		/// <summary> Porovnanie struktur. </summary>
		/// <param name="other">Struktura, s ktorou sa ma tato struktura porovnat. </param>
		/// <returns>True ak su struktury zhodne typom aj obsahom. </returns>
		bool equals(Structure& other) override;

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do pola. </exception>
		T& operator[](int index);

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do pola. </exception>
		T& at(int index);

		/// <summary> Skopiruje length prvkov z pola src od pozicie srcStartIndex do pola dest od pozicie destStartIndex. </summary>
		/// <param name = "src"> Zdrojove pole. </param>
		/// <param name = "srcStartIndex"> Index prvku v poli src, od ktoreho sa zacne citat. </param>
		/// <param name = "dest"> Cielove pole. </param>
		/// <param name = "destStartIndex"> Index prvku v poli dest, od ktoreho sa zacne zapisovat. </param>
		/// <param name = "length"> Pocet prvkov, ktore budu skopirovane z pol src od pozicie srcStartIndex do pola dest od pozicie destStartIndex. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak zaciatocne alebo koncove indexy nepatria do prislusnych poli. </exception>
		static void copy(Array<T>& src, int srcStartIndex, Array<T>& dest, int destStartIndex, int length);

	private:
		/// <summary> Vektor s datami. </summary>
		Vector* vector_;
		/// <summary> Pocet prvkov v poli. </summary>
		size_t size_;

	private:
		/// <summary> Mapovacia funkcia, ktora prevedie index v poli na index vo vektore. </summary>
		/// <param name = "index"> Index v poli. </param>
		/// <returns> Index vo vektore. </returns>
		int mapFunction(int index) const;
	};

	template<typename T>                    
	Array<T>::Array(size_t size) :
		vector_(new Vector(size * sizeof(T))),   //novy vektor o velkosti size * velkost T 
		size_(size)   //ak chceme pole 5 int tak spravi 5* 4 = 20 BAJTOV vytvori
	{					//toto je v poriadku ak chceme primitivne typy - int,..
	}					//ale ak chceme pole objektov, tak s tym bude problem lebo objekt moze mat atributy
						//a vsetky vynulujeme pri tomto volani, museli by sme aj zavolat konstruktory objektov,..
						//pole objektov nemozeme urobit, ale pole pointrov na objekty
	template<typename T>
	Array<T>::Array(Array<T>& other) :  //kopirovaci konstruktor
		vector_(new Vector(*(other.vector_))),   //* je kvoli tomu, ze je to pointer aby sme z toho spravili objekt
		size_(other.size_)
	{
	}

	template<typename T>
	Array<T>::~Array()
	{
		delete this->vector_;
		this->vector_ = nullptr;
		this->size_ = 0;

	}

	template<typename T>
	Structure& Array<T>::assign(Structure& other)  //&je odkaz
	{
		if (this != &other) { //this je adresa mojho objektu
			Array<T>& otherArray = dynamic_cast<Array<T>&>(other);   //vytvorime len alternativu pre other
			// v pameti sa nic nove nevytvorilo
			if (this->size_ == otherArray.size_) {
				this->vector_->assign(*(otherArray.vector_)); //dereferencujeme na objekt	
																//lebo assign to vyzaduje
			}
			else {
				throw std::logic_error("Array<T>::assign: Sizes of arrays are different.");
			}
				
		}
		return *this; //dereferencujeme
	}

	template<typename T>
	inline bool Array<T>::equals(Structure& other)
	{
		Array<T>* otherArray = dynamic_cast<Array<T>*>(&other);  //other uz nemoze byt objekt ale adresa objektu
														//cize toto bude pointer
		//nova premenna v pameti a ukazuje na strukturu other
		//ak zlyha tak sa nic nestane
		if (otherArray == nullptr) {
			return false;
		}
		return this->size_ == otherArray->size_ && this->vector_->equals(*(otherArray->vector_));
	}

	template<typename T>
	size_t Array<T>::size()
	{
		return this->size_;
	}

	template<typename T>
	T& Array<T>::operator[](int index)
	{
		return this->at(index);
	}

	template<typename T>
	inline T& Array<T>::at(int index)
	{
		if (index< 0 || index >= this->size_) {
			throw std::out_of_range("Array<T>::at: invalid index.");
		}

		int vectorIndex = this->mapFunction(index);
		return *reinterpret_cast<T*>(this->vector_->getBytePointer(vectorIndex)); 
	}

	template<typename T>
	void Array<T>::copy(Array<T>& src, int srcStartIndex, Array<T>& dest, int destStartIndex, int length)
	{
		if (length > 0) {
			if (srcStartIndex < 0 || srcStartIndex >= src.size_) {
				throw std::out_of_range("Array<T>::copy: Invalid srcStartIndex.");
			}
			if (srcStartIndex + length - 1 < 0 || srcStartIndex + length - 1 >= src.size_) {
				throw std::out_of_range("Array<T>::copy: Invalid srcStartIndex + length - 1.");
			}
			if (destStartIndex < 0 || destStartIndex >= src.size_) {
				throw std::out_of_range("Array<T>::copy: Invalid destStartIndex.");
			}
			if (destStartIndex + length - 1 < 0 || destStartIndex + length - 1 >= src.size_) {
				throw std::out_of_range("Array<T>::copy: Invalid destStartIndex + length - 1.");
			}
			Vector::copy(*src.vector_, src.mapFunction(srcStartIndex),
				*dest.vector_, dest.mapFunction(destStartIndex), length*sizeof(T));
		}
	}

	template<typename T>
	inline int Array<T>::mapFunction(int index) const
	{
		return index * sizeof(T);
	}
}


