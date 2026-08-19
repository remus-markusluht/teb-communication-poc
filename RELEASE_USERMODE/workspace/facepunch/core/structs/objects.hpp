#ifndef OBJECTS_HPP
#define OBJECTS_HPP

namespace sdk {
	namespace object {

		class c_base_player {
		public:
			c_base_player( ) = default;
			~c_base_player( ) = default;
		};

		class c_base_combat_entity {
		public:
			c_base_combat_entity( ) = default;
			~c_base_combat_entity( ) = default;
		};

		class c_local_player {
		public:
			c_local_player( ) = default;
			~c_local_player( ) = default;
		};
	}
}


#endif // !OBJECTS_HPP