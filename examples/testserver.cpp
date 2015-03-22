// This file is part of xsonrpc, an XML/JSON RPC library.
// Copyright (C) 2015 Erik Johansson <erik@ejohansson.se
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by the
// Free Software Foundation; either version 2.1 of the License, or (at your
// option) any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
// for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software Foundation,
// Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA

#include "server.h"

#include <numeric>
#include <poll.h>
#include <string>

int Add(int a, int b)
{
  return a + b;
}

int64_t AddArray(const xsonrpc::Value::Array& a)
{
  return std::accumulate(a.begin(), a.end(), int64_t(0),
                         [](const int64_t& a, const xsonrpc::Value& b)
                         { return a + b.AsInteger32(); });
};

std::string Concat(const std::string& a, const std::string& b)
{
  return a + b;
}

xsonrpc::Value::Struct ToStruct(const xsonrpc::Value::Array& a)
{
  xsonrpc::Value::Struct s;
  for (size_t i = 0; i < a.size(); ++i) {
    s[std::to_string(i)] = xsonrpc::Value(a[i]);
  }
  return s;
}

int main()
{
  xsonrpc::Server server(8080);

  auto& dispatcher = server.GetDispatcher();
  dispatcher.AddMethod("add", &Add);
  dispatcher.AddMethod("add_array", &AddArray);
  dispatcher.AddMethod("concat", &Concat);
  dispatcher.AddMethod("to_struct", &ToStruct);

  server.Run();

  pollfd fd;
  fd.fd = server.GetFileDescriptor();
  fd.events = POLLIN;

  while (poll(&fd, 1, -1) == 1) {
    server.OnReadableFileDescriptor();
  }

  return 0;
}