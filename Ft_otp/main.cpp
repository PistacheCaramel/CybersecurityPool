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
	unsigned char	out[in.size() + EVP_MAX_BLOCK_LENGTH];
	FILE		*fcry = fopen("ft_otp.key", "wb");
	int		ret;
	int		size;
	unsigned char	iv[7];
	
	std::cout << "here" << std::endl;
	bzero(out, in.size() + 1);
	memcpy(iv, "ft_otp", 7);
	size = in.size() + EVP_MAX_BLOCK_LENGTH;
	//	Setting crypt context
	EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (const unsigned char *)get_key().c_str(), iv);
	//	Encrypting the key
	ret = EVP_EncryptUpdate(ctx, out, &size, (const unsigned char *)in.c_str(), in.size());
	fwrite(out, 1, size, fcry);
	EVP_EncryptFinal_ex(ctx, out, &size);
	fwrite(out, 1, size, fcry);
	//	Free ressources
	EVP_CIPHER_CTX_free(ctx);
	fclose(fcry);
	return (0);
}

int	dec_data(ENV_CIPHER_CTX *ctx)
{
	unsigned char	iv[7];
	unsigned char	in[1024];
	unsigned char	out[1024];
	int		inlen;
	int		outlen;

	memcpy(iv, "ft_otp", 7);
	EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, (const unsigned char *)get_key.c_str(), iv);
	while ((inlen = fread(in, 1,//in progress	

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
}
