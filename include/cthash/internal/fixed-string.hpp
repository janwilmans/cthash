#ifndef CTHASH_INTERNAL_FIXED_STRING_HPP
#define CTHASH_INTERNAL_FIXED_STRING_HPP

#include <span>
#include <string_view>

namespace cthash::internal {

template <typename CharT, size_t N> struct fixed_string {
	std::array<CharT, N> buffer;

	consteval static auto from_string_literal(const CharT (&in)[N + 1]) -> std::array<CharT, N> {
		std::array<CharT, N> out;
		std::copy_n(in, N, out.data());
		return out;
	}

	consteval fixed_string(const CharT (&in)[N + 1]) noexcept: buffer{from_string_literal(in)} { }

	consteval const CharT * data() const noexcept {
		return buffer.data();
	}

	consteval size_t size() const noexcept {
		return buffer.size();
	}

	consteval operator std::span<const CharT, N>() const noexcept {
		return std::span<const CharT, N>(buffer.data(), buffer.size());
	}

	consteval operator std::span<const CharT>() const noexcept {
		return std::span<const CharT>(buffer.data(), buffer.size());
	}

	consteval operator std::basic_string_view<CharT>() const noexcept {
		return std::basic_string_view<CharT>(buffer.data(), buffer.size());
	}
};

template <typename CharT, size_t N> fixed_string(const CharT (&)[N]) -> fixed_string<CharT, N - 1zu>;

} // namespace cthash::internal

#endif