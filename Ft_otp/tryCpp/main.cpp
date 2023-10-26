#include "Crypt.hpp"

int main()
{
	std::ifstream	file("key.txt");
	Crypt("ft_otp", "onekey", file, 0);
	return (0);
}
