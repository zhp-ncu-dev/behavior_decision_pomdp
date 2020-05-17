#include <despot/util/logging.h>
// #include <thread>

using namespace std;

namespace despot {

const string logging::markers_[] = { "None", "Error", "Warn", "Info", "Debug",
	"Verbose" };
const int logging::None = 0;
const int logging::Error = 1;
const int logging::Warn = 2;
const int logging::Info = 3;
const int logging::Debug = 4;
const int logging::Verbose = 5;

log_ostream::log_ostream(ostream& out, string marker) :
	ostream(&buffer_),
	buffer_(out, marker) {
}

log_ostream::log_buf::log_buf(ostream& out, string marker) :
	out_(out),
	marker_(marker) {
}

log_ostream::log_buf::~log_buf() {
	// pubsync();
}

streambuf* log_ostream::log_buf::setbuf(char* s, streamsize n) {
	return this;
}

int log_ostream::log_buf::sync() {
	//NOTE: disabled c++11 feature
	// out_ << marker_ << "-" << this_thread::get_id() << ": " << str();
	out_ << marker_ << ": " << str();
	str("");
	return !out_;
}

int logging::verbosity_ = Error;

void logging::level(int verbosity) {
	verbosity_ = verbosity;
}

int logging::level() {
	return verbosity_;
}

log_ostream& logging::stream(int level) {
	return *(streams_[level]);
}

void logging::stream(int level, ostream& out) {
	if (level >= Error && level <= Verbose) {
		streams_[level] = new log_ostream(out, markers_[level]);
	}
}

vector<log_ostream*> logging::InitializeLogStreams() {
	vector<log_ostream*> streams(6);

	streams[None] = NULL;
	streams[Error] = new log_ostream(cerr, markers_[Error]);
	streams[Warn] = new log_ostream(cerr, markers_[Warn]);
	streams[Info] = new log_ostream(cerr, markers_[Info]);
	streams[Debug] = new log_ostream(cerr, markers_[Debug]);
	streams[Verbose] = new log_ostream(cerr, markers_[Verbose]);

	return streams;
}

vector<log_ostream*> logging::streams_ = logging::InitializeLogStreams();

} // namespace despot
