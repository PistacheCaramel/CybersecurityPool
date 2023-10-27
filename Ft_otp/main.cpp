#include "Crypt.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
		return (0);
	FILE	*file = fopen(av[1], "rb");
	Crypt	otp(file);
	otp.encDecFile();
	Crypt	otp_dec(fopen("ft_otp.key", "rb"), 0);
	std::cout << otp_dec.encDecFile() << std::endl;
	return (0);
}
