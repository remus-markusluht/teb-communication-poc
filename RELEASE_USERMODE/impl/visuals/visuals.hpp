#ifndef VISUALS_HPP
#define VISUALS_HPP

namespace visuals_interface {

    class c_visuals {
    public:
        c_visuals( ) = default;
        ~c_visuals( ) = default;

	public:
		void players( ImDrawList* ImDrawList );

        void framerate( ImDrawList* ImDrawList );

        void on_screen( ImDrawList* ImDrawList );

        void world( ImDrawList* ImDrawList );
    };

} inline auto visuals = std::make_shared<visuals_interface::c_visuals>( );

#endif // VISUALS_HPP