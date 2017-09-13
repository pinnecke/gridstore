// Copyright (C) 2017 Marcus Pinnecke
//
// This program is free software: you can redistribute it and/or modify it under the terms of the
// GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
// warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program.
// If not, see <http://www.gnu.org/licenses/>.

#pragma once

// ---------------------------------------------------------------------------------------------------------------------
// C O N S T A N T S
// ---------------------------------------------------------------------------------------------------------------------

#define BADARG           "Illegal argument: '%s'"
#define BADCALL          "Illegal call: '%s'"
#define BADMALLOC        "Memory allocation failed: '%s'"
#define BADEXPR          "Bad expression evaluation: '%s'"
#define NOTIMPLEMENTED   "Not implemented: '%s'"
#define BADBRANCH        "Internal error: unknown condition during operation on object %p."
#define BADCAST          "Unsupported cast request for persistent ptr %p."
#define BADPOOLINIT      "Internal error: page pool %p is already initialized."
#define BADPAGEID        "Internal error: page id '%du' was not loaded into hot store. Maybe it does not exists."
#define BADARGNULL       "Illegal argument for function. Parameter '%s' points to null"
#define BADARGZERO       "Illegal argument for function. Parameter '%s' is zero"
#define UNEXPECTED       "Unexpected behavior: '%s'"
#define BADPAGESIZE      "Request to create a page size of %zuB with a hot store limit of %zuB is illegal"
#define BADSTATE         "Bad state: %s"
#define BADCOLDSTOREINIT "Memory allocation failed: unable to initialize cold store of buffer manager"
#define BADFREELISTINIT  "Memory allocation failed: unable to initialize page free list in buffer manager"
#define BADHOTSTOREOBJ   "Page with id '%du' is not located in hot store"
#define BADINTERNAL      "Internal error: %s"
#define BADBOUNDS        "Out of bounds access: %s"
#define BADTAG           "Casting error. Object is not instance of required type."
#define BADFRAGTYPE      "Unknown fragment type was requested: %d"
#define BADINT           "Argument must be a positive non-zero integer."