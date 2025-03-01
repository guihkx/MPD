/*
 * Copyright 2003-2021 The Music Player Daemon Project
 * http://www.musicpd.org
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef MPD_REQUEST_HXX
#define MPD_REQUEST_HXX

#include "protocol/ArgParser.hxx"
#include "protocol/RangeArg.hxx"
#include "Chrono.hxx"

#include <cassert>
#include <span>
#include <utility>

class Response;

class Request {
	std::span<const char *const> args;

public:
	explicit constexpr Request(const char *const*argv, std::size_t n)
		:args(argv, n) {}

	constexpr bool empty() const noexcept {
		return args.empty();
	}

	constexpr std::size_t size() const noexcept {
		return args.size();
	}

	constexpr const char *front() const noexcept {
		return args.front();
	}

	constexpr const char *back() const noexcept {
		return args.back();
	}

	constexpr const char *shift() noexcept {
		const char *value = args.front();
		args = args.subspan(1);
		return value;
	}

	constexpr const char *pop_back() noexcept {
		const char *value = args.back();
		args = args.first(args.size() - 1);
		return value;
	}

	constexpr const char *operator[](std::size_t i) const noexcept {
		return args[i];
	}

	constexpr auto begin() const noexcept {
		return args.begin();
	}

	constexpr auto end() const noexcept {
		return args.end();
	}

	constexpr operator std::span<const char *const>() const noexcept {
		return args;
	}

	constexpr const char *GetOptional(unsigned idx,
					  const char *default_value=nullptr) const {
		return idx < size()
			     ? args[idx]
			     : default_value;
	}

	int ParseInt(unsigned idx) const {
		assert(idx < size());
		return ParseCommandArgInt(args[idx]);
	}

	int ParseInt(unsigned idx, int min_value, int max_value) const {
		assert(idx < size());
		return ParseCommandArgInt(args[idx], min_value, max_value);
	}

	unsigned ParseUnsigned(unsigned idx) const {
		assert(idx < size());
		return ParseCommandArgUnsigned(args[idx]);
	}

	unsigned ParseUnsigned(unsigned idx, unsigned max_value) const {
		assert(idx < size());
		return ParseCommandArgUnsigned(args[idx], max_value);
	}

	bool ParseBool(unsigned idx) const {
		assert(idx < size());
		return ParseCommandArgBool(args[idx]);
	}

	RangeArg ParseRange(unsigned idx) const {
		assert(idx < size());
		return ParseCommandArgRange(args[idx]);
	}

	float ParseFloat(unsigned idx) const {
		assert(idx < size());
		return ParseCommandArgFloat(args[idx]);
	}

	SongTime ParseSongTime(unsigned idx) const {
		assert(idx < size());
		return ParseCommandArgSongTime(args[idx]);
	}

	SignedSongTime ParseSignedSongTime(unsigned idx) const {
		assert(idx < size());
		return ParseCommandArgSignedSongTime(args[idx]);
	}

	int ParseOptional(unsigned idx, int default_value) const {
		return idx < size()
			? ParseInt(idx)
			: default_value;
	}

	RangeArg ParseOptional(unsigned idx, RangeArg default_value) const {
		return idx < size()
			? ParseRange(idx)
			: default_value;
	}
};

#endif
