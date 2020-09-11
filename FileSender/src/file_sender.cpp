#include "../include/file_sender.hpp"

namespace file_sender
{
    inline static constexpr const uint8_t BLOCK_SIZE_IN_BYTES {23};
    


    void send_error_code_and_close_connection(sockpp::tcp_connector& sock, const uint8_t code) noexcept
    {
        send_error_code(sock, code);
        sock.close();
    }

    std::string read_file(std::FILE* file) noexcept
    {
        char buffer {};
        std::string file_data {};

        while (std::fread(&buffer, sizeof(buffer), sizeof(char), file))
            file_data += buffer;

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