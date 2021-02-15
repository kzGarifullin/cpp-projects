#include <iostream> 
#include <vector>
int main()
{
	std::vector<int> arr1 = { 0,1,2,3,4,5,6,7,8,9 };
	std::cout << "capacity: " << arr1.capacity() << std::endl;

	arr1.push_back(10); // ��������������� ����� � ��� �������
	std::cout << "capacity: " << arr1.capacity() << std::endl;
	std::cout << std::endl;
	std::vector<int> arr2;
	arr2.reserve(10);
	std::cout << "capacity: " << arr2.capacity() << std::endl;
	arr2.push_back(10);
	std::cout << "capacity: " << arr2.capacity() << std::endl;
	arr2.push_back(10);
	std::cout << "capacity: " << arr2.capacity() << std::endl;//capacity �� ��������
	arr2.push_back(10);
	std::cout << std::endl;
	try {
		std::vector<int> arr3;
		arr3.reserve(100000000);
		arr3.push_back(10);
		std::cout << "capacity: " << arr3.capacity() << std::endl;
		arr3.reserve(9000000000);
		std::cout << "capacity: " << arr3.capacity() << std::endl;
		//�������� �������������� ���������� �� ������ 0x778D46D2 �
		//vector_memory.exe: ���������� Microsoft C++: std::bad_alloc �� ������ ������ 0x00EFF138.
	}
	catch (...) {
		std::cerr << "Error";
	}

	return 0;
}