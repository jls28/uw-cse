/*
 * Copyright 2011 Steven Gribble
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

#include <iostream>
#include <algorithm>

#include "./QueryProcessor.h"

extern "C" {
#include "./libhw1/CSE333.h"
}

namespace hw3 {

QueryProcessor::QueryProcessor(list<string> indexlist, bool validate) {
  // Stash away a copy of the index list.
  indexlist_ = indexlist;
  arraylen_ = indexlist_.size();
  Verify333(arraylen_ > 0);

  // Create the arrays of DocTableReader*'s. and IndexTableReader*'s.
  dtr_array_ = new DocTableReader *[arraylen_];
  itr_array_ = new IndexTableReader *[arraylen_];

  // Populate the arrays with heap-allocated DocTableReader and
  // IndexTableReader object instances.
  list<string>::iterator idx_iterator = indexlist_.begin();
  for (HWSize_t i = 0; i < arraylen_; i++) {
    FileIndexReader fir(*idx_iterator, validate);
    dtr_array_[i] = new DocTableReader(fir.GetDocTableReader());
    itr_array_[i] = new IndexTableReader(fir.GetIndexTableReader());
    idx_iterator++;
  }
}

QueryProcessor::~QueryProcessor() {
  // Delete the heap-allocated DocTableReader and IndexTableReader
  // object instances.
  Verify333(dtr_array_ != nullptr);
  Verify333(itr_array_ != nullptr);
  for (HWSize_t i = 0; i < arraylen_; i++) {
    delete dtr_array_[i];
    delete itr_array_[i];
  }

  // Delete the arrays of DocTableReader*'s and IndexTableReader*'s.
  delete[] dtr_array_;
  delete[] itr_array_;
  dtr_array_ = nullptr;
  itr_array_ = nullptr;
}

vector<QueryProcessor::QueryResult> QueryProcessor::ProcessQuery(
    const vector<string> &query) {
  Verify333(query.size() > 0);
  vector<QueryProcessor::QueryResult> finalresult;

  // MISSING:
  // look up docids in index, count them
  vector<QueryResult> results;

  // just look at the first word in the query, then trim via rest
  for (unsigned int i = 0; i < arraylen_; i++) {
    DocIDTableReader *tempIdReader = itr_array_[i]->LookupWord(query[0]);
    // get list of elements from ids, and store
    if (tempIdReader != nullptr) {
      list<docid_element_header> temp = tempIdReader->GetDocIDList();
      while (!temp.empty()) {
        docid_element_header conv = temp.front();
        QueryResult result;
        dtr_array_[i]->LookupDocID(conv.docid, &result.document_name);
        result.rank = conv.num_positions;
        results.push_back(result);
        temp.pop_front();
      }
      delete tempIdReader;
    }
  }

  // for each query
  // call processquery
  // union the two vectors
  vector<string> subquery(query.begin() + 1, query.end());
  if (subquery.size() > 0) {
    vector<QueryResult> recursiveResult = ProcessQuery(subquery);
    for (auto a : results) {
      for (auto b : recursiveResult) {
        if (a.document_name.compare(b.document_name) == 0) {
          QueryResult polished = {a.document_name, a.rank + b.rank};
          finalresult.push_back(polished);
        }
      }
    }
  } else {
    finalresult = results;
  }

  // Sort the final results.
  std::sort(finalresult.begin(), finalresult.end());
  return finalresult;
}

}  // namespace hw3
