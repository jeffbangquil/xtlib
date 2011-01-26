// Copyright (c) 2010 by OpenMFG LLC, d/b/a xTuple
/** \class xtClassCode
    \brief An object for working with a Class Code.

    Class Codes are used for Inventory control and provide a
    mechanism for categorizing Items regardless of Item Type.
 */

#include "xtClassCode.h"
#include "xtQuery.h"

#include <boost/lexical_cast.hpp>

#include <iostream>
#include <stdexcept>

//
// xtClassCode implementation
//

/**
    \brief Construct an empty \c xtClassCode.
 */
xtClassCode::xtClassCode()
  : xtAbstractCode()
{
  setTableName("classcode");
  setFieldPrefix("classcode_");
}

void xtClassCode::doDelete()
{
  std::string sql = "SELECT deleteClassCode(";
  sql += boost::lexical_cast<std::string>(getId());
  sql += ") AS result;";

  if(xtlib::debug)
    std::cerr << "executing: " << sql << std::endl;
  xtQuery query;
  query.exec(sql);
  if(query.rowCount() < 1)
    return;
  if(boost::lexical_cast<long long>(query.getValue(0, "result")) < 0)
  {
    throw std::runtime_error("Can not delete Class Code as one or more items reference it.");
  }
}
