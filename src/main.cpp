#include <iostream>
#include <stdexcept>
#include <typeinfo>
#include <cstdio>

bool is_connected = false;

void activate_connection()
{
    (void)printf("Establishing Connection");
    is_connected = true;
}

void deactivate_connection()
{
    (void)printf("Deactivating Connection");
    is_connected = false;
}

std::string format_exception(const std::exception &e)
{
    const char *errorTypeID = typeid(e).name();
    const char *errorMessage = e.what();

    std::string formatted_message = "ErrorTypeID: " + std::string(errorTypeID) +
                                    ", ErrorMessage: " + std::string(errorMessage);
    return formatted_message;
}

void print_exception(const std::exception &e)
{
    std::string formatted_message = format_exception(e);
    fprintf(stderr, "%s\n", formatted_message.c_str());
}

class DB_Connection
{
public:
    DB_Connection()
    {
        if (is_connected)
        {
            throw std::runtime_error("Connection already active!");
        }
        activate_connection();
        std::cout << "DB_Connection established.\n";
    }
    ~DB_Connection()
    {
        if (is_connected)
        {
            deactivate_connection();
            std::cout << "DB_Connection closed.\n";
        }
    }
};

void print_connection_status()
{
    if (is_connected)
    {
        std::cout << "Heartbeat Check: IsAlive\n";
    }
    else
    {
        std::cout << "Heartbeat Check: IsDead\n";
    }
}

int main()
{
    print_connection_status();
    try
    {
        {
            DB_Connection db1;
            print_connection_status();
        }
        print_connection_status();
        DB_Connection db2;
        print_connection_status();
        DB_Connection db3;
    }
    catch (const std::exception &e)
    {
        print_exception(e);
        deactivate_connection();
    }

    print_connection_status();

    return 0;
}
