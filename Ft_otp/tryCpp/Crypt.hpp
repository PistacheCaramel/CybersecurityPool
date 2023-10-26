#ifndef CRYPT_HPP
# define CRYPT_HPP

# include <openssl/evp.h>
# include <openssl/aes.h>
# include <openssl/rand.h>
# include <string.h>
# include <iostream>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <fstream>

class	Crypt
{
	private:
		std::string		_key;
		std::string		_iv;
		unsigned int		_enc_dec; // 0 for dec and 1 for enc
		const EVP_CIPHER*	_cipher_type;
		std::ifstream		_file;
		EVP_CIPHER_CTX*		_ctx;
		int			_num_bytes_read;
		int			_out_len;


					Crypt(void);
		

	public:
					Crypt(std::string iv, std::string key, std::ifstream& file, unsigned int enc_dec);
					~Crypt(void);
		std::string		getKey(void) const;
		std::string		getIv(void) const;
		bool			getEncDec(void) const;
		const EVP_CIPHER*	getCipherType(void) const;
		std::ofstream		getFile(void) const;
		void			encFile(void);
};

#endif
