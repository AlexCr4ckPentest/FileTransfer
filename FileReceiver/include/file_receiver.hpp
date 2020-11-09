#include <sockpp/tcp_acceptor.h>

#ifndef __FILE_RECEIVER_HPP__
#define __FILE_RECEIVER_HPP__

namespace file_receiver
{
    size_t read_next_block_size(sockpp::tcp_socket& sock) noexcept;
    std::string receive_filename(sockpp::tcp_socket& sock) noexcept;
    std::string receive_file_data(sockpp::tcp_socket& sock) noexcept;
    void write_data_to_file(const std::string& file_path, const char* data, const size_t data_size) noexcept;
} // namespace file_receiver

#endif // __FILE_RECEIVER_HPP__
