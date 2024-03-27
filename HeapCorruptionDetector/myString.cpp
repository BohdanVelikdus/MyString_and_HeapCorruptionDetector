#include "myString.hpp"
#include "HeapChecker.hpp"
#include "MemoryCheckpoint.hpp"


#ifdef _DEBUG
#define DEBUG_NEW  new(_NORMAL_BLOCK, __FILE__, __LINE__) 
#else
#define DEBUG_NEW new
#endif // DEBUG

myString::myString()
{
	HeapChecker;
	m_pBuffer = DEBUG_NEW char[1];
	m_Length = 1;
	*m_pBuffer = '\0';
}

myString::~myString()
{
	delete[] m_pBuffer;
}

myString::myString(const char* pstr)
{
	Allocate(pstr);
}

myString::myString(char*&& pstr)
{
	m_pBuffer = pstr;
	m_Length = strlen(pstr) + 1;
}

myString::myString(const myString& other)
{
	Allocate(other.GetString());
}

myString& myString::operator=(const myString& other)
{
	HEAPCHECK;
	if (this != &other)
		Allocate(other.GetString());
	return *this;
}

void myString::Allocate(const char* pstr)
{
	HEAPCHECK;
	m_Length = strlen(pstr)+1;
	m_pBuffer = DEBUG_NEW char[m_Length];
	strncpy_s(m_pBuffer, m_Length, pstr, m_Length);
}

myString myString::operator+(const myString& other) const
{
	myString temp(*this);
	temp += other;
	return temp;
}

myString& myString::operator+=(const myString& other)
{
	Append(other.GetString());
	return *this;
}

void myString::Insert(const myString& other, size_t position) {
	Insert(other.GetString(), position);
}

void myString::Insert(const char* pStr, size_t position)
{
	HEAPCHECK;
	if (position > m_Length)
		throw std::runtime_error("index out of bound");

	size_t totalLength = strlen(pStr) + m_Length;
	char* pTemp = DEBUG_NEW char[totalLength];

	if (position == 0) {
		strncpy_s(pTemp, totalLength, pStr, strlen(pStr)+1);
		strcat_s(pTemp, totalLength, m_pBuffer);
	}
	else if (position < m_Length) {
		strncpy_s(pTemp, totalLength, m_pBuffer, position);
		pTemp[position] = '\0';
		strcat_s(pTemp, totalLength, pStr);
		strcat_s(pTemp, totalLength, m_pBuffer + position);
	}
	else if (position == m_Length) {
		strncpy_s(pTemp, totalLength, m_pBuffer, strlen(m_pBuffer)+1);
		strcat_s(pTemp, totalLength, pStr);
	}
	delete[] m_pBuffer;
	m_pBuffer = nullptr;

	m_pBuffer = pTemp;
	m_Length = totalLength-1;
	
}

void myString::Append(const char* pStr)
{
	Insert(pStr, m_Length);
}

void myString::Append(const myString& other)
{
	Append(other.GetString());
}

void myString::Assign(const char* pStr)
{
	Allocate(pStr);
}

int myString::CompareTo(const myString& other) const
{
	if (other.m_Length != m_Length)
		return other.m_Length - m_Length;
	for (int i = 0; i < m_Length; i++) {
		if (m_pBuffer[i] != other.m_pBuffer[i])
			return m_pBuffer[i] - other.m_pBuffer[i];
	}
	return 0;
}

inline bool myString::Empty() const
{
	if(m_Length == 1)
		return true;
	return false;
}

void myString::Clear()
{
	HEAPCHECK;
	delete[] m_pBuffer;
	myString temp;
	*this = temp;
}

void myString::Erase(int position)
{
	HEAPCHECK;
	if (position <= 0 || position >= m_Length)
		throw std::runtime_error("The position to erase is out of bounce");
	
	int positionToErase = position - 1;
	char* pTemp = DEBUG_NEW char[m_Length-1];
	strncpy_s(pTemp, m_Length - 1, m_pBuffer, positionToErase); 
	pTemp[positionToErase] = '\0';
	strcat_s(pTemp, m_Length - 1, m_pBuffer + position);
	
	delete[] m_pBuffer;
	m_pBuffer = pTemp;
	m_Length--;

}

void myString::Erase(int position, int range)
{
	HEAPCHECK;
	if (position <= 0 || position + range >= m_Length)
		throw std::runtime_error("Current string is too small or index <= 0");

	int positionToErase = position - 1;
	char* pTemp = DEBUG_NEW char[m_Length - range];

	strncpy_s(pTemp, m_Length - range, m_pBuffer, positionToErase); 
	pTemp[positionToErase] = '\0';
	strcat_s(pTemp, m_Length - range, m_pBuffer + positionToErase + range);
	delete[] m_pBuffer;
	m_pBuffer = pTemp;
	m_Length -= range;

}

void myString::Replace(int position, const char* excange)
{
	HEAPCHECK;
	if (position <= 0 || position + strlen(excange) >= m_Length)
		throw std::runtime_error("Cant replace chars, string is too small or index <= 0");

	for (int i = position - 1; i < position - 1 + strlen(excange); ++i) {
		m_pBuffer[i] = excange[i];
	}

}


/*
 * @brief Returns substring, inclding ends
*/
myString myString::Substr(int start, int end) const
{
	HEAPCHECK;
	if (start > end || start <= 0 || end >= m_Length)
		throw std::runtime_error("Error with bound in substring");
	int length = end - start + 1 + 1; // + 1 - to iclude ends, +1 - for null terminator
	char* Temp = DEBUG_NEW char[length];
	strncpy_s(Temp, length, m_pBuffer + start - 1, end - start + 1);
	Temp[end - start + 1] = '\0';
	return myString(std::move(Temp));
	
}

/*
 * @brief Return the pos(started from 0), where we find a substring
 */

int myString::Find(const char* substr) const
{
	HEAPCHECK;
	int temp = strlen(substr);
	for (int i = 0; i <= temp; i++) {
		if (memcmp(m_pBuffer + i, substr, temp) == 0) {
			return i;
		}
	}
	return -1;
}

int myString::FindFirstOf(const char* substr) const
{
	return Find(substr);
}

int myString::FindLastOf(const char* substr) const
{
	HEAPCHECK;
	int find = -1;
	int temp = strlen(substr);
	for (int i = 0; i <= temp; i++) {
		if (memcmp(m_pBuffer + i, substr, temp) == 0) {
			find =  i;
		}
	}
	return find;
}
