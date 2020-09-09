#include "../include/file_receiver.hpp"

namespace file_receiver
{
    inline static constexpr const uint8_t BLOCK_SIZE_IN_BYTES {23};



    size_t read_next_block_size(sockpp::tcp_socket& sock) noexcept
    {
        char next_block_size[BLOCK_SIZE_IN_BYTES] {};
        sock.read_n(next_block_size, BLOCK_SIZE_IN_BYTES);
        return (static_cast<size_t>(std::stoull(next_block_size)));
    }

    std::pair<std::string, size_t> receive_data_from_client(sockpp::tcp_socket& sock) noexcept
    {
        const size_t buffer_size {read_next_block_size(sock)};

        char buffer[buffer_size];
        sock.read_n(buffer, buffer_size);

        return {buffer, buffer_size};
    }
} // namespace file_receiver