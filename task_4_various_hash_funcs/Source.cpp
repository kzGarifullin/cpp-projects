#include <iostream>
#include <chrono>
#include <random>
#include <set>
#include <string>
#include <functional>
#include <vector>
std::set < std::string > make_random_words(std::size_t N, std::size_t length) // length = 10 - good enough
{
	std::uniform_int_distribution <> letter(97, 122);
	std::default_random_engine e(static_cast <std::size_t> (
		std::chrono::system_clock::now().time_since_epoch().count()));

	std::set < std::string > words;

	for (std::string s(length, '_'); std::size(words) < N; words.insert(s))
		for (auto& c : s)
			c = letter(e);

	return words;
}
unsigned int RSHash(const char* str, unsigned int length)
{
	unsigned int b = 378551;
	unsigned int a = 63689;
	unsigned int hash = 0;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = hash * a + (*str);
		a = a * b;
	}

	return hash;
}
unsigned int JSHash(const char* str, unsigned int length)
{
    unsigned int hash = 1315423911;
    unsigned int i = 0;

    for (i = 0; i < length; ++str, ++i)
    {
        hash ^= ((hash << 5) + (*str) + (hash >> 2));
    }

    return hash;
}
unsigned int PJWHash(const char* str, unsigned int length)
{
	const unsigned int BitsInUnsignedInt = (unsigned int)(sizeof(unsigned int) * 8);
	const unsigned int ThreeQuarters = (unsigned int)((BitsInUnsignedInt * 3) / 4);
	const unsigned int OneEighth = (unsigned int)(BitsInUnsignedInt / 8);
	const unsigned int HighBits =
		(unsigned int)(0xFFFFFFFF) << (BitsInUnsignedInt - OneEighth);
	unsigned int hash = 0;
	unsigned int test = 0;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = (hash << OneEighth) + (*str);

		if ((test = hash & HighBits) != 0)
		{
			hash = ((hash ^ (test >> ThreeQuarters)) & (~HighBits));
		}
	}

	return hash;
}
unsigned int ELFHash(const char* str, unsigned int length)
{
	unsigned int hash = 0;
	unsigned int x = 0;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = (hash << 4) + (*str);

		if ((x = hash & 0xF0000000L) != 0)
		{
			hash ^= (x >> 24);
		}

		hash &= ~x;
	}

	return hash;
}
unsigned int BKDRHash(const char* str, unsigned int length)
{
	unsigned int seed = 131; /* 31 131 1313 13131 131313 etc.. */
	unsigned int hash = 0;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = (hash * seed) + (*str);
	}

	return hash;
}
unsigned int SDBMHash(const char* str, unsigned int length)
{
	unsigned int hash = 0;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = (*str) + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}
unsigned int DJBHash(const char* str, unsigned int length)
{
	unsigned int hash = 5381;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = ((hash << 5) + hash) + (*str);
	}

	return hash;
}
unsigned int DEKHash(const char* str, unsigned int length)
{
	unsigned int hash = length;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash = ((hash << 5) ^ (hash >> 27)) ^ (*str);
	}

	return hash;
}
unsigned int APHash(const char* str, unsigned int length)
{
	unsigned int hash = 0xAAAAAAAA;
	unsigned int i = 0;

	for (i = 0; i < length; ++str, ++i)
	{
		hash ^= ((i & 1) == 0) ? ((hash << 7) ^ (*str) * (hash >> 3)) :
			(~((hash << 11) + ((*str) ^ (hash >> 5))));
	}

	return hash;
}
int main(int argc, char** argv)
{
	std::vector<std::function<int(const char* , unsigned int)>> hashes{JSHash,PJWHash,ELFHash,BKDRHash,SDBMHash,
	DJBHash,DEKHash,APHash,RSHash};
	//hashes.push_back(APHash);
	std::set <int> hash;
	int index = 0;
	int N = 5000000;
	std::set < std::string > words = make_random_words(N, 10);
	for (int i = 0; i < 9; i++) {
		std::set <int> hash;
		for (auto word : words) {
			//std::cout << i << std::endl;
			const char* c = word.c_str();
			hash.insert(hashes[i](c, 10));
		}
		std::cout << "   "<<i<<"     " << std::endl;
	
		std::cout << "collisions " << N - hash.size();
		std::cout << "           " << std::endl;;
		
	}
	
	//std::string Columns[] = { "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R",
	//	"S","T","U","V","W","X","Y","Z" };
	//std::string columns[] = { "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r",
	//	"s","t","u","v","w","x","y","z" };
	//int N = 20;
	//for (int a = 0; a < N; a++)
	//{
	//	std::string str1 = columns[a];//можно взять Columns-тогда будет верхний регистр
	//	for (int b = 0; b < N; b++)
	//	{
	//		std::string str2 = str1 + columns[b];
	//		for (int c = 0; c < N; c++)
	//		{
	//			std::string str3 = str2 + columns[c];
	//			for (int d = 0; d < N; d++)
	//			{

	//				std::string str4 = str3 + columns[d];
	//				for (int e = 0; e < N; e++) {
	//					//std::cout << str5<<std::endl;
	//					std::string str5 = str4 + columns[e];
	//					for (int f = 0; f < N; f++)
	//					{
	//						std::string str6 = str5 + columns[f];
	//						const char* c = str6.c_str();
	//						//std::cout << c<< std::endl;
	//						hash.insert(JSHash(c, 6));
	//						//hash.insert(PJWHash(c, 6));
	//						//std::cout << str6 << std::endl;
	//						//std::cout << JSHash(c, 6)<<std::endl;
	//						index++;
	//						//std::cout<<Customer_Hash()(Customer(str5, index % 100));
	//						//hash.insert(Customer_Hash()(Customer(str5, index % 100)));
	//					}
	//				}

	//			}
	//		}
	//	}
	//}


}