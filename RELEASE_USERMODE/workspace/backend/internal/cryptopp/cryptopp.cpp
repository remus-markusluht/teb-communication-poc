#ifndef CRYPTOPP_CPP
#define CRYPTOPP_CPP

#include <impl/includes.hpp>

std::string crypto::c_crypto::aes_encrypt( const std::string& text, std::string* out, const std::string& private_key )
{
    if ( private_key.length( ) > CryptoPP::AES::MAX_KEYLENGTH )
        return { };

    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::SecByteBlock iv( CryptoPP::AES::BLOCKSIZE );
    rng.GenerateBlock( iv, iv.size( ) );

    std::string ciphertext;

    CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption encryptor;
    encryptor.SetKeyWithIV( reinterpret_cast< const BYTE* >( private_key.data( ) ), private_key.size( ), iv );

    CryptoPP::StringSource( text, true,
        new CryptoPP::StreamTransformationFilter( encryptor,
            new CryptoPP::StringSink( ciphertext )
        )
    );

    std::string encoded_iv;
    CryptoPP::StringSource( iv, iv.size( ), true,
        new CryptoPP::Base64Encoder(
            new CryptoPP::StringSink( encoded_iv ), false // No newline
        )
    );

    std::string encoded_ciphertext;
    CryptoPP::StringSource( ciphertext, true,
        new CryptoPP::Base64Encoder(
            new CryptoPP::StringSink( encoded_ciphertext ), false // No newline
        )
    );

    *out = encoded_iv;
    return encoded_ciphertext;
}

std::string crypto::c_crypto::aes_decrypt( const std::string& text, const std::string& iv, const std::string& private_key )
{
    if ( private_key.length( ) > CryptoPP::AES::MAX_KEYLENGTH )
        return { };

    std::string decoded_iv;
    CryptoPP::StringSource( iv, true,
        new CryptoPP::Base64Decoder(
            new CryptoPP::StringSink( decoded_iv )
        )
    );

    std::string decoded_ciphertext;
    CryptoPP::StringSource( text, true,
        new CryptoPP::Base64Decoder(
            new CryptoPP::StringSink( decoded_ciphertext )
        )
    );

    std::string plaintext;

    CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryptor;
    decryptor.SetKeyWithIV( reinterpret_cast< const BYTE* >( private_key.data( ) ), private_key.size( ), reinterpret_cast< const BYTE* >( decoded_iv.data( ) ) );

    CryptoPP::StringSource( decoded_ciphertext, true,
        new CryptoPP::StreamTransformationFilter( decryptor,
            new CryptoPP::StringSink( plaintext )
        )
    );

    return plaintext;
}

std::string crypto::c_crypto::hex_encode( const std::string& text )
{
    std::string encoded_text;

    CryptoPP::StringSource encoding( text, true,
        new CryptoPP::HexEncoder(
            new CryptoPP::StringSink( encoded_text ),
            false
        )
    );

    return encoded_text;
}

std::string crypto::c_crypto::sha256( const std::string& text )
{
    CryptoPP::SHA256 hash;
    std::string digest;
    CryptoPP::StringSource ss( text, true,
        new CryptoPP::HashFilter( hash,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink( digest ) ) ) );
    return digest;
}

std::string crypto::c_crypto::base64_encode( const std::string& plaintext )
{
    std::string out;

    CryptoPP::StringSource(
        plaintext,
        true,
        new CryptoPP::Base64Encoder(
            new CryptoPP::StringSink( out ),
            false
        )
    );

    return out;
}

std::string crypto::c_crypto::base64_decode( const std::string& ciphertext )
{
    std::string out;

    CryptoPP::StringSource(
        ciphertext,
        true,
        new CryptoPP::Base64Decoder(
            new CryptoPP::StringSink( out )
        )
    );

    return out;
}

#endif // !CRYPTOPP_CPP
