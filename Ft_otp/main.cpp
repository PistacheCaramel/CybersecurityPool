#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <string.h>
#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

std::string	get_key(void)
{
	int		fd;
	std::string	key_saved;
	unsigned char	c;

	fd = open("enc_key", O_RDONLY);
	if (fd <= 0)
		return (NULL);
	while (read(fd, &c, 1) > 0)
		key_saved.push_back(c);
	close(fd);
	return (key_saved);
}

int	enc_data(std::string in, EVP_CIPHER_CTX *ctx)
{
	unsigned char	out[in.size() + EVP_MAX_BLOCK_LENGTH + 1];
	int		fcry = open("ft_otp.key", O_CREAT | O_WRONLY);
	int		size;
	std::string	iv("ft_otp");
	
	if (fcry <= 0)
		return (1);
	bzero(out, in.size() + 1 + EVP_MAX_BLOCK_LENGTH);
	//	Setting crypt context
	EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (const unsigned char *)get_key().c_str(), (const unsigned char *)iv.c_str());
	//	Encrypting the key
	EVP_EncryptUpdate(ctx, out, &size, (const unsigned char *)in.c_str(), in.size());
	std::cout << "size:" << size << std::endl;
	write(1, out, size);
	std::cout << "////////" << std::endl;
	std::cout << "retour write:" << write(fcry, out, size - 1) << std::endl;
	EVP_EncryptFinal_ex(ctx, out, &size);
	std::cout << "retour write 2:" << write(fcry, out, size) << std::endl;
	//	Free ressources
	close(fcry);
	EVP_CIPHER_CTX_free(ctx);
	return (0);
}

int	dec_data(EVP_CIPHER_CTX *ctx)
{
	std::string	iv("ft_otp");
	unsigned char	in[1024];
	unsigned char	out[1024];
	int		inlen;
	int		outlen;
	FILE		*infile = fopen("ft_otp.key", "rb");

	bzero(in, 1024);
	bzero(out, 1024);
	EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (const unsigned char *)get_key().c_str(), (const unsigned char *)iv.c_str());
	while ((inlen = fread(in, 1, 1024, infile)) > 0)
	{
		EVP_DecryptUpdate(ctx, out, &outlen, in, inlen);
		write(1, out, outlen);
		bzero(out, 1024);
	}
	EVP_DecryptFinal_ex(ctx, out, &outlen);
	write(1, out, outlen);
	EVP_CIPHER_CTX_free(ctx);
	fclose(infile);
	return (0);
}

int	main(int ac, char **av)
{
	unsigned char	buffer[64];
	std::string	buff;
	int		fd;
	char		c;

	if (ac != 2)
		return (0);
	FILE *input = fopen(av[1], "r");
	if (fread(buffer, 1, 63, input) < 63)
	{
		std::cerr << "./ft_otp: error: key must be 64 hexadecimal characters." << std::endl;
		fclose(input);
		return (0);
	}
	fclose(input);
	fd = open(av[1], O_RDONLY);
	if (fd <= 0)
	{
		std::cout << "fd" << std::endl;
		return (1);
	}
	while (read(fd, &c, 1) > 0)
		buff.push_back(c);
	close(fd);
	enc_data(buff, EVP_CIPHER_CTX_new());
	dec_data(EVP_CIPHER_CTX_new());
}
