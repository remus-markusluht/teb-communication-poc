#ifndef ENV_HPP
#define ENV_HPP

namespace env_interface {

	class c_env {
	public:
		c_env( ) = default;
		~c_env( ) = default;

	public:
		void first_thread( );

	private:
		void base_projectile( );
	};

} inline auto env = std::make_shared<env_interface::c_env>( );

#endif // !ENV_HPP
