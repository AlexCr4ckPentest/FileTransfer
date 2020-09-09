#include <sockpp/tcp_connector.h>

#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#ifndef __FILE_SENDER_HPP__
#define __FILE_SENDER_HPP__

namespace file_sender
{
    inline void send_error_code(sockpp::tcp_connector& sock, const uint8_t code) noexcept
    { sock.write_n(&code, sizeof(code)); }

    void send_error_code_and_close_connection(sockpp::tcp_connector& sock, const uint8_t code) noexcept;

    inline bool check_file_type(const boost::filesystem::path& path) noexcept
    { return (boost::filesystem::status(path).type() == boost::filesystem::file_type::regular_file); }

    std::string read_file(std::FILE* file) noexcept;
    ssize_t send_filename(sockpp::tcp_connector& sock, const std::string& filename) noexcept;
    ssize_t send_file_data(sockpp::tcp_connector& sock, const std::string& file_data) noexcept;
} // namespace file_sender

#endif // __FILE_SENDER_HPP__