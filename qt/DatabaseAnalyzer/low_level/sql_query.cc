#include "low_level/sql_query.h"
#include <cassert>

#include "logger.h"

namespace {
  typedef enum Error {
    OK = 0,     /* Successful result */
    ERROR,      /* SQL error or missing database */
    INTERNAL,   /* Internal logic error in SQLite */
    PERM,       /* Access permission denied */
    ABORT,      /* Callback routine requested an abort */
    BUSY,       /* The database file is locked */
    LOCKED,     /* A table in the database is locked */
    NOMEM,      /* A malloc() failed */
    READONLY,   /* Attempt to write a readonly database */
    INTERRUPT,  /* Operation terminated by sqlite3_interrupt()*/
    IOERR,      /* Some kind of disk I/O error occurred */
    CORRUPT,    /* The database disk image is malformed */
    NOTFOUND,   /* Unknown opcode in sqlite3_file_control() */
    FULL,       /* Insertion failed because database is full */
    CANTOPEN,   /* Unable to open the database file */
    PROTOCOL,   /* Database lock protocol error */
    EMPTY,      /* Database is empty */
    SCHEMA,     /* The database schema changed */
    TOOBIG,     /* String or BLOB exceeds size limit */
    CONSTRAINT, /* Abort due to constraint violation */
    MISMATCH,   /* Data type mismatch */
    MISUSE,     /* Library used incorrectly */
    NOLFS,      /* Uses OS features not supported on host */
    AUTH,       /* Authorization denied */
    FORMAT,     /* Auxiliary database format error */
    RANGE,      /* 2nd parameter to sqlite3_bind out of range */
    NOTADB,     /* File opened that is not a database file */
    NOTICE,     /* Notifications from sqlite3_log() */
    WARNING,    /* Warnings from sqlite3_log() */
    ROW = 100,  /* sqlite3_step() has another row ready */
    DONE = 101  /* sqlite3_step() has finished executing */
  } Error;
}


SQLQuery::SQLQuery(DatabaseWrapper& wrapper)
    : wrapper_(wrapper), query_(""), statement_(NULL), error_(SQLITE_OK) {}

SQLQuery::~SQLQuery() {
  Finalize();
}

bool SQLQuery::Prepare(const std::string& query) {
  Finalize();
  if (statement_)
    return false;

  error_ = sqlite3_prepare(
      wrapper_.conn(), query.c_str(), query.length(), &statement_, NULL);
  query_ = query;
  return error_ == SQLITE_OK;
}

bool SQLQuery::Exec() {
  error_ = sqlite3_step(statement_);
  return error_ == SQLITE_ROW || error_ == SQLITE_DONE;
}

bool SQLQuery::Next() {
  error_ = sqlite3_step(statement_);
  return error_ == SQLITE_ROW;
}

bool SQLQuery::Reset() {
  error_ = sqlite3_reset(statement_);
  return error_ == SQLITE_OK;
}

void SQLQuery::Finalize() {
  error_ = sqlite3_finalize(statement_);
  if (error_ == SQLITE_OK) {

    statement_ = NULL;
  }
}

bool SQLQuery::Exec(const std::string& query) {
  query_ = query;
  error_ = sqlite3_exec(wrapper_.conn(), query.c_str(), NULL, NULL, NULL);
  return error_ == SQLITE_OK;
}

void SQLQuery::Bind(int pos, int value) {
  // In SQLite the number of position for binding starts since 1.
  error_ = sqlite3_bind_int(statement_, pos + 1, value);
}

void SQLQuery::Bind(int pos, int64_t value) {
  // In SQLite the number of position for binding starts since 1.
  error_ = sqlite3_bind_int64(statement_, pos + 1, value);
}

void SQLQuery::Bind(int pos, double value) {
  // In SQLite the number of position for binding starts since 1.
  error_ = sqlite3_bind_double(statement_, pos + 1, value);
}

void SQLQuery::Bind(int pos, bool value) {
  Bind(pos, static_cast<int>(value));
}

void SQLQuery::Bind(int pos, const std::string& value) {
  // In SQLite the number of position for binding starts since 1.
  error_ = sqlite3_bind_text(
      statement_, pos + 1, value.c_str(), value.length(), SQLITE_TRANSIENT);
}

bool SQLQuery::GetBoolean(int pos) const {
  return static_cast<bool>(GetInteger(pos));
}

int SQLQuery::GetInteger(int pos) const {
  return sqlite3_column_int(statement_, pos);
}

uint32_t SQLQuery::GetUInteger(int pos) const {
  return static_cast<uint32_t>(sqlite3_column_int64(statement_, pos));
}

int64_t SQLQuery::GetLongInt(int pos) const {
  return static_cast<int64_t>(sqlite3_column_int64(statement_, pos));
}

double SQLQuery::GetDouble(int pos) const {
  return sqlite3_column_double(statement_, pos);
}

std::string SQLQuery::GetString(int pos) const {
  const unsigned char* str = sqlite3_column_text(statement_, pos);
  return str ? reinterpret_cast<const char*>(str) : "";
}

const std::string& SQLQuery::query() const {
  return query_;
}

bool SQLQuery::IsNull(int pos) const {
  return sqlite3_column_type(statement_, pos) == SQLITE_NULL;
}

void SQLQuery::Bind(int pos) {
  // In SQLite the number of position for binding starts since 1.
  error_ = sqlite3_bind_null(statement_, pos + 1);
}

std::string SQLQuery::LastError() {
  return LastErrorText();
}

int64_t SQLQuery::LastInsertId() const {
  return sqlite3_last_insert_rowid(wrapper_.conn());
}

const std::string& SQLQuery::LastErrorText() {
  if (!error_text_.empty()) {
    return error_text_;
  }
  switch (error_) {
    case OK:
      error_text_ = "Successful result";
      break;
    case ERROR:
      error_text_ = "SQL error or missing database";
      break;
    case INTERNAL:
      error_text_ = "Internal logic error in SQLite";
      break;
    case PERM:
      error_text_ = "Access permission denied";
      break;
    case ABORT:
      error_text_ = "Callback routine requested an abort";
      break;
    case BUSY:
      error_text_ = "The database file is locked";
      break;
    case LOCKED:
      error_text_ = "A table in the database is locked";
      break;
    case NOMEM:
      error_text_ = "A malloc() failed";
      break;
    case READONLY:
      error_text_ = "Attempt to write a readonly database";
      break;
    case INTERRUPT:
      error_text_ = "Operation terminated by sqlite3_interrupt()";
      break;
    case IOERR:
      error_text_ = "Some kind of disk I/O error occurred";
      break;
    case CORRUPT:
      error_text_ = "The database disk image is malformed";
      break;
    case NOTFOUND:
      error_text_ = "Unknown opcode in sqlite3_file_control()";
      break;
    case FULL:
      error_text_ = "Insertion failed because database is full";
      break;
    case CANTOPEN:
      error_text_ = "Unable to open the database file";
      break;
    case PROTOCOL:
      error_text_ = "Database lock protocol error";
      break;
    case EMPTY:
      error_text_ = "Database is empty";
      break;
    case SCHEMA:
      error_text_ = "The database schema changed";
      break;
    case TOOBIG:
      error_text_ = "String or BLOB exceeds size limit";
      break;
    case CONSTRAINT:
      error_text_ = "Abort due to constraint violation";
      break;
    case MISMATCH:
      error_text_ = "Data type mismatch";
      break;
    case MISUSE:
      error_text_ = "Library used incorrectly";
      break;
    case NOLFS:
      error_text_ = "Uses OS features not supported on host";
      break;
    case AUTH:
      error_text_ = "Authorization denied";
      break;
    case FORMAT:
      error_text_ = "Auxiliary database format error";
      break;
    case RANGE:
      error_text_ = "2nd parameter to sqlite3_bind out of range";
      break;
    case NOTADB:
      error_text_ = "File opened that is not a database file";
      break;
    case NOTICE:
      error_text_ = "Notifications from sqlite3_log()";
      break;
    case WARNING:
      error_text_ = "Warnings from sqlite3_log()";
      break;
    case ROW:
      error_text_ = "sqlite3_step() has another row ready";
      break;
    case DONE:
      error_text_ = "sqlite3_step() has finished executing";
      break;
    default:
      error_text_ = "Unknown error";
  }
  return error_text_;
}

