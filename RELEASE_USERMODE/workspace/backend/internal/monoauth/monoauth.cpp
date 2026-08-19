#ifndef MONOAUTH_CPP
#define MONOAUTH_CPP

#include <impl/includes.hpp>

auto monoauth_interface::c_monoauth::create_session( std::string token ) -> std::expected<nlohmann::json, session_setup_error_code>
{
    cpr::Response request = cpr::Post(
        cpr::Url { api_url + HASH_STR( "/user/session/create" ) },
        cpr::Header {
            { HASH_STR( "Authorization" ), HASH_STR( "Bearer " ) + token }
        },
        cpr::Parameters {
            cpr::Parameter{ HASH_STR( "token" ), project_token }
        },
        cpr::Timeout { static_cast< int32_t >( timeout.count( ) ) }
    );

    if ( request.status_code != 200 )
        return std::unexpected( session_setup_error_code::create_error );

    nlohmann::json result = nlohmann::json::parse( request.text, nullptr, false );
    if ( result.empty( ) )
        return std::unexpected( session_setup_error_code::odd_response );

    this->session = new c_session( this, token );
	return result;
}

auto monoauth_interface::c_session::get_brand( u32 id ) -> std::expected<nlohmann::json, brand_setup_error_code>
{
    cpr::Response request = cpr::Get(
        cpr::Url { auth->api_url + HASH_STR( "/user/brands/get" ) },
        cpr::Header {
            { HASH_STR( "Authorization" ), HASH_STR( "Bearer " ) + token }
        },
        cpr::Parameters {
            cpr::Parameter{ HASH_STR( "token" ), auth->project_token },
            cpr::Parameter{ HASH_STR( "id" ), std::to_string( id ) },
        },
        cpr::Timeout { static_cast< int32_t >( auth->timeout.count( ) ) }
    );

    if ( request.status_code != 200 )
        return std::unexpected( brand_setup_error_code::get_error );

    nlohmann::json result = nlohmann::json::parse( request.text, nullptr, false );
    if ( result.empty( ) )
        return std::unexpected( brand_setup_error_code::odd_response );

    this->brand = new c_brand( 
        result [ HASH_STR( "name" ) ].get<std::string>( ),
        result [ HASH_STR( "color" ) ].get<std::string>( ),
        result [ HASH_STR( "logo" ) ].get<std::string>( )
    );

    return result;
}

auto monoauth_interface::c_brand::setup_texture( ) -> void
{
    std::string decoded = cryptopp->base64_decode( logo );
    if ( decoded.empty( ) )
        return;

    fs::path image_path = textures_path / ( name + HASH_STR( ".png" ) );

    std::ofstream file( image_path, std::ios::binary );
    if ( !file.is_open( ) )
        return;

    file.write( decoded.c_str( ), decoded.size( ) );
    file.close( );

    texture = textures->get_texture_from_file( name, textures_path );
}

ImColor monoauth_interface::c_brand::get_color( )
{
    int r = std::stoi( color.substr( 0, 2 ), nullptr, 16 );
    int g = std::stoi( color.substr( 2, 2 ), nullptr, 16 );
    int b = std::stoi( color.substr( 4, 2 ), nullptr, 16 );

    return ImColor( r, g, b, 255 );
}

#endif // !MONOAUTH_CPP
