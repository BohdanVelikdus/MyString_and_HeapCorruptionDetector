#pragma once
#include <stdexcept>
#include <iostream>

class myString {
	char* m_pBuffer;
	size_t m_Length;
public:
	myString();
	~myString();

	myString(const char* pstr);
	myString(char*&& pstr);
	myString(const myString& other);
	myString& operator= (const myString& other);

	void Allocate(const char* pstr);
	/*
	* @brief Returns the size of a buffer, with null terminator
	*/
	size_t GetLength() const {
		return m_Length;
	}

	/*
	* @brief Returns the size of a string, WITHOUT null terminator
	*/
	size_t GetSize() const {
		return m_Length - 1;
	}

	const char* GetString() const {
		return m_pBuffer;
	}

	myString operator +(const myString& other) const;
	myString& operator +=(const myString& other);
	char operator[](int index) const {
		if (index > m_Length)
			throw std::runtime_error("Invalid index");
		return m_pBuffer[index];
	}
	char& operator[](int index) {
		if (index > m_Length)
			throw std::runtime_error("Invalid index");
		return m_pBuffer[index];
	}

	friend std::ostream& operator<<(std::ostream& os,const myString& str) {
		os << "The length: " << str.GetLength() << " The string: " << str.GetString();
		return os;
	}

	inline void Insert(const char* pStr, size_t position);
	inline void Insert(const myString& other, size_t position);
	inline void Append(const char* pStr);
	inline void Append(const myString& other);
	inline void Assign(const char* pStr);
	
	int CompareTo(const myString& other) const;
	inline bool Empty() const;
	void Clear();

	void Erase(int position);
	void Erase(int position, int range);

	void Replace(int position, const char* excange);

	myString Substr(int start, int end) const;

	int Find(const char* substr) const;

	int FindFirstOf(const char* substr) const;
	int FindLastOf(const char* substr) const;
};

