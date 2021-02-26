#include <functional>
#include <iostream>
#include <string>
#include <unordered_set>
#include <set>
#include <chrono>
#include <random>
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

// http://www.boost.org/doc/libs/1_35_0/doc/html/hash/combine.html

template < typename T >
void hash_combine(std::size_t& seed, const T& value) noexcept
{
	seed ^= std::hash < T >()(value) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template < typename T >
void hash_value(std::size_t& seed, const T& value) noexcept
{
	hash_combine(seed, value);
}

template < typename T, typename ... Types >
void hash_value(std::size_t& seed, const T& value, const Types & ... args) noexcept
{
	hash_combine(seed, value);
	hash_value(seed, args...);
}

template < typename ... Types >
std::size_t hash_value(const Types & ... args) noexcept
{
	std::size_t seed = 0;
	hash_value(seed, args...);
	return seed;
}

class Customer
{
private:
	friend struct Customer_Hash;
	friend struct Customer_Equal;

public:
	explicit Customer(const std::string& name, const std::size_t mark) :
		m_name(name), m_mark(mark)
	{}

	~Customer() noexcept = default;

public:
	friend std::ostream& operator << (std::ostream& stream, const Customer& customer)
	{
		return (stream << customer.m_name << "," << customer.m_mark);
	}

private:
	std::string m_name;
	std::size_t m_mark;
};

struct Customer_Hash
{
	std::size_t operator() (const Customer& customer) const noexcept
	{
		return hash_value(customer.m_name, customer.m_mark);
	}
};

struct Customer_Equal
{
	bool operator() (const Customer& lhs, const Customer& rhs) const noexcept
	{
		return (lhs.m_name == rhs.m_name);
	}
};

int main()
{
	std::unordered_set < Customer, Customer_Hash, Customer_Equal > customers;

	customers.insert(Customer("Ivan", 42));
	customers.insert(Customer("Jens", 66));

		
	std::set <int> hash;
	int index = 0;
	int N = 2500000;
	std::set < std::string > words = make_random_words(N, 10);
	
		for (auto word : words) {
			
			customers.insert(Customer(word, index % 100));
			index++;
			hash.insert(Customer_Hash()(Customer(word, index % 100)));
}

		std::cout << "collisions " << N - hash.size();
		std::cout << "           " << std::endl;
	
}