#ifndef MONOAUTH_HPP
#define MONOAUTH_HPP

namespace monoauth_interface {

	enum class session_setup_error_code : u8 {
		create_error = 0,
		odd_response = 1,
	};

	enum class brand_setup_error_code : u8 {
		get_error = 0,
		odd_response = 1,
	};

	class c_brand {
	private:
		ID3D11Texture2D* texture { };
		fs::path textures_path = fs::temp_directory_path( ) / HASH_STR( "textures" );

	private:
		std::string name, color, logo;

	public:
		c_brand( std::string name, std::string color, std::string logo ) : name( name ), color( color ), logo( logo ) { fs::create_directories( textures_path ); };
		~c_brand( ) = default;

	public:
		ImColor get_color( );

		void setup_texture( );
		ID3D11Texture2D* get_texture( ) const { return texture; }
	};

	class c_monoauth;

	class c_session {
	private:
		c_monoauth* auth;
		std::string token;

	public:
		c_session( c_monoauth* auth, std::string token ) : token( token ), auth( auth ) { };
		~c_session( ) = default;

	public:
		std::expected<nlohmann::json, brand_setup_error_code> get_brand( u32 id );
		c_brand* brand;
	};

	class c_monoauth {
	private:
		std::string name, ownerid, version;

	public:
		ch::milliseconds timeout = ch::seconds( 10 );
		std::string project_token, api_url;

	public:
		c_monoauth( const std::string& name, const std::string& ownerid, const std::string& version, const std::string& project_token, const std::string& api_url ) : name( name ), ownerid( ownerid ), version( version ), project_token( project_token ), api_url( api_url ) { };
		~c_monoauth( ) = default;

	public:
		std::expected<nlohmann::json, session_setup_error_code> create_session( std::string token );
		c_session* session;
	};

} inline auto monoauth = std::make_shared<monoauth_interface::c_monoauth>( HASH_STR( "Banned Cheats" ), HASH_STR( "1" ), HASH_STR( "5.0.0" ), HASH_STR( "bcd7f2a4" ), HASH_STR( MONOAUTH_API_URL ) );

#endif // !MONOAUTH_HPP
