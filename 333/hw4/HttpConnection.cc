/*
 * Copyright 2012 Steven Gribble
 *
 *  This file is part of the UW CSE 333 course project sequence
 *  (333proj).
 *
 *  333proj is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  333proj is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with 333proj.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <map>
#include <string>
#include <vector>
#include <iostream>

#include "./HttpRequest.h"
#include "./HttpUtils.h"
#include "./HttpConnection.h"

using std::map;
using std::string;

namespace hw4 {

bool HttpConnection::GetNextRequest(HttpRequest *request) {
  // Use "WrappedRead" to read data into the buffer_
  // instance variable.  Keep reading data until either the
  // connection drops or you see a "\r\n\r\n" that demarcates
  // the end of the request header.
  //
  // Once you've seen the request header, use ParseRequest()
  // to parse the header into the *request argument.
  //
  // Very tricky part:  clients can send back-to-back requests
  // on the same socket.  So, you need to preserve everything
  // after the "\r\n\r\n" in buffer_ for the next time the
  // caller invokes GetNextRequest()!

  // MISSING:
  if (buffer_.length() == 0) {
    unsigned char buf[1024];
    while (true) {
      int amountRead = WrappedRead(fd_, buf, 1024);
      if (amountRead == -1) {
        // Error reading!
        return false;
      }
      if (amountRead < 1024) {
        buf[amountRead] = '\0';
        buffer_.append(reinterpret_cast<char *>(buf));
        break;
      }
      buffer_.append(reinterpret_cast<char *>(buf));
    }
  }
  // all done reading!

  // Need to find where the rnrn appears
  size_t endOfHeader = buffer_.find("\r\n\r\n");
  if (endOfHeader == std::string::npos) {
    return false;
  }
  // Parse the header
  // make a httprequest
  HttpRequest tempRequest = ParseRequest(endOfHeader);
  // deepcopy params
  request->URI = tempRequest.URI;
  std::map<std::string, std::string>::iterator reqIter;
  for (reqIter = tempRequest.headers.begin();
       reqIter != tempRequest.headers.end(); reqIter++) {
    request->headers[reqIter->first] = reqIter->second;
  }

  // delete everything before and including the \r\n\r\n in buffer_
  buffer_.erase(buffer_.begin(), buffer_.begin() + endOfHeader + 4);
  return true;
}

bool HttpConnection::WriteResponse(const HttpResponse &response) {
  std::string str = response.GenerateResponseString();
  int res = WrappedWrite(fd_, (unsigned char *)str.c_str(), str.length());
  if (res != static_cast<int>(str.length())) return false;
  return true;
}

HttpRequest HttpConnection::ParseRequest(size_t end) {
  HttpRequest req;
  req.URI = "/";  // by default, get "/".

  // Get the header.
  std::string str = buffer_.substr(0, end);

  // Split the header into lines.  Extract the URI from the first line
  // and store it in req.URI.  For each additional line beyond the
  // first, extract out the header name and value and store them in
  // req.headers (i.e., req.headers[headername] = headervalue).
  // You should look at HttpResponse.h for details about the HTTP header
  // format that you need to parse.
  //
  // You'll probably want to look up boost functions for (a) splitting
  // a string into lines on a "\r\n" delimiter, (b) trimming
  // whitespace from the end of a string, and (c) converting a string
  // to lowercase.

  // MISSING:

  std::vector<std::string> lines;
  boost::split(lines, str, boost::is_any_of("\r\n"));
  std::vector<std::string> containsURI;
  boost::split(containsURI, lines[0], boost::is_any_of(" "));
  if (containsURI.size() != 3) {
    // Malformed http header
    std::cerr << "ERROR: Malformed http header!" << std::endl;
  }
  req.URI = containsURI[1];
  for (unsigned int i = 1; i < lines.size(); i++) {
    // if it contains a colon,
    if (lines[i].find(":") == std::string::npos) {
      continue;
    }
    boost::algorithm::to_lower(lines[i]);
    std::vector<std::string> headerAndValue;
    // split on colon
    boost::split(headerAndValue, lines[i], boost::is_any_of(":"),
                 boost::token_compress_on);
    // pushback?? key.lower val.lower
    boost::algorithm::trim(headerAndValue[0]);
    boost::algorithm::trim(headerAndValue[1]);
    req.headers[headerAndValue[0]] = headerAndValue[1];
  }
  return req;
}

}  // namespace hw4
