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

#include <boost/algorithm/string.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <sstream>
#include <chrono>

#include "./FileReader.h"
#include "./HttpConnection.h"
#include "./HttpRequest.h"
#include "./HttpUtils.h"
#include "./HttpServer.h"
#include "./libhw3/QueryProcessor.h"

using std::cerr;
using std::cout;
using std::endl;

namespace hw4 {

// This is the function that threads are dispatched into
// in order to process new client connections.
void HttpServer_ThrFn(ThreadPool::Task *t);

// Given a request, produce a response.
HttpResponse ProcessRequest(const HttpRequest &req, const std::string &basedir,
                            const std::list<std::string> *indices);

// Process a file request.
HttpResponse ProcessFileRequest(const std::string &uri,
                                const std::string &basedir);

// Process a query request.
HttpResponse ProcessQueryRequest(const std::string &uri,
                                 const std::list<std::string> *indices);

bool HttpServer::Run(void) {
  // Create the server listening socket.
  int listen_fd;
  cout << "  creating and binding the listening socket..." << endl;
  if (!ss_.BindAndListen(AF_UNSPEC, &listen_fd)) {
    cerr << endl << "Couldn't bind to the listening socket." << endl;
    return false;
  }

  // Spin, accepting connections and dispatching them.  Use a
  // threadpool to dispatch connections into their own thread.
  cout << "  accepting connections..." << endl << endl;
  ThreadPool tp(kNumThreads);
  while (1) {
    HttpServerTask *hst = new HttpServerTask(HttpServer_ThrFn);
    hst->basedir = staticfile_dirpath_;
    hst->indices = &indices_;
    if (!ss_.Accept(&hst->client_fd, &hst->caddr, &hst->cport, &hst->cdns,
                    &hst->saddr, &hst->sdns)) {
      // The accept failed for some reason, so quit out of the server.
      // (Will happen when kill command is used to shut down the server.)
      break;
    }
    // The accept succeeded; dispatch it.
    tp.Dispatch(hst);
  }
  return true;
}

void HttpServer_ThrFn(ThreadPool::Task *t) {
  // Cast back our HttpServerTask structure with all of our new
  // client's information in it.
  std::unique_ptr<HttpServerTask> hst(static_cast<HttpServerTask *>(t));
  cout << "  client " << hst->cdns << ":" << hst->cport << " "
       << "(IP address " << hst->caddr << ")"
       << " connected." << endl;

  bool done = false;
  while (!done) {
    // Use the HttpConnection class to read in the next request from
    // this client, process it by invoking ProcessRequest(), and then
    // use the HttpConnection class to write the response.  If the
    // client sent a "Connection: close\r\n" header, then shut down
    // the connection.

    // MISSING:
    HttpConnection connection(hst->client_fd);
    HttpRequest request;
    bool getRequest = connection.GetNextRequest(&request);
    if (getRequest) {
      HttpResponse response =
          ProcessRequest(request, hst->basedir, hst->indices);
      connection.WriteResponse(response);
    }
    done = true;
  }
}

HttpResponse ProcessRequest(const HttpRequest &req, const std::string &basedir,
                            const std::list<std::string> *indices) {
  // Is the user asking for a static file?
  if (req.URI.substr(0, 8) == "/static/") {
    return ProcessFileRequest(req.URI, basedir);
  }

  // The user must be asking for a query.
  return ProcessQueryRequest(req.URI, indices);
}

HttpResponse ProcessFileRequest(const std::string &uri,
                                const std::string &basedir) {
  // The response we'll build up.
  HttpResponse ret;

  // Steps to follow:
  //  - use the URLParser class to figure out what filename
  //    the user is asking for.
  //
  //  - use the FileReader class to read the file into memory
  //
  //  - copy the file content into the ret.body
  //
  //  - depending on the file name suffix, set the response
  //    Content-type header as appropriate, e.g.,:
  //      --> for ".html" or ".htm", set to "text/html"
  //      --> for ".jpeg" or ".jpg", set to "image/jpeg"
  //      --> for ".png", set to "image/png"
  //      etc.
  //
  // be sure to set the response code, protocol, and message
  // in the HttpResponse as well.
  std::string fname = "";
  // MISSING:
  URLParser parser;
  parser.Parse(uri);
  fname = parser.get_path();
  fname = fname.substr(8);
  std::cerr << "Got a file request for: " << fname << std::endl;
  FileReader fReader(basedir, fname);
  std::string fileConents;
  bool fileWasRead = fReader.ReadFile(&fileConents);
  // Only want to render the file if it exists and isn't a directory
  if (fileWasRead && fileConents.size() != 0) {
    ret.body = fileConents;
    // Set content type header, protocol, response code
    ret.response_code = 200;
    ret.protocol = "HTTP/1.1";
    std::string filetype = fname.substr(fname.size() - 5);
    if (filetype.find("htm") != std::string::npos) {
      ret.headers["Content-type"] = "text/html";
    }
    if (filetype.find("jpeg") != std::string::npos ||
        filetype.find("jpg") != std::string::npos) {
      ret.headers["Content-type"] = "image/jpeg";
    }
    if (filetype.find("png") != std::string::npos) {
      ret.headers["Content-type"] = "image/png";
    }
    ret.message = "Ok";
    return ret;
  }

  // If you couldn't find the file, return an HTTP 404 error.
  ret.protocol = "HTTP/1.1";
  ret.response_code = 404;
  ret.message = "Not Found";
  ret.body = "<html><body>Couldn't find file \"";
  ret.body += EscapeHTML(fname);
  ret.body += "\"</body></html>";
  return ret;
}

HttpResponse ProcessQueryRequest(const std::string &uri,
                                 const std::list<std::string> *indices) {
  // The response we're building up.
  HttpResponse ret;

  // Your job here is to figure out how to present the user with
  // the same query interface as our solution_binaries/http333d server.
  // A couple of notes:
  //
  //  - no matter what, you need to present the 333gle logo and the
  //    search box/button
  //
  //  - if the user had previously typed in a search query, you also
  //    need to display the search results.
  //
  //  - you'll want to use the URLParser to parse the uri and extract
  //    search terms from a typed-in search query.  convert them
  //    to lower case.
  //
  //  - you'll want to create and use a hw3::QueryProcessor to process
  //    the query against the search indices
  //
  //  - in your generated search results, see if you can figure out
  //    how to hyperlink results to the file contents, like we did
  //    in our solution_binaries/http333d.

  // MISSING:
  // set up headers
  ret.protocol = "HTTP/1.1";
  ret.response_code = 200;
  ret.message = "Ok";
  ret.headers["Content-type"] = "text/html";
  // present the above the fold stuff
  ret.body =
      "<html>\n"
      "<head><title>333gle</title></head>\n"
      "<body>\n"
      "<center style=\"font-size:500%;\">\n"
      "<span "
      "style=\"position:relative;bottom:-0.33em;color:orange;\">3</span><span "
      "style=\"color:red;\">3</span><span style=\"color:gold;\">3</span><span "
      "style=\"color:blue;\">g</span><span "
      "style=\"color:green;\">l</span><span style=\"color:red;\">e</span>\n"
      "</center>\n"
      "<p>\n"
      "<div style=\"height:20px;\"></div>\n"
      "<center>\n"
      "<form action=\"/query\" method=\"get\">\n"
      "<input type=\"text\" size=30 name=\"terms\" />\n"
      "<input type=\"submit\" value=\"Search\" />\n"
      "</form>\n"
      "</center><p>\n";

  // Concatenation is ugly...

  // if queries exist, list in the specified format and the results
  URLParser parser;
  parser.Parse(uri);
  std::string termString = parser.get_args()["terms"];
  if (termString.length() != 0) {
    std::vector<std::string> terms;
    boost::split(terms, termString, boost::is_any_of(" "));
    std::cerr << "Had " << terms.size() << " terms: " << termString
              << std::endl;
    // get unique terms, don't need to double count
    std::vector<std::string> uniqueTerms;
    for (unsigned int i = 0; i < terms.size(); i++) {
      bool found = false;
      for (unsigned int j = 0; j < uniqueTerms.size(); j++) {
        if (uniqueTerms[j].compare(terms[i]) == 0) {
          found = true;
        }
      }
      if (!found) {
        // add it and lowercase it
        boost::algorithm::to_lower(terms[i]);
        uniqueTerms.push_back(terms[i]);
      }
    }
    // Time the query
    auto begin = std::chrono::high_resolution_clock::now();
    hw3::QueryProcessor queryProcessor(*indices, false);
    std::vector<hw3::QueryProcessor::QueryResult> results =
        queryProcessor.ProcessQuery(uniqueTerms);
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = end - begin;
    auto ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(dur).count();
    std::cerr << "Took " << ms << " milliseconds to query" << std::endl;

    // Build up the results list
    std::ostringstream title;
    title << "<p><br>\n" << results.size()
          << std::string(" results found for <b>") << EscapeHTML(termString)
          << "</b>\n"
          << "<ul>\n";
    ret.body += title.str();
    for (unsigned int i = 0; i < results.size(); i++) {
      std::ostringstream o;
      if (results[i].document_name.find("http://") == std::string::npos) {
        o << "<li><a href='/static/" << results[i].document_name;
      } else {
        o << "<li><a href='" << results[i].document_name;
      }
      o << "'>" << results[i].document_name << "</a> [" << results[i].rank
        << "]<br>\n";
      ret.body += o.str();
    }
    ret.body += "</ul>\n";
  }
  ret.body += "</body>\n</html>";
  // close html

  return ret;
}

}  // namespace hw4
