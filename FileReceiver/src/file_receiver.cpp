#include "../include/file_receiver.hpp"

#include <string>
#include <fstream>



namespace file_receiver
{
    inline static constexpr const uint8_t BLOCK_SIZE_IN_BYTES {23};



    size_t read_next_block_size(sockpp::tcp_socket& sock) noexcept
    {
        char next_block_size[BLOCK_SIZE_IN_BYTES] {};
        sock.read_n(next_block_size, BLOCK_SIZE_IN_BYTES);
        return (static_cast<size_t>(std::stoull(next_block_size)));
    }



    std::string receive_filename(sockpp::tcp_socket& sock) noexcept
    {
        const size_t buffer_size {read_next_block_size(sock)};

        char buffer[buffer_size];
        sock.read_n(buffer, buffer_size);

        return {buffer};
    }



    std::string receive_file_data(sockpp::tcp_socket& sock) noexcept
    {
        const size_t buffer_size {read_next_block_size(sock)};
        std::string buffer {};

        buffer.reserve(buffer_size);
        buffer.resize(buffer_size);
        sock.read_n(buffer.data(), buffer_size);

        return buffer;
    }



    void write_data_to_file(const std::string& file_path, const char* data, const size_t data_size) noexcept
    {
        std::ofstream {file_path, std::ios::binary}.write(data, data_size);
    }
} // namespace file_receiver
