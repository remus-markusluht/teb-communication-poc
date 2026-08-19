#ifndef CRYPTOPP_HPP
#define CRYPTOPP_HPP

namespace crypto {

	class c_crypto {
	public:
		c_crypto( ) = default;
		~c_crypto( ) = default;

		// symetric
		// openssl rand -hex 32
		std::string aes_encrypt( const std::string& text, std::string* out, const std::string& private_key );
		std::string aes_decrypt( const std::string& text, const std::string& iv, const std::string& private_key );

		// sha256
		std::string sha256( const std::string& text );

		// hex
		std::string hex_encode( const std::string& text );

		// base64
		std::string base64_encode( const std::string& text );
		std::string base64_decode( const std::string& text );
	};

} inline auto cryptopp = std::make_unique<crypto::c_crypto>( );

#endif // !CRYPTOPP_HPP
