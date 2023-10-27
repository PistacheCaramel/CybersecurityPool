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


# define AES_256_KEY_SIZE 32
# define BUFSIZE 1024

class	Crypt
{
	private:
		std::string		_iv;
		std::string		_key;
		FILE*			_file;
		FILE*			_outfile;
		unsigned int		_enc_dec; // 0 for dec and 1 for enc
		const EVP_CIPHER*	_cipher_type;
		int			_num_bytes_read;
		int			_out_len;


					Crypt(void);
		

	public:
					//CONSTRUCTORS/DESTRUCTOR//
					Crypt(std::string iv, std::string key, FILE *file, unsigned int enc_dec);
					Crypt(FILE *file, unsigned int enc_dec);
					Crypt(FILE *file); // Will set encrypt an genererate random iv/key by default
					~Crypt(void);

					//GETTERS//
		std::string		getKey(void) const;
		std::string		getIv(void) const;
		unsigned int		getEncDec(void) const;
		const EVP_CIPHER*	getCipherType(void) const;
		FILE*			getFile(void) const;
		FILE*			getOutFile(void);

					//SETTERS//
		void			setFile(FILE *file); //Will close and replace the file if the instance already has one
		void			setOutFile(FILE *outfile);
		void			setEncDec(unsigned int mode);
		void			setCipherType(EVP_CIPHER* cipher_type);
		void			setKeyFromFile(void);
		void			setIvFromFile(void);

					//MEMBERS FUNCTIONS//
		std::string			encDecFile(void);
		std::string			generateRanKey(void); //Will generate a random key
		void				generateRanKeySaveFile(void); //Will generate a random key and save it in a file named "key.crypt"

		std::string			generateRanIv(void); //Will generate a random Iv
		void				generateRanIvSaveFile(void); //Will generate a random Iv and save it in a file named "iv.crypt"

};

#endif
