#include "../include/file_sender.hpp"

namespace file_sender
{
    inline static constexpr const uint8_t BLOCK_SIZE_IN_BYTES {23};



    void send_error_code(sockpp::tcp_connector& sock, const uint8_t code) noexcept
    {
        sock.write_n(&code, sizeof(code));
    }



    void send_error_code_and_close_connection(sockpp::tcp_connector& sock, const uint8_t code) noexcept
    {
        send_error_code(sock, code);
        sock.close();
    }



    std::string read_file(std::FILE* file) noexcept
    {
        std::fseek(file, 0, SEEK_END);
        const size_t file_size {static_cast<size_t>(std::ftell(file))};

        std::fseek(file, 0, SEEK_SET);

        if (file_size <= 4096)
        {
            char buffer[file_size];
            std::fread(buffer, file_size, sizeof(char), file);
            return {buffer};
        }

        std::string file_data {};
        file_data.reserve(file_size);
        file_data.resize(file_size);

        std::fread(file_data.data(), sizeof(char), file_size, file);

        return file_data;
    }



    ssize_t send_filename(sockpp::tcp_connector& sock, const std::string& filename) noexcept
    {
        const size_t filename_size {filename.size() + 1};
        sock.write_n(std::to_string(filename_size).c_str(), BLOCK_SIZE_IN_BYTES);
        return (sock.write_n(filename.c_str(), filename_size));
    }



    ssize_t send_file_data(sockpp::tcp_connector& sock, const std::string& file_data) noexcept
    {
        const size_t file_data_size {file_data.size()};
        sock.write_n(std::to_string(file_data_size).c_str(), BLOCK_SIZE_IN_BYTES);
        return (sock.write_n(file_data.c_str(), file_data_size));
    }
} // namesapce file_sender
