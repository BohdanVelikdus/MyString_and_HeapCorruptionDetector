#include "HeapChecker.hpp"
#include <crtdbg.h>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <fstream>


HeapChecker::HeapChecker(const char* pFun, const char* pFile) : m_pFunction(pFun), m_pFile(pFile)
{
	if (!m_Initialized) {
		throw std::runtime_error("HeapChecker need to be initialized first!");
	}
}

HeapChecker::~HeapChecker()
{
	
	if (_CrtCheckMemory() == 0) {
		std::ostringstream output;
		output << "### HEAP CORRUPTION DETECTED ###" << "\n";
		output << "\tIn function -> " << m_pFunction << "\n";
		output << "\tIn file-> " << m_pFile << "\n";
		switch (m_Output)
		{
		case HeapChecker::OutputType::CONSOLE:
			std::cout << output.str();
			break;
		case HeapChecker::OutputType::VSWINDOWS:
			OutputDebugStringA(output.str().c_str());
			break;
		case HeapChecker::OutputType::TXTFILE: 
			m_OutStream << output.str();;
			break;
		default:
			break;
		}
	}
	
}
