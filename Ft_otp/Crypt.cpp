#include "Crypt.hpp"

		//CONSTRUCTOR/DESTRUCTOR//

		Crypt::Crypt(std::string iv, std::string key, FILE *file, unsigned int enc_dec): _iv(iv), _key(key), _file(file), _enc_dec(enc_dec), _cipher_type(EVP_aes_256_cbc())
{
	if (_enc_dec == 1)
	{
		_outfile = fopen("ft_otp.key", "wb");
	}
	else
		_outfile = NULL;
}

	Crypt::Crypt(FILE *file, unsigned int enc_dec): _file(file),
								_enc_dec(enc_dec),
								_cipher_type(EVP_aes_256_cbc())
{
	if (_enc_dec == 1)
	{
		_outfile = fopen("ft_otp.key", "wb");
	}
	else
	{
		_outfile = NULL;
		this->setKeyFromFile();
		this->setIvFromFile();
	}
}

	Crypt::Crypt(FILE *file): _file(file),
					_enc_dec(1),
					_cipher_type(EVP_aes_256_cbc())
{
	this->generateRanKeySaveFile();
	this->generateRanIvSaveFile();
	if (_enc_dec == 1)
	{
		_outfile = fopen("ft_otp.key", "wb");
	}
	else
		_outfile = NULL;
}

		Crypt::~Crypt(void)
{
	if (_file)
		fclose(_file);
	if (_outfile)
		fclose(_outfile);
}

		//GETTER//
std::string		Crypt::getKey(void) const { return (_key); }
std::string		Crypt::getIv(void) const { return (_iv); }
unsigned int		Crypt::getEncDec(void) const { return (_enc_dec); }
const EVP_CIPHER*	Crypt::getCipherType(void) const { return (_cipher_type); }
FILE*			Crypt::getFile(void) const { return (_file); }
FILE*			Crypt::getOutFile(void) { return (_outfile); }

		//SETTER//
void			Crypt::setFile(FILE *file)
{
	if (_file)
		fclose(_file);
	_file = file;
}

void			Crypt::setOutFile(FILE *outfile)
{
	if (_outfile)
		fclose(_outfile);
	_outfile = outfile;
}

void			Crypt::setEncDec(unsigned int mode)
{
	_enc_dec = mode;
}

void			Crypt::setCipherType(EVP_CIPHER *cipher_type)
{
	_cipher_type = cipher_type;
}

void			Crypt::setKeyFromFile(void)
{
	FILE	*fkey = fopen("key.crypt", "rb");
	unsigned char	buffer[AES_256_KEY_SIZE];

	if (getKey().empty())
	{
		if (fread(buffer, AES_256_KEY_SIZE, 1, fkey) )//== AES_256_KEY_SIZE)
		{
			_key.append((const char *)buffer, sizeof(buffer));
		}
		else
			std::cerr << "Key should have the size defined in AES_256_KEY_SIZE." << std::endl;
		fclose(fkey);
	}
}

void			Crypt::setIvFromFile(void)
{
	FILE	*fiv = fopen("iv.crypt", "rb");
	unsigned char	buffer[AES_BLOCK_SIZE];

	if (getIv().empty())
	{
		if (fread(buffer, AES_BLOCK_SIZE, 1, fiv) )//== AES_256_KEY_SIZE)
		{
			_iv.append((const char *)buffer, sizeof(buffer));
		}
		else
			std::cerr << "Iv should have the size defined in AES_BLOCK_SIZE." << std::endl;
		fclose(fiv);
	}
}
		//ENCRYPT/DECRYPT//
std::string		Crypt::encDecFile(void)
{
	unsigned char	in_buf[BUFSIZE];
	unsigned char	out_buf[BUFSIZE + EVP_CIPHER_block_size(getCipherType())];
	int		num_bytes_read;
	int		outlen;
	std::string	dec_data;
	EVP_CIPHER_CTX*	ctx;

	//Error management//
	if (getKey().empty() || getIv().empty()) // Checking if we have a key and a Iv
	{
		std::cerr << "Need a key and a iv to encrypt/decrypy datas." << std::endl;
		return (dec_data);
	}
	if (getEncDec() == 1 && getOutFile() == NULL)
	{
		std::cerr << "Need an outfile to encrypt, you can set it with setOutfile(FILE *file)." << std::endl;
		return (dec_data);
	}
	if (getFile() == NULL)
	{
		std::cerr << "Need a file to decrypt/encrypt, you can set it with setFile(FILE *file)." << std::endl;
		return (dec_data);
	}
	ctx = EVP_CIPHER_CTX_new();
	//Initializing//
	EVP_CipherInit_ex(ctx, _cipher_type, NULL, NULL, NULL, _enc_dec);
	OPENSSL_assert(EVP_CIPHER_CTX_key_length(ctx) == AES_256_KEY_SIZE);
	OPENSSL_assert(EVP_CIPHER_CTX_iv_length(ctx) == AES_BLOCK_SIZE);
	//Setting key and Iv//
	EVP_CipherInit_ex(ctx, NULL, NULL, (const unsigned char *)_key.c_str(), (const unsigned char *)_iv.c_str(), _enc_dec);

	num_bytes_read = fread(in_buf, sizeof(unsigned char), BUFSIZE, getFile()); // Reading File
	//Encrypting/Decrypting//
	EVP_CipherUpdate(ctx, out_buf, &outlen, in_buf, num_bytes_read);
	if (getEncDec() == 1)
	{
		fwrite(out_buf, sizeof(unsigned char), outlen, getOutFile());
	}
	else
	{
		dec_data.append((const char *)out_buf, (size_t)outlen);
	}
	EVP_CipherFinal_ex(ctx, out_buf, &outlen);
	if (getEncDec() == 1)
	{
		fwrite(out_buf, sizeof(unsigned char), outlen, getOutFile());
	}
	else
	{
		dec_data.append((const char *)out_buf, (size_t)outlen);
	}
	//Closing outfile//
	if (getEncDec() == 1)
	{
		fclose(_outfile);
		_outfile = NULL;
	}
	EVP_CIPHER_CTX_cleanup(ctx);
	EVP_CIPHER_CTX_free(ctx);
	return (dec_data);
}

	// GENERATE RANDOM KEY/IV AND RETURN IT //
std::string	Crypt::generateRanKey(void)
{
	unsigned char	tmp[AES_256_KEY_SIZE];

	if (!(getKey().empty()))
	{
		std::cerr << "There is already a key in this instance" << std::endl;
		return (getKey());
	}
	RAND_bytes(tmp, sizeof(tmp));
	_key.append((const char*)tmp, sizeof(tmp));
	return (getKey());
}

void	Crypt::generateRanKeySaveFile(void)
{
	FILE	*key = fopen("key.crypt", "wb");

	generateRanKey();
	fwrite((unsigned char *)_key.c_str(), AES_256_KEY_SIZE, 1, key);
	fclose(key);

}

std::string	Crypt::generateRanIv(void)
{
	unsigned char	tmp[AES_BLOCK_SIZE];

	if (!(getIv().empty()))
	{
		std::cerr << "There is already a key in this instance" << std::endl;
		return (getIv());
	}
	RAND_bytes(tmp, sizeof(tmp));
	_iv.append((const char*)tmp, sizeof(tmp));
	return (getIv());
}

void		Crypt::generateRanIvSaveFile(void)
{
	FILE	*iv = fopen("iv.crypt", "wb");

	generateRanIv();
	fwrite((unsigned char *)_iv.c_str(), AES_BLOCK_SIZE, 1, iv);
	fclose(iv);

}
