#include "Crypt.hpp"

		//CONSTRUCTOR/DESTRUCTOR//

		Crypt::Crypt(void) {}

		Crypt::Crypt(std::string iv, std::string key, std::ifstream &file, unsigned int enc_dec): _iv(iv), _key(key), _file(file), _enc_dec(enc_dec), _cipher_type(EVP_aes_256_cbc()), _ctx(EVP_CIPHER_CTX_new())
{
	EVP_CipherInit_ex(_ctx, _cipher_type, NULL, NULL, NULL, _enc_dec);
	OPENSSL_assert(EVP_CIPHER_CTX_key_length(_ctx) == AES_256_KEY_SIZE);
	OPENSSL_assert(EVP_CIPHER_CTX_iv_length(_ctx) == AES_BLOCK_SIZE);
	EVP_CipherInit_ex(_ctx, NULL, NULL, _key.c_str(), iv.c_str(), _enc_dec);
}
		
		Crypt::~Crypt(void) { EVP_CIPHER_CTX_cleanup(ctx); }

		//GETTER//
std::string		Crypt::getKey(void) { return (_key); }
std::string		Crypt::getIV(void) { return (_iv); }
unsigned int			Crypt::getEncDec(void) { return (_enc_dec); }
const EVP_CIPHER*	Crypt::getCipherType(void) { return (_cipher_type); }

		//ENCRYPT/DECRYPT//
void			encDecFile(void)
{

}
