```cpp
#include <meta>

struct Config
{
    std::string host;
    int port;
    bool tls;
};

Config cfg { "example.com", 443, false };

constexpr std::meta::info config_info = ^^Config;
constexpr std::meta::info port_info = ^^Config::port;
constexpr std::meta::info int_info = ^^int;

using T = [:int_info:];
auto port = cfg.[:port_info:];

static_assert( std::meta::is_type( config_info ));
static_assert( std::meta::is_nonstatic_data_member( port_info ));
static_assert( std::meta::identifier_of( port_info ) == "port" );
static_assert( std::meta::type_of( port_info ) == ^^int );

constexpr ctx = std::meta::access_context::current();
template for ( constexpr auto member : std::define_static_array( std::meta::non_static_data_members_of( ^^Config, ctx ) ) )
{
    std::cout << std::meta::identifier_of( member ) << "\n";
}

template <typename Enum>
    requires std::is_enum_v<Enum>
constexpr std::string_view to_string( Enum value )
{
    template for ( constexpr auto e : std::define_static_array( std::meta::enumerators_of(^^Enum) ) )
    {
        if ( value == [:e:] )
        {
            return std::meta::identifier_of( e );
        }
    }

    return "<unknown>";
}

template <typename T>
void print_value(T value)
{
    std::cout << value;
}

template <typename T>
void print_json( const T& obj )
{
    constexpr auto ctx = std::meta::access_context::current();
    bool first = true;
    std::cout << "{";
    template for ( constexpr auto member : std::define_static_array( std::meta::non_static_data_members_of(^^T, ctx) ) )
    {
        if ( !first )
        {
            std::cout << ",";
        }
        first = false;
        std::cout << "\"" << std::meta::identifier_of( member ) << "\":";
        print_value( obj.[:member:]);
    }
    std::cout <<"}\n";
}
```

```cpp
#include <meta>

auto make_location()
{
    struct location;

    consteval {
        std::vector<std::meta::info> members = {
            std::meta::data_member_spec(^^int, { .name = "x" }),
            std::meta::data_member_spec(^^int, { .name = "y" }),
        };
        std::meta::define_agggregate(^^location, members);
    }

    return location{};
}

using location = decltype( make_location() );

int main()
{
    location loc{ .x = 1, .y = 5 };
    return 0;
}

```