#include <fstream>

#include <sockpp/tcp_acceptor.h>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#ifndef __FILE_RECEIVER_HPP__
#define __FILE_RECEIVER_HPP__

namespace file_receiver
{
    size_t read_next_block_size(sockpp::tcp_socket& sock) noexcept;
    std::pair<std::string, size_t> receive_data_from_client(sockpp::tcp_socket& sock) noexcept;

    inline void write_data_to_file(const std::string& file_path, const std::string& data) noexcept
    { std::ofstream {file_path, std::ios::binary}.write(data.c_str(), data.size()); }
} // namespace file_receiver

#endif // __FILE_RECEIVER_HPP__
